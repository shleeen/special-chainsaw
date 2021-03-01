// file to use best agent from evolution, and then run simulations

#include "main.h"
#include <string>

// global constants
const int TRIALS = 1;
const float TARGET_MIN = 0.5; 
const float TARGET_MAX = 1.0;
const int NO_OF_TARGETS = 50; // target_max - target_min/no_of_targets => interval between points selected
const float INTERVAL = (TARGET_MAX - TARGET_MIN) / NO_OF_TARGETS;
const float TIMESTEP = 0.1;

Plot pl;

int main(int argc, char* argv[]){
    // open file
    fstream myFile("Agent.csv", ios::in);
    Individual best;
    string line;
    for(int i=0; i<GENES; i++){
        getline(myFile, line); //get one line from file
        best.genome[i] = stof(line); //save value as float into Indv
    }
    best.fitness = 0.0;

    int trials = 0;
    float target = 0;
    // float fitness_across_trials[20];

    Agent sender(NEURONS, GENES); //sender
    Agent receiver(NEURONS, GENES); //receiver
    receiver.updateTargetSensor(-1); //target sensor value for receiver is fixed

    // set both Agents params with Best Indv's genome
    sender.updateNeuronParams(best.genome);
    sender.updateNeuronParams(best.genome);

    while (trials < TRIALS){
        // target += INTERVAL;
        target = 0.8;
        pl.target = 0.8;
        cout<<" target : "<<target<<endl;

        // draw starting position of agents
        sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
        receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));

        // cout<<"starting pos - > "<<bee1.getSelfPosition()<<endl;

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
            moveAgent(sender);
            moveAgent(receiver);

            // write data to a csv file
            pl.storeDataFig8(sender.getSelfPosition(), receiver.getSelfPosition(), time);

        }

        // fitness_across_trials[trials] = 1 - (abs(bee2.getSelfPosition() - target));


        ++trials;

    }


    //write stored data to file
    pl.writeFig8();
    cout<<"stuff was written"<<endl;

}