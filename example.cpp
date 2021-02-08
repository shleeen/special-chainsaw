// ***************************************
// A very simple example program for CTRNN
// ***************************************

#include "CTRNN.h"


// Global constants
const double RunDuration = 250;
const double StepSize = 0.01;

// The main program
int main(int argc, char* argv[])
{
    // Set up the circuit
    CTRNN c(2);
    c.SetNeuronBias(1, -2.75); 
    c.SetNeuronBias(2, -1.75);
    c.SetConnectionWeight(1, 1, 4.5);
    c.SetConnectionWeight(1, 2, -1);
    c.SetConnectionWeight(2, 1, 1);
    c.SetConnectionWeight(2, 2, 4.5);
  
    // Run the circuit
    // random initial states or outputs uniformly distributed over a given range
    c.RandomizeCircuitState(-0.5,0.5);

    //view outputs on terminal
    cout<< "time " <<"N1-output "<<"N2-output "<<endl;
    cout << 0.0 << " " << c.NeuronOutput(1) << " " << c.NeuronOutput(2) << endl;

    // loop where the appropriate CTRNN state update function is called repeatedly
    cout<<"-------- entering loop";
    for (double time = StepSize; time <= RunDuration; time += StepSize) {
        
        // check environment, make update based on that???
        c.EulerStep(StepSize);
        cout << time << " " << c.NeuronOutput(1) << " " << c.NeuronOutput(2) << endl;
    }

    cout<< "time " <<"N1-output "<<"N2-output "<<endl;
    
    // Finished
    return 0;
}
