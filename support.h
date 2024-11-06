#include "type.h"

#ifndef __SSU_C_SUPPORT__
#define __SSU_C_SUPPORT__

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);
A_ID *makeIdentifier(char *);
void checkForwardReference();
A_ID *linkDeclaratorList(A_ID *id1, A_ID *id2);
void syntax_error(int, char *);

#endif
