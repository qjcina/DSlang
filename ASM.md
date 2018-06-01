# DSlang assembly specification
Basic operations:
```asm
PUS _var              ;pushes variable to stack
PUS _var _type        ;pushes variable to stack as type (0 - integer, 1 - floating point)
POS _var              ;pops top value from stack to variable
ADD                   ;adds 2 values from stack
SUB                   ;substracts 2 values from stack
DIV                   ;divides 2 values from stack
MUL                   ;multiplies 2 values from stack
JMP _line             ;jumps to line
JEQ _line _val        ;jumps to line when top of stack is equal
JNE _line _val        ;jumps to line when top of stack is not equal
JGR _line _val        ;jumps to line when top of stack is greater
JGE _line _val        ;jumps to line when top of stack is greater or equal
JLS _line _val        ;jumps to line when top of stack is lesser
JLE _line _val        ;jumps to line when top of stack is lesser or equal
DUB                   ;doubles top of stack
SVM _hash             ;saves variable to memory
RVM _hash             ;reads variable from memory
SVC _pos              ;saves variable to cache memory address
RVM _pos              ;reads variable from cache memory address
GEC                   ;pushes first available cache address to stack 
RRR                   ;exits program
```
Examples:
```asm
PUS 1       ;push 1
PUS 2       ;push 2
ADD         ;add 1+2=3
PUS 3       ;push 3
MUL         ;multiply 3*3
DUB         ;double 9 (stack is now 9,9)
JNE 9 9     ;jump to line 9 when top not equal 9
RRR         ;exit program
PUS 2       ;push 2
ADD         ;add 9+2
POP         ;pop top of stack (to stdout)
RRR         ;exit program
```
```asm
PUS 40030000006f0500 1 ;push 2 numbers as floats
PUS 4000000000000000 1
MUL
POP
CST 0                   ;cast to integer
POP
```
