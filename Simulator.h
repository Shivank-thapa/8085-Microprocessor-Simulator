#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "header.h"
#include "size.h"
#include "command.h"
using namespace std;

/*  Class for creating an instance of simulator
    The 8085 simulator has memory, flags, PC, registers */
class Simulator {
    private:
        map<string, pair<string, int>> memory;
        map<string, string> registers;
        map<char, bool> flags;
        string PC;
    public:
        Simulator();
        void initRegisters();
        void initFlags();
        void setPC(string);
        string getPC();
        void updatePC(int);
        void loadProgramInMemory(string);
        void execute(string);
        void printState();
};

#endif