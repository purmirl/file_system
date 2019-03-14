#include <stdio.h>
#include "SectorIO.h"
char buffer[BLOCK_SIZE] = {0,};
int main(){
	printf("Hello World!\n");
	init_IO();
	Block_Write(buffer, 0,  1);
	close_IO();
}
