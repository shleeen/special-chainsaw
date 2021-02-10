// ***************************************
// trying to do the thing for project
// ***************************************

#include "CTRNN.h"
// #include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
// using namespace std;


// Global constants
const int NEURONS = 3;
const int GENES = (NEURONS+3)*NEURONS;

const int POP_SIZE = 10;

const double RunDuration = 250;
const double StepSize = 0.01;

struct Solution{
    float genome[GENES];
    float fitness_score;
};

// Function declarations
float assesPopulation(Solution individual);

// Agent class
class Agent {
    public:
        CTRNN c(int newsize = NEURONS);
        // int location;
        float self_position;
        float contact_sensor;
        float target_sensor;
        float motor; // ??! ⊙︿⊙

        //constructor
        Agent(){ //pass values
            //param: genome
            //decode the genome

            // c.SetNeuronBias(1, -2.75); 
            // c.SetNeuronBias(2, -1.75);
            // c.SetConnectionWeight(1, 1, 4.5);
            // c.SetConnectionWeight(1, 2, -1);
            // c.SetConnectionWeight(2, 1, 1);
            // c.SetConnectionWeight(2, 2, 4.5);
        }

        void updateAgent(){
            // // Run the circuit
            // // c().RandomizeCircuitState(-0.5,0.5);
            // cout << 0.0 << " " << c().NeuronOutput(1) << " " << c().NeuronOutput(2) << endl;

            // // move for loop outside
            // for (double time = StepSize; time <= RunDuration; time += StepSize) {
            //     c().EulerStep(StepSize);
            //     // cout << time << " " << c().NeuronOutput(1) << " " << c().NeuronOutput(2) << endl;
            // }
        }

        void moveAgent(){
            // update the agent location
            // sensors, motor neurons and location
        }


        void viewAgentLocation(){
            // a getter function to return params??
        }
};

// struct gene{
//     float tau;
//     float bias;
//     float gain;
//     float weights[NEURONS];
// };
// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33

// chromosome/genotype consists of 3 genes
/*
gene* create_genotype(gene genome[]) { // referencing an array
    // int len = TARGET.size();

    // string gnome = ""; 
    // for(int i = 0;i<len;i++) 
        // gnome += mutated_genes();
    // return gnome; 
    // int y[10];

    for (int i=0; i<NEURONS-1; i++){
        gene g1;
        g1.tau = 0.05;
        genome[i] = g1; 
    }
    return genome;
} 
*/

// struct Solution{
//     float genome[GENES];
//     float fitness_score;
// };

void init_population(Solution (&population)[POP_SIZE]){
    srand((unsigned int)time(NULL));

    for (int i=0; i<POP_SIZE; i++){
        for (int j=0; j<GENES; j++){        
            population[i].genome[j] = float(rand());
            cout<<population[i].genome[j]<<" ";
        }
        population[i].fitness_score = 0;
        cout<<endl;
    }
}



int main(int argc, char* argv[])
{
    cout<<"in main"<<endl;

    Agent bee1();
    Agent bee2();

    // array<int, 5>
    // gene g1;
    // gene test[NEURONS] = {0,0,0};
    // cout<<test[0] << test[1] << test[2]<<endl;
    // gene *res = create_genotype(test);
    // cout<<res[0] << res[1] << res[2]<<endl;

    // initialize population?
    Solution population[POP_SIZE];
    init_population(population);
    
    // assess population
    // Solution ne;
    for (int i=0; i<POP_SIZE; i++){
        float cur_fitness = assesPopulation(population[i].genome);
    }
    // for all in population
            // assess(indv)
    // loop: repeat until stopping condition
        // breed()
        // mutate()
        // asses()

    // ??
    // end of generation
        //  solutions selected using a rank-based system
        // The selection of the parents depends on the rank of each individual and not the fitness.
        // The higher ranked individuals are preferred more than the lower ranked ones.
    
    return 0;
}


// generates the fitness scores
float assesPopulation(Solution individual){
    int trials = 0; //this aint gonna change
    while (trials < 20){
        float target = (float)(rand()) / ((float)(RAND_MAX/(0.5 - 1)));
        
        cout<<"!!!!! "<< target<<endl;
        // updateAgent
        target++;
    }

    return 0.0;
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

