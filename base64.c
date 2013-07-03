#include "base64.h"

char base64_index_table[] = {
	'A','B','C','D','E','F','G','H','I',
	'J','K','L','M','N','O','P','Q','R',
	'S','T','U','V','W','X','Y','Z','a',
	'b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','0','1',
	'2','3','4','5','6','7','8','9','+',
	'/'
};


int base64_encode(char *src, char *dst){
	int i = 0, len = 0;
	int index = 0;
	char buff[5] = {'\0'};
	int retval = 0;

	len = strlen(src);
	memset(dst,0,sizeof(dst));
	
	while (i<len){
		if (i+2<len){
			index = (src[i]&HIGH6BIT_MASK)>>2;
			buff[0] = base64_index_table[index];
			index = ((src[i]&LOW2BIT_MASK)<<4) +
				((src[i+1]&HIGH4BIT_MASK)>>4);
			buff[1] = base64_index_table[index];
			index = ((src[i+1]&LOW4BIT_MASK)<<2) +
				((src[i+2]&HIGH2BIT_MASK)>>6);
			buff[2] = base64_index_table[index];
			index = src[i+2]&LOW6BIT_MASK;
			buff[3] = base64_index_table[index];
		}else{
			switch(len-i){
				case 1:
					index = ((src[i]&HIGH6BIT_MASK)>>2);
					buff[0] = base64_index_table[index];
					index = ((src[i]&LOW2BIT_MASK)<<4);
					buff[1] = base64_index_table[index];
					buff[2] = '=';
					buff[3] = '=';
					break;
				case 2:
					index = ((src[i]&HIGH6BIT_MASK)>>2);
					buff[0] = base64_index_table[index];
					index = ((src[i]&LOW2BIT_MASK)<<4) +
						((src[i+1]&HIGH4BIT_MASK)>>4);
					buff[1] = base64_index_table[index];
					index = ((src[i+1]&LOW4BIT_MASK)<<2);
					buff[2] = base64_index_table[index];
					buff[3] = '=';
					break;
				default:
					retval = -1;
					return retval;
					break;
			}
		}
		strcat(dst,buff);
		i += 3;
	}
	return retval;
}

