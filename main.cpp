// ***************************************
// trying to do the thing for project
// ***************************************

#include "main.h"

// #include <ctime>
// #include <algorithm>
// #include <limits>
// #include <cmath>


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


// void calcRankBasedOverallFitness(Individual population[POP_SIZE], float (&overall)[POP_SIZE]){
float calcFitnessOverTrials(float fitness_list[20]){
    // for (int k=0; k<POP_SIZE; k++){
    //     overall[k] = population[k].fitness;
    // }
    //does list need to be sorted?
    // std::sort(fitness_overall, fitness_overall + POP_SIZE, std::greater<float>());

    float final_fitness = 0.0;
    float rank[20];
    findRank(20, fitness_list, rank);

    for (int k=0; k<20; k++){
        final_fitness += fitness_list[k] * (1/rank[k]);
    }

    return final_fitness;
}


void assessIndividual(Individual indv){    
    Agent bee1(NEURONS, GENES); //sender
    Agent bee2(NEURONS, GENES); //receiver
    bee2.updateTargetSensor(-1); //target sensor value for receiver is fixed

    // set Agent params according to the genome
    bee1.updateNeuronParams(indv.genome);
    bee2.updateNeuronParams(indv.genome);

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
            contactAgent(bee1, bee2);

            // update relative dist to target
            float dist_to_target = abs(bee1.getSelfPosition() - target);
            bee1.updateTargetSensor(dist_to_target);

            // perform calc for one timestep
            bee1.stepAgent(TIMESTEP_SIZE);
            bee2.stepAgent(TIMESTEP_SIZE);

            // update location of c1 - based on motor neuron output
            moveAgent(bee1);
            moveAgent(bee2);

            // write data to a csv file
            // TODO: only save data of the fittest trial?
            // p.storeData(bee1.getSelfPosition(), time);
        }

        // p.writeCSV(trials);
        
        // update fitness of indv
        fitness_across_trials[trials] = 1 - (abs(bee2.getSelfPosition() - target));
                
        trials++;
    }


    // rank based fitness overall calc
    if (calcFitnessOverTrials(fitness_across_trials) < 0){
        indv.fitness = 0;
    }
    else{
        indv.fitness = calcFitnessOverTrials(fitness_across_trials);
    }
    // indv.fitness = calcFitnessOverTrials(fitness_across_trials);
}


// tSearch - ? 
// rank based selection from the overall fitness values
    // end of generation
        //  solutions selected using a rank-based system
        // The selection of the parents depends on the rank of each individual and not the fitness.
        // The higher ranked individuals are preferred more than the lower ranked ones.
Individual selectParent(Individual population[POP_SIZE]){   
    float rank[POP_SIZE];
    float prob[POP_SIZE];
    float overall[POP_SIZE];

    for (int k=0; k<POP_SIZE; k++){
        overall[k] = population[k].fitness;
    }

    findRank(POP_SIZE, overall, rank);

    float Sum = 0.0;
    float total = 0.0;

    // # if probs[i] = 1   then i is the best indivdiual
    // # if probs[i] = 1/N then this is the worst individual
    for (int i=0; i<POP_SIZE; i++){
        prob[i] = 1 / (1+rank[i]);
        Sum += prob[i];
    }
    float r = randomNumberUniform(0, Sum);
    
    int k = 0;
    while (k <= POP_SIZE){
        total += prob[k];
        if (total >= r){
            break;
        }
    }

    return population[k];
}


// to find: mutation rate ??
Individual mutateOffspring(Individual offspring){
    Individual I;
    I.fitness = 0.0;

    // decode genome??
    // TODO: dont mutate gain
    for (int i=0; i<GENES; i++){
        I.genome[i] = randomNumberGaussian(offspring.genome[i]);
    }

    return I;
}


void updatePopulation(Individual (&population)[POP_SIZE], Individual new_pop[POP_SIZE]){
    for (int i=0; i<POP_SIZE; i++){
        population[i] = new_pop[i];
    }
}


/***
 ***    MAIN FUNCTION
***/
int main(int argc, char* argv[]){

    // initialize population
    Individual population[POP_SIZE];
    init_population(population);
    
    // assess population
    for (int i=0; i<POP_SIZE; i++){
        assessIndividual(population[i]);
    }

    int gen = 0;
    while(gen <= GENERATIONS){ // loop: repeat until stopping condition
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = selectParent(population);
            Individual offspring = parent; //make a copy of parent

            Individual mutated_offspring = mutateOffspring(offspring);
            
            assessIndividual(mutated_offspring);
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

    cout<<"Evolution complete. :) "<<endl;

    float max_fit=0.0; int index;
    for(int k=0; k<POP_SIZE; k++ ){
        // cout<<population[k].fitness<<" ";
        if(population[k].fitness > max_fit){        
            max_fit = population[k].fitness;
            index = k;
        }
    }
    cout << "Largest fitness = " << max_fit <<" index: "<< index <<" "<<population[index].fitness<<endl;;

    return 0;
}
