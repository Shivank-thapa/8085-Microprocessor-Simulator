#ifndef SIZE_H
#define SIZE_H

#include "header.h"
using namespace std;

int getMnemonicSize(string mnemonic) {
    if(mnemonic == "ADD" || mnemonic == "SUB" || mnemonic == "MOV" || mnemonic == "INR" || mnemonic == "DCR" || mnemonic == "INX" || mnemonic == "DCX" || mnemonic == "XCHG" || mnemonic == "SET" || mnemonic == "CMA" ||
       mnemonic == "STAX" || mnemonic == "LDAX" || mnemonic == "DAD" || mnemonic == "CMP" || mnemonic == "HLT" || mnemonic == "STC" || mnemonic == "CMC")
        return 1;
    else if(mnemonic == "ADI" || mnemonic == "SUI" || mnemonic == "MVI" || mnemonic == "CPI")
        return 2;
    else if(mnemonic == "LDA" || mnemonic == "STA" || mnemonic == "JMP" || mnemonic == "JZ" || mnemonic == "JNZ" || mnemonic == "JC" || mnemonic == "JNC" || mnemonic == "LHLD" || mnemonic == "SHLD" ||
        mnemonic == "LXI" || mnemonic == "JP" || mnemonic == "JM" || mnemonic == "JPE" || mnemonic == "JPO")
        return 3;
    else
        return 0;
}

#endif