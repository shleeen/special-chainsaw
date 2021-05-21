// file to use best agent from evolution, and then run simulations

#include "main.h"
#include <string>
#include <vector>

// global constants
const int TRIALS = 50;
const float TARGET_MIN = 0.5; 
const float TARGET_MAX = 1.0;


// Function to plot a diachronic look at behaviour of best agent for a single target.
void diachronicTesting(Individual best){
    cout<<"DIACHRONIC TEST "<<endl;

    fstream fout;
    fout.open("data/diachronic.csv", ios::out);
    
    float target = 0.8;
    cout<<" target : "<<target<<endl;

    // new set of agents for each trial, params initialized to 0
    Agent sender(NEURONS, GENES);
    Agent receiver(NEURONS, GENES);
    receiver.updateTargetSensor(-1);

    // set both Agents params with Best Indv's genome
    sender.updateNeuronParams(best.genome, 1);
    receiver.updateNeuronParams(best.genome, 1);

    // draw starting position of agents
    sender.updateSelfPosition(UniformRandom(0.0, 0.3));
    receiver.updateSelfPosition(UniformRandom(0.0, 0.3));

    // update sender target sensor for more accurate plots
    sender.updateTargetSensor(abs(sender.getSelfPosition() - target));

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
        receiver.updateTargetSensor(-1);

        // perform calc for one timestep
        sender.stepAgent(TIMESTEP_SIZE);
        receiver.stepAgent(TIMESTEP_SIZE);

        // update location of c1 - based on motor neuron output
        moveAgent(sender);
        
        // clip the senderrrr
        float sender_pos = sender.getSelfPosition();
        if (sender_pos > 0.3){
            sender.updateSelfPosition(0.3);
        }
        else if (sender_pos < 0.0){
            sender.updateSelfPosition(0.0);
        }

        moveAgent(receiver);
    }

    // close file
    fout.close();

    cout<<"-------------------------------------------- \n";
}




// Function to run multiple trials on the best agent.
void trialedTesting(Individual best){
    cout<<"TRIALED TESTS "<<endl;

    Agent sender(NEURONS, GENES);
    Agent receiver(NEURONS, GENES);

    fstream f6, f7, f9;
    f6.open("data/AbsMeanDist.csv", ios::out);
    f7.open("data/MeanFinalPosition.csv", ios::out);
    f9.open("data/MeanContactTime.csv", ios::out);

    int successful_trials = 0; //counter for counting # of successes
    int num_targets = 0;
    vector<float> final_dists_trials;
    
    // set the first target
    float target = TARGET_MIN;

    // <= TARGET_MAX gives 51 different targets to test against, rather than 50
    for (float i=0; i<50; i++){
        num_targets += 1;

        // target += 0.01;
        // target += 0.005;
        target = 0.8;
        cout<<" target : "<<target<<endl;

        float mean_dist = 0.0, mean_pos = 0.0;

        float start_contact = 0.0, end_contact = 0.0;
        float mean_contact_time = 0.0;

        // for each target, do 50 trials
        for (int trials=0; trials<50; trials++){
            // new set of agents for each trial, params initialized to 0
            sender.resetState();
            receiver.resetState();
            receiver.updateTargetSensor(-1);

            // set both Agents params with Best Indv's genome
            // doesnt need to be done multiple times
            sender.updateNeuronParams(best.genome, 1);
            receiver.updateNeuronParams(best.genome, 1);

            // draw starting position of agents
            sender.updateSelfPosition(UniformRandom(0.0, 0.3));
            receiver.updateSelfPosition(UniformRandom(0.0, 0.3));

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
                receiver.updateTargetSensor(-1);

                // perform calc for one timestep
                sender.stepAgent(TIMESTEP_SIZE);
                receiver.stepAgent(TIMESTEP_SIZE);

                // update location of c1 - based on motor neuron output
                moveAgent(sender);
                
                // clip the senderrrr
                float sender_pos = sender.getSelfPosition();
                if (sender_pos > 0.3){
                    sender.updateSelfPosition(0.3);
                }
                else if (sender_pos < 0.0){
                    sender.updateSelfPosition(0.0);
                }
                
                moveAgent(receiver);
            }

            float next_dist = abs(receiver.getSelfPosition() - target);
            mean_dist = mean_dist + (next_dist - mean_dist)/(trials+1);

            mean_pos = mean_pos + (receiver.getSelfPosition() - mean_pos)/(trials+1);

            final_dists_trials.push_back(next_dist); //keep track of all the final distances of receiver

            // check success of trial
            if (abs(receiver.getSelfPosition() - target) <= 0.05){ //then its a success
                successful_trials += 1;
            }

        } //end of trials While

        f6<< target << ", " << mean_dist <<"\n";   
        f7<< target << ", " << mean_pos <<"\n";
        f9<< target << ", " << abs(mean_contact_time) <<"\n";

    } //end of Targets While

    f6.close();
    f7.close();

    // cout<<TRIALS<<" "<<num_targets<<" "<<(float)(TRIALS*num_targets)<<endl;
    float success_rate = (float)successful_trials/(float)(TRIALS*num_targets);
    cout<<"50 trials complete for "<<num_targets<<" targets."<<endl;
    cout<<"Success --> "<<success_rate<<" "<<success_rate*100<<endl;
    cout<<"-------------------------------------------- \n";

    // calculating mean and std of the dist b/w receiver final pos and target, over ALL the trials
    float total = 0.0, sum_sq = 0.0;
    int total_trials = final_dists_trials.size();
    for (int k=0; k<total_trials; k++){
        total += final_dists_trials[k];
    }
    float abs_mean = total/total_trials;
    for (int k=0; k<total_trials; k++){
        sum_sq += ( (final_dists_trials[k] - abs_mean)*(final_dists_trials[k] - abs_mean) );
    }
    float std = sqrt(sum_sq/total_trials);

    cout<<"Absolute mean distance of 2500 trials: "<<abs_mean<<endl;
    cout<<"Standard deviation of 2500 trials: "<<std<<endl;
    cout<<"-------------------------------------------- \n";
}



int main(int argc, char* argv[]){
    SetRandomSeed(964); //964
// 32536
    // open file
    fstream myFile("data/Agent.csv", ios::in);
    Individual best_agent;
    string line;
    for(int i=0; i<GENES; i++){
        getline(myFile, line); //get one line from file
        best_agent.genome[i] = stof(line); //save value as float into Indv
    }
    best_agent.fitness = 0.0;

    // call experiments/tests
    diachronicTesting(best_agent);
    // multipleDiachronic(best_agent);
    trialedTesting(best_agent);

    // -------------------------------------------------------------------
    cout<<"-------- OVERALL BEST AGENT --------\n";

    fstream overall("data/OverallBestAgent.csv", ios::in);
    Individual best_overall;
    string line2;
    for(int i=0; i<GENES; i++){
        getline(overall, line2); //get one line from file
        best_overall.genome[i] = stof(line2); //save value as float into Indv
    }

    // call experiments/tests
    diachronicTesting(best_overall);
    trialedTesting(best_overall);

    cout<<"Data written to file."<<endl;
}