#include "Agent.h"
#include "Plot.h"

#include <iostream>
#include <array>
#include <random>


using namespace std;


/*
 *  Global constants
 */
const int NEURONS = 3;
// const int GENES = (NEURONS+3)*NEURONS;

const int GENERATIONS = 10;
const int POP_SIZE = 10;

const double RUN_DURATION = 250;
const double TIMESTEP_SIZE = 0.1; // or 0.01
const float SPEED = 0.01; //"units per time unit"
const float DIST = SPEED/TIMESTEP_SIZE; // 0.01 is the biggest step/movement

/*
 *  Global variables
 */
Plot p;


/*
 * STRUCT for an Individual in population
 */
// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33
struct Individual{
    float genome[GENES]; //aka Chromosome, Genotype
    float fitness;
};


/*
 * Util Functions 
 */
float randomNumberUniform(float start, float end);
float randomNumberGaussian(float mean);
void findRank(int size, float *array, float *rank);


/*
 * GA functions 
 */
void init_population(Individual (&population)[POP_SIZE]);
bool checkAgentContact(float a, float b);
void contactAgent(Agent &agent1, Agent &agent2);
void moveAgent(Agent &agent);
float calcFitnessOverTrials(float fitness_list[20]);
void assessIndividual(Individual indv);
Individual selectParent(Individual population[POP_SIZE]); 
Individual mutateOffspring(Individual offspring);
void updatePopulation(Individual (&population)[POP_SIZE], Individual new_pop[POP_SIZE]);
