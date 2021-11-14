# 🧠 headache
A C brainfuck runtime for POSIX computers created in about ~1.5h.

## How does headache work?
Headaches first loads brainfuck code from a file provided as an argument. 
Then, headache filters out only brainfuck-characters (those are `<>+-.,[]`) 
and puts them into an array which, in result, only contains commands for 
the brainfuck runtime. At this point, the brainfuck runtime takes over
and runs the commands after each other. The cell-system of brainfuck is
handled by another array which, every time it could overflow, is extended 
to fit the memory needed to run the program.

## How could this be improved?
Currently headache has some major performance flaws. Those can be fixed easily
which I might do at some point:

-   Brainfuck commands (those are `<>+-.,[]`) are currently saved as 
    char (0-256). This isn't necessary: There are only 8 directives 
    which can be expressed by only 3 bits instead of 8. This means a
    ***huge*** problem for modern computers, as Windows Explorer will
    probably eat up all the remaining RAM, thus, every single bit of
    RAM needs to be saved for it.

-   The whole code-file is loaded to RAM. This should not be done as
    this means that there will be problems when loading files bigger
    than the amount of RAM available. Files should be parted by a
    fixed amount of characters or, if in a loop, the [ and ] directives.

## What is this project for?
This project is something I wanted to do for myself for a longer time. I 
(a) wanted to learn how brainfuck works and wanted to write my own runtime
or compiler for a programming language to further understand the principles
used in programming languages and interpretation. Moreover, (b) I wanted to 
create a well documented brainfuck compiler itself for other people to 
have a easier time understanding how the exact thing I was trying to understand
creating this project works.

## Credits
headache runtime was created by [@jbohnst](https://github.com/jbohnst).
