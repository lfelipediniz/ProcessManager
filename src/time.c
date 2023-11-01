#include "time.h"

struct time_{
   int hh;
   int mm;
   int ss;
};

// create a time function that returns a pointer to a TIME struct
TIME* createTime(int hour, int minute, int second) {
    TIME* time = (TIME*)malloc(sizeof(TIME));

    if(time != NULL) {
        time->hh = hour;
        time->mm = minute;
        time->ss = second;
    }
    return time;
}

// compare two times
int compareTime(TIME* time1, TIME* time2) {
    if((time1 != NULL) && (time2 != NULL)) {
        // -1 time1 < time2
        // 1 time1 > time2
        if (time1->hh < time2->hh) return -1;
        if (time1->hh > time2->hh) return 1;
        if (time1->mm < time2->mm) return -1;
        if (time1->mm > time2->mm) return 1;
        if (time1->ss < time2->ss) return -1;
        if (time1->ss > time2->ss) return 1;
        return 0;  // if time1 == time2
    }
}

// print all the elements of a pointer to a TIME struct
void printTime(TIME* time) {
    if(time != NULL)
        printf("%02d:%02d:%02d", time->hh, time->mm, time->ss);
}

// change the time's info to a new one
bool changeInfo(TIME* old, TIME* new) {
    if((old != NULL) && (new != NULL)) {
        old->hh = new->hh;
        old->mm = new->mm;
        old->ss = new->ss;
        return true;
    }
    return false;
}

// free the memory allocated to time
void freeTime(TIME** time) {
    if((*time) != NULL) {
        free(*time);
        *time = NULL;
    }
}