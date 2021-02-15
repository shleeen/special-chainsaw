// ***************************************
// trying to do the thing for project
// ***************************************

#include "CTRNN.h"
#include "Agent.h"
#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;


// -- Global constants
const int NEURONS = 3;
// const int GENES = (NEURONS+3)*NEURONS;

const int GENERATIONS = 100;
const int POP_SIZE = 10;

const double RUN_DURATION = 250; //what unit is this?
const double TIMESTEP_SIZE = 0.1; // 0.01
const float SPEED = 0.01; //"units per time unit"
const float DIST = SPEED/TIMESTEP_SIZE; // 0.01 is the biggest step/movement


// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33
struct Individual{
    float genome[GENES]; //aka Chromosome, Genotype
    float fitness;
};


/***
 * 
 * GA FUNCTIONS
 * 
***/
void init_population(Individual (&population)[POP_SIZE]){
    srand((unsigned int)time(NULL));
    // TODO: range
    // seed
    // number b/w 0 and 1

    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            population[i].genome[j] = float(rand());
        }
        population[i].fitness = 0;
    }
    cout<<"created population :)"<<endl;
}


bool checkAgentContact(float a, float b){
    float a_sensor_range = a + 0.2;
    float b_location = b;
    // if (b < a_sensor_range && ){

    // }
    // else{

    // }
    // return true;
}


// West <---- (._.) ----> East
float moveAgent(Agent &agent){
    double state = agent.getState(1); //state of motor neuron
    float cur_location = agent.getSelfPosition();
    if (state < 0.5){
        // move east
        float new_location = abs(cur_location + DIST);
        agent.updateSelfPosition(new_location);
    }
    else if (state >= 0.5){
        // move west
        float new_location = abs(cur_location - DIST);
        agent.updateSelfPosition(new_location);
    }
}


float assesIndividual(float individual[18]){
    Agent bee1(NEURONS, GENES); //sender
    Agent bee2(NEURONS, GENES); //receiver
    bee2.updateTargetSensor(-1); //target sensor value for receiver is fixed

    int trials = 0;
    while (trials < 20){
        // draw target
        float target = (float)(rand()) / ((float)(RAND_MAX/(0.5 - 1)));
        // cout<<"!!!!! "<< target <<endl;

        // draw the pos of bees from a uniform random distribution in range of [0, 0.3]
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_real_distribution<float> distr(0.0, 0.3);

        bee1.updateSelfPosition(distr(generator));
        bee2.updateSelfPosition(distr(generator));

        // SIMULATE THE BEES
        for (double time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
            // set input values for c1 - based on where c1 is and where c2 is
            bool inRange = checkAgentContact(bee1.getSelfPosition(), bee2.getSelfPosition());
            if (inRange){
                bee1.updateContactSensor(1);
                bee2.updateContactSensor(0);
            }
            else {
                bee2.updateContactSensor(0);
            }

            // update relative dist to target
            float dist_to_target = abs(bee1.getSelfPosition() - target);
            bee1.updateTargetSensor(dist_to_target);

            // perform calc for one timestep
            bee1.stepAgent(TIMESTEP_SIZE);
            bee2.stepAgent(TIMESTEP_SIZE);

            // update location of c1 - based on motor neuron output
            moveAgent(bee1);
            moveAgent(bee2);
        }
        
        //fitness = 1 – distance to the target
        // float fitness = 1 - (abs(bee2.self_position - target));
        
        trials++;
    }

    cout<<"assessed individual  ";
    return 0.0;
}


// selecting the parents?
// copying parents, to then mutate
// tSearch - ? 
Individual pickParent(Individual population[POP_SIZE]){   
    // rank based selection from the overall fitness values
}


// actually create the offsprings
Individual mutateOffspring(Individual offspring){
    // --  replacing offspring alleles with random alternatives
        // Gaussian mutation with variance of 0.2
        // for each parameter to be modified
        // the descendant is only conserved if its performance is better than the individual selected
    // to find: mutation rate
}


void fitnessRankBased(Individual population[POP_SIZE]){
    float fitness_list[POP_SIZE];
    for (int k=0; k<POP_SIZE; k++){
        fitness_list[k] = population[k].fitness;
    }
    std::sort(fitness_list, fitness_list + POP_SIZE, std::greater<float>());
}

void updatePopulation(Individual (&population)[POP_SIZE], Individual new_pop[POP_SIZE]){
    for (int i=0; i<POP_SIZE; i++){
        population[i] = new_pop[i];
    }
}

/***
 * 
 * MAIN FUNCTION
 * 
***/
int main(int argc, char* argv[]){

    int STOP_CND = 0;

    // initialize population
    Individual population[POP_SIZE];
    init_population(population);
    
    // assess population
    for (int i=0; i<POP_SIZE; i++){
        population[i].fitness = assesIndividual(population[i].genome);
    }

    int gen = 0;
    while(gen <= GENERATIONS){ // loop: repeat until stopping condition
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = pickParent(population);
            Individual offspring = parent; //make a copy of parent

            Individual mutated_offspring = mutateOffspring(offspring);
            
            float score = assesIndividual(mutated_offspring.genome);
            if (score > parent.fitness){ // does the order of insertion never matter?
                new_population[i] = mutated_offspring;
            }
            else{
                new_population[i] = parent;
            }
        }

        updatePopulation(population, new_population);

        // end of generation
            //  solutions selected using a rank-based system
            // The selection of the parents depends on the rank of each individual and not the fitness.
            // The higher ranked individuals are preferred more than the lower ranked ones.
        // fitnessRankBased(population);

        gen++;
    }


    return 0;
}
