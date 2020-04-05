#ifndef UTIL_H
#define UTIL_H

#include "header.h"

using namespace std;

string getAddressFromRegPair(string reg1, string reg2, map<string, string> registers) {
    return (registers[reg1] + registers[reg2]);
}

string hexAddition(string n1, string n2) {
    stringstream ss1, ss2, ss3;
    int x, y;
    string result;

    ss1 << hex << n1;
    ss1 >> x;

    ss2 << hex << n2;
    ss2 >> y;
    x += y;

    ss3 << hex << x;
    result = ss3.str();

    for(int i=0; i<2; i++) {
        if(result[i] >= 'a' & result[i] <= 'f') {
            result[i] -= 32; 
        }
    }
    
    return result;
}

string hexSubtraction(string n1, string n2) {
    stringstream ss1, ss2, ss3;
    int x, y;
    string result;

    ss1 << hex << n1;
    ss1 >> x;

    ss2 << hex << n2;
    ss2 >> y;
    x -= y;

    ss3 << hex << x;
    result = ss3.str();
    
    for(int i=0; i<2; i++) {
        if(result[i] >= 'a' & result[i] <= 'f') {
            result[i] -= 32; 
        }
    }
    
    return result;
}

int compareData(string num1, string num2) {
    if(num1 == num2)
        return 0;
    int n1 = stoul(num1, nullptr, 16);
    int n2 = stoul(num2, nullptr, 16);

    if(n1 < n2) {
        return 1;
    }

    else {
        return -1;
    }
}

#endif