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


struct Individual{
    float genome[GENES];
    float fitness_score;
};



/***
 * 
 * GA FUNCTIONS
 * 
***/
// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33

void init_population(Individual (&population)[POP_SIZE]){
    srand((unsigned int)time(NULL));
    // TODO: range
    // seed
    // number b/w 0 and 1

    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            population[i].genome[j] = float(rand());
        }
        population[i].fitness_score = 0;
    }
    cout<<"created population :)"<<endl;
}


// generates the fitness scores
float assesIndividual(float individual[18], Agent &bee1, Agent &bee2){
    int trials = 0; //this aint gonna change
    while (trials < 20){
        // draw target
        float target = (float)(rand()) / ((float)(RAND_MAX/(0.5 - 1)));
        // cout<<"!!!!! "<< target <<endl;

        // draw the pos of bees from a uniform random distribution in range of [0, 0.3]
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_real_distribution<float> distr(0.0, 0.3);

        // float location1 = distr(generator);
        // float location2 = distr(generator);
        // cout<< " location: "<<location1<<" location 2: "<<location2<<endl;
        bee1.self_position = distr(generator);
        bee2.self_position = distr(generator);

        // SIMULATE THE BEES
        for (double time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
            // set input values for c1 - based on where c1 is and where c2 is
            // calc values for c1
            bee1.updateExternalInput();
            bee2.updateExternalInput();

            // do one step for each
            bee1.runAgent();
            bee2.runAgent();

            // update location of c1 - based on motor neuron output
            // (send absolute location)
            float dist = SPEED/TIMESTEP_SIZE; // 0.01 is the biggest step
            float next_location = 0;
            bee1.moveAgent(next_location);
            // bee2.moveAgent();
        }
        
        
        //fitness = 1 – distance to the target
        float fitness = 1 - (abs(bee2.self_position - target));
        
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
        fitness_list[k] = population[k].fitness_score;
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

    Agent bee1; //sender
    Agent bee2; //receiver
    int STOP_CND = 0;

    // initialize population
    Individual population[POP_SIZE];
    init_population(population);
    
    // assess population
        // for indv in population
            // assess(indv)
    for (int i=0; i<POP_SIZE; i++){
        float cur_fitness = assesIndividual(population[i].genome, bee1, bee2);
        population[i].fitness_score = cur_fitness;
    }

    int gen = 0;
    while(gen <= GENERATIONS){ // loop: repeat until stopping condition
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = pickParent(population);
            Individual offspring = parent; //make a copy of parent

            Individual mutated_offspring = mutateOffspring(offspring);
            
            float score = assesIndividual(mutated_offspring.genome, bee1, bee2);
            if (score > parent.fitness_score){ // does the order of insertion never matter?
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





/*

// struct Solution{
//     float genome[GENES];
//     float fitness_score;
// };

*/