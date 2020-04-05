/* Methods for manipulation of flag registers */

#ifndef FLAG_H
#define FLAG_H

#include "header.h"

using namespace std;

void checkZeroFlag(string data, map<char, bool> &flags) {
    if(data == "00") {
        flags['Z'] = true;
    }
    else {
        flags['Z'] = false;
    }
}

string checkCarryFlag(string num, map<char, bool> &flags) {
    stringstream ss1, ss2;
    string res;
    int n;

    n = stoul(num, nullptr, 16);
    
    if(n > 255) {
        flags['C'] = true;
        n -= 256;
    }
    else if(n < 0) {
        flags['C'] = true;
        n += 256;
    }

    ss2 << hex << n;
    res = ss2.str();

    res = string(2 - res.length(), '0').append(res);                         // padding result to maintain data length of 2

    for(int i=0; i<2; i++) {
        if(res[i] >= 'a' && res[i] <= 'f')
            res[i] -= 32;
    }

    return res;
}

void checkParityFlag(string accData, map<char, bool> &flags) {
    stringstream ss;
    int num, c=0;
    bool parity = false;

    ss << hex << accData;
    ss >> num;

    while(num) {
        parity = !parity;
        num = num & (num-1);
    }
    if(!parity)
        flags['P'] = true;
    else 
        flags['P'] = false;
}

void checkSignFlag(string accData, map<char, bool> &flags) {
    stringstream ss;
    int num;

    ss << hex << accData;
    ss >> num;

    if(num >= 128) {
        flags['S'] = true;
    }
    else {
        flags['S'] = false;
    }
}

void checkAuxCarryFlag(string d1, string d2, map<char, bool> &flags) {
    string res= hexAddition(d1.substr(d1.length()-1), d2.substr(d2.length()-1));

    int x = stoul(res, nullptr, 16);

    if(x >= 16) {
        flags['A'] = true;
    }
    else {
        flags['A'] = false;
    }
}

#endif