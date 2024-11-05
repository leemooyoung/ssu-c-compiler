#include "type.h"

#ifndef __SSU_C_SUPPORT__
#define __SSU_C_SUPPORT__

A_ID *makeIdentifier(char *);
void checkForwardReference();
void syntax_error(int, char *);

#endif
