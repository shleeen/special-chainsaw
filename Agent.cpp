#include "Agent.h"


// constructor
Agent::Agent(int neurons, int genes){
    neurons_count = neurons;
    genes_count = genes;

    c.SetCircuitSize(neurons);

    self_position = 0.0;
    contact_sensor = 0.0;
    target_sensor = 0.0;

    contact_weight = 0.0;
    self_pos_weight = 0.0;
    target_weight = 0.0;
    
    // TODO: Do i need to do this, or set it all to 0
    // c.RandomizeCircuitState(-0.5,0.5); // why this range

    for (int i=1; i<=neurons_count; i++){ // since 3 neurons
        c.SetNeuronTimeConstant(i, 0.0);
        c.SetNeuronGain(i, 1.0); //gain always fixed to 1
        c.SetNeuronState(i, 0.0);
    }

}

// Function to reset all values in the Agent object, include CTRNN parameters
void Agent::reset(){
    //sets all the internal CTRNN params to 0
    c.SetCircuitSize(neurons_count);

    // c.RandomizeCircuitState(-0.5, 0.5);

    self_position = 0.0;
    contact_sensor = 0.0;
    target_sensor = 0.0;

    contact_weight = 0.0;
    self_pos_weight = 0.0;
    target_weight = 0.0;

    for (int i=1; i<=neurons_count; i++){
        c.SetNeuronTimeConstant(i, 0.0);
        c.SetNeuronGain(i, 1.0); //gain always fixed to 1
        c.SetNeuronState(i, 0.0);
    }
}

// map values from [0,1] to [x,y]
void Agent::decodeGenome(float genome[GENES], float (&decoded)[GENES]){
    for (int i = 0; i<GENES; i++){
        decoded[i] = GENES_RANGE[i].min + ((GENES_RANGE[i].max - GENES_RANGE[i].min) * (genome[i]));
    }
}

//decode the genome & set the agent up with the params
void Agent::updateNeuronParams(float genome[GENES], int flag){
    float decoded[GENES];

    // if flag is 1, decode
    if (flag == 1){
        decodeGenome(genome, decoded);
    }
    // else don't bound the genome
    else{
        for (int i = 0; i<GENES; i++){
            decoded[i] = genome[i];

            // check lower bound of tau, clip at 0
            if (i == 0 || i == 6 || i == 12 ){
                if (genome[i] < 0){
                    decoded[i] = 0.0;
                }
            }
        }
    }

    int offset = 0; // 3+3=6

    for (int i=1; i<=neurons_count; i++){
        c.SetNeuronTimeConstant(i, decoded[offset]);
        c.SetNeuronBias(i, decoded[offset+1]);
        c.SetNeuronGain(i, 1.0); //gain always fixed to 1
        c.SetConnectionWeight(i, 1, decoded[offset+3]);
        c.SetConnectionWeight(i, 2, decoded[offset+4]);
        c.SetConnectionWeight(i, 3, decoded[offset+5]);
        offset += 6;
    }

    contact_weight = decoded[18];
    self_pos_weight = decoded[19];
    target_weight = decoded[20];
}


// Run the one step of the circuit !!
void Agent::stepAgent(double timestep){
    c.EulerStep(timestep);
}

void Agent::updateContactSensor(int value){
    contact_sensor = value;
    c.SetNeuronExternalInput(1, contact_sensor*contact_weight);
}

void Agent::updateTargetSensor(float target_range){
    target_sensor = target_range;
    c.SetNeuronExternalInput(2, target_sensor*target_weight);
}

void Agent::updateSelfPosition(float new_location){
    self_position = new_location;
    c.SetNeuronExternalInput(3, self_position*self_pos_weight);
}


// --------- Getters
float Agent::getSelfPosition(){
    return self_position;
}

int Agent::getContactSensor(){
    return contact_sensor;
}

float Agent::getTargetSensor(){
    return target_sensor;
}

double Agent::getState(int index){
    return c.NeuronState(index);
}

double Agent::getOutput(int index){
    return c.NeuronOutput(index);
}


ostream& operator<<(ostream& os, Agent agt){    
    cout<<agt.c;
    os<<"\n";
    os << "Self position \t"<< agt.self_position<<"\n";
    os << "Self position weight \t"<< agt.self_pos_weight<<"\n";

    os << "Contact sensor \t"<< agt.contact_sensor<<"\n";
    os << "Contact Sensor weight \t"<< agt.contact_weight<<"\n";

    os << "Target sensor: \t"<< agt.target_sensor<<"\n";
    os << "Target sensor weight: \t"<<agt.target_weight<<"\n";

    return os;
}
