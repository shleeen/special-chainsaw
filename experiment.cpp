// file to use best agent from evolution, and then run simulations

#include "main.h"
#include <string>

// global constants
const int TRIALS = 50;
const float TARGET_MIN = 0.5; 
const float TARGET_MAX = 1.0;
const int NO_OF_TARGETS = 50; // target_max - target_min/no_of_targets => interval between points selected
const float INTERVAL = (TARGET_MAX - TARGET_MIN) / NO_OF_TARGETS;
const float TIMESTEP = 0.1;

Plot pl;

void diachronicTesting(Individual best){
    fstream fout;
    fout.open("data/diachronic.csv", ios::out);
    
    float target = 0.8;
    cout<<" target : "<<target<<endl;

    // for each target, do 50 trials
    // for (int trials=0; trials<50; trials++){

    // new set of agents for each trial, params initialized to 0
    Agent sender(NEURONS, GENES);
    Agent receiver(NEURONS, GENES);
    receiver.updateTargetSensor(-1);

    // set both Agents params with Best Indv's genome
    sender.updateNeuronParams(best.genome);
    receiver.updateNeuronParams(best.genome);

    // draw starting position of agents
    sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
    receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));
    cout<<"starting pos - > "<<sender.getSelfPosition()<<" "<<receiver.getSelfPosition()<<endl;

    // SIMULATE THE BEES
    for (float time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
        // write data to file
        fout<< time<<", "<<target<<", "<<sender.getSelfPosition()<<", "<<receiver.getSelfPosition()<<", "<<sender.getContactSensor()<<", "<<receiver.getContactSensor()<<", "<<sender.getTargetSensor()<<", "<<receiver.getTargetSensor()<<"\n";

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
    }
    // }   

    // close file
    fout.close();
}


void trialedTesting(Individual best){
    fstream f6, f7;
    f6.open("data/AbsMeanDist.csv", ios::out);
    f7.open("data/MeanFinalPosition.csv", ios::out);

    float target = 0;
    
    for (float target=TARGET_MIN; target <=TARGET_MAX; target+=0.01){
        target += 0.01;
        pl.target = target;
        cout<<" target : "<<target<<endl;

        float mean_dist = 0.0;
        float mean_pos = 0.0;

        // for each target, do 50 trials
        for (int trials=0; trials<50; trials++){

            // new set of agents for each trial, params initialized to 0
            Agent sender(NEURONS, GENES);
            Agent receiver(NEURONS, GENES);
            receiver.updateTargetSensor(-1);

            // set both Agents params with Best Indv's genome
            sender.updateNeuronParams(best.genome);
            receiver.updateNeuronParams(best.genome);

            // draw starting position of agents
            sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
            receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));
            // cout<<"starting pos - > "<<sender.getSelfPosition()<<" "<<receiver.getSelfPosition()<<endl;

            // SIMULATE THE BEES
            for (float time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
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
                // pl.storeDataFig8(sender.getSelfPosition(), receiver.getSelfPosition(), time);
            }

            // fitness_across_trials[trials] = 1 - (abs(bee2.getSelfPosition() - target));

            float next_dist = receiver.getSelfPosition() - target;
            mean_dist = mean_dist + (next_dist - mean_dist)/(trials+1);

            mean_pos = mean_pos + (receiver.getSelfPosition() - mean_pos)/(trials+1);

        } //end of trials While

        // cout<<mean_dist<<endl;
        f6<< target << ", " << abs(mean_dist) <<"\n";   
        f7<< target << ", " << mean_pos <<"\n";

    } //end of Targets While

    f6.close();
    f7.close();
}



int main(int argc, char* argv[]){
    // open file
    fstream myFile("data/Agent.csv", ios::in);
    Individual best;
    string line;
    for(int i=0; i<GENES; i++){
        // cout<<line<<" "<<endl;
        getline(myFile, line); //get one line from file
        best.genome[i] = stof(line); //save value as float into Indv
    }
    best.fitness = 0.0;

    //call experiments/tests
    diachronicTesting(best);
    // trialedTesting(best);

    cout<<"stuff was written"<<endl;
}