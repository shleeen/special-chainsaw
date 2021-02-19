#include "CTRNN.h"

const int GENES = 18;

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
        float motor; 

    public:        
        // constructor
        Agent(int neurons, int genes);

        float getSelfPosition();
        int getContactSensor();
        float getTargetSensor();
        float getMotor();
        double getState(int index);
        double getOutput(int index);

        void stepAgent(double timestep);

        void updateNeuronParams(float genome[GENES]);
        void updateSelfPosition(float new_location);
        void updateContactSensor(int value);
        void updateTargetSensor(float target_range);
        void updateMotor();
};