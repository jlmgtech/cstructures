#ifndef map_h
#define map_h

#define MAP_SIZE 1024;

typedef struct MapValue {
    char* key;
    void* value;
    struct MapValue* next;
} MapValue;
MapValue* MapValueCreate(char* key, void* value);
void MapValueDestroyList(MapValue* this);


// ---------------------------- //

typedef struct Map {
    MapValue** buckets;
    size_t size;
} Map;
Map* MapCreate(size_t size);
void MapDestroy(Map* this);
void* MapGet(Map* this, char* key);
void MapSet(Map* this, char* key, void* value);

#endif
