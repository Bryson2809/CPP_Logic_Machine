/***
 * @author James Carroll
 * @date 4/18/2022
 * @email jbc2@email.sc.edu
 * @description This file calls the necessary functions to convert an epsilon NFA to a regular NFA
*/

#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	Graph graph(argv[1]);
	graph.popEpsilon();
	graph.printNFA();

	return 0;
}