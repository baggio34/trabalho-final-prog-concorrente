#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "valhalla.h"
#include "config.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

void check_arguments() {
    if (config.horde_size < 0) {
        printf("Negative vikings is a new one.\nUnless you want vikings being unborn, please specify a horde size greater than 0!\n");
        exit(-1);
    }
    if (config.horde_size == 0) {
        printf("How can a horde have no vikings, did Chieftain get impeached?\nPlease specify a horde size greater than 0!\n");
        exit(-1);
    }
    if (config.max_eat_time < 0 || config.max_pray_time < 0) {
        printf("Do you want the vikings to break the rules of causality?\nIf not, then please make sure specified times are greater than 0!\n");
        exit(-1);
    }
    if (config.max_eat_time == 0) {
        printf("What, you want the vikings to choke on their food?\nI hope not, please specify a maximum eat time greater than 0!\n");
        exit(-1);
    }
    if (config.max_pray_time == 0) {
        printf("No god would be satisfied with a prayer done in less than a second!\nPlease set a maximum prayer time greater than 0\n");
        exit(-1);
    }
    if (config.table_size <= 0) {
        printf("No table, really? I guess no one's eating then!\nPlease specify a valid table size!\n");
        exit(-1);
    }
    if (config.table_size < 2) {
        printf("That table isn't even enough for one single viking.\nPlease specify a table size greater than 1!\n");
        exit(-1);
    }
}

int valhalla_lower_gods_prayer_count(valhalla_t* self) {
    int count = 0;
    for (int i = 0; i < ODIN; i++) {
        count += self->prayers[i];
    }
    return count;
}

int valhalla_max_prayers(valhalla_t* self, god_t god) {
    if (god == ODIN || god == THOR) return ceil(valhalla_lower_gods_prayer_count(self) * 1.1);

    int other_god_count = self->prayers[valhalla_get_rival(god)];
    return MAX(1, (int) ceil(other_god_count * 1.05));
}

prayer_options_t valhalla_prayer_options(valhalla_t* self) {
    prayer_options_t options;
    options.amount = 0;

    for (int god = 0; god < NUMBER_OF_GODS; god++) {
        int prayer_count = self->prayers[god];

        if (prayer_count < valhalla_max_prayers(self, god)) {
            options.gods[options.amount++] = god;
        }
    }

    return options;
}

void valhalla_init(valhalla_t *self) {
    plog("Checking given arguments\n");
    check_arguments();
    
    for (int i = 0; i < NUMBER_OF_GODS; i++) {
        self->prayers[i] = 0;
    }
    
    pthread_mutex_init(&self->mutex, NULL);
    sem_init(&self->semaphore, 0, 0);

    plog("[valhalla] Initialized\n");
}

void valhalla_finalize(valhalla_t *self) {
    pthread_mutex_destroy(&self->mutex);
    sem_destroy(&self->semaphore);
    
    plog("[valhalla] Finalized\n");
}

void valhalla_pray(valhalla_t *self, god_t god) {
    /* Realiza a prece por um tempo determinado (NÃO ALTERE!). */
    msleep(rand() % config.max_pray_time);
}

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo! */
/* --------------------------------------------------------- */

int valhalla_is_super(god_t god)
{
    return (god == ODIN || god == THOR);
}

int valhalla_is_rival(god_t god1, god_t god2)
{
    if ((god1 < ODIN && god2 < ODIN) && (god1 - god2 == 1 || god1 - god2 == -1)) return 1;
    return 0;
}

god_t valhalla_get_rival(god_t god)
{
    if (god == ODIN || god == THOR)
        return -1;
    
    if (god % 2 == 0)
        return god + 1;
    return god - 1;
}

char * valhalla_get_name(god_t god)
{
    switch (god) {
        case BALDR:
            return "BALDR";
            break;
        case LOKI:
            return "LOKI ";
            break;
        case VALI:
            return "VALI ";
            break;
        case HODER:
            return "HODER";
            break;
        case FRIGG:
            return "FRIGG";
            break;
        case JORD:
            return "JORD ";
            break;
        case ODIN:
            return "ODIN ";
            break;
        case THOR:
            return "THOR ";
            break;
        default:
            return "?";
    }
}

void valhalla_print(valhalla_t *self)
{
    int max = 0, total = 0, total_normal = 0;
    int max_allowed, min_allowed, error;

    printf("Prayers statistics:\n");

    for (int god = 0; god < NUMBER_OF_GODS; god++) {
        int count = self->prayers[god];
        total += count;
        if (!valhalla_is_super(god)) total_normal += count;
        if (count > max) max = count;
    }
    
    for (int god = 0; god < NUMBER_OF_GODS; god++) {
        int count = self->prayers[god];
        error = 0;
        if (!valhalla_is_super(god)) {
            int rival_count = self->prayers[valhalla_get_rival(god)];
            max_allowed = MAX(1, (int) ceil(rival_count * (1.0 + RIVAL_TOLERANCE_RATE)));
            min_allowed = (int) floor(rival_count * (1.0 - RIVAL_TOLERANCE_RATE));
            if (count < min_allowed)
                error = -1;
            else if (count > max_allowed)
                error = 1;
        }
        else 
            if (count > ceil(total_normal * (1.0 + SUPER_GOD_TOLERANCE_RATE)))
                error = 1;

        printf("%s |", valhalla_get_name(god));
        
        for (int i = 0; i < 50 * count/(double)max; i++)
            printf("#");
        
        printf(" %d ", count);

        if (error == 1)
            printf("[TOO MUCH]");
        else if (error == -1)
            printf("[TOO FEW]");
        
        printf("\n");
    }
    printf("Total: %d prayers!\n", total);
    plog(BAR);
    plog("\n");
}
