#include "main.h"

/***
 ***   GA FUNCTIONS
***/
void initPopulation(Individual (&population)[POP_SIZE]){
    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            // population[i].genome[j] = randomNumberUniform(0.0, 1.0);
            population[i].genome[j] = UniformRandom(0.0, 1.0);
        }
        population[i].fitness = 0;
    }
    cout<<"created population :)"<<endl;
}


float calcFitnessOverTrials(float fitness_list[20]){
    float final_fitness = 0.0;
    float rank[20];
    findRankAscending(20, fitness_list, rank);

    for (int k=0; k<20; k++){
        // final_fitness += fitness_list[k] * (1.0/rank[k]);
        final_fitness += fitness_list[k] * ((21-rank[k])/20);
    }

    // rescale fitness to [0, 1] instead of [0, 9] ??

    return final_fitness;
}


Individual assessIndividual(Individual indv, Agent &sender, Agent &receiver, int cur_gen){  
    // reset Agent object
    sender.reset();
    receiver.reset();

    receiver.updateTargetSensor(-1); //target sensor value for receiver is fixed

    // change below flag based on generation count
    int flag = 1;
    // if (cur_gen < 0.1*GENERATIONS)
    //     flag = 1;
    // else 
    //     flag = 0;

    // set Agent params according to the genome
    sender.updateNeuronParams(indv.genome, flag);
    receiver.updateNeuronParams(indv.genome, flag);

    int trials = 0;
    float fitness_across_trials[20];

    while (trials < 20){
        // draw target from uniform random distribution in range [0.5, 1.0]
        // float target = randomNumberUniform(0.5, 1.0);
        float target = UniformRandom(0.5, 1.0);

        // draw the pos of bees from uniform random distribution in range of [0, 0.3]
        sender.updateSelfPosition(UniformRandom(0.0, 0.3)); //randomNumberUniform(0.0, 0.3));
        receiver.updateSelfPosition(UniformRandom(0.0, 0.3)); //randomNumberUniform(0.0, 0.3)); 

        // SIMULATE THE BEES
        for (double time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
            // set input values for c1 - based on where c1 is and where c2 is
            contactAgent(sender, receiver);

            // update relative dist to target
            float dist_to_target = abs(sender.getSelfPosition() - target);
            sender.updateTargetSensor(dist_to_target);

            // perform calc for one timestep
            sender.stepAgent(TIMESTEP_SIZE);
            receiver.stepAgent(TIMESTEP_SIZE);

            // update location of c1 - based on motor neuron output
            moveAgent(sender, TIMESTEP_SIZE);

            // clip the senderrrr
            float sender_pos = sender.getSelfPosition();
            if (sender_pos > 0.3){
                sender.updateSelfPosition(0.3);
            }
            else if (sender_pos < 0.0){
                sender.updateSelfPosition(0.0);
            }
            
            // sender.updateSelfPosition(clip(sender_pos, 0.0, 0.3));
            
            moveAgent(receiver, TIMESTEP_SIZE);
        }
        
        // update fitness of indv
        fitness_across_trials[trials] = max(0.0, 1.0 - (abs(receiver.getSelfPosition() - target)));
                
        trials++;
    }

    // rank based fitness overall calc
    indv.fitness = calcFitnessOverTrials(fitness_across_trials);

    return indv;
}


Individual selectParent(Individual population[POP_SIZE]){   
    float rank[POP_SIZE];
    float prob[POP_SIZE];
    float overall[POP_SIZE];

    for (int k=0; k<POP_SIZE; k++){
        overall[k] = population[k].fitness;
    }

    // rank 1 -> best fitness
    // rank N -> lowest fitness
    findRankDescending(POP_SIZE, overall, rank);

    // TODO: Sum is not 1!?? for this (POP_SIZE - rank[i]).. but that shouldnt be tru...??
    float Sum = 0.0; // sum of probs is 1
    float total = 0.0;

    for (int i=0; i<POP_SIZE; i++){
        // Low selection pressure, from Beer
        // prob[i] = (MAX_EXP_OFFSPRING + (2.0 - 2.0*MAX_EXP_OFFSPRING)*(((POP_SIZE - rank[i])-1.0)/(POP_SIZE-1)))/POP_SIZE;
        prob[i] = (MAX_EXP_OFFSPRING + (2.0 - 2.0*MAX_EXP_OFFSPRING)*((rank[i]-1)/(POP_SIZE-1)))/POP_SIZE;

        // High selection pressure
        // prob[i] = 1 / (1+rank[i]);

        Sum += prob[i];
    }
    // float r = randomNumberUniform(0, Sum);
    float r = UniformRandom(0, Sum);
    
    int k = 0;
    while (k <= POP_SIZE){
        total += prob[k];
        if (total >= r){
            break;
        }
        k++;
    }

    return population[k];
}


// Function that mutates offspring by a value randomly picked from Gaussian distr
Individual mutateOffspring(Individual offspring){
    Individual I;
    I.fitness = 0.0;

    for (int i=0; i<GENES; i++){
        I.genome[i] = GaussianRandom(offspring.genome[i], 0.2);
        // I.genome[i] = randomNumberGaussian(offspring.genome[i]);
    }

    return I;
}


