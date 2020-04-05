#ifndef LOGICAL_H
#define LOGICAL_H

#include "header.h"
#include "util.h"

using namespace std;

bool executeLogicalCommand(string mnemonic, string op1, string op2, map<string, string> &registers, map<char, bool> &flags, map<string, pair<string, int>> &memory) {
    
    if(mnemonic == "CMA") {
        if(op1 == "" && op2 == "") {
            string res = hexSubtraction("FF", registers["A"]);
            res = string(2 - res.length(), '0').append(res);
            registers["A"] = res;
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "CMP") {
        if(validRegister(op1) && op2 == "") {
            int res = compareData(registers["A"],registers[op1]);
            if(res == 0) {
                flags['Z'] = true;
            }
            else if(res == 1) {
                flags['C'] = true;
            }
            else {
                flags['C'] = false;
                flags['Z'] = false; 
            }
        }

        else if(op1 == "M" && op2 == "") {
            string mem = getAddressFromRegPair("H", "L", registers);
            int res = compareData(registers["A"], memory[mem].first);
            if(res == 0) {
                flags['Z'] = true;
            }
            else if(res == 1) {
                flags['C'] = true;
            }
            else {
                flags['C'] = false;
                flags['Z'] = false; 
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "CPI") {
        if(validData(op1) && op2 == "") {
            int res = compareData(registers["A"], op1);
            if(res == 0) {
                flags['Z'] = true;
            }
            else if(res == 1) {
                flags['C'] = true;
            }
            else {
                flags['C'] = false;
                flags['Z'] = false; 
            }
        }
    }

    else if(mnemonic == "STC") {
        if(op1 == "" && op2 == "") {
            flags['C'] = true;
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "CMC") {
        if(op1 == "" && op2 == "") {
            flags['C'] = !flags['C'];
        }

        else {
            return false;
        }
    }

    return true;    
}

#endif