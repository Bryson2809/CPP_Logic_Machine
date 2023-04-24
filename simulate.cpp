/***
 * @author James Carroll
 * @date 4/18/2022
 * @email jbc2@email.sc.edu
 * @description This file runs the necessary functions to simulate a string in an NFA
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Graph.h"

using namespace std;

// int main(int argc, char** argv) {
// 	Graph graph(argv[1]);

// }

int main(int argc, char *argv[]) {
	Graph graph(argv[1]);
	//graph.popEpsilon();
	//graph.printNFA();
	//graph.printConn();

	while (true) {
		string input;
		cin >> input;
		graph.simulate(input);
		cout << endl;
	}
	return 0;
}