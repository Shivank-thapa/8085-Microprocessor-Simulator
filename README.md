# 8085-Microprocessor-Simulator
A simulator for the 8085 microprocessor. 

### Installing

Use git clone from terminal to get a copy of the project.

```
git clone https://github.com/Shivank-thapa/8085-Microprocessor-Simulator.git
```


### Usage

Create you own 8085 program in a text file or start exploring with the programs provided in SamplePrograms folder.

To run a program first build the project and then run the executable file created. Provide the 8085 program file's path as argument to run.

```
g++ main.cpp
./a.exe SampleProgram/OnesComplement.txt
```

### Description

The simulator supports the following instrutions:
* Load and Store
LDA, STA, MOV, MVI, LHLD, SHLD, LXI, XCHG, STAX, LDAX
* Arithmetic
ADD, SUB, ADI, SUI, INR, DCR, INX, DCX, DAD
* Logical
CMA, CPI, CMP, CMC, STC
* Branching
JMP, JZ, JNZ, JC, JNC, JP, JM, JPE, JPO

One additional SET instruction is also present to set data in a valid memory location.
```
SET 2000,10    //loads memory location 2000H with data 10H
```

### Future Scope

* Support for more intstructions in microprocessor.
* Functionality of using labels.
* Functionality of adding breakpoints
* Improving user experience
