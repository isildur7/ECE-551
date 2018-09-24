#include "election.h"
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  char population[15], electoral[15];
  size_t i, j, k;

  for (i = 0; line[i] != ':'; i++) {
    state.name[i] = line[i];
  }
  state.name[i] = '\0';

  for (j = 0; line[i] != ':'; j++) {
    population[j] = line[i];
  }
  population[j] = '\0';
  state.population = atoll(population);

  for (k = 0; line[i] != '\0'; k++) {
    electoral[k] = line[i];
  }
  electoral[k] = '\0';
  state.electoralVotes = atoi(electoral);

  return state;
}
unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
