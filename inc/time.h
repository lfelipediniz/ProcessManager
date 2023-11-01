#ifndef TIME_H
#define TIME_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct time_ TIME;

TIME* createTime(int hour, int minute, int second);
int compareTime(TIME* time1, TIME* time2);
void printTime(TIME* time);
bool changeInfo(TIME* old, TIME* new);
void freeTime(TIME** time);

#endif