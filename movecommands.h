#ifndef MOVE_H
#define MOVE_H

#include "header.h"
#include "validate.h"
#include "util.h"

using namespace std;

/* Instructions for loading, storing and moving data between registers or/and memory*/

bool executeMoveCommand(string mnemonic, string op1, string op2, map<string, string> &registers, map<char, bool> &flags, map<string, pair<string, int>> &memory) {
    if(mnemonic == "SET") {
        if(validMemory(op1) && validData(op2)) {
            memory[op1] = make_pair(op2, -1);
        }
        else
            return false;
    }

    else if(mnemonic == "MOV") {
        if(validRegister(op1) && validRegister(op2)) {
            registers[op1] = registers[op2];
        }
        else if(op1 == "M" && validRegister(op2)) {
            string mem = getAddressFromRegPair("H", "L", registers);
            memory[mem] = make_pair(registers[op2], -1);
        }
        else if(validRegister(op1) && op2 == "M") {
            string mem = getAddressFromRegPair("H", "L", registers);
            if(memory.find(mem) != memory.end()) 
                registers[op1] = memory[mem].first; 
            else
                registers[op1] = "00";
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "MVI") {
        if(validRegister(op1) && validData(op2)) {
            registers[op1] = op2;
        }
        else if(op1 == "M" && validData(op2)) {
            string mem = getAddressFromRegPair("H", "L", registers);
            memory[mem] = make_pair(op2, -1);
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "LDA") {
        if(validMemory(op1) && op2 == "") {
            registers["A"] = memory[op1].first;
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "STA") {
        if(validMemory(op1) && op2 == "") {
            memory[op1] = make_pair(registers["A"], -1);
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "XCHG") {
        if(op1 == "" && op2 == "") {
            string tmp;
            tmp = registers["D"];
            registers["D"] = registers["H"];
            registers["H"] = tmp;

            tmp = registers["E"];
            registers["E"] = registers["L"];
            registers["L"] = tmp;
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "LHLD") {
        if(validMemory(op1) && op2 == "") {
            registers["L"] = memory[op1].first;
            registers["H"] = memory[hexAddition(op1, "1")].first;
        }
        else {
            return false;
        }
    } 

    else if(mnemonic == "SHLD") {
        if(validMemory(op1) && op2 == "") {
            memory[op1] = make_pair(registers["L"], -1);
            memory[hexAddition(op1, "1")] = make_pair(registers["H"], -1);
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "LXI") {
        if(validateRegisterPair(op1) && validMemory(op2)) {
            registers[op1] = op2.substr(0,2);
            if(op1 == "B") {
                registers["C"] = op2.substr(2);
            }
            else if(op1 == "D") {
                registers["E"] = op2.substr(2);
            }
            else {
                registers["L"] = op2.substr(2);
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "STAX") {
        string mem;
        if((op1 == "B" || op1 == "D") && op2 == "") {
            if(op1 == "B") {
                mem = getAddressFromRegPair("B", "C", registers);
            }
            else {
                mem = getAddressFromRegPair("D", "E", registers);
            }
            memory[mem] = make_pair(registers["A"], -1);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "LDAX") {
        string mem;
        if((op1 == "B" || op1 == "D") && op2 == "") {
            if(op1 == "B") {
                mem = getAddressFromRegPair("B", "C", registers);
            }
            else {
                mem = getAddressFromRegPair("D", "E", registers);
            }
            if(validMemory(mem)) {
                registers["A"] = memory[mem].first;
            }
            else {
                return false;
            }
        }

        else {
            return false;
        }
    }

    return true;    
}

#endif