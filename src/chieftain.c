#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "chieftain.h"
#include "valhalla.h"

void table_init(table_t* self) {
    self->occupied_seatplates = 0;
    pthread_mutex_init(&self->mutex, NULL);
    for (int i = 0; i < config.table_size/2; i++) {
        self->seatplates[i] = EMPTY;
    }
}

void table_finalize(table_t* self) {
    pthread_mutex_destroy(&self->mutex);
    free(self);
}

void chieftain_init(chieftain_t *self, valhalla_t *valhalla)
{
    // Número de espaços disponíveis é metade do número de assentos arredondado para baixo
    self->table = (table_t*) malloc(sizeof(table_t) + sizeof(seatplates_t) * config.table_size/2); 
    self->valhalla = valhalla;
    plog("[chieftain] Initialized\n");
}

int chieftain_acquire_seat_plates(chieftain_t *self, int berserker)
{
    /* TODO: Implementar! */
    return 1;
}

void chieftain_release_seat_plates(chieftain_t *self, int pos)
{
    /* TODO: Implementar! */
}

god_t chieftain_get_god(chieftain_t *self)
{
    god_t god;
    
    return god;
}

void chieftain_finalize(chieftain_t *self)
{
    table_finalize(self->table);
    plog("[chieftain] Finalized\n");
}
