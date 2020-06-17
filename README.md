# Assembler-CSandE
Hi. At this point, stage 1 of the assembler is complete (the assembler that can only take "symboless" assembbly code). Handling of comments and white/empty spaces have not been implemented. Those will be added in stage 2.


To compile, run "g++ -o Assembler main.cpp code.cpp parser.cpp" in your Linux terminal after cloning this project.


To convert an asm file (say add.asm) to hack, run "./Assembler add.asm" in your Linux terminal.



Stage 2 loading ...

First pass of Stage 2 completed. At this stage, compile with "g++ -o Assembler symboltable.cpp main.cpp code.cpp parser.cpp" in your Linux terminal after cloning the project. To convert an asm file (say add.asm) to hack, run "./Assembler add.asm" in your Linux terminal.

With this stage completed, all variables and labels will be added to Symbol Table once program is run. Empty lines and comments will be ignored. Also, for all other lines that are considered valid lines, all leading, trailing and in-between whitespaces will be removed before processing.

Second pass loading ...