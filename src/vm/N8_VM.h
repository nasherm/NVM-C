/*
 * Author: Nashe Mncube
 * Virtual machine definitions.
*/

#include <stdint.h>
#include <stdbool.h>


/*
 * Definition of the virtual machine. This machine is held as a struct with
 * 7 registers. There are 4 registers which are program specific. The SP
 * holds the value of the stack pointer, PC holds the program counter and
 * the CC register holds the flags set on operation.
 *
 * There are 256 bytes of addressable memory.
 */

typedef struct{
  uint8_t A;
  uint8_t B;
  uint8_t X;
  uint8_t Y;
  uint8_t SP;
  uint8_t PC;
  uint8_t CC;

  uint8_t memory[256];
}N8_VM;

/*
 * Flags set on different operations
 *
*/
typedef enum{
  N8_Zero     = 0,
  N8_Carry    = 1,
  N8_Overflow = 2,
  N8_Neg      = 3
}N8_Flags;

/*
 * The operations performed by the VM
 */

 typedef enum{
   ADD, SUB, MUL, DIV
 }N8_OP;

 // TODO: These visulisation functions
 void print_stack_head(const N8_VM *vm);
 void print_registers(const N8_VM *vm);
 void init_VM(N8_VM *vm);
 bool fetch_decode_exe(N8_VM *vm, const uint8_t instr);
