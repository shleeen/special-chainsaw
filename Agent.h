#include "CTRNN.h"

// maybe dont hardcoded this (scream)
const int GENES = 18 + 4;

struct range{
    float min;
    float max;
};

// chromosome = tau1 | bias1 | gain1 | weight11 | weight12 | weight13 | tau2 | bias2 | gain2 | weight21 | weight22 | weight23 | tau3 | bias3 | gain3 | weight31 | weight32 | weight33 | 
//              contact_weight | motor_weight | self-pos_weight | target_weight 
const range GENES_RANGE[GENES] = {{ .min = 0.0, .max = 30.0 },  { .min = -16.0, .max = 16.0 },  { .min = -16.0, .max = 16.0 },  { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, 
                                { .min = 0.0, .max = 30.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 },
                                { .min = 0.0, .max = 30.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 }, { .min = -16.0, .max = 16.0 },
                                { .min = -16.0, .max = 16.0 }, //contact weight
                                { .min = -16.0, .max = 16.0 }, //motor weight
                                { .min = -16.0, .max = 16.0 }, //self position weight
                                { .min = -16.0, .max = 16.0 }, //target weight
                                };


class Agent {
    private:
        CTRNN c;
        int neurons_count;
        int genes_count;

        // input to neuron 3
        // absolute location along the 1D environment.
        float self_position; 
        // input to neuron 1
        // contact sensor length is 0.2 units
        // discrete signal - on (1) if the agent is in contact with the other agent and is off (0) otherwise
        int contact_sensor; 
        // input to neuron 2
        // a relative measure of the sender’s distance to the target.
        // The receiver also has this sensor, but its value is fixed to -1.
        float target_sensor;
        // input to neuron 1
        // float motor;
        float contact_weight;
        float motor_weight;
        float self_pos_weight;
        float target_weight;

    public:        
        // constructor
        Agent(int neurons, int genes);

        float getSelfPosition();
        int getContactSensor();
        float getTargetSensor();
        float getMotorWeight();
        double getState(int index);
        double getOutput(int index);

        void stepAgent(double timestep);

        void decodeGenome(float genome[GENES], float (&decoded)[GENES]);
        void updateNeuronParams(float genome[GENES]);
        void updateSelfPosition(float new_location);
        void updateContactSensor(int value);
        void updateTargetSensor(float target_range);
};