#include <stdio.h>
#include <stdlib.h>

#include "N8_VM.h"
#include "N8_INSTRUCTIONS.h"

#define ZERO 0
#define MAX 255
#define STACK_SIZE 50
//TODO: Setting flags function
//TODO: Arithmetic logic support for negative numbers
//DONE: POP from stack functions
//DONE: Setting Register functions
//DONE: Halt computing functions
//DONE: The fetch_decode_exe function
//TODO: Parser for input files
//TODO: Testing

void set_flags_control(N8_VM *vm, const uint8_t result, const uint8_t op1, N8_OP operation);
void init_VM(N8_VM *vm){
  vm->A = 0;
  vm->B = 0;
  vm->X = 0;
  vm->Y = 0;
  vm->SP = MAX; // Stack grows upwards from bottom of memory
  vm->PC = 0;
  vm->CC = 0;
}

void print_stack(const N8_VM *vm){
  uint16_t sp = MAX-STACK_SIZE;
  while(sp <= 255){
    printf("%02x: %02x\n", sp, vm->memory[sp]);
    sp++;
  }
}

void print_registers(const N8_VM *vm){
  printf("A:  %02x\n", vm->A);
  printf("B:  %02x\n", vm->B);
  printf("X:  %02x\n", vm->X);
  printf("Y:  %02x\n", vm->Y);
  printf("SP: %02x\n", vm->SP);
  printf("PC: %02x\n", vm->PC);
  printf("CC: %02x\n", vm->CC);
}

/*
 * Pushes register or immediate values onto the stack based on op
 */
void push_to_stack(N8_VM *vm, INSTRUCTION_SET op, uint8_t reg)
{
  if(vm->SP == (MAX - STACK_SIZE)){
    fprintf(stderr, "Stack overflow\n");
    exit(2);
  }
  switch(op){
    case PSHi:
      vm->memory[vm->SP] = vm->memory[++vm->PC]; //Get next value in mem(the operand)
      break;
    default:
      vm->memory[vm->SP] = reg;
      break;
  }
  vm->SP--;
}

/*
 * Pops values from the stack, second instr indicates where to store result
 */
void pop_from_stack(N8_VM *vm, INSTRUCTION_SET instr)
{
  if(vm->SP == MAX){
    fprintf(stderr, "No values on stack\n");
    exit(3);
  }
  uint8_t stack_value = vm->memory[vm->SP];

  switch(instr){
    case POPA: vm->A = stack_value; break;
    case POPB: vm->B = stack_value; break;
    case POPX: vm->X = stack_value; break;
    case POPY: vm->Y = stack_value; break;
    default: fprintf(stderr, "Bad call to pop. No destination register\n"); exit(3);
  }
  vm->SP++;
}

/*
 * Sets register values
 */
void set_register(N8_VM *vm, INSTRUCTION_SET instr)
{
  uint8_t operand = vm->memory[++vm->PC];

  switch(instr){
    case SETA: vm->A = operand; break;
    case SETB: vm->B = operand; break;
    case SETX: vm->X = operand; break;
    case SETY: vm->Y = operand; break;
    default: fprintf(stderr, "Bad call to set\n"); exit(4);
  }
  //set_flags_control;
}

/*
 * Add value to register
 */
void add_to_register(N8_VM *vm, uint8_t *dest_reg)
{
  uint8_t val = vm->memory[++vm->PC];
  uint8_t prev_reg_value = *dest_reg;
  uint8_t result; //Need these value to set appropriate flags on overflow, zero etc

  *dest_reg += val;
  result = *dest_reg;

  set_flags_control(vm, result, prev_reg_value, ADD);

}

/*
 * Returns the flag value
 */
void handle_conditional_branch(N8_VM *vm, N8_Flags f, uint8_t branch_address){
  uint8_t flag_value = vm->CC >> f & 0x01; // Mask relevant flag bit with one

  if(flag_value == 0x01)
    vm->PC = branch_address;
  else
    ++vm->PC;
}
/*
 * Handles conditional branches. Jumps to destination address given by input
 */
void branch_control(N8_VM *vm, INSTRUCTION_SET instr)
{
  uint8_t branch_address = vm->memory[++vm->PC];
  if(branch_address >= MAX-STACK_SIZE){
    //Must keep stack protected, as well as preventing overflow
    fprintf(stderr, "Memory access fault, trying to acess prohibited memory\n");
    exit(5);
  }
  switch(instr){
    case BRZ: handle_conditional_branch(vm, N8_Zero, branch_address);     break;
    case BRV: handle_conditional_branch(vm, N8_Overflow, branch_address); break;
    case BRN: handle_conditional_branch(vm, N8_Neg, branch_address);      break;
    default:  ++vm->PC; break;
  }
}

/*
 * Lower 4 bits of CC register hold the flags
 */
void set_flag(N8_VM *vm, N8_Flags flag)
{
  vm->CC |= 1 << flag;
}


/*
 * Sets the necessary flags on operations based on results and input arguments
 *
*/
void set_flags_control(N8_VM *vm, const uint8_t result, const uint8_t op1, N8_OP operation)
{
  switch(operation){
    case ADD: // Op1 is the previous value of result in add operation
      if(result <= op1) set_flag(vm, N8_Overflow);
      else if(result == 0) set_flag(vm, N8_Zero);
    /*case SUB: // Op1 is the previous value, as in addition
      if()*/
    default:
      fprintf(stderr, "Invalid arithmetic operation\n");
      exit(6);
      break;
  }
}


bool fetch_decode_exe(N8_VM *vm, const uint8_t instr){
  switch(instr){
    case PSHi: push_to_stack(vm, PSHi, ZERO); break;
    case PSHA: push_to_stack(vm, PSHA, vm->A); break;
    case PSHB: push_to_stack(vm, PSHB, vm->B); break;
    case PSHX: push_to_stack(vm, PSHX, vm->X); break;
    case PSHY: push_to_stack(vm, PSHY, vm->Y); break;

    case ADDA: add_to_register(vm, &vm->A); break;
    case ADDB: add_to_register(vm, &vm->B); break;
    case ADDX: add_to_register(vm, &vm->X); break;
    case ADDY: add_to_register(vm, &vm->Y); break;

    case BRZ: branch_control(vm, BRZ); break;
    case BRV: branch_control(vm, BRV); break;
    case BRN: branch_control(vm, BRN); break;

    case POPA: pop_from_stack(vm, POPA); break;
    case POPB: pop_from_stack(vm, POPB); break;
    case POPX: pop_from_stack(vm, POPX); break;
    case POPY: pop_from_stack(vm, POPY); break;

    case SETA: set_register(vm, SETA); break;
    case SETB: set_register(vm, SETB); break;
    case SETX: set_register(vm, SETX); break;
    case SETY: set_register(vm, SETY); break;

    case HLT:
      fprintf(stdout, "Program halted\n");
      return false;
    default:
      fprintf(stderr, "Instruction failed to decode\n");
      exit(-1);
      break;
  }
  vm->PC++;
  return true;
}
