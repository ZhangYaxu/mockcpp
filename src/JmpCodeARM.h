
#ifndef __MOCKCPP_JMP_CODE_ARM_H__
#define __MOCKCPP_JMP_CODE_ARM_H__
#include <stdio.h>
const unsigned char jmpCodeTemplate[]  = { 0xF6, 0x00, 0x00, 0x00 };

void setJumpCode(unsigned long* base, unsigned long * from, unsigned long* to){
   unsigned long offset = (unsigned long)to - (unsigned long)from -  sizeof(jmpCodeTemplate);
   printf("\r\nbase 0x%x, from 0x%x to 0x%x, offset 0x%x\r\n",base,from,to,offset);
   unsigned char bbb[6]={0};
   *(unsigned long*)bbb = (offset & 0x00FFFFFF) | 0xF6000000; 
   printf("\r\nOpCode 0x%x, 0x%x, 0x%x, 0x%x, 0x%x",*(unsigned long *)bbb, bbb[0],bbb[1],bbb[2],bbb[3]);
   *(unsigned long*)base = (offset & 0x00FFFFFF) | 0xF6000000; 
   printf("\r\nOpCode 0x%x, 0x%x, 0x%x, 0x%x, 0x%x",*(unsigned long *)base, bbb[0],bbb[1],bbb[2],bbb[3]);
   
}

#define SET_JMP_CODE(base, from, to) do { \
   setJumpCode((unsigned long*) base, (unsigned long *) from, (unsigned long*) to);\
  } while(0)

#endif
//         memcpy(bbb, base, sizeof(jmpCodeTemplate)); \
//         printf("OpCode 0x%x, 0x%x,0x%x,0x%x,0x%x,", *(unsigned long *)base),*((unsigned char *)(unsigned long)base),\
//                 *((unsigned char *)((unsigned long)base +1)),*((unsigned char *)((unsigned long)base +2)),*((unsigned char *)((unsigned long)base +3));\
 