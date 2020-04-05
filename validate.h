#ifndef VALIDATE_H
#define VALIDATE_H

#include "header.h"

using namespace std;

/* Validate memory address to be in range from 0000 to FFFF */ 
bool validMemory(string address) {
    if(address.length() != 4)
        return false;
    for(int i=0; i<4; i++) {
        if((address[i] >= 'A' && address[i] <= 'F') || (address[i] >= '0' && address[i] <= '9'))
            continue;
        else
            return false;
    }
    return true;
}

/* Validate data to be in range from 00 to FF */
bool validData(string data) {
    if(data.length() != 2)
        return false;
    for(int i=0; i<2; i++) {
        if((data[i] >= 'A' && data[i] <= 'F') || (data[i] >= '0' && data[i] <= '9'))
            continue;
        else
            return false;
    }
    return true;
}


/* Validate register to be either A,B,C,D,E,H or L */
bool validRegister(string reg) {
    if(reg == "A" || reg == "B" || reg == "C" || reg == "D" || reg == "E" || reg == "H" || reg == "L")
        return true;
    return false;
}


/* Validate type of operation type */
bool validateOperation(char op) {
    switch(op) {
        case 'm':
        case 'l':
        case 'b':
        case 'a':
            return true;
        default:
            return false;
    }
}


/* Validate register pair */
bool validateRegisterPair(string reg) {
    if(reg == "B" || reg == "D" || reg == "H")
        return true;
    return false;
}

#endif