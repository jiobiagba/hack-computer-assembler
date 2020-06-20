# Hack Computer Assembler
This project is an assembler for the Hack Computer. **_It converts Hack Assembly Code to 16-bit machine code._**

# Motivation
This project was inspired by my drive to understand computers even to the level of the gates in them. This led me to discovering the work of *Prof. Noam Nisan and Prof. Shimon Schocken* as documented in https://www.nand2tetris.org/. 

As part of the journey, I have self-taught myself from their materials about gates, CPU and other fundamental aspects of computer hardware. This assembler project is my attempt at the first software project they provided.

Interestingly, in doing this project, I also stepped out of the world of JavaScript/TypeScript which I'm used to into the world of C++. It has been a fascinating journey and now I can say I know C++ at a working level.

# Tech/Languages
* C++
* Hack assembly language
* G++ Compiler

# Features
Hack **assembly code** is compiled to **machine code** for the Hack computer.
A **Symbol Table** (created using a **Hash Table**) is used to store variables and labels
**White spaces and comments are not processed**. This ensures it's actual code that is finally compiled.

# Essential Files
Before, during and after cloning, ensure you do not change any of the files. In particular, do not alter the following files else there will be errors in compilation
* predefinedsymbols.txt
* dest.txt
* comp.txt
* jump.txt

# Files Explained
* *symboltable.h*: header file defining properties and routines for the symboltable module
* *symboltable.cpp*: implementation of rotines defined in symboltable.h
* *parser.h*: header file defining properties and routines for the parser module
* *parser.cpp*: implementation of routines in parser.h
* *code.h*: header file defining properties and routines for the code module
* *code.cpp*: implementation of routines defined in code.h
* *main.cpp*: entry point of the app
* *predefinedsymbols.txt*: file containing all predefined symbols as specified in the Assembler design specification. It is a essential input to the app
* *dest.txt*: file containing dest instructions to be used in the app. It is a essential input to the app
* *comp.txt*: file containing comp instructions to be used in the app. It is a essential input to the app
* *jump.txt*: file comtaining jump instructions to be used in the app. It is a essential input to the app

The *.asm* files were added so whoever is given access can use it to test their code.

# Getting Started
Before starting, ensure you have the following installed on your computer:
* Linux operating system (I used Ubuntu 18.04 LTS on a Windows 10 Laptop through WSL 2)
* Git
* A C++ compiler (g++ was used in this project)

# Installation
1. `git clone https://github.com/jiobiagba/Assembler-EofCS.git`
2. `cd Assembler-EofCS`
3. `g++ -o Assembler symboltable.cpp main.cpp code.cpp parser.cpp`

# Usage
After installation, your executable Assembler now exists in the folder. To use: 
1. Create an assembler file following the Hack Computer Assembly Language guideline (e.g. testfile.asm). The ".asm" extension MUST exist in the file else compilation will fail.
2. Run `./Assembler testfile.asm` in your terminal to generate a .hack file (machine code only). Console logs have been intentionally left so you can follow all processes as they occur. At the end also, you will see the symbol table used during compilation.
*(Hint: You can rename one of the existing .asm files to testFile.asm, convert to machine code, and compare to alreay existing .hack file)*

# Contribution
Contributions are welcome. Kindly check if the issue you intend raising has not been attended to in the past.If it hasn't, please feel free to raise a new [issue](https://github.com/jiobiagba/Assembler-EofCS/issues).

Please note that pull requests are also welcome but PRs made directly to the master branch are discouraged. Also please make it easy to understand what you are trying to address by specifying:
* the problem
* your operating system and 
* your compiler

# Credits
 Prof. Noam Nisan and Prof. Shimon Schocken of [NAND AND TETRIS](https://www.nand2tetris.org/)
