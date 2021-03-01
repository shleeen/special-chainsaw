// struct Individual:
//      float genome[];
//      float fitness;


// main(){
//     initialize population
//          population = []
//          initPopulation(population)
//          with fitness set to 0, and genome a random number between 0 and 1
//     for indv in population:
//          assesIndividual(indv)

//     G=0
//     loop until G generations have been done
//        new_pop = []
//        for i in range POP_SIZE:
//            selectParent() (biased towards the fitter members of pop)
//            copy parent => offspring
//            mutated_offspring = mutateOffspring(offspring)
//            assessIndividual(mutated_offspring)
//            if mutated_offspring.fitness > parent.fitness:
//                new_pop[i] = mutated_offspring
//            else:
//                new_pop[i] = parent
//            updatePopulation(population, new_pop)
//         write out some stats 
//         G+=1
// }


// selectParent(population){
//      rank[N], prob[N]
//      rank[N] => rank of ith fitness of ith indv in population
    
//      for i in range(N):
//          probs[i] = 1/(1+ranks[i])
//      Sum = sum(probs)
//      r = randomNumber(0, Sum)
//      total = 0, i = 0
//      while i < N:
//          total += probs[i]
//          if total > r:
//              break
//      return population[i]     
// }


// mutateOffspring(offspring){
//      Individual new_I
//      for genes in genome:
//          r => random no. from Gaussian distr with mean= offspring.genome[gene], and variance = 0.2
//          new_I.genome[gene] = r
//      return I 
// }


// void assesIndividual(Individual indv){ 
//      Agent bee1; //sender
//      Agent bee2; //receiver
//      bee2.TargetSensor = -1; //since its receiever this is fixed

//     // set Agent params according to the genome
//      bee1.updateNeuronParams(indv.genome);
//      bee2.updateNeuronParams(indv.genome);
    
//      trials = 0
//      fitness_across_trials[20]
//      for trial < 20:
//          target = randomNumber(0.5, 1)
//          // update starting positions of both bees
//          bee1.SelfPosition( randomNumber(0, 0.3) )
//          bee2.SelfPosition( randomNumber(0, 0.3) )

//          // run the simulation
//          for timestep:
//              if Bee1 is in range of Bee2:
//                  update both contact sensors to 1
//              else:
//                  update both sensors to 0
             
//              calc distance of bee1 to target
             
//              EulerStep(bee1)
//              EulerStep(bee2)
 
//              moveAgent(bee1)
//              moveAgent(bee2)
//          fitness_across_trials[trial] = 1 – (bee2.position - target)
//          trial++
//     indv.fitness = rankFitnessOverTrials(fitness_across_trials)
// }


// updatePopulation(&population, new_pop):
//    pop = copy(new_pop) 


// moveAgent(agent):
//      state = state of agent's motor neuron
//      current_location = agent's current location
//      if state < 0.5:
//          new_location = current_location + 0.1
//      else:
//          new_location = current_location - 0.1
//      agent.updateSelfPosition(new_location)


// rankFitnessOverTrials(fitness_list[]):
//     rank[20] => rank of i-th trial in fitness_list[]
//     inversely weighting each score according to its rank
//     then sum the fitness of each trial 



// ----------------------------------------------------------------------
// selecting the parents?
// copying parents, to then mutate
// tSearch - ? 
void breed(){   
    // rank based selection from the overall fitness values
}


// actually create the offsprings
void mutate(){
    // --  replacing offspring alleles with random alternatives
        // Gaussian mutation with variance of 0.2
        // for each parameter to be modified
        // the descendant is only conserved if its performance is better than the individual selected
    // to find: mutation rate
}


/* 

    SOME OLD RANDOM NUMBER CODE :)

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
*/




// void writeBestAgents(Individual population[POP_SIZE]){
//     float max = 0.0;
//     int index;
//     for (int i=0; i<POP_SIZE; i++){
//         cout<< population[i].fitness<<endl;
//         if (population[i].fitness > max){
//             max = population[i].fitness;
//             index = i;
//         }
//     }
//     cout<<"reached here"<<endl;
//     for (int i=0; i<18; i++){
//         cout<< max <<endl;
//     }    
// }
