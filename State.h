#include <cstdlib>
#include <iostream>
#include <vector>
#include <tuple>

class Transition;

class State {
private:
	std::vector<Transition> transitions;

public:
	int data;
	bool accepting;

	State();
	State(int, bool);

	void addTransition(State, int);
	//void print();
	//void removeTransition(State, int);
	//bool hasEpsilonTransition(State);
	int getTransition(State);
	std::vector<Transition> getTransitions();
	//void eTransitionRemover();


	bool operator==(State);
	bool operator!=(State);
	bool operator<(const State);
};

class Transition {
private:
	int edgeLabel;
	State into;

public:
	std::vector<int> test;

	Transition();
	Transition(int, State&);
	Transition(const Transition& t);

	int getEdgeLabel();
	State getInto();

	bool operator==(Transition);
	bool operator!=(Transition);
	Transition operator=(const Transition&);
};