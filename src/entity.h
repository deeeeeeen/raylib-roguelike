#ifndef ENTITY_H
#define ENTITY_H
#include "mathlib.h"

#define MAX_ENTITIES 21

typedef struct entity_s {
    int8_t hp;
    int8_t atk;
    int8_t def;
    int hostile;
} entity_t;

#endif