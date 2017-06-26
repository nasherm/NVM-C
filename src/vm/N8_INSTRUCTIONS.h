/*
 * Author: Nashe Mncube
 * The instruction set for this 8-bit architecture has 15 instructions.
*/


typedef enum{
  PSHi = 0x01, // Pushes the argument to the stack
  PSHA = 0x02, // Pushes the value in register A to the stack
  PSHB = 0x03, // Pushes the value in register B to the stack
  PSHX = 0x04, // Pushes the calue in register X to the stack
  PSHY = 0x05, // Pushes the value in register Y to the stack
  ADDA = 0x06, // Adds the argument to the value in register A
  ADDB = 0x07, // Adds the argument to the value in register B
  ADDX = 0x08, // Adds the argument to the value in register X
  ADDY = 0x09, // Adds the argument to the value in register Y
  BRZ  = 0x0a, // Branch if zero (CC = 0)
  BRV  = 0x0b, // Branch on overflow (CC = 2)
  BRN  = 0x0c, // Branch if negative (CC = 3)
  POPA = 0x0d, // Pop from the stack copy to register A
  POPB = 0x0e, // Pop from the stack copy to register B
  POPX = 0x0f, // Pop from the stack copy to register X
  POPY = 0x10, // Pop from the stack copy to register Y
  SETA = 0x11, // Set register A to argument
  SETB = 0x12, // Set register B to argument
  SETX = 0x13, // Set register X to argument
  SETY = 0x14, // Set register Y to argument
  HLT  = 0x15  // Stop the programs
}INSTRUCTION_SET;
