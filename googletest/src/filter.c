#include "filter.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int my_filter[BUFFER_SIZE];
int readIdx = 0;
int writeIdx = 0;


int filter_len() { 
    return (BUFFER_SIZE + writeIdx - readIdx) % BUFFER_SIZE;
}

void filter_add(int val) {
    my_filter[writeIdx] = val;
    writeIdx = (writeIdx+1) & (BUFFER_SIZE-1);
    if(writeIdx == readIdx) readIdx = (readIdx+1) & (BUFFER_SIZE-1);
}

int filter_get_average() {
    int len = filter_len();
    if(0 == len) return 0;
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += my_filter[(i+readIdx)%BUFFER_SIZE];
    }
    return sum/len;
}
