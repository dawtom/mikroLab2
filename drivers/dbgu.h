#ifndef __DBGU_H__
#define __DBGU_H__

#include <inttypes.h>

void debug_init_default(void);
void debug_chr(char chr);
int debug_test(void);
char debug_inkey(void);
char debug_waitkey(void);

#endif


