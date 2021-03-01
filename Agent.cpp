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
    motor_weight = 0.0;
    self_pos_weight = 0.0;
    target_weight = 0.0;
    
    //  DO I NEED TO RANDOMIZE
    // c.RandomizeCircuitState(-0.5,0.5); //whats the range
}

// map values from [0,1] to [x,y]
void Agent::decodeGenome(float genome[GENES], float (&decoded)[GENES]){

    for (int i =0; i<GENES; i++){
        decoded[i] = GENES_RANGE[i].min + ((GENES_RANGE[GENES].max - GENES_RANGE[GENES].min) / (1 - 0)) * (genome[i] - 0);
    }

}

//decode the genome & set the agent up with the params
// also set the location/motor values
void Agent::updateNeuronParams(float genome[GENES]){

    float decoded[GENES];
    decodeGenome(genome, decoded);

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
    motor_weight = decoded[19];
    target_weight = decoded[20];
    self_pos_weight = decoded[21];
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

float Agent::getMotorWeight(){
    return motor_weight;
}

double Agent::getState(int index){
    return c.NeuronState(index);
}

double Agent::getOutput(int index){
    return c.NeuronOutput(index);
}