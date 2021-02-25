// file to use best agent from evolution, and then run simulations

#include "main.h"
// #include "CTRNN.h"
// #include "Agent.h"
// #include "Plot.h"

const int TRIALS = 2500;
const float TARGET_MAX = 0.5; 
const float TARGET_MIN = 1.0;
const int NO_OF_TARGETS = 50; // target_max - target_min/no_of_targets => interval between points selected



int main(int argc, char* argv[]){
    // open file
    // read in agent info
    Individual best;

    Agent sender(NEURONS, GENES); //sender
    Agent receiver(NEURONS, GENES); //receiver
    receiver.updateTargetSensor(-1); //target sensor value for receiver is fixed

    // set both Agents params with Best Indv's genome
    sender.updateNeuronParams(best.genome);
    sender.updateNeuronParams(best.genome);

    float target = randomNumberUniform(0.5, 1.0);

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
        // TODO: only save data of the fittest trial?
        // p.storeData(bee1.getSelfPosition(), time);
    }

}