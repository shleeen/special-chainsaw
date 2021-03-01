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
        list<float> receiver;
        list<float> time;
        float target;

        CTRNN best_agent();

        void storeData(float target_val, float timestep);
        void storeDataFig8(float sender_val, float receiver_val, float timestep);
        void writeCSV(int trial);
        void writeFig8();

};



void Plot::writeCSV(int trial){
    string filename = "data"+ to_string(trial) +".csv";
    fout.open(filename, ios::out);

    // Create iterator pointing to first element
    list<float>::iterator it_s = sender.begin();
    list<float>::iterator it_t = time.begin();

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


void Plot::storeDataFig8(float sender_val, float receiver_val, float timestep){
    sender.push_back(sender_val);
    receiver.push_back(receiver_val);
    time.push_back(timestep);
}


void Plot::writeFig8(){
    string filename = "fig8.csv";
    fout.open(filename, ios::out);

    // Create iterator pointing to first element
    list<float>::iterator it_s = sender.begin();
    list<float>::iterator it_r = receiver.begin();
    list<float>::iterator it_t = time.begin();

    int i = 0;
    while (i <100){
        fout<< *it_t <<", "<< target <<", "<< *it_s <<", "<< *it_r <<"\n";

        advance(it_s, 1);
        advance(it_r, 1);
        advance(it_t, 1);

        i++;
    }

    fout.close();   // closing csv file
}