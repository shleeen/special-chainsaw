#include <iostream>
#include "math.h"
#include "random.h"
using namespace std;

const int GENES = 21;

struct Individual{
  float fitness;
  float gene[GENES];
};

void mutate(float (&offspring)[GENES]){
    cout<<"in mutate"<<endl;

    float random_muts[GENES];
    float sum_sq = 0.0;

    float mutation_size = GaussianRandom(0.0, 0.2);
    cout<<"magnitude "<<mutation_size<<endl;

    // # random perturbation for each gene
    for (int i = 0; i<GENES; i++){
      random_muts[i] = GaussianRandom(0.0, 1.0);

      // sum the squares of each random mut
      sum_sq += random_muts[i] * random_muts[i];

      cout<<random_muts[i]<<"\t"<<sum_sq<<"\n";

      // Calc total sum of the sum squares
      // total += sum_sq;
    }

    cout<<"sum "<<sum_sq<<endl;
    sum_sq = sqrt(sum_sq);
    cout<<"sum sqrt "<<sum_sq<<endl;

    // normalize the random muts
    cout<<"\nnormalized: -------------------- "<<endl;
    float norm_total = 0.0;
    for (int j=0; j<GENES; j++){
      random_muts[j] = random_muts[j]/sum_sq;
      norm_total += random_muts[j];
      cout<<random_muts[j]<<endl;
    }
    cout<<"normalized total --> "<<norm_total<<endl;
  
    // calc mutation size based on gauss random nno.

    // actual mutation value
    cout<<"mutated amount: "<<endl;
    for (int i=0; i<GENES; i++){
      offspring[i] += random_muts[i]*mutation_size;

      // clip genes
      if (offspring[i] < 0.0){
        offspring[i] = 0.0;
      }
      else if (offspring[i] > 1.0){
        offspring[i] = 1.0;
      }
      cout<<offspring[i]<<endl;
    }

  // clip genes to (0,1) or (-1,1)
  // genes = [min(1,max(0,gene)) for gene in genes]
}

// pass the min and max
float getRand(float min, float max){
  return (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}


// MAIN FUNCTION
int main() {
    SetRandomSeed(3);

    // generate array with 22 values between (0,1)
    float offspring[GENES] = {0.0579494, 0.115819, -0.0801093, 0.115049, 0.395646, -0.448853, 0.164635, -0.801854, -0.801253, -0.794541, 0.14263, -0.332885, 0.462502, -0.0519415, 0.976606, 0.988133, 0.392469, 0.167125, -0.480957, 0.86343, -0.703071};
    // for (int i=0; i<GENES; i++){
      // offspring[i] = UniformRandom(0.0, 1.0);
      // cout<<offspring[i]<<"\n";
    // }
    // cout<<endl;

    // mutate the offspring
    mutate(offspring);

    // offpsring after mutation
    // cout<<"\nMutated offspring is: "<<endl;
    // for (int i=0; i<GENES; i++){
    //     cout<<offspring[i]<<"\n";
    // }
    // cout<<endl;


  cout<<"the end"<<endl;
}