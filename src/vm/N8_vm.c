#include <stdio.h>
#include <stdlib.h>

#include "N8_VM.h"
#include "N8_INSTRUCTIONS.h"

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

void push_to_stack(const N8_VM *vm, INSTRUCTION_SET op, uint8_t reg)
{
  (vm->SP == 50){
    fprintf(stderr, "Stack overflow\n");
    exit(2);
  }
  switch(op){
    case PSHi:
      vm->memory[--vm->SP] = vm->memory[++vm->PC];
      break;
    default:
      vm->memory[--vm->SP] = reg;
      break;
  }
}
