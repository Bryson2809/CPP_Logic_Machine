#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include "State.h"
#include <set>

class Graph {
private:
	std::vector<std::list<State>> g;
	int numStates;
	int alphabetSize;
	std::set<int> acceptingStates;
	std::vector<State> states;
	std::vector<char> transitionAlphabet;
public:
	Graph();
	Graph(std::string);

	void addState(State);
	void addEdge(int, int, int);
	void print();
	void readFile(std::string);
	bool isAcceptingState(int);
	void makeStates(int);
	void parseBrackets(int, std::string, int);
	void popEpsilon();
	void printNFA();
	void simulate(std::string);
};