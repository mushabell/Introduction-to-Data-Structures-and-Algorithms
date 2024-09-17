#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;
using std::cout;
using std::endl;
using std::stoi;

//define infinity so we can use it throughout the code
const int infinity = std::numeric_limits<int>::max();

struct State {
  int a; //amount in jug A
  int b; //amount in jug B

  //where to go on each of the six actions
  int fillA;
  int fillB;
  int emptyA;
  int emptyB;
  int AtoB;
  int BtoA;

  //these fields are useful when we do Dijkstra's method
  string connection = "no connection"; //realtion to the previous and current node
  int previous; //position of previous node
  int distance; //cost of traveling to current node
  bool visited; //marker if the node was visted

  //constructor for a possible state the jugs can be in
  State(int a=infinity,
	int b=infinity,
	int fillA=infinity,
	int fillB=infinity,
	int emptyA=infinity,
	int emptyB=infinity,
	int AtoB=infinity,
	int BtoA=infinity)
    : a(a),
      b(b),
      fillA(fillA),
      fillB(fillB),
      emptyA(emptyA),
      emptyB(emptyB),
      AtoB(AtoB),
      BtoA(BtoA),
      previous(infinity),
      distance(infinity),
      visited(false)
  {
  }
};

class Jug {
  int Ca; //capaciy of jug A
  int Cb; //capacity of jug B
  int n; //goal for jug B
  int a; //amount of water in A
  int b; //amount of water in B
  bool validInputs = true; //checks if the inputs given are valid
  std::vector<State> states;
  public:
    //constructor for one Jug problem
    //no decontructor needed because keyword new is not used
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), n(N)
    {
      make_map(Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA);
    };
    

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);
      
  private:
    //creates the map in the array and calls on find_path()
    void make_map(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);

    //returns the position of the jugs in the array
    int state_number(int a, int b, int Ca, int Cb);

    //maps out all the paths from two empty jugs to all the possible senarios
    //including mapping the jugs back to themselves
    void find_path(int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
};