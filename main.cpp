// ***************************************
// trying to do the thing for project
// ***************************************

#include "CTRNN.h"
#include "Agent.h"
#include <iostream>
#include <array>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <random>
#include <algorithm>
#include <limits>
#include <cmath>

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


// float getRandomNumber(float start, float end, float seed=std::numeric_limits<double>::quiet_NaN()) {
//     if (std::isnan(seed)){ //seed using time
//         srand((unsigned int)time(NULL));
//     }
//     else{
//         //seed using given number
//     }

//     // float range = (end-start)+1;  //why +1?
//     // float random_int = start+(rand()%range); 
//     float range = (end-start);
//     float random_int = start + ( (float)rand()/ ((float)(RAND_MAX/range)) );
//     return random_int; 
// } 

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

void findRank(float array[20], float (&rank)[20]){       
    for (int i = 0; i < 20; i++) { 
        int r = 1, s = 1; 
          
        for (int j = 0; j < 20; j++) { 
            if (j != i && array[j] < array[i]) 
                r += 1; 
                  
            if (j != i && array[j] == array[i]) 
                s += 1;      
        }
          
        // Use formula to obtain rank 
        rank[i] = r + (float)(s - 1) / (float) 2;
    } 
}


/***
 ***   GA FUNCTIONS
***/
void init_population(Individual (&population)[POP_SIZE]){
    // srand((unsigned int)time(NULL));
    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            population[i].genome[j] = randomNumberUniform(0.0, 1.0);
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



// void calcRankBasedOverallFitness(Individual population[POP_SIZE], float (&overall)[POP_SIZE]){
float calcFitnessOverTrials(float fitness_list[20]){
    // for (int k=0; k<POP_SIZE; k++){
    //     overall[k] = population[k].fitness;
    // }
    //does list need to be sorted?
    // std::sort(fitness_overall, fitness_overall + POP_SIZE, std::greater<float>());

    float final_fitness = 0.0;
    float rank[20];
    findRank(fitness_list, rank);

    for (int k=0; k<20; k++){
        final_fitness += fitness_list[k] * (1/rank[k]);
    }

    return final_fitness;
}


void assesIndividual(Individual indv){    
    Agent bee1(NEURONS, GENES); //sender
    Agent bee2(NEURONS, GENES); //receiver
    bee2.updateTargetSensor(-1); //target sensor value for receiver is fixed

    // TODO: unpack genome!!!

    int trials = 0;
    float fitness_across_trials[20];

    while (trials < 20){
        // draw target from uniform random distribution in range [0.5, 1.0]
        float target = randomNumberUniform(0.5, 1.0);

        // draw the pos of bees from uniform random distribution in range of [0, 0.3]
        bee1.updateSelfPosition(randomNumberUniform(0.0, 0.3));
        bee2.updateSelfPosition(randomNumberUniform(0.0, 0.3));

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
        
        // update fitness of indv
        fitness_across_trials[trials] = 1 - (abs(bee2.getSelfPosition() - target));

        trials++;
    }

    cout<<" 20 trials done. "<<endl;

    // rank based fitness overall calc
    indv.fitness = calcFitnessOverTrials(fitness_across_trials);
}


// tSearch - ? 
// rank based selection from the overall fitness values
    // end of generation
        //  solutions selected using a rank-based system
        // The selection of the parents depends on the rank of each individual and not the fitness.
        // The higher ranked individuals are preferred more than the lower ranked ones.
Individual selectParent(Individual population[POP_SIZE]){   
    Individual I;

    // sum(fitnesses(population)) => S
    // rand(0,S) => roll

    // float total = 0.0;
    // loop i from 1 to N:
    //     running_total + fitness(i) => running_total
    //     if running_total >= roll:
    //     return(i)

    float Sum = 0.0;
    //sum the ranks instead of fitness here?
    for (int i=0; i<POP_SIZE; i++){
        Sum += population->fitness;
    }
    float r = randomNumberUniform(0, Sum);

    return I;
}


// replace alleles with 
Individual mutateOffspring(Individual offspring){
    // decode genome

    // to find: mutation rate

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(1.0, sqrt(0.2));


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
        assesIndividual(population[i]);
    }

    int gen = 0;
    while(gen <= GENERATIONS){ // loop: repeat until stopping condition
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = selectParent(population);
            Individual offspring = parent; //make a copy of parent

            Individual mutated_offspring = mutateOffspring(offspring);
            
            assesIndividual(mutated_offspring);
            if (mutated_offspring.fitness > parent.fitness){ // does the order of insertion never matter?
                new_population[i] = mutated_offspring;
            }
            else{
                new_population[i] = parent;
            }
        }

        updatePopulation(population, new_population);

        cout<<"Generation "<<gen<<" complete."<<endl;
        gen++;
    }


    return 0;
}
