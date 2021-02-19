#include "Agent.h"


// constructor
Agent::Agent(int neurons, int genes){
    neurons_count = neurons;
    genes_count = genes;

    c.SetCircuitSize(neurons);

    self_position = 0.0;
    contact_sensor = 0.0;
    target_sensor = 0.0;
    motor = 0.0;

    c.RandomizeCircuitState(-0.5,0.5); //whats the range
}

//decode the genome & set the agent up with the params
// also set the location/motor values
void Agent::updateNeuronParams(float genome[GENES]){

    // float real_values = decodeGenome();

    int offset = 0; // 3+3=6

    for (int i=1; i<=neurons_count; i++){
        c.SetNeuronTimeConstant(i, genome[offset]);
        c.SetNeuronBias(i, genome[offset+1]);
        c.SetNeuronGain(i, genome[offset+2]);
        c.SetConnectionWeight(i, 1, genome[offset+3]);
        c.SetConnectionWeight(i, 2, genome[offset+4]);
        c.SetConnectionWeight(i, 3, genome[offset+5]);
        offset += 6;
    }

}


// Run the one step of the circuit !!
void Agent::stepAgent(double timestep){
    c.EulerStep(timestep);
}

void Agent::updateContactSensor(int value){
    contact_sensor = value;
    c.SetNeuronExternalInput(1, contact_sensor);
}

void Agent::updateTargetSensor(float target_range){
    target_sensor = target_range;
    c.SetNeuronExternalInput(2, target_sensor);
}

void Agent::updateSelfPosition(float new_location){
    self_position = new_location;
    c.SetNeuronExternalInput(3, self_position);
}

void Agent::updateMotor(){
    // c().SetNeuronExternalInput(1, motor);
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

float Agent::getMotor(){
    return motor;
}

double Agent::getState(int index){
    return c.NeuronState(index);
}

double Agent::getOutput(int index){
    return c.NeuronOutput(index);
}