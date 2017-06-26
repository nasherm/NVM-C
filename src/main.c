#include <stdio.h>
#include <stdlib.h>

#include "vm/N8_INSTRUCTIONS.h"
#include "vm/N8_VM.h"

int main(int argc, char *argv[])
{
  N8_VM *vm = malloc(sizeof(N8_VM));
  print_stack(vm);print_registers(vm);
  return 0;
}
