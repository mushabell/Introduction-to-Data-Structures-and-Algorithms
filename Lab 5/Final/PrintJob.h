# pragma once

using namespace std;

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  //declaration of functions for PrintJob class
  PrintJob ( int, int, int);
  int getPriority ( );   //returns priority value
  int getJobNumber ( );  //returns jobNumber value
  int getPages ( );      //returns numPages value

  //Rule of threes
  ~PrintJob(){};  //deconstructor
  PrintJob(const PrintJob&) = delete;  //copy constructor
  PrintJob& operator=(const PrintJob&) = delete;  //copy assignmnet operator
};