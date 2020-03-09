# Two-PASM
Implementation of a two pass assembler using C code to demonstrate how assembly language computation occurs. 

### Pass-1: 
- Define symbols and literals and remember them in symbol table and literal table respectively.
- Keep track of location counter
- Process pseudo-operations

### Pass-2:
- Generate object code by converting symbolic op-code into respective numeric op-code
- Generate data for literals and look for values of symbols


# Two-pass assemblers
The two pass assembler performs two passes over the source program. 

In the first pass, it reads the entire source program, looking only for label definitions. All the labels are collected, assigned address, and placed in the symbol table in this pass, no instructions as assembled and at the end the symbol table should contain all the labels defined in the program. To assign address to labels, the assembles maintains a Location Counter (LC).


In the second pass the instructions are again read and are assembled using the symbol table.
Basically, the assembler goes through the program one line at a time, and generates machine code for that instruction. Then the assembler proceeds to the next instruction. In this way, the entire machine code program is created. For most instructions this process works fine, for example for instructions that only reference registers, the assembler can compute the machine code easily, since the assembler knows where the registers are.

![5](http://i.imgur.com/XIway7g.jpg)

## Difference between One Pass and Two Pass Assemblers
The difference between one pass and two pass assemblers are:-

A one pass assembler passes over the source file exactly once, in the same pass collecting the labels, resolving future references and doing the actual assembly. The difficult part is to resolve future label references (the problem of forward referencing) and assemble code in one pass. The one pass assembler prepares an intermediate file, which is used as input by the two pass assembler.


A two pass assembler does two passes over the source file (the second pass can be over an intermediate file generated in the first pass of the assembler). In the first pass all it does is looks for label definitions and introduces them in the symbol table (a dynamic table which includes the label name and address for each label in the source program). In the second pass, after the symbol table is complete, it does the actual assembly by translating the operations into machine codes and so on.
