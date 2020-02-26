# Two-PASM
Implementation of a two pass assembler using C code to demonstrate how assembly language computation occurs. 

### Pass-1: 
- Define symbols and literals and remember them in symbol table and literal table respectively.
- Keep track of location counter
- Process pseudo-operations

### Pass-2:
- Generate object code by converting symbolic op-code into respective numeric op-code
- Generate data for literals and look for values of symbols
