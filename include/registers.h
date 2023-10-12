#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <sys/user.h>

struct i386_user_regs_struct {
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t esi;
  uint32_t edi;
  uint32_t ebp;
  uint32_t eax;
  uint32_t xds;
  uint32_t xes;
  uint32_t xfs;
  uint32_t xgs;
  uint32_t orig_eax;
  uint32_t eip;
  uint32_t xcs;
  uint32_t eflags;
  uint32_t esp;
  uint32_t xss;
};

union user_regs_t {
  struct i386_user_regs_struct regs32;
  struct user_regs_struct      regs64;
};

#endif  // REGISTERS_H
