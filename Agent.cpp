#include "Agent.h"

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