#include <stdio.h>
#include <time.h>
#include <string.h>
#include "SectorIO.h"
#include "ext2.h"
#include "super.h"
#include "group.h"
int main(){
	char command_buffer[255 + 1] ={0,};
	char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	init_IO();
	/* Shell interface... */
	while(1){
		printf("shell>");
		memset(command_buffer,0,256);
		scanf("%255s",command_buffer);
		getchar();
		/*
		 * Now linear search O(n) algorithm
		 * But It's quite acceptable
		 */
		if(strcmp(command_buffer,"exit")==0){
			printf("%s\n");
			break;
		}
		if(strcmp(command_buffer,"infosuper")==0){
			ku_ext2_info_super();
			continue;
		}
		if(strcmp(command_buffer,"formatsuper")==0){
			ku_ext2_format_super();
			continue;
		}
		if(strcmp(command_buffer,"infogroup")==0){
			ku_ext2_info_group();
			continue;
		}
		if(strcmp(command_buffer,"formatgroup")==0){
			ku_ext2_format_group();
			continue;
		}
		printf("Can not find '%s'...\n", command_buffer);
	}
	close_IO();
}
