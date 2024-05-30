// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/6/add/Add.asm

// Computes R0 = 2 + 3  (R0 refers to RAM[0])

@2
D=A
@3
D=D+A
@0
M=D
D=D
MD=D
A=D
AM=D
AD=D
AMD=D
@0
D;JMP
@0
D;JGT
@0
D;JEQ
@0
D;JGE
@0
D;JLT
@0
D;JNE
@0
D;JLE
@0
D;JMP
