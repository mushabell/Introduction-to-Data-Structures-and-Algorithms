#include "PrintJob.h"

//constructor
PrintJob::PrintJob ( int setP, int setJ, int numP ):priority(setP), jobNumber(setJ), numPages(numP){}

//returns priority value
int PrintJob::getPriority ( ){
    return priority;
}

//returns jobNumber value
int PrintJob::getJobNumber ( ){
    return jobNumber;
}

//returns numPages value
int PrintJob::getPages ( ){
    return numPages;
}