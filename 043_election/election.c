#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  char population[15], electoral[15];
  size_t i, j;
  int zone = 0;
  for (i = 0; line[i] != '\0'; i++) {
    if (line[i] == ':')
      zone++;
  }

  if (zone != 2) {
    printf("Incorrect formatting of input! Enter data in following format:\n"
           "State:Population:Votes\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; line[i] != ':'; i++) {
    if (isalpha(line[i]) || isspace(line[i])) {
      state.name[i] = line[i];
    }
    else {
      printf("Nonalphabet entered as state name\n");
      exit(EXIT_FAILURE);
    }
  }
  state.name[i] = '\0';
  i++;

  for (j = 0; line[i] != ':'; j++) {
    if (isdigit(line[i])) {
      population[j] = line[i];
      i++;
    }
    else {
      printf("Non-numeric value entered for population\n");
      exit(EXIT_FAILURE);
    }
  }
  population[j] = '\0';
  i++;
  state.population = atoll(population);

  for (j = 0; line[i] != '\0'; j++) {
    if (isdigit(line[i])) {
      electoral[j] = line[i];
      i++;
    }
    else {
      printf("Non-numeric value entered for electoral votes\n");
      exit(EXIT_FAILURE);
    }
  }
  electoral[j] = '\0';
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
