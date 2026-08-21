#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "config.h"
#include "chieftain.h"
#include "valhalla.h"

void table_init(table_t* self) {
    self->occupied_seatplates = 0;
    sem_init(&self->semaphore, 0, config.table_size/2);
    pthread_mutex_init(&self->mutex, NULL);
    for (int i = 0; i < config.table_size/2; i++) {
        self->seatplates[i] = EMPTY;
    }
}

void table_finalize(table_t* self) {
    sem_destroy(&self->semaphore);
    pthread_mutex_destroy(&self->mutex);
    free(self);
}

void chieftain_init(chieftain_t *self, valhalla_t *valhalla) {
    // Número de espaços disponíveis é metade do número de assentos arredondado para baixo
    self->table = (table_t*) malloc(sizeof(table_t) + sizeof(seatplates_t) * config.table_size/2); 
    table_init(self->table);

    self->valhalla = valhalla;
    plog("[chieftain] Initialized\n");
}

int chieftain_acquire_seat_plates(chieftain_t *self, int berserker) {
    sem_wait(&self->table->semaphore);
    pthread_mutex_lock(&self->table->mutex);

    self->table->occupied_seatplates++;
    
    int i = 0;
    for (; i < config.table_size/2; i++) {
        if (self->table->seatplates[i] == EMPTY) {
            self->table->seatplates[i] = TAKEN;
            break;
        }
    }

    pthread_mutex_unlock(&self->table->mutex);
    return i*2;
}

void chieftain_release_seat_plates(chieftain_t *self, int pos) {
    table_t* table = self->table;

    pthread_mutex_lock(&table->mutex);

    table->seatplates[pos/2] = EMPTY;
    table->occupied_seatplates--;

    if (table->occupied_seatplates == 0) {
        for (int i = 0; i < config.horde_size*2; i++) {
            sem_post(&self->valhalla->semaphore);
        }
    }   
    
    pthread_mutex_unlock(&table->mutex);
    sem_post(&table->semaphore);
}

god_t chieftain_get_god(chieftain_t *self) {
    sem_wait(&self->valhalla->semaphore); // semaforo de espera para iniciar a reza braba
    pthread_mutex_lock(&self->valhalla->mutex);
   
    prayer_options_t options = valhalla_prayer_options(self->valhalla);
    int random_index = rand() % options.amount;
    god_t god = options.gods[random_index];

    self->valhalla->prayers[god]++;
    
    pthread_mutex_unlock(&self->valhalla->mutex);
    return god;
}

void chieftain_finalize(chieftain_t *self) {
    table_finalize(self->table);
    plog("[chieftain] Finalized\n");
}
