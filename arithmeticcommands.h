#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "header.h"
#include "util.h"
#include "flag.h"

using namespace std;

/* Instruction for performing arithmetic oprations like add, sub, inrement, etc. */

bool executeArithmeticCommand(string mnemonic, string op1, string op2, map<string, string> &registers, map<char, bool> &flags, map<string, pair<string, int>> &memory) {

    if(mnemonic == "ADD") {
        if(validRegister(op1) && op2 == "") {
            string temp = registers["A"];
            string res = hexAddition(registers["A"], registers[op1]);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
            checkAuxCarryFlag(temp, registers[op1], flags);
        }

        else if(op1 == "M" && op2 == "") {
            string temp = registers["A"];
            string mem = getAddressFromRegPair("H", "L", registers);
            string res = hexAddition(registers["A"], memory[mem].first);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
            checkAuxCarryFlag(temp, registers[op1], flags);
        }
        
        else {
            return false;
        }
    }

    else if(mnemonic == "ADI") {
        if(validData(op1) && op2 == "") {
            string temp = registers["A"];
            string res = hexAddition(registers["A"], op1);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
            checkAuxCarryFlag(temp, op1, flags);
        }
        else {
            return false;
        }
    }

    else if(mnemonic == "INR") {
        stringstream ss;
        int x;

        if(validRegister(op1) && op2 == "") {
            string res = hexAddition(registers[op1], "01");
            ss << hex << res;
            ss >> x;

            if(x > 255)
                res = "00";
            
            res = string(2 - res.length(), '0').append(res);

            registers[op1] = res; 
            checkSignFlag(res, flags);
            checkZeroFlag(res, flags);
            checkParityFlag(res, flags);
        }

        else if(op1 == "M" && op2 == "") {
            string mem = getAddressFromRegPair("H", "L", registers);
            string res = hexAddition(memory[mem].first, "01");

            ss << hex << res;
            ss >> x;
            
            if(x > 255)
                res = "00";

            res = string(2 - res.length(), '0').append(res);

            memory[mem] = make_pair(res, -1);
            checkSignFlag(res, flags);
            checkZeroFlag(res, flags);
            checkParityFlag(res, flags);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "DCR") {
        stringstream ss;
        int x;
        
        if(validRegister(op1) && op2 == "") {
            string res = hexSubtraction(registers[op1], "01");

            ss << hex << res;
            ss >> x;

            if(x > 255) {
                res = "FF";
            }

            res = string(2 - res.length(), '0').append(res);

            registers[op1] = res;
            checkSignFlag(res, flags);
            checkZeroFlag(res, flags);
            checkParityFlag(res, flags);
        }

        else if(op1 == "M" && op2 == "") {
            string mem = getAddressFromRegPair("H", "L", registers);
            string res = hexSubtraction(memory[mem].first, "01");

            ss << hex << res;
            ss >> x;

            if(x > 255) {
                res = "FF";
            }

             res = string(2 - res.length(), '0').append(res);

            memory[mem] = make_pair(res, -1);
            checkSignFlag(res, flags);
            checkZeroFlag(res, flags);
            checkParityFlag(res, flags);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "SUB") {
        if(validRegister(op1) && op2 == "") {
            string res = hexSubtraction(registers["A"], registers[op1]);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
        }

        else if(op1 == "M" && op2 == "") {
            string mem = getAddressFromRegPair("H", "L", registers);
            string res = hexSubtraction(registers["A"], memory[mem].first);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "SUI") {
        if(validData(op1) && op2 == "") {
            string res = hexSubtraction(registers["A"], op1);
            res = checkCarryFlag(res, flags);
            registers["A"] = res;
            checkZeroFlag(registers["A"], flags);
            checkParityFlag(registers["A"], flags);
            checkSignFlag(registers["A"], flags);
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "DAD") {
        stringstream ss;
        if(validateRegisterPair(op1) && op2 == "") {
            string rp2;
            if(op1 == "H")
                rp2 = "L";
            else if(op1 == "B")
                rp2 = "C";
            else
                rp2 = "E";
            string res1 = hexAddition(registers["L"], registers[rp2]);
            
            int num = stoul(res1, nullptr, 16);
            string ac = "00";

            if(num > 255) {
                num -= 256;
                ac = "01";
            }

            ss << hex << num;
            res1 = ss.str();

            res1 = string(2 - res1.length(), '0').append(res1);

            for(int i=0; i<2; i++) {
                if(res1[i] >= 'a' && res1[i] <= 'f')
                    res1[i] -= 32;
            }

            registers["L"] = res1;

            string res2 = hexAddition(hexAddition(registers["H"], registers[op1]), ac);

            res2 = checkCarryFlag(res2, flags);
            registers["H"] = res2;
        }

        else {
            return false;
        }
    }

    else if(mnemonic == "INX") {
        string rp2, res1, res2;
        stringstream ss;
        if(validateRegisterPair(op1) && op2 == "") {
            if(op1 == "H")
                rp2 = "L";
            else if(op1 == "B")
                rp2 = "C";
            else
                rp2 = "E";
            
            string mem = getAddressFromRegPair(op1, rp2, registers);
            string res = hexAddition(mem, "01");

            int num = stoul(res, nullptr, 16);

            if(num > 65535) {
                num = 0;
            }

            ss << hex << num;
            res = ss.str();

            if(res.size() <= 2) {
                res1 = "00";
                res2 = res;
            }

            else {
                res1 = res.substr(0, res.size()-2);
                res2 = res.substr(res.size()-2);
            }

            registers[op1] = res1;
            registers[rp2] = res2;

        }

        else {
            return false;
        }
    }

    else if(mnemonic == "DCX") {
        string rp2, res1, res2;
        stringstream ss;
        if(validateRegisterPair(op1) && op2 == "") {
            if(op1 == "H")
                rp2 = "L";
            else if(op1 == "B")
                rp2 = "C";
            else
                rp2 = "E";
            
            string mem = getAddressFromRegPair(op1, rp2, registers);
            string res = hexSubtraction(mem, "01");

            int num = stoul(res, nullptr, 16);

            if(num < 0) {
                num = 65535;
            }

            ss << hex << num;
            res = ss.str();

            if(res.size() <= 2) {
                res1 = "00";
                res2 = res;
            }

            else {
                res1 = res.substr(0, res.size()-2);
                res2 = res.substr(res.size()-2);
            }

            registers[op1] = res1;
            registers[rp2] = res2;

        }

        else {
            return false;
        }
    }

    return true;    
}

#endif