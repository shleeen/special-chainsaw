// ***************************************
// trying to do the thing for project
// ***************************************

#include "main.h"

/***
 ***   GA FUNCTIONS
***/
void initPopulation(Individual (&population)[POP_SIZE]){
    // srand((unsigned int)time(NULL));
    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            population[i].genome[j] = randomNumberUniform(0.0, 1.0);
        }
        population[i].fitness = 0;
    }
    cout<<"created population :)"<<endl;
}


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
        // final_fitness += fitness_list[k] * (1.0/rank[k]);
        final_fitness += fitness_list[k] * ((21-rank[k])/20);
    }

    return final_fitness;
}


Individual assessIndividual(Individual indv, int cur_gen){  
    Agent sender(NEURONS, GENES); //sender
    Agent receiver(NEURONS, GENES); //receiver
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
        float target = randomNumberUniform(0.5, 1.0);

        // draw the pos of bees from uniform random distribution in range of [0, 0.3]
        sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
        receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));

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
                // cout<<"OUTSIDE RANGE aaaa"<<sender_pos<<" "<<sender.getSelfPosition()<<endl;   
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
    // indv.fitness = (1.1 + (2.0 - 2.0*1.1)*((i-1.0)/(POP_SIZE-1)))/POP_SIZE;
    // cout<<indv.fitness<<endl;

    return indv;
}


Individual selectParent(Individual population[POP_SIZE]){   
    float rank[POP_SIZE];
    float prob[POP_SIZE];
    float overall[POP_SIZE];
    float selection_prob[POP_SIZE];
    float alpha = 1.1;

    // if alpha > 1, stronger selection
    // if alpha < 1, weaker selection 
    // selection_probability[i] = 1/pow(rank[i], alpha);

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
        // selection_prob[i] = 1/pow(rank[i], alpha);
        // Sum += selection_prob[i] * prob[i];
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
    fstream fout, fmean;
    fout.open("data/BestFitVsGeneration.csv", ios::out);
    fmean.open("data/MeanFitness.csv", ios::out);
    
    // initialize population
    Individual population[POP_SIZE];
    initPopulation(population);
    
    // assess population
    for (int i=0; i<POP_SIZE; i++){
        population[i] = assessIndividual(population[i]);
    }

    int gen = 0;
    while(gen <= GENERATIONS){ // loop: repeat until stopping condition
        Individual new_population[POP_SIZE];

        for (int i=0; i<POP_SIZE; i++) {

            // pick parent from population
            Individual parent = selectParent(population);
            Individual offspring = parent; //make a copy of parent

            Individual mutated_offspring = mutateOffspring(offspring);
            mutated_offspring = assessIndividual(mutated_offspring);

            if (mutated_offspring.fitness > parent.fitness){
                new_population[i] = mutated_offspring;
            }
            else{
                new_population[i] = parent;
            }
        }

        updatePopulation(population, new_population);
        
        // --------  STATS CALC --------
        float sum_fit = 0.0;
        // plot best fit vs generation
        float max_fit=0.0; int index;
        for(int k=0; k<POP_SIZE; k++ ){
            // cout<<population[k].fitness<<" ";
            sum_fit += population[k].fitness;
            if(population[k].fitness > max_fit){        
                max_fit = population[k].fitness;
                index = k;
            }
        }

        cout<<"Generation "<<gen<<" complete. "<<" Best fit = " << max_fit <<endl;
        // cout << "\n Largest fitness = " << max_fit <<" index: "<< index <<" "<<population[index].fitness<<endl;;
        
        // only write to file, every 500 generations
        // if (gen%500){
        fout<<gen<<", "<<max_fit<<"\n";
        fmean<<gen<<", "<< sum_fit/POP_SIZE <<"\n";
        // }

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

    // close files
    fout.close();
    fmean.close();
    agent_file.close();

    cout<<"Everything written to file!!"<<endl;

    return 0;
}
