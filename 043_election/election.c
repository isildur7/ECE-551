#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  char population[20], electoral[10];
  size_t i, j;
  int zone = 0;

  // Check if there are exzctly two zone separators ':'
  // Otherwise throw error and exit the program
  for (i = 0; line[i] != '\0'; i++) {
    if (line[i] == ':')
      zone++;
  }
  if (zone != 2) {
    printf("Incorrect formatting of input! Enter data in following format:\n"
           "State:Population:Votes\n");
    exit(EXIT_FAILURE);
  }
  // Name is in the first zone, so iterate till you reach the first
  // zone separator. For every character check if it is an alphabet
  // or space. If not, throw error and exit. Copy the valid charac-
  // ters as state name. Add terminator at the end.
  for (i = 0; line[i] != ':'; i++) {
    if (i == MAX_STATE_NAME_LENGTH) {
      printf("input too long\n");
      exit(EXIT_FAILURE);
    }

    if (line[i] != '\0') {
      state.name[i] = line[i];
    }
    else {
      printf("Abrupt end of input\n");
      exit(EXIT_FAILURE);
    }
  }
  state.name[i] = '\0';
  i++;

  // Iterate till second separator for population. Check if all characters
  // are numbers. If not throw error and exit. copy the valid characters to
  // population and set state population by converting it to long long int.
  for (j = 0; line[i] != ':'; j++) {
    if (j == 20) {
      printf("input too long\n");
      exit(EXIT_FAILURE);
    }

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

  // Iterate till Null terminator for electoral votes. Check if all chara-
  // cters are numbers. If not throw error and exit. copy the valid chara-
  // cters to population and set state population by converting it to int.
  for (j = 0; line[i] != '\0'; j++) {
    if (j == 10) {
      printf("input too long\n");
      exit(EXIT_FAILURE);
    }

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
  // So, if a candidate wins more than half the vote count  he wins all the
  // electoral votes. Or if the population is less than double of vote count
  // he wins all the electoral votes. So, loop over all the states, snd find
  // where candidate wins all electoral votes and add that to his total.
  unsigned int total_electoral_votes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (stateData[i].population < voteCounts[i]) {
      printf("Voting more than Population. Look for them Russkies\n");
      exit(EXIT_FAILURE);
    }
    if (stateData[i].population / voteCounts[i] < 2) {
      total_electoral_votes += stateData[i].electoralVotes;
    }
  }
  return total_electoral_votes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  // calculate percentage fraction by typecasting, test for +/- 0.5% condition
  // and print if true.
  for (size_t i = 0; i < nStates; i++) {
    float percentage = (float)voteCounts[i] / (float)stateData[i].population;
    if (percentage > 1) {
      printf("Voting more than Population. Look for them Russkies\n");
      exit(EXIT_FAILURE);
    }
    if ((percentage - 0.5 <= 0.005) && (percentage - 0.5 >= -0.005)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100);
    }
  }
  return;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  // Iterate over the arrays, store a value for the highest yet and its index
  // print at the end
  float high = 0;
  size_t whereHigh = 0;
  for (size_t i = 0; i < nStates; i++) {
    float percentage = (float)voteCounts[i] / (float)stateData[i].population;
    if (percentage > 1) {
      printf("Voting more than Population. Look for them Russkies\n");
      exit(EXIT_FAILURE);
    }
    if (percentage > high) {
      high = percentage;
      whereHigh = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[whereHigh].name, high * 100);
  return;
}
