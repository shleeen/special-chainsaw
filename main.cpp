// ***************************************
// trying to do the thing for project
// ***************************************

#include "CTRNN.h"
#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;


// -- Global constants
const int NEURONS = 3;
const int GENES = (NEURONS+3)*NEURONS;

const int POP_SIZE = 10;

const double RUN_DURATION = 250; //what unit is this?
const double STEP_SIZE = 0.1; // 0.01
const float SPEED = 0.01; //"units per time unit"


struct Solution{
    float genome[GENES];
    float fitness_score;
};


/***
 * 
 * AGENT CLASS
 * 
***/
class Agent {
    private:
        CTRNN c;
    public:
        // int flag = 0; //0 is sender, 1 is receiver?
        
        float self_position; 
            //input to neuron 3
            // absolute location along the 1D environment.
        float contact_sensor; 
            //inpput to neuron 1
            // discrete signal - on (1) if the agent is in contact with the other agent and is off (0) otherwise
        float target_sensor; 
            //input to neuron 2
            // a relative measure of the sender’s distance to the target.
            // The receiver also has this sensor, but its value is fixed to -1.
        float motor; 
            // input to neuron 1

        Agent(){
            c.SetCircuitSize(3);

            self_position = 0.0;
            contact_sensor = 0.0;
            target_sensor = 0.0;
            motor = 0.0;
        }

        //constructor
        //decode the genome & set the agent up with the params
        // also set the location/motor values
        Agent(float genome[GENES]){ //param: genome
            int offset = 0; // 3+3=6

            for (int i=1; i<=NEURONS; i++){
                c.SetNeuronTimeConstant(i, genome[offset]);
                c.SetNeuronBias(i, genome[offset+1]);
                c.SetNeuronGain(i, genome[offset+2]);
                c.SetConnectionWeight(i, 1, genome[offset+3]);
                c.SetConnectionWeight(i, 2, genome[offset+4]);
                c.SetConnectionWeight(i, 3, genome[offset+5]);
                offset += 6;
            }

            //set neuron external input
            c.SetNeuronExternalInput(1, contact_sensor);
            c.SetNeuronExternalInput(1, motor);
            c.SetNeuronExternalInput(2, target_sensor);
            c.SetNeuronExternalInput(3, self_position);
        }

        void updateAgentParams(float genome[GENES]);

        // Run the one step of the circuit !! (lol)
        void runAgent(){
            c.RandomizeCircuitState(-0.5,0.5); //should this still be random?
            c.EulerStep(STEP_SIZE);
        }

        // change the self position of agent
        void moveAgent(float new_location){
            c.SetNeuronExternalInput(3, self_position);
        }

        void updateExternalInput(){
            // contact sensor length 0.2 units
            // on (1) if the agent is in contact with the other agent and is off (0) otherwise.
        }
};

void Agent::updateAgentParams(float genome[GENES]){
    int offset = 0; // 3+3=6

    for (int i=1; i<=NEURONS; i++){
        c.SetNeuronTimeConstant(i, genome[offset]);
        c.SetNeuronBias(i, genome[offset+1]);
        c.SetNeuronGain(i, genome[offset+2]);
        c.SetConnectionWeight(i, 1, genome[offset+3]);
        c.SetConnectionWeight(i, 2, genome[offset+4]);
        c.SetConnectionWeight(i, 3, genome[offset+5]);
        offset += 6;
    }

    //set neuron external input
    // c().SetNeuronExternalInput(1, contact_sensor);
    // c().SetNeuronExternalInput(1, motor);
    // c().SetNeuronExternalInput(2, target_sensor);
    // c().SetNeuronExternalInput(3, self_position);
}




/***
 * 
 * GA FUNCTIONS
 * 
***/
// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33
void init_population(Solution (&population)[POP_SIZE]){
    srand((unsigned int)time(NULL));

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
        cout<<"!!!!! "<< target <<endl;

        // draw the pos of bees from a uniform random distribution in range of [0, 0.3]
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_real_distribution<float> distr(0.0, 0.3);

        // float location1 = distr(generator);
        // float location2 = distr(generator);
        // cout<< " location: "<<location1<<" location 2: "<<location2<<endl;
        bee1.self_position = distr(generator);
        bee2.self_position = distr(generator);

        

        for (double time = STEP_SIZE; time <= RUN_DURATION; time += STEP_SIZE) {
            // set input values for c1 - based on where c1 is and where c2 is
            // calc values for c1
            bee1.updateExternalInput();
            bee2.updateExternalInput();

            // do one step for each
            bee1.runAgent();
            bee2.runAgent();

            // update location of c1 - based on motor neuron output
            // (send absolute location)
            float dist = SPEED/STEP_SIZE; // this is fixed throughout??
            float next_location = 0;
            bee1.moveAgent(next_location);
            // bee2.moveAgent();
        }
        
        
        // calc dist to the target
        // calc fitness        
        
        trials++;
    }

    cout<<"assessed individual  ";
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

void fitnessRankBased(Solution population[POP_SIZE]){
    float fitness_list[POP_SIZE];
    for (int k=0; k<POP_SIZE; k++){
        fitness_list[k] = population[k].fitness_score;
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
    Solution population[POP_SIZE];
    init_population(population);
    
    // assess population
        // for indv in population
            // assess(indv)
    for (int i=0; i<POP_SIZE; i++){
        float cur_fitness = assesIndividual(population[i].genome, bee1, bee2);
        population[i].fitness_score = cur_fitness;
    }

    while(STOP_CND < 10){     // loop: repeat until stopping condition
        // breed
        breed();

        // mutate
        mutate();

        //assess
        for (int i=0; i<POP_SIZE; i++){
            float cur_fitness = assesIndividual(population[i].genome, bee1, bee2);
            population[i].fitness_score = cur_fitness;
        }


        // end of generation
            //  solutions selected using a rank-based system
            // The selection of the parents depends on the rank of each individual and not the fitness.
            // The higher ranked individuals are preferred more than the lower ranked ones.
        fitnessRankBased(population);

        STOP_CND++;
    }


    return 0;
}





/*

// struct Solution{
//     float genome[GENES];
//     float fitness_score;
// };

*/