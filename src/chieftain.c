#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "chieftain.h"
#include "valhalla.h"

void table_init(table_t* self) {
    self->occupied_chairs = 0;
    pthread_mutex_init(&self->mutex, NULL);
    for (int i = 0; i < config.table_size; i++) {
        self->chairs[i] = EMPTY;
    }
}

void table_finalize(table_t* self) {
    pthread_mutex_destroy(&self->mutex);
    free(self);
}

void chieftain_init(chieftain_t *self, valhalla_t *valhalla)
{
    self->table = (table_t*) malloc(sizeof(table_t) + sizeof(chair_t) * config.table_size); 
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
    /* TODO: Implementar! O código abaixo deve ser modificado! */
    god_t god = THOR;
    
    return god;
}

void chieftain_finalize(chieftain_t *self)
{
    table_finalize(self->table);
    plog("[chieftain] Finalized\n");
}
