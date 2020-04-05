#ifndef BRANCH_H
#define BRANCH_H

#include "header.h"

using namespace std;

bool executeBranchCommand(string mnemonic, string op1, string op2, map<string, string> &registers, map<char, bool> &flags, map<string, pair<string, int>> &memory, map<string, pair<string, int>> :: iterator &itr) {
    
    if(mnemonic == "JMP") {
        if(validMemory(op1) && op2 == "") {
            itr = memory.find(op1);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JZ") {
        if(validMemory(op1) && op2 == "") {
            if(flags['Z']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JNZ") {
        if(validMemory(op1) && op2 == "") {
            if(!flags['Z']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JC") {
        if(validMemory(op1) && op2 == "") {
            if(flags['C']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JNC") {
        if(validMemory(op1) && op2 == "") {
            if(!flags['C']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JP") {
        if(validMemory(op1) && op2 == "") {
            if(!flags['S']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JM") {
        if(validMemory(op1) && op2 == "") {
            if(flags['S']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JPE") {
        if(validMemory(op1) && op2 == "") {
            if(flags['P']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "JPO") {
        if(validMemory(op1) && op2 == "") {
            if(!flags['P']) {
                itr = memory.find(op1);
            }
            else {
                ++itr;
            }
        }

        else {
            return false;
        }
    }

    return true;    
}

#endif