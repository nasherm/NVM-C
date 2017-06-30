#include <stdio.h>
#include <stdlib.h>

#include "vm/N8_INSTRUCTIONS.h"
#include "vm/N8_VM.h"

int main(int argc, char *argv[])
{
  N8_VM *vm = malloc(sizeof(N8_VM));
  //print_stack(vm);print_registers(vm);
  uint8_t program[256] = {SETA, 10, SETB, 10, ADDA, 10, PSHB, POPA, HLT};
  init_VM(vm);
  for(int i = 0; i < 256; i++){
    vm->memory[i] = program[i];
  }

  //print_stack(vm);
  while(fetch_decode_exe(vm, vm->memory[vm->PC])){}
  print_registers(vm);
  print_stack_head(vm);
  free(vm);
  return 0;
}
