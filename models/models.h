#ifndef MODELS_PARAM
#define MODELS_PARAM 1

#include<stdio.h>

struct Patient {
    char *name;
    int day, year;
    char *month;

    struct Patient *next;
    struct Patient *prev;
};

#endif