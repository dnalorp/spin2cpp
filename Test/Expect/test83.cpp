#include <propeller.h>
#include "test83.h"

uint8_t test83::dat[] = {
  0x2d, 0x2d, 0x0d, 0x00, 0x20, 0x21, 0x00, 0x00, 0xf0, 0x03, 0xbc, 0xa0, 0x44, 0x33, 0x22, 0x11, 
};
void test83::Start(void)
{
  cognew((int32_t)(&(*(int32_t *)&dat[8])), 0);
}

