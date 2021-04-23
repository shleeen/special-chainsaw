// ***************************************************
// A very simple example program for the TSearch class
// ***************************************************

#include "TSearch.h"
#include "main.h"


// A simple 2D inverted quadratic evaluation function
// -- need to use random state in any random number generation in evaluation >_<
double Evaluate(TVector<double> &v, RandomState &){
	double p1 = MapSearchParameter(v[1],-10,10), 
         p2 = MapSearchParameter(v[2],-10,10);
  return 200-(p1*p1+p2*p2);

  // --- do the CTRNN simulation and return fitness?
  // Individual indv;

  // for (int i = 1; i<v.Size(); i++){
  // cout<<"here "<<v(1)<<" "<<v(22)<<endl;
  // so each v is one value of genome... but now to make it make sense as params on the CTRNN
  // }

/*
  Agent bee1(NEURONS, GENES); //sender
  Agent bee2(NEURONS, GENES); //receiver
  bee2.updateTargetSensor(-1); //target sensor value for receiver is fixed

  // set Agent params according to the genome
  bee1.updateNeuronParams(indv.genome);
  bee2.updateNeuronParams(indv.genome);

  int trials = 0;
  float fitness_across_trials[20];

  while (trials < 20){
    // draw target from uniform random distribution in range [0.5, 1.0]
    float target = randomNumberUniform(0.5, 1.0);

    // draw the pos of bees from uniform random distribution in range of [0, 0.3]
    bee1.updateSelfPosition(randomNumberUniform(0.0, 0.3));
    bee2.updateSelfPosition(randomNumberUniform(0.0, 0.3));

    // SIMULATE THE BEES
    for (double time = TIMESTEP_SIZE; time <= RUN_DURATION; time += TIMESTEP_SIZE) {
      // set input values for c1 - based on where c1 is and where c2 is
      contactAgent(bee1, bee2);

      // update relative dist to target
      float dist_to_target = abs(bee1.getSelfPosition() - target);
      bee1.updateTargetSensor(dist_to_target);

      // perform calc for one timestep
      bee1.stepAgent(TIMESTEP_SIZE);
      bee2.stepAgent(TIMESTEP_SIZE);

      // update location of c1 - based on motor neuron output
      moveAgent(bee1);
      moveAgent(bee2);
    }
    // update fitness of indv
    fitness_across_trials[trials] = max(0.0 , 1.0 - (abs(bee2.getSelfPosition() - target)));
            
    trials++;
  }

  // rank based fitness overall calc
  return (double)calcFitnessOverTrials(fitness_across_trials);
  */
 return 0.0;
}


// The main program

int main (int argc, const char* argv[]) {
  TSearch s(21);

  // Configure the search
  s.SetRandomSeed(3);
  s.SetEvaluationFunction(Evaluate);
  s.SetSelectionMode(RANK_BASED);
  s.SetReproductionMode(GENETIC_ALGORITHM);
  s.SetPopulationSize(50);
  s.SetMaxGenerations(5000);
  s.SetMutationVariance(0.2);
  // s.SetCrossoverProbability(0); //does this stop crossover?
  // s.SetCrossoverMode(TWO_POINT); //need to remove crossover
  s.SetMaxExpectedOffspring(1.1);
  s.SetElitistFraction(0.1); //remove this?
  s.SetSearchConstraint(1);
  s.SetCheckpointInterval(5);
    
  // Run the search
  s.ExecuteSearch();
  
  // Display the best individual found
  cout << s.BestIndividual() << endl;

  return 0;
}