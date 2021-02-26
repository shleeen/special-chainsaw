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

const int GENERATIONS = 100;
const int POP_SIZE = 90;

const double RUN_DURATION = 300;
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



/***
 ***    HELPER FUNCTIONS
***/
// Generate random number in given range from a uniform distribution
float randomNumberUniform(float start, float end){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(start, end);
    return distr(eng);
}

// Generate random number from Gaussian distr
float randomNumberGaussian(float mean){
    float variance = 0.2;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<float> distr(mean, sqrt(variance));
    return distr(generator);
}

// find rank based on number of occurences of an element
// rank of 1 -> smallest element, rank of N -> largest element
// void findRank(float *array, float (&rank)[20]){  
void findRank(int size, float *array, float *rank){      
    for (int i = 0; i < size; i++) { 
        int r = 1, s = 1; 
          
        for (int j = 0; j < size; j++) { 
            if (j != i && array[j] < array[i]) 
                r += 1; 
                  
            if (j != i && array[j] == array[i]) 
                s += 1;      
        }
          
        rank[i] = r + (float)(s - 1) / (float) 2;
    } 
}


// a & b -> location of respective agent
bool checkAgentContact(float a, float b){
    // float a_low = a - 0.2;
    // float a_high = a + 0.2;

    // if b is in the range of a, return true
    if (abs(a-b) < 0.4){
        return true;
    }

    return false;
}

void contactAgent(Agent &agent1, Agent &agent2){
    // if they are in range of each other, then signal is 1
    if (checkAgentContact(agent1.getSelfPosition(), agent2.getSelfPosition())){ 
        agent1.updateContactSensor(1);
        agent2.updateContactSensor(1);
    }
    else {
        agent1.updateContactSensor(0);
        agent2.updateContactSensor(0);
    }
}

// West <---- (._.) ----> East
void moveAgent(Agent &agent){
    double output = agent.getOutput(0); //state of motor neuron
    float cur_location = agent.getSelfPosition();
    float new_location = cur_location; //just in case? lol
    if (output < 0.5){
        // move east
        new_location = abs(cur_location + DIST);
        // agent.updateSelfPosition(new_location);
    }
    else if (output >= 0.5){
        // move west
        new_location = abs(cur_location - DIST);
        // agent.updateSelfPosition(new_location);
    }
    else {
        // new_location = abs(cur_location - DIST);
        // cout<<"how did i get here "<<output<<endl;
    }
    agent.updateSelfPosition(new_location);
}
