#include "Simulator.h"
#include "header.h"

using namespace std;


/* Constructor for Simulator class */
Simulator :: Simulator() {
    initRegisters();
    initFlags();
    setPC("0000");
}


/* Initialise all registers with default value 0 */
void Simulator :: initRegisters() {
    registers.insert({"A", "00"});
    registers.insert({"B", "00"});
    registers.insert({"C", "00"});
    registers.insert({"D", "00"});
    registers.insert({"E", "00"});
    registers.insert({"H", "00"});
    registers.insert({"L", "00"}); 
}


/* Initialise all flags with default value false */
void Simulator :: initFlags() {
    flags.insert({'S', false});
    flags.insert({'Z', false});
    flags.insert({'P', false});
    flags.insert({'C', false});
    flags.insert({'A', false});
}


/* Setter function for Program Counter */
void Simulator :: setPC(string addr) {
    PC = addr;
}


/* Getter function for Program Counter */
string Simulator :: getPC() {
    return PC;
}


/* Function to update program counter after each instruction */
void Simulator :: updatePC(int mnemonicSize) {   
    stringstream ss1, ss2;
    int decimalValuePC;
    ss1 << hex << PC;
    ss1 >> decimalValuePC;

    decimalValuePC += mnemonicSize;

    ss2 << hex << decimalValuePC;
    PC = ss2.str();

    for(int i=0; i<4; i++) {
        if(PC[i] >= 'a' & PC[i] <= 'f') {
            PC[i] -= 32; 
        }
    }
}


/* Load a program from input file to memory starting from the specified address */
void Simulator :: loadProgramInMemory(string filename) {
    int lineCount = 1, mnemonicSize;
    string instruction, mnemonic;
    ifstream infile(filename);
    if(infile.is_open()) {
        while(getline(infile, instruction)) {
            if(!validMemory(PC)) {
                cerr << "Error at line number " << lineCount << ". Program does not fit in memory!" << endl;
                exit(0);
            }
            if(instruction.find(' ') == -1)                                     // if no operand is present
                mnemonic = instruction;
            else
                mnemonic = instruction.substr(0, instruction.find(' '));        // if any operand is present
            memory[PC] = make_pair(instruction, 0);                             // insert current instruction in memory
            
            mnemonicSize = getMnemonicSize(mnemonic);
            if(mnemonicSize == 0) {
                cerr << "Error at line number " << lineCount << ". Invalid mnemonic found: \'" << mnemonic << "\'" << endl;  
                exit(0);
            }

            updatePC(mnemonicSize);                                             // update PC to point to next address
            lineCount++;
        }
    }
    else {
        cerr << "Error in opening file!" << endl;
    }
}


/* Execute the loaded program from memory */
void Simulator :: execute(string startAddr) {
    int lineCount = 1, position;
    string instruction, mnemonic, operand1, operand2;
    bool flag = true;
    map<string, pair<string, int>> :: iterator itr;

    for(itr = memory.begin(); itr != memory.end(); ) {
        instruction = "";
        mnemonic = "";
        operand1 = "";
        operand2 = "";

        if(itr->second.second == 0) {
            instruction = itr->second.first;
            
            // snippet to find mnemonic and operands from the instruction
            position = instruction.find(' ');
            if(position == -1) {
                mnemonic = instruction;
                operand1 = "";
                operand2 = "";
            }
            else {
                mnemonic = instruction.substr(0, position);
                instruction = instruction.substr(position+1);
                position = instruction.find(',');
                if(position == -1) {
                    operand1 = instruction.substr(0, position);
                    operand2 == "";
                }
                else {
                    operand1 = instruction.substr(0, position);
                    operand2 = instruction.substr(position+1);
                }
            }

            if(mnemonic == "HLT") {
                break;
            }

            char type = getOperationType(mnemonic);                               // check type of operation to be performed
            
            //  perform operation depending on type of the mnemonic
            if(type == 'l') {                                                 
                flag = executeLogicalCommand(mnemonic, operand1, operand2, registers, flags, memory);
                ++itr;
            }
            else if(type == 'm') {
                flag = executeMoveCommand(mnemonic, operand1, operand2, registers, flags, memory);
                ++itr;
            }
            else if(type == 'a') {
                flag = executeArithmeticCommand(mnemonic, operand1, operand2, registers, flags, memory);
                ++itr;
            }
            else if(type == 'b'){
                flag = executeBranchCommand(mnemonic, operand1, operand2, registers, flags, memory, itr);
            }

            if(!flag) {
                cerr << "Error occured at line number " << lineCount << ". Exiting!" << endl;
                exit(0);
            }
            lineCount++;
        }
        else {
            ++itr;
        }
    }
}


/* Print state of simulator: memory, registers and flag status */
void Simulator :: printState() {
    
    //Register values
    cout << "-----REGISTERS-----" << endl;
    map<string, string> :: iterator itr; 
    itr = registers.begin();
    while(itr != registers.end()) {
        cout << itr->first << " " << itr->second << endl;
        itr++;
    }

    cout << endl;
    //Flag values
    cout << "-----FLAGS-----" << endl;
    map<char, bool> :: iterator itr2;
    itr2 = flags.begin();
    while(itr2 != flags.end()) {
        cout << itr2->first << " " << itr2->second << endl;
        itr2++;
    }
    
    cout << endl;
    //Memory content
    cout << "-----MEMORY-----" << endl;
    map<string, pair<string, int>> :: iterator itr3;
    itr3 = memory.begin();
    while(itr3 != memory.end()) {
        cout << itr3->first << " " << itr3->second.first << endl;
        itr3++;
    }

    cout << endl;
    //Program Counter
    cout << "-----PROGRAM COUNTER-----" << endl;
    cout << "PC = " << PC << endl;
}