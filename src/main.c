/**
 * 2019 EXT2 Study
 * main.c
 * ------------
 *
 * Ext2 Format
 *  - Boot Block : First ext2's partition block.
 *  - Boot Group 0 ~ N : Partition except boot block of ext2.
 *  - Super Block : 1 Block. Information of the whole ext2 file system.
 *  - Group Descriptor : n Blocks. Information of the whole block groups.
 *  - Data Block Bitmap : 1 Block. State of the block using.
 *  - Inode Bitmap : 1 Block. State of the Inode using.
 *  - Inode Table : n Blocks. Information of the whole Inode.
 *  - Data Blocks : n Blocks. Data blocks.
 */

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

	/**
	 * SectorIO.h :: init_IO()
	 */ 
	init_IO();
	
	/** 
 	 * Shell interface... : shell>
 	 * Command : 	- exit
 	 * 	 	- infosuper : Information of super block.
 	 * 	 	- formatsuper : Set the super block. 
 	 * 	 	- infogroup : Information of group descriptor
 	 * 	 	- formatgroup : Set the group descriptor
 	 */
	while(1){
		printf("shell>");
		memset(command_buffer,0,256);
		scanf("%255s",command_buffer);
		getchar();
		/**
		 * Now linear search O(n) algorithm
		 * But It's quite acceptable
		 */
		if(strcmp(command_buffer,"exit")==0){
			printf("%s\n");
			break;
		}
		if(strcmp(command_buffer,"infosuper")==0){
			/* super.h :: ku_ext2_info_super() */
			ku_ext2_info_super(); 
			continue;
		}
		if(strcmp(command_buffer,"formatsuper")==0){
			/* super.h :: ku_ext2_format_super() */
			ku_ext2_format_super();
			continue;
		}
		if(strcmp(command_buffer,"infogroup")==0){
			/* group.h :: ku_ext2_info_group() */
			ku_ext2_info_group();
			continue;
		}
		if(strcmp(command_buffer,"formatgroup")==0){
			/* group.h :: ku_ext2_format_group() */
			ku_ext2_format_group();
			continue;
		}
		printf("Can not find '%s'...\n", command_buffer);
	}
	
	/**
 	* SectorIO.h :: close_IO() 
 	*/
	close_IO();
}
