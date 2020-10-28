#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/Map.h"

static size_t hashify(char* str) {
    size_t hash = 0;
    while (*str) {
        hash += *str;
        str++;
    }
    return hash;
}

void* MapGet(Map* this, char* key) {
    size_t index = hashify(key) % this->size;
    MapValue* bucket = this->buckets[index];
    while (bucket != NULL) {
        if (strncmp(key, bucket->key, 1024) == 0) {
            return bucket->value;
        } else {
            bucket = bucket->next;
        }
    }
    return NULL;
}

void MapSet(Map* this, char* key, void* value) {
    size_t index = hashify(key) % this->size;
    if (this->buckets[index] == NULL) {
        this->buckets[index] = MapValueCreate(key, value);
    } else {
        MapValue* bucket = this->buckets[index];
        while (bucket->next != NULL) {
          bucket = bucket->next;
        }
        bucket->next = MapValueCreate(key, value);
    }
}

Map* MapCreate(size_t size) {
    Map* this = malloc(sizeof(Map));
    this->buckets = calloc(size, sizeof(MapValue));
    this->size = size;
        return this;
}

void MapDestroy(Map* this) {
    for (int i = 0; i < this->size; i++) {
        if (this->buckets[i] != NULL) {
            MapValueDestroyList(this->buckets[i]);
        }
    }
    free(this->buckets);
    free(this);
}

MapValue* MapValueCreate(char* key, void* value) {
    MapValue* this = malloc(sizeof(MapValue));
    this->key = key;
    this->value = value;
    this->next = NULL;
    return this;
}

void MapValueDestroyList(MapValue* this) {
    if (this->next != NULL) {
        MapValueDestroyList(this->next);
    }
    free(this);
}
