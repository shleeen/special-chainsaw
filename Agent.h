#include "CTRNN.h"

const int NEURONS = 3;
const int GENES = (NEURONS+3)*NEURONS;

const int GENERATIONS = 100;
const int POP_SIZE = 10;

const double RUN_DURATION = 250; //what unit is this?
const double TIMESTEP_SIZE = 0.1; // 0.01
const float SPEED = 0.01; //"units per time unit"


class Agent {
    private:
        CTRNN c;
    public:
        // int flag = 0; //0 is sender, 1 is receiver?
        
        float self_position; 
            //input to neuron 3
            // absolute location along the 1D environment.
        float contact_sensor; 
            //inpput to neuron 1
            // discrete signal - on (1) if the agent is in contact with the other agent and is off (0) otherwise
        float target_sensor;
            //input to neuron 2
            // a relative measure of the sender’s distance to the target.
            // The receiver also has this sensor, but its value is fixed to -1.
        float motor; 
            // input to neuron 1
            // oh

        Agent(){
            c.SetCircuitSize(3);

            self_position = 0.0;
            contact_sensor = 0.0;
            target_sensor = 0.0;
            motor = 0.0;
        }

        //constructor
        //decode the genome & set the agent up with the params
        // also set the location/motor values
        Agent(float genome[GENES]){ //param: genome
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
            c.SetNeuronExternalInput(1, contact_sensor);
            c.SetNeuronExternalInput(1, motor);
            c.SetNeuronExternalInput(2, target_sensor);
            c.SetNeuronExternalInput(3, self_position);
        }

        void updateAgentParams(float genome[GENES]);

        // Run the one step of the circuit !! (lol)
        void runAgent(){
            c.RandomizeCircuitState(-0.5,0.5); //should this still be random?
            c.EulerStep(TIMESTEP_SIZE);
        }

        // change the self position of agent
        void moveAgent(float new_location){
            c.SetNeuronExternalInput(3, self_position);
        }

        void updateExternalInput(){
            // contact sensor length 0.2 units
            // on (1) if the agent is in contact with the other agent and is off (0) otherwise.
        }
};