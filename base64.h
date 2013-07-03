#ifndef __BASE64_H__
#define __BASE64_H__

#include <string.h>



#define HIGH2BIT_MASK (0xc0)
#define HIGH4BIT_MASK (0xf0)
#define HIGH6BIT_MASK (0xfc)
#define LOW2BIT_MASK  (0x03)
#define LOW4BIT_MASK  (0x0f)
#define LOW6BIT_MASK  (0x3f)

int base64_encode(char *,char*);

#endif