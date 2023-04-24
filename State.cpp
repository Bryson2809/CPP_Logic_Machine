/***
 * @author James Carroll
 * @date 4/18/2022
 * @email jbc2@email.sc.edu
 * @description This file creates the State object which holds the data in the state (the state label), the accepting status of the state, and a vector of 
 * transitions out of the state
 * This file also has a class called Transitions, a transition contains the edge label (the alphabet symbol that causes the transition) and the state that the
 * transition goes into
*/

#include "State.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <tuple>

/// <summary>
/// Default constructor for State
/// </summary>
State::State() {
	this->data = -1;
	this->accepting = false;
}

/// <summary>
/// Parameterized constructor for State
/// </summary>
/// <param name="data"> the label of the State </param>
/// <param name="accepting"> bool for if the state is accepting or not </param>
State::State(int data, bool accepting) {
	this->data = data;
	this->accepting = accepting;
}

///<summary>
/// get list of transitions
/// </summary>
/// <return> vector of transitions </return>
std::vector<Transition> State::getTransitions() {
	return this->transitions;
}

/// <summary>
/// adds a new transition into the State
/// </summary>
/// <param name="destination"> the state it is going into </param>
/// <param name="transition" the alphabet character that causes the transition </param>
void State::addTransition(State destination, int transition) {
	Transition t(transition, destination);
	this->transitions.push_back(t);
}


// void State::removeTransition(State destination, int transition) {
// 	Transition t(transition, destination);
// 	for (int i = 0; i < this->transitions.size(); i++) {
// 		if (this->transitions[i] == t)
// 			this->transitions.erase(this->transitions.begin() + i);
// 	}
// }

// void State::print() {
// 	for (Transition t : this->transitions) {
// 		if (t.getEdgeLabel() != 0)
// 			std::cout << this->data << " connects to " << t.getInto().data << " by a " << t.getEdgeLabel() << " transition " << std::endl;
// 	}
// }

// void State::eTransitionRemover() {
// 	for (Transition t : this->transitions) {
// 		if (t.getEdgeLabel() == 0) {
// 			std::cout << "will not print to console" << std::endl;
// 		}
// 	}
// }

/// <summary>
/// overload == operator
/// </summary>
/// <param name="s"> state equality is being checked against </param>
/// <return> true: states are equal; false: states are not equal </return>
bool State::operator==(State s) {
	return s.data == this->data && s.accepting == this->accepting;
}

/// <summary>
/// overload != operator
/// </summary>
/// <param name="s"> State equality is being checked against
/// <return> true: states are not equal; false: states are equal </return>
bool State::operator!=(State s) {
	return s.data != this->data || s.accepting != this->accepting;
}

/// <summary>
/// Default constructor for transition
/// </summary>
Transition::Transition() {
	this->edgeLabel = -1;
	State state;
	this->into = state;
}

/// <summary>
/// Parameterized constructor for Transition
/// </summary>
/// <param name="edgeLabel"> int value to access the index of the alphabet labels that cause the transition </param>
/// <param name="into"> State that the transition goes into </param>
Transition::Transition(int edgeLabel, State& into) {
	this->edgeLabel = edgeLabel;
	this->into = into;
}

/// <summary>
/// copy constructor for Transition
/// <param name="copy"> Transition being copied </param>
Transition::Transition(const Transition& copy) {
	this->edgeLabel = copy.edgeLabel;
	this->into = copy.into;
}

/// <summary>
/// get the edge label of the transition
/// </summary>
/// <return> edge label </return>
int Transition::getEdgeLabel() {
	return this->edgeLabel;
}

/// <summary>
/// get the state the Transition goes into
/// </summary>
/// <return> into </return>
State Transition::getInto() {
	return this->into;
}

/// <summary>
/// overload == operator
/// </summary>
/// <param name="t"> Transition equality is being checked against </param>
/// <return> true: Transitions are equal; false: transitions are not equal </return>
bool Transition::operator==(Transition t) {
	return this->edgeLabel == t.getEdgeLabel() && this->into == t.getInto();
}

/// <summary>
/// overload != operator
/// </summary>
/// <param name="t"> Transition inequality is being checked against </param>
/// <return> true: Transitions are not equal; false: Transitions are equal
bool Transition::operator!=(Transition t) {
	return this->edgeLabel != t.getEdgeLabel() || this->into != t.getInto();
}

/// <summary>
/// overload = operator
/// </summary>
/// <param name="t"> Transition it is being set to </param>
/// <return> Copy of t </return>
Transition Transition::operator=(const Transition& t) {
	Transition tran(t);
	return tran;
}