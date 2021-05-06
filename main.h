#include "Agent.h"

#include <iostream>
#include <array>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;


/*
 *  Global constants
 */
const int NEURONS = 3;
// const int GENES = (NEURONS+3)*NEURONS;

const int GENERATIONS = 5000;
const int POP_SIZE = 50;
const float MAX_EXP_OFFSPRING = 1.1;
const float MUTATION_VARIANCE = 0.2;
const int MIN_GEN_DECODE = 0.1*GENERATIONS;

const double RUN_DURATION = 300;
const double TIMESTEP_SIZE = 0.1; // or 0.01


/*
 * STRUCT for an Individual in population
 */
// chromosome = tau1 | bias1 | weight11 | weight12 | weight13 |
//              tau2 | bias2 | weight21 | weight22 | weight23 | 
//              tau3 | bias3 | weight31 | weight32 | weight33 |
//              contact_weight | self-pos_weight | target_weight 
struct Individual{
    float genome[GENES]; //aka Chromosome, Genotype
    float fitness;
};


/*
 * Util Functions 
 */
float randomNumberUniform(float start, float end);
float randomNumberGaussian(float mean, float variance);
void findRankAscending(int size, float *array, float *rank);
void findRankDescending(int size, float *array, float *rank);


/*
 * GA functions 
 */
void initPopulation(Individual (&population)[POP_SIZE]);
bool checkAgentContact(float a, float b);
void contactAgent(Agent &agent1, Agent &agent2);
void moveAgent(Agent &agent);
float calcFitnessOverTrials(float fitness_list[20]);
float assessIndividual(Individual indv, Agent &sender, Agent &receiver, int cur_gen);
void selectParent(Individual population[POP_SIZE], int (&parent_index)[POP_SIZE]); 
Individual mutateOffspring(Individual offspring);
void beerMutation(Individual &offspring);
void updatePopulation(Individual (&population)[POP_SIZE], Individual new_pop[POP_SIZE]);



/***
 ***    HELPER FUNCTIONS
***/
// Sigmoid function
float sigmoid(float x){
    return 1/(1 + exp(-x));
}

// Generate random number in given range from a uniform distribution
float randomNumberUniform(float start, float end){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(start, end);
    return distr(eng);
}

// Generate random number from Gaussian distr
float randomNumberGaussian(float mean, float variance){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<float> distr(mean, sqrt(variance));
    return distr(generator);
}

// rank of 1 -> smallest element, rank of N -> largest element
void findRankAscending(int size, float *array, float *rank){      
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

// rank of 1 -> largest element, rank of N -> smallest element
void findRankDescending(int size, float *array, float *rank){      
    for (int i = 0; i < size; i++) { 
        int r = 1, s = 1; 
          
        for (int j = 0; j < size; j++) { 
            if (j != i && array[j] > array[i]) 
                r += 1; 
                  
            if (j != i && array[j] == array[i]) 
                s += 1;      
        }
          
        rank[i] = r + (float)(s - 1) / (float) 2;
    } 
}


// copies contents of struct 'old' to struct 'new' 
void copyIndividual(Individual oldIndv, Individual &newIndv){
    newIndv.fitness = oldIndv.fitness;
    for (int i=0; i<GENES; ++i){
        newIndv.genome[i] = oldIndv.genome[i];
    }
}


// calc avg for each gene in a genome, across all individuals in the population
void averageGenomeInPop(Individual &avg, Individual population[POP_SIZE]){
    for(int i=0; i<GENES; i++){
        float sum=0.0;
        for(int j=0; j<POP_SIZE; j++){
            sum += population[j].genome[i];
        }
        avg.genome[i] = (sum/POP_SIZE);
    }
}

/*
// a & b -> location of respective agent
bool checkAgentContact(float a, float b){
    // float a_low = a - 0.2;
    // float a_high = a + 0.2;

    // if b is in the range of a, return true
    // if distance between a and b is less than 0.4, then in range
    if (abs(a-b) < 0.4){
        return true;
    }

    return false;
}*/


// a & b -> location of respective agent
void contactAgent(Agent &agent1, Agent &agent2){
    float a = agent1.getSelfPosition();
    float b = agent2.getSelfPosition();

    // if they are in range of each other, then signal is 1
    // if distance between a and b is less than 0.4, then in range
    if (abs(a-b) < 0.4){ 
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
    double output = agent.getOutput(1);
    float cur_location = agent.getSelfPosition();

    // --- old step calulation
    // float weight = agent.getMotorWeight();
    // float step = (sigma(weight*output) - 0.5) * 0.2; // rescales to range -0.1, 0.1

    // rescales to range [-0.1*stepize, 0.1*stepSize]
    // float step = (sigma(output) - 0.5) * TIMESTEP_SIZE * 0.2;
    float step = (2*(output - 0.5)) * TIMESTEP_SIZE * 0.1;
    // float step = (2 * (output - 0.5)) * TIMESTEP_SIZE * 0.01;

    // if step is negative, it moves west
    //                else, moves east
    agent.updateSelfPosition(cur_location + step);
}
