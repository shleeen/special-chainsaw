#include <fstream>
#include <list>
#include <string>

#include "CTRNN.h"

using namespace std;


// i cant believe i have to create a class to plot stuff
class Plot{
    public:
        fstream fout;

        list<float> sender;
        list<float> time;

        CTRNN best_agent();

        // float target[100];
        // float sender[100];
        // float timestep[100];

        // Plot(){
        //     // open file ??
        // }

        // ~Plot(){
        //     //close file at the end of the main program
        // }

        void storeData(float target_val, float timestep);
        void writeCSV(int trial);
};



void Plot::writeCSV(int trial){
    string filename = "data"+ to_string(trial) +".csv";
    fout.open(filename, ios::out);

    // insert target data
    // fout<<"Name"<<","<<"College"<<","<<"Class"<<","<<"Roll no"<<"\n";
    // for (int i=0; i<100; i++){
    //     fout<<sender[i]<<","<<time[i]<<"\n";
    // }
    // for (auto const &v : sender){
    //     fout<< v;
    // }

    // Create iterator pointing to first element
    list<float>::iterator it_s = sender.begin();
    list<float>::iterator it_t = time.begin();

                // // Advance the iterator by 2 positions,
                // std::advance(it_s, 2);
                // // Now iterator it points to 3rd element
                // std::cout << "3rd element = " << *it << std::endl;
                // /**** Finding nth element using std::next() ******/
                // // Find 3rd element from list
                // // It returns a new iterator pointing to n position after the
                // // base iterator given as first argument
                // auto it1 = std::next(listOfStrs.begin(), 2);
                // std::cout << "3rd element = " << *it1 << std::endl;

    int i = 0;
    while (i <100){
        fout<< *it_s <<", "<<*it_t<<"\n";

        advance(it_s, 1);
        advance(it_t, 1);

        i++;
    }


    fout.close();   // closing csv file
}

void Plot::storeData(float sender_val, float timestep){
    sender.push_back(sender_val);
    time.push_back(timestep);
}