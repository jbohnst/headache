#include <stdio.h>
#include <stdlib.h>


/**
 * Buffer containing currently used code segment from file
 */
char* codeBuffer;

/**
 * Current character position in code buffer
 */
size_t codeBufferPos = 0;

/**
 * Memory variable for brainfuck cells
 */
int* runtimeMemory;

/**
 * Current runtime memory size
 */
size_t memorySize = 256;

/**
 * Current brainfuck cell in memory
 */
size_t memoryPos = 0;


/**
 * Increases current pointer position by one cell
 */
void bf_increasePointer() {
    // Allocate more memory if needed
    if(memoryPos == memorySize) {
        int* newRuntimeMemory = realloc(runtimeMemory, memorySize + (size_t) 256);

        if(newRuntimeMemory != NULL) {
            runtimeMemory = newRuntimeMemory;
        }
    }

    memoryPos++;
}

/**
 * Decreases current pointer position by one cell
 */
void bf_decreasePointer() {
    if(memoryPos == 0) {
        printf("Warning: Memory access violation! Tried to move pointer to a cell below zero!");
        return;
    }

    memoryPos--;
}

/**
 * Increases value in current cell by one
 */
void bf_increseValue() {
    runtimeMemory[memoryPos]++;
}

/**
 * Decreases value in current cell by one
 */
void bf_decreaseValue() {
    runtimeMemory[memoryPos]--;
}

/**
 * Prints current cell value as ascii character
 */
void bf_asciiPrint() {
    printf("%c", runtimeMemory[memoryPos]);
}

/**
 * Reads one ascii character from user input
 */
void bf_readAsciiChar() {
    runtimeMemory[memoryPos] = getchar();
}

/**
 * Jumps back to loop beginning (jumps after next '[')
 */
void bf_continueLoop() {
    if(runtimeMemory[memoryPos] == 0) {
        return;
    }

    // Go back until '[' is found...
    while(1) {
        codeBufferPos--;

        if(codeBuffer[codeBufferPos] == '[') {
            // And execute the code after the ']'
            return;
        }
    }
}

/**
 * Runs the function for a brainfuck character
 */
void bf_runChar(char c) {
    switch(c) {
        case '>':
            bf_increasePointer();
            break;

        case '<':
            bf_decreasePointer();
            break;

        case '+':
            bf_increseValue();
            break;

        case '-':
            bf_decreaseValue();
            break;

        case '.':
            bf_asciiPrint();
            break;

        case ',':
            bf_readAsciiChar();
            break;

        case ']':
            bf_continueLoop();
            break;
    }
}

/**
 * C Entry Method
 * @param argc Argument count
 * @param argv Argument strings
 */
int main(int argc, char* argv[]) {
    // Check if file argument is present
    if(argc < 2) {
        printf("headache - brainfuck runtime by @jbohnst\n\n"
               "Error: No input file provided.");
        exit(-1);
    }

    // Open file
    FILE* sourceFile = fopen(argv[1], "r");

    if(sourceFile == NULL) {
        printf("headache - brainfuck runtime by @jbohnst\n\n"
               "Error: Unable to read input file.");
        exit(-1);
    }

    // Read file to code buffer and ignore all non-brainfuck-characters
    // This is done for runtime performance reasons.
    fseek(sourceFile, 0L, SEEK_END);

    size_t bufferLength = 1;
    char currentChar;

    // Count brainfuck characters to know buffer size
    while((currentChar = (char) fgetc(sourceFile))) {
        // Break loop if EOF is reached
        if(currentChar == EOF) {
            break;
        }

        switch(currentChar) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                bufferLength++;
        }
    }

    codeBuffer = malloc(sizeof(char) * (bufferLength + 1));

    fseek(sourceFile, 0L, SEEK_SET);

    // Read all brainfuck characters to the codeBuffer
    while((currentChar = (char) fgetc(sourceFile))) {
        // Break loop if EOF is reached
        if(currentChar == EOF) {
            break;
        }

        switch(currentChar) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                codeBuffer[codeBufferPos] = currentChar;
                codeBufferPos++;
        }
    }

    codeBuffer[codeBufferPos] = EOF;
    codeBufferPos = 0;

    // Initialize memory buffer
    runtimeMemory = calloc((size_t) 256, sizeof(int));

    // Run from code buffer
    while(1) {
        if(codeBuffer[codeBufferPos] == EOF) {
            break;
        }

        bf_runChar(codeBuffer[codeBufferPos]);
        codeBufferPos++;
    }

    // Free runtime memory and code buffer
    free(runtimeMemory);
    free(codeBuffer);
}
