
#include "../inc/processManager.h"

// create a time function that returns a pointer to a TIME struct
TIME* createTime(int hour, int minute, int second){
    TIME * time = (TIME *) malloc(sizeof(TIME));
    time->hour = hour;
    time->minute = minute;
    time->second = second;
    return time;
}
