#include "header.h"
#include "validate.h"
#include "Simulator.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    Simulator sim;
    string filename, addr;

    if(argc > 1) {
        filename = string(argv[1]);
    }
    else {
        cerr << "File path missing! Please enter path for program file!" << endl;
        exit(0);
    }

    while(true) {
        cout << "Enter starting memory address: ";
        cin >> addr;
        if(!validMemory(addr)) {
            cerr << "Please enter a valid memory address!" << endl;
            continue;
        }
        sim.setPC(addr); 
        break;
    }
    sim.loadProgramInMemory(filename);
    sim.execute(addr);
    sim.printState();
    return 0;
}