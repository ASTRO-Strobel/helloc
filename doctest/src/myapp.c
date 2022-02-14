#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"
#include "facul.h"


#ifndef TESTING
// this implementation is not wanted for the test, so the test build
// can avoid it by defining TESTING at the compiler commandline
int myapp_do_dangerous_io()
{
    // we simulate the "dangerous io" here by returning a random value
    return rand() % 5;
}
#else 
    // the forward declaration is needed for the test compilation run
    // (the test code replaces the implementation)
    int myapp_do_dangerous_io();
#endif

int myapp_task()
{
    // get value from register
    int nextval = myapp_do_dangerous_io();

    // add to filter line
    filter_add(nextval);

    // return the average value as the next delay
    return filter_get_average();
}

void myapp_mainloop(int loops)
{
    for(int i=0; i<loops; i++){
        int nextloopdelay = myapp_task();
        printf("sleeping %d seconds...\n", nextloopdelay);
        sleep(nextloopdelay);
    }
}

void myapp_run() {
    // initialize random  generator
    srand( (unsigned int) time(NULL));
    int random = rand() % 4;

    int count = facul(random);
    printf("Starting %d loops\n", count);
    myapp_mainloop(count);
}
