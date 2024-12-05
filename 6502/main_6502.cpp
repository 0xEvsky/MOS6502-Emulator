#include <iostream>
using namespace std;

using Byte = unsigned char;
using Word = unsigned short;

struct Mem 
{

};

struct CPU
{
    
    Word PC;           //program counter
    Word SP;          //stack pointer

    Byte A, X, Y;    //registers

    Byte C : 1;     //status flags
    Byte Z : 1;    
    Byte I : 1;   
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    void Reset()                             //method to mimic the resetting proccess 
    {
        PC = 0xFFFC;   
        SP = 0x0100;                        //the stack beings at 0x01000 in the memory     
        C = Z = I = D = B = V = N = 0;     //all flags are deactive
        A = X = Y = 0;                    //registers are empty
    }
};


int main() 
{
    CPU cpu;
    return 0;
}