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
    cout<<"DIACHRONIC TEST "<<endl;

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
    sender.updateNeuronParams(best.genome, 1);
    receiver.updateNeuronParams(best.genome, 1);

    // draw starting position of agents
    sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
    receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));
    cout<<"starting pos - > "<<sender.getSelfPosition()<<" "<<receiver.getSelfPosition()<<endl;

    // SIMULATE THE BEES
    for (float time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
        // write position data to file
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
        moveAgent(sender, TIMESTEP_SIZE);
        // clip the senderrrr
        float sender_pos = sender.getSelfPosition();
        if (sender_pos > 0.3){
            sender.updateSelfPosition(0.3);
        }
        else if (sender_pos < 0.0){
            sender.updateSelfPosition(0.0);
        }

        moveAgent(receiver, TIMESTEP_SIZE);
    }

    // close file
    fout.close();

    cout<<"-------------------------------------------- \n";
}


void trialedTesting(Individual best){
    cout<<"TRIALED TESTS "<<endl;

    fstream f6, f7, f9;
    f6.open("data/AbsMeanDist.csv", ios::out);
    f7.open("data/MeanFinalPosition.csv", ios::out);
    f9.open("data/MeanContactTime.csv", ios::out);

    int successful_trials = 0; //counter for counting # of successes
    int num_targets = 0;
    
    // <= TARGET_MAX gives 51 different targets to test against, rather than 50
    for (float target=TARGET_MIN; target<TARGET_MAX; target+=0.01){
        num_targets += 1;

        pl.target = target;
        cout<<" target : "<<target<<endl;

        float mean_dist = 0.0;
        float mean_pos = 0.0;

        float contact_time = 0.0;
        float start_contact = 0.0, end_contact = 0.0;
        float mean_contact_time = 0.0;

        // for each target, do 50 trials
        for (int trials=0; trials<50; trials++){
            // new set of agents for each trial, params initialized to 0
            Agent sender(NEURONS, GENES);
            Agent receiver(NEURONS, GENES);
            receiver.updateTargetSensor(-1);

            // set both Agents params with Best Indv's genome
            // doesnt need to be done multiple times
            sender.updateNeuronParams(best.genome, 1);
            receiver.updateNeuronParams(best.genome, 1);

            // draw starting position of agents
            sender.updateSelfPosition(randomNumberUniform(0.0, 0.3));
            receiver.updateSelfPosition(randomNumberUniform(0.0, 0.3));
            // cout<<"starting pos - > "<<sender.getSelfPosition()<<" "<<receiver.getSelfPosition()<<endl;

            // SIMULATE THE BEES
            for (float time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
                // set input values for c1 - based on where c1 is and where c2 is
                contactAgent(sender, receiver);

                if (sender.getContactSensor() == 1){
                    start_contact = time;
                }
                else{
                    end_contact = time;
                }

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
                
                moveAgent(receiver, TIMESTEP_SIZE);
            }

            // fitness_across_trials[trials] = 1 - (abs(bee2.getSelfPosition() - target));

            float next_dist = receiver.getSelfPosition() - target;
            mean_dist = mean_dist + (next_dist - mean_dist)/(trials+1);

            mean_pos = mean_pos + (receiver.getSelfPosition() - mean_pos)/(trials+1);

            mean_contact_time = mean_contact_time + ((end_contact - start_contact) - mean_contact_time)/(trials+1);

            // check success of trial
            if (abs(receiver.getSelfPosition() - target) < 0.05){ //then its a success
                successful_trials += 1;
            }

        } //end of trials While

        f6<< target << ", " << abs(mean_dist) <<"\n";   
        f7<< target << ", " << mean_pos <<"\n";
        f9<< target << ", " << mean_contact_time <<"\n";

    } //end of Targets While

    f6.close();
    f7.close();

    // cout<<TRIALS<<" "<<num_targets<<" "<<(float)(TRIALS*num_targets)<<endl;
    float success_rate = (float)successful_trials/(float)(TRIALS*num_targets);
    cout<<"50 trials complete for "<<num_targets<<" targets."<<endl;
    cout<<"Success --> "<<success_rate<<" "<<success_rate*100<<endl;
    cout<<"-------------------------------------------- \n";
}



int main(int argc, char* argv[]){
    // open file
    fstream myFile("data/Agent.csv", ios::in);
    Individual best_agent;
    string line;
    for(int i=0; i<GENES; i++){
        // cout<<line<<" "<<endl;
        getline(myFile, line); //get one line from file
        best_agent.genome[i] = stof(line); //save value as float into Indv
    }
    best_agent.fitness = 0.0;

    //call experiments/tests
    diachronicTesting(best_agent);
    // trialedTesting(best_agent);

    cout<<"Data written to file."<<endl;
}