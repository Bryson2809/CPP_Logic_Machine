/***
 * @author James Carroll
 * @date 4/18/2022
 * @email jbc2@email.sc.edu
 * @description This file creates a graph, which is an adjacency list of States in an eNFA or NFA.  Included are many operations necessary for either converting an eNFA to
 * an NFA or checking a string against an NFA.
*/

#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <set>

using namespace std;

/***
 * Default constructor for graph
*/
Graph::Graph() {
	this->numStates = 0;
	this->alphabetSize = 0;
}

/// <summary>
/// Perameteried constructor for Graph, reads a text file of an eNFA or NFA ans sets the corresponding adjacency list
/// </summary>
/// <param name="fileName">The filename to be read</param>
Graph::Graph(string fileName) {
	this->transitionAlphabet = { '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	readFile(fileName);
}

/// <summary>
/// Add head of new node list to the adjacency list
/// </summary>
/// <param name="node">The new node being added to the list</param>
void Graph::addState(State state) {
	list<State> curr;
	curr.push_back(state);
	g.push_back(curr);
}

/// <summary>
/// Add an edge from one node to another
/// </summary>
/// <param name="src">the start node of the edge (the source node)</param>
/// <param name="dst">the destination node of the edge</param>
void Graph::addEdge(int src, int transition, int dst) {
	g[src].push_back(states[dst]);
	g[src].front().addTransition(g[src].back(), transition);
}

/// <summary>
/// Prints adjacency list, used for testing purposes
/// </summary>
void Graph::print() {
	for (list<State> curr : g) {
		for (State state : curr) {
			cout << state.data << " -> ";
		}
		cout << "\n";
	}
}

/// <summary>
/// Populate the adjacency list by reading the file containing eNFA or NFA
/// </summary>
/// <param name="fileName"></param>
void Graph::readFile(string fileName) {
	ifstream file;
	file.open(fileName);
	string line = "";
	int count = 0;
	int stateNum = 0;

	//Ensure file is open
	if (file.is_open()) {
		//Loop through entire file line by line
		while (file) {
			getline(file, line);
			//Get number of states
			if (count == 0) {
				string temp = line.substr(18);
				this->numStates = stoi(temp);
			}
			//Get alphabet sie
			else if (count == 1) {
				string temp = line.substr(15);
				this->alphabetSize = stoi(temp);
			}
			//Get list of accepting states
			else if (count == 2) {
				string temp = line.substr(18);
				int space = 0;
				while (true) {
					space = temp.find(' ');
					if (space != string::npos) {
						this->acceptingStates.insert(stoi(temp.substr(0, space)));
						temp = temp.substr(space+1);
					}
					else {
						this->acceptingStates.insert(stoi(temp));
						break;
					}
				}
				makeStates(numStates);
			}
			//Populate adjacency list from tabular form of eNFA/NFA
			else {
				string temp = line.substr(1);
				int space;
				int bracket;
				string temp2;
				int transition = 0;
				while (true) {
					space = temp.find(' ');
					bracket = temp.find('}');
					if (space != string::npos) {
						temp2 = temp.substr(0, bracket);
						parseBrackets(stateNum, temp2, transition);
						temp = temp.substr(space+2);
					}
					else {
						temp2 = temp.substr(0, bracket);
						parseBrackets(stateNum, temp2, transition);
						break;
					}
					transition++;
				}
				stateNum++;
				if (stateNum == numStates)
					break;
			}
			count++;
		}
	}
	file.close();
}

/// <summary>
/// Check to see if a certain node of the adjacency list is an accepting state, used to create the initial node list.
/// </summary>
/// <param name="stateData">the state to be checked</param>
/// <returns>true: is an accepting state; false: is not an accepting state</returns>
bool Graph::isAcceptingState(int stateData) {
	for (int state : acceptingStates) {
		if (state == stateData)
			return true;
	}
	return false;
}

/// <summary>
/// Make a list of all nodes so they do not have to be constructed and checked for acceptance multiple times, used as soon as the accepting states have been determined in readFile 
/// </summary>
/// <param name="numNodes">the number of nodes to create</param>
void Graph::makeStates(int numStates) {
	for (int i = 0; i < numStates; i++) {
		State state(i, isAcceptingState(i));
		this->states.push_back(state);
		this->addState(state);
	}
}

/// <summary>
/// get the data between {} in the tabular form and create edges using the data
/// </summary>
/// <param name="src">the source node that the edge will point from</param>
/// <param name="s">the string being parsed for data</param>
void Graph::parseBrackets(int src, string s, int transition) {
	if (s != "") {
		int comma = 0;
		string temp = s;
		while (true) {
			comma = temp.find(',');
			if (comma != string::npos) {
				//State state = this->states[stoi(temp)];
				addEdge(src, transition, stoi(temp));
				temp = temp.substr(comma + 1);
			}
			else {
				int bracket = temp.find('}');
				temp = temp.substr(0, bracket);
				//State state = this->states[stoi(temp)];
				addEdge(src, transition, stoi(temp));
				break;
			}
		}
	}
}

/// <summary>
/// loop through all States and the transitions out of them and remove the epsilon moves
/// </summary>
void Graph::popEpsilon() {
	for (list<State>& l : g) {
		for (State& s : l) {
			for (Transition t : s.getTransitions()) {
				//Check for epsilon transition
				if (t.getEdgeLabel() == 0) {
					int index = t.getInto().data;
					State& temp = g[index].front();
					//move accepting state to previous state
					if (t.getInto().accepting == true) {
						s.accepting = true;
						acceptingStates.insert(s.data);
					}
					//when state a has an epsilon transition to state b, and b has a transition to state c, add transition from state a to state c
					for (Transition transfer : temp.getTransitions()) {
						s.addTransition(transfer.getInto(), transfer.getEdgeLabel());
					}
				}
			}
		}
	}
}

/// <summary>
/// Print NFA to console
/// </summary>
void Graph::printNFA() {
	cout << "Number of states: " << this->numStates << endl;
	cout << "Alphabet size: " << this->alphabetSize << endl;
	cout << "Accepting states: ";
	for (int i : this->acceptingStates) {
		cout << i << " ";
	}
	cout << endl;
	for (list<State> l : g) {
		int count = 1;
		cout << "{}" << "\t";
		for (int i = 0; i < this->alphabetSize; i++) {
			cout << "{";
			int size = 0;
			string temp = "";
			for (Transition t : l.front().getTransitions()) {
				if (t.getEdgeLabel() == count) {
					temp += to_string(t.getInto().data) + ",";
				}
				size++;
			}
			count++;
			cout << temp.substr(0, temp.size() - 1);
			cout << "}" << "\t";
		}
		cout << endl;
	}
}

/// <summary>
/// Output accepts or rejects for a string based on the NFA currently stored as an adjacency list
/// <param name-"input"> The string to be simulated </param>
void Graph::simulate(string input) {
	vector<State> currStates = { g[0].front() };
	vector<State> temp;

	//loop through each character in the input string
	for (char index : input) {
		for (State s : currStates) {
			for (Transition t : s.getTransitions()) {
				int transition = t.getEdgeLabel();
				//Check if the transitions in the State are the same as the current character
				if (transitionAlphabet[transition] == index) {
					int i = t.getInto().data;
					State& state = g[i].front();
					temp.push_back(state);
				}
			}
		}
		currStates = temp;
	}
	bool passes = false;
	for (State s : currStates) {
		if (s.accepting == true) {
			passes = true;
		}
	}
	if (passes) {
		cout << "accepts" << endl;
	}
	else {
		cout << "rejects" << endl;
	}
}