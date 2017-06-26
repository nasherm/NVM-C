#include <stdio.h>
#include <stdlib.h>

#include "N8_VM.h"
#include "N8_INSTRUCTIONS.h"

//TODO: Setting flags function
//TODO: POP from stack functions
//TODO: Setting Register functions
//TODO: Halt computing functions
//TODO: The fetch_decode_exe function
//TODO: Parser for input files
//TODO: 
void init_VM(N8_VM *vm){
  vm->A = 0;
  vm->B = 0;
  vm->X = 0;
  vm->Y = 0;
  vm->SP = 255; // Stack grows upwards from bottom of memory
  vm->PC = 0;
  vm->CC = 0;
}

void print_stack(const N8_VM *vm){
  while(vm->SP <=255){
    printf("%02x: %02x\n", vm->SP, vm->memory[vm->SP]);
    vm->SP++;
  }
}

void print_registers(const N8_VM *vm){
  printf("A: %02x\n", vm->A);
  printf("B: %02x\n", vm->B);
  printf("X: %02x\n", vm->X);
  printf("Y: %02x\n", vm->Y);
  printf("SP: %02x\n", vm->SP);
  printf("PC: %02x\n", vm->PC);
  printf("CC: %02x\n", vm->CC);
}

/*
 * Pushes register or immediate values onto the stack based
 */
void push_to_stack(const N8_VM *vm, INSTRUCTION_SET op, uint8_t reg)
{
  (vm->SP == 50){
    fprintf(stderr, "Stack overflow\n");
    exit(2);
  }
  switch(op){
    case PSHi:
      vm->memory[--vm->SP] = vm->memory[++vm->PC]; //Get next value in mem(the operand)
      break;
    default:
      vm->memory[--vm->SP] = reg;
      break;
  }
}

void add_to_register(const N8_VM *vm, uint8_t reg)
{
  uint8_t val = vm->memory[++vm->PC];
  uint8_t check = vm->reg;
  vm->reg += val;
  //set_flags()

}

/*
 * Sets the necessary flags on operations based on results and input arguments
 *
 */

//void set_flags(const N8_VM *vm, uint8_t result,const uint8_t op1, const uint8_t op2);
