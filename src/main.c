#include <stdio.h>
#include <time.h>
#include "SectorIO.h"
#include "ext2.h"
#include "super.h"
char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
int main(){
	init_IO();
	printf("%ld\n",sizeof(time_t));
	ku_ext2_read_super((struct super_block*) buffer);
	close_IO();
}