// Mutation function thats similar to Beer's TSearch
void beerMutation(Individual &offspring){
    float random_muts[GENES];
    float sum_sq = 0.0;

    float mutation_size = GaussianRandom(0.0, MUTATION_VARIANCE);

    for (int i = 0; i<GENES; i++){
        // random perturbation for each gene
        random_muts[i] = GaussianRandom(0.0, 1.0);

        // sum the squares of each random mut
        sum_sq += random_muts[i] * random_muts[i];
    }

    sum_sq = sqrt(sum_sq);

    // normalize the random muts
    for (int j=0; j<GENES; j++){
        random_muts[j] = random_muts[j]/sum_sq;
    }
  
    // update the offspring with mutation amt
    for (int i=0; i<GENES; i++){
      offspring.genome[i] += random_muts[i]*mutation_size;

      // clip genes to [0,1] or [-1,1]
      if (offspring.genome[i] < 0.0){
        offspring.genome[i] = 0.0;
      }
      else if (offspring.genome[i] > 1.0){
        offspring.genome[i] = 1.0;
      }
    }
}


// Function to update old population variable with new pop
void updatePopulation(Individual (&population)[POP_SIZE], Individual new_pop[POP_SIZE]){
    for (int i=0; i<POP_SIZE; i++){
        population[i] = new_pop[i];
    }
}


/***
 ***    MAIN FUNCTION
***/
int main(int argc, char* argv[]){
    // set seed for all random number generation
    // SetRandomSeed(3);

    fstream fout, fmean, finalpop;
    fout.open("data/BestFitVsGeneration.csv", ios::out);
    fmean.open("data/MeanFitness.csv", ios::out);
    finalpop.open("data/final_population.csv", ios::out);

    Agent sender(NEURONS, GENES); //sender
    Agent receiver(NEURONS, GENES); //receiver

    // initialize population
    Individual population[POP_SIZE];
    initPopulation(population);
    
    // assess population
    for (int i=0; i<POP_SIZE; i++){
        population[i] = assessIndividual(population[i], sender, receiver, 0);
    }

    int gen = 0;
    while(gen <= GENERATIONS){
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = selectParent(population);
            Individual offspring = parent; //make a copy of parent

            // Individual mutated_offspring = mutateOffspring(offspring);  
            // Individual mutated_offspring = beerMutation(offspring); 
            beerMutation(offspring);
            Individual mutated_offspring = assessIndividual(offspring, sender, receiver, gen+1);

            if (mutated_offspring.fitness > parent.fitness){
                new_population[i] = mutated_offspring;
            }
            else{
                new_population[i] = parent;
            }
        }

        updatePopulation(population, new_population);
        
        // ---------------  STATS CALC ------------------
        float sum_fit = 0.0, max_fit = 0.0;
        int index;
        for(int k=0; k<POP_SIZE; k++ ){
            sum_fit += population[k].fitness;
            if(population[k].fitness > max_fit){        
                max_fit = population[k].fitness;
                index = k;
            }
        }

        cout<<"Generation "<<gen<<" complete. "<<" Best fit = " << max_fit <<endl;
        // cout << "\n Largest fitness = " << max_fit <<" index: "<< index <<" "<<population[index].fitness<<endl;;
        
        // write to file every x generations
        if (gen!=0 && gen%100 == 0){
            cout<<"------------------------------------------------\n";
            cout<<"Writing to the file..."<<endl;
            cout<<"mean: "<<sum_fit/POP_SIZE<<endl;
            cout<<"------------------------------------------------\n";

            fout<<gen<<", "<< max_fit <<"\n";
            fmean<<gen<<", "<< sum_fit/POP_SIZE <<"\n";
        } 
        // ----------------------------------------------

        // INC GENERATION COUNTER
        gen++;
    }

    cout<<"Evolution complete. :) "<<endl;

    // Find genome with best/max fitness.
    float max_fit = 0.0; int index=0;
    for(int k=0; k<POP_SIZE; k++ ){
        // cout<<population[k].fitness<<" ";
        if(population[k].fitness > max_fit){        
            max_fit = population[k].fitness;
            index = k;
        }
    }
    cout << "\n Best fitness from final generation = " << max_fit <<" index: "<< index <<" "<<population[index].fitness<<endl;

    // Save genome of best agent in a file.
    fstream agent_file;
    agent_file.open("data/Agent.csv", ios::out);
    cout<<"BEST AGENT: "<<endl;
    for (int i=0; i<GENES; i++){
        cout<<population[index].genome[i]<<endl;
        agent_file<<population[index].genome[i]<<"\n";
    }

    // Save final population genotype
    finalpop<<"FITNESS\tGENES...\n";
    for(int k=0; k<POP_SIZE; k++ ){
        finalpop<<population[k].fitness<<"\t";
        for (int l=0; l<GENES; l++){
            finalpop<<population[k].genome[l]<<"\t";
        }
        finalpop<<"\n";
    }
    finalpop.close();


    // close files
    fout.close();
    fmean.close();
    agent_file.close();

    cout<<"Everything written to file!!"<<endl;

    return 0;
}
