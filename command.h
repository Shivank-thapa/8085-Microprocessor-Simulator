#ifndef COMMAND_H
#define COMMAND_H

#include "logicalcommands.h"
#include "arithmeticcommands.h"
#include "movecommands.h"
#include "branchcommands.h"

using namespace std;

char getOperationType(string mnemonic) {
    if(mnemonic == "LDA" || mnemonic == "STA" || mnemonic == "MOV" || mnemonic == "MVI" || mnemonic == "LHLD" || mnemonic == "SHLD" || mnemonic == "LXI" || mnemonic == "XCHG" || mnemonic == "SET" || mnemonic == "STAX" || mnemonic == "LDAX")
        return 'm';
    else if(mnemonic == "ADD" || mnemonic == "SUB" || mnemonic == "INR" || mnemonic == "DCR" || mnemonic == "ADI" || mnemonic == "SUI" || mnemonic == "INX" || mnemonic == "DCX" || mnemonic == "DAD")
        return 'a';
    else if(mnemonic == "CMA" || mnemonic == "CMP" || mnemonic == "CPI" || mnemonic == "CMC" | mnemonic == "STC")
        return 'l';
    else if(mnemonic == "JMP" || mnemonic == "JC" || mnemonic == "JNC" || mnemonic == "JZ" || mnemonic == "JNZ" || mnemonic == "JP" || mnemonic == "JM" || mnemonic == "JPE" || mnemonic == "JPO")
        return 'b';
    return 'x';
}

#endif