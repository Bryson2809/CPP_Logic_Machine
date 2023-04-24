# CSCE355 Final Coding Project

## Part 1: Convert an epsilon NFA to an NFA
### Run instructions:
  #### g++ Graph.cpp State.cpp EpsilonRemover.cpp -o e-remove
  #### ./a.out <file name containing tabular form of eNFA> 
  #### /*Check e-remove folder for tabular form tests given by the professor as well as the expected outcomes of the tests*/ 
  #### NFA will be printed into standard output 
  
 ## Part 2: Simulate checking a string to see if it is accepted by an NFA
 ### Run instructions: 
  #### g++ Graph.cpp State.cpp simulate.cpp -o simulate
  #### ./a.out <file name containing tabular for of NFA>
  #### /*Check e-remove folder for tabular forms of NFAs, these are the text files ending in output, and are the expected outcomes of the eNFAs from part 1.
  #### input strings into standard input and their acceptance will be printed through standard output
  #### terminate program with control/command c
