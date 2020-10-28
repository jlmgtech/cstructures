#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./include/Map.h"

bool test0() {
    printf("should return the value that was set on key 'a': ");
    bool success;
    int value = 10;
    Map* map = MapCreate(1024);
    MapSet(map, "aaaa", (void*)&value);
    int *newval = (int*)MapGet(map, "aaaa");
    if (newval == NULL) {
        success = false;
    } else {
        success = value == *newval;
    }
    MapDestroy(map);
    return success;
}

bool test1() {
    printf("should return NULL when trying to access a key that hasn't been set: ");
    bool success;
    Map* map = MapCreate(1024);
    int value = 10;
    MapSet(map, "a", (void*)&value);
    int *newval = (int*)MapGet(map, "bbb");
    success = newval == NULL;
    MapDestroy(map);
    return success;
}

bool test2() {

    printf("should handle collisions: ");
    bool success;
    Map* map = MapCreate(1);
    int aval = 10;
    int bval = 11;
    MapSet(map, "jimmy", (void*)&aval);
    MapSet(map, "Bob brown Jr.", (void*)&bval);

    int* aval_2 = (int*)MapGet(map, "jimmy");
    int* bval_2 = (int*)MapGet(map, "Bob brown Jr.");

    success = *aval_2 == aval && *bval_2 == bval;
    MapDestroy(map);
    return success;
}

int main() {
    printf("\nrunning tests\n\n");

    if (test0()) {
        printf("PASS\n");
    } else {
        printf("FAIL\n\n");
        return 1;
    }

    if (test1()) {
        printf("PASS\n");
    } else {
        printf("FAIL\n\n");
        return 1;
    }


    if (test2()) {
        printf("PASS\n");
    } else {
        printf("FAIL\n\n");
        return 1;
    }

    printf("\n\nSUCCESS! all tests PASSED\n\n");
    return 0;
}
