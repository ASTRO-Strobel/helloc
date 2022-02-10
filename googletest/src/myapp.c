#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// This must be a power of 2!
#define BUFFER_SIZE 8
#define MAX_ITEMS (BUFFER_SIZE-1)
static int my_filter[BUFFER_SIZE];
static int readIdx = 0;
static int writeIdx = 0;

int filter_len(){ return (BUFFER_SIZE + writeIdx - readIdx) % BUFFER_SIZE; }

void filter_add(int val) {
    my_filter[writeIdx] = val;
    writeIdx = (writeIdx+1) & (BUFFER_SIZE-1);
    if(writeIdx == readIdx) readIdx = (readIdx+1) & (BUFFER_SIZE-1);
}

#ifndef TESTING
int myapp_do_dangerous_io()
{
    // we simulate the "dangerous io" here by returning a random value
    return rand() % 5;
}
#endif

int myapp_get_average(){
    int len = filter_len();
    if(0 == len) return 0;
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += my_filter[(i+readIdx)%BUFFER_SIZE];
    }
    return sum/len;
}

int myapp_task()
{
    // get value from register
    int nextval = myapp_do_dangerous_io();

    // add to filter line
    filter_add(nextval);

    // return the average value as the next delay
    return myapp_get_average();
}

void myapp_mainloop(int loops)
{
    for(int i=0; i<loops; i++){
        int nextloopdelay = myapp_task();
        printf("sleeping %d seconds...\n", nextloopdelay);
        sleep(nextloopdelay);
    }
}

int facul(int f) {
    if (f <= 0) return 1;
    
    int result = 1;
    for (int i = f; i > 1; i--)
        result *= i;
    
    return result;
}

#ifndef TESTING
int main() {
    // initialize random  generator
    srand( (unsigned int) time(NULL));
    int random = rand() % 4;

    int count = facul(random);
    printf("!!!Hello World!!!\n");
    myapp_mainloop(count);
}
#endif
