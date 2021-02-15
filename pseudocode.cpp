

void main(){

    Agent bee1();
    Agent bee2();

    // initialize population?
    // assess population
        // for all in population
            // assess(indv)

    // G=0
    // loop until G generations have been done
    //    new_pop = []
    //    for i in range POP_SIZE
    //        pick parent from pop (biased towards the fitter members of pop)
    //        copy parent => offspring
    //        mutate offspring => offspring
    //        fit = assessIndividual(offspring)
    //        if fit > parent.fitness:
    //            new_pop[i] = offspring
    //        else:
    //            new_pop[i] = parent
    //     pop = copy(new_pop) 
    //     write out some stats 
    //     G+=1

    // ??
    // end of generation
        //  solutions selected using a rank-based system
        // The selection of the parents depends on the rank of each individual and not the fitness.
        // The higher ranked individuals are preferred more than the lower ranked ones.

}

// generates the fitness scores
void asses(string individual){ 
    // 20 trials
        // draw random target [0.5, 1]
        // update the network! updateAgent() for some timesteps
            // check location, inputs 
            // w, g, b constant thorughout whole lifetime of agent
        // fitness = 1 – distance to the target
            // if fitness is -ve, fitness = 0

    // overall fitness:
        // rank trials
        // inversely weighting each score according to its rank
        // then sum the fitness of each trial 

    // return overall fitness 
}

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