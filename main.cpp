// ***************************************
// trying to do the thing for project
// ***************************************

#include "CTRNN.h"


// Global constants
const double RunDuration = 250;
const double StepSize = 0.01;

// Agent class
class Agent {
    public:
        CTRNN c(int newsize = 3);
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
            // Run the circuit
            // c().RandomizeCircuitState(-0.5,0.5);
            cout << 0.0 << " " << c().NeuronOutput(1) << " " << c().NeuronOutput(2) << endl;

            // move for loop outside
            for (double time = StepSize; time <= RunDuration; time += StepSize) {
                c().EulerStep(StepSize);
                // cout << time << " " << c().NeuronOutput(1) << " " << c().NeuronOutput(2) << endl;
            }
        }

        void moveAgent(){
            // update the agent location
            // sensors, motor neurons and location
        }


        void viewAgentLocation(){
            // a getter function to return params??
        }
};


// create chromosome or string of genes 
string create_gnome() 
{ 
    int len = TARGET.size(); 
    string gnome = ""; 
    for(int i = 0;i<len;i++) 
        gnome += mutated_genes(); 
    return gnome; 
} 


int main(int argc, char* argv[])
{
    cout<<"in main"<<endl;

    Agent bee1();
    Agent bee2();
    
    // initialize population?
    // assess population
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

