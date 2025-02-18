/**
 * 2019 EXT2 Study
 * group.c
 * ------------
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "group.h"
#include "ext2.h"
#include "SectorIO.h"

/**
 * ext2.h :: ku_ext2_format_group()
 * 좀 더 엄밀하게 말하면 group_descriptor table을 format하는 것이다.
 */
extern void ku_ext2_format_group(){
	char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	struct block_group *pst_group;
	struct block_group init_group;
	/* 현재 block_group 사이즈는 32바이트이다  */
	int i,j;
	int k = 0;
	pst_group = (struct block_group *)buffer;
	for(i = 0; i <= KU_EXT2_BLOCK_GROUP_COUNT; i++){
		/* 마지막에는 NULL descriptor을 넣어준다. */
		if( i == KU_EXT2_BLOCK_GROUP_COUNT)
			memset(&init_group,0,sizeof(struct block_group));
		else
			ku_ext2_init_group(&init_group, i);

		memcpy(&(pst_group[i]),&init_group,sizeof(struct block_group));
		j+=sizeof(struct block_group);

		if(j >= KU_EXT2_BLOCK_SIZE){
			printf("Block writing...!\n");
			Block_Write(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET + k++, 1);
			j=0;
		}
	}
	if(j != 0){
		printf("Block writing...!\n");
		Block_Write(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET + k, 1);
	}
	printf("Group Format Success...!\n");

}

/**
 * ext2.h :: ku_ext2_info_group()
 */
extern void ku_ext2_info_group(){
	char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	struct block_group *pst_group;
	int i;
	int j = 0;
	pst_group = (struct block_group *)buffer;
	while(1){
		Block_Read(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET + j, 1);
		for(i = 0; i * sizeof(struct block_group) < KU_EXT2_BLOCK_SIZE; i++){
			/* 마지막 디스크립터를 발견*/
			if(pst_group[i].bg_block_bitmap == 0 && pst_group[i].bg_inode_bitmap == 0){
				printf("Arrived at null Descriptor...!\n");
				return;
			}
			printf("Group descriptor [%d]\n",i);
			ku_ext2_info_group_descriptor(&(pst_group[i]));
			printf("Press the 'q' to exit...\n");
			if(getchar() == 'q')
				return;
		}
		j++;
	}
}

/**
 * ku_ext2_info_group_descriptor(struct block_group *bg) : print the information of the group blocks.
 */
static void ku_ext2_info_group_descriptor(struct block_group *bg){
	printf("Data  Bitmap Block Offset [%d]\n", bg->bg_block_bitmap);
	printf("Inode Bitmap Block Offset [%d]\n", bg->bg_inode_bitmap);
	printf("Inode table  Block Offset [%d]\n", bg->bg_inode_table);
	printf("Free Data  Block Count [%d]\n", bg->bg_free_blocks_count);
	printf("Free inode Block Count [%d]\n", bg->bg_free_inodes_count);
	printf("Used Dir Count [%d]\n", bg->bg_used_dirs_count);
}

/**
 * ku_ext2_init_group(struct block_group *bg, int index) : init the group blocks.
 */
static void ku_ext2_init_group(struct block_group *bg, int index){
	char buffer[KU_EXT2_BLOCK_SIZE]= {0,};
	memset(bg,0,sizeof(struct block_group));
	bg->bg_block_bitmap =  KU_EXT2_BLOCK_GROUP_TOTAL_COUNT * index + \
			KU_EXT2_BLOCK_BITMAP_BLOCK_OFSSET;
	bg->bg_inode_bitmap =  KU_EXT2_BLOCK_GROUP_TOTAL_COUNT * index + \
			KU_EXT2_INODE_BITMAP_BLOCK_OFFSET;
	bg->bg_inode_table =  KU_EXT2_BLOCK_GROUP_TOTAL_COUNT * index + \
			KU_EXT2_INODE_BLOCK_OFFSET;
	bg->bg_free_blocks_count = KU_EXT2_INODE_BLOCK_COUNT;
	bg->bg_free_inodes_count = KU_EXT2_DATA_BLOCK_COUNT;
	bg->bg_used_dirs_count = 0;
	/* 비트맵 초기화 */
	Block_Write(buffer, bg->bg_block_bitmap, 1);
	Block_Write(buffer, bg->bg_inode_bitmap, 1);
}
