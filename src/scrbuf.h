#include "types.h"

#ifndef SCRBUF_H_INCLUDED
#define SCRBUF_H_INCLUDED

void ScrBuf_Init();
void ScrBuf_Destroy();
void ScrBuf_PutPixBuf(byte *pixBuf, word x, word y, word width, word height);
void ScrBuf_FlushToVga();

#endif
