/**
 * 2019 EXT2 Study
 * super.c
 * ------------
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */

#include "SectorIO.h"
#include "inode.h"
#include "ext2.h"
#include <time.h>

/**
 * ext2.h :: ku_ext2_write_super(void *pstSuper)
 */
extern int ku_ext2_write_super (void *pstSuper){
	/**
 	 * SectorIO.h :: Block_Write()
 	 */ 
	return Block_Write(pstSuper, KU_EXT2_SUPER_BLOCK_OFFSET, KU_EXT2_SUPER_BLOCK_COUNT);
}

/**
 * ext2.h :: ku_ext2_read_super(void *pstSuper)
 */
extern int ku_ext2_read_super (void *pstSuper){
	/**
  	 * SectorIO.h :: Block_Read()
  	 */ 
	return Block_Read(pstSuper, KU_EXT2_SUPER_BLOCK_OFFSET, KU_EXT2_SUPER_BLOCK_COUNT);
}

/**
 * ext2.h :: ku_ext2_format_super()
 */
extern void ku_ext2_format_super(){
	char buffer[KU_EXT2_BLOCK_SIZE]= {0,};
	struct super_block* pstSuper;
	time_t current_time;
	pstSuper = (struct super_block*)buffer;
	pstSuper->s_inodes_count = KU_EXT2_INODE_BLOCK_COUNT;
	pstSuper->s_blocks_count = KU_EXT2_DATA_BLOCK_COUNT;
	pstSuper->s_r_blocks_count = 0;
	pstSuper->s_free_blocks_count = KU_EXT2_DATA_BLOCK_COUNT;
	pstSuper->s_free_inodes_count =KU_EXT2_INODE_BLOCK_COUNT;
	pstSuper->s_first_data_block = KU_EXT2_DATA_BLOCK_OFFSET;
	pstSuper->s_log_block_size = KU_EXT2_BLOCK_SIZE;
	pstSuper->s_blocks_per_group = KU_EXT2_DATA_BLOCK_COUNT;
	pstSuper->s_inodes_per_group = KU_EXT2_INODE_BLOCK_COUNT;

	time(&current_time);
	pstSuper->s_mtime = current_time;
	pstSuper->s_wtime = current_time;
	pstSuper->s_magic = KU_EXT2_SUPER_MAGIC;
	pstSuper->s_first_ino = KU_EXT2_INODE_BLOCK_OFFSET;
	pstSuper->s_inode_size = sizeof(struct inode);
	if(ku_ext2_write_super(buffer)<0)
		printf("Format failed...!\n");
	else
		printf("Format Success...!\n");
}

/**
 * ext2.h :: ku_ext2_info_super()
 */
extern void ku_ext2_info_super(){
	char buffer[KU_EXT2_BLOCK_SIZE]= {0,};
	struct super_block* pstSuper;
	time_t st_time;
	pstSuper = (struct super_block*)buffer;
	if(ku_ext2_read_super(pstSuper)<0){
		printf("super block read failed...!\n");
		return;
	}
	if(pstSuper->s_magic != KU_EXT2_SUPER_MAGIC){
		printf("We don't support this format...\n");
		return;
	}
	printf("Total Inode count: [%d]\t",pstSuper->s_inodes_count);
	printf("Total Block count: [%d]\n",pstSuper->s_blocks_count);

	printf("Free Inode count: [%d]\t\t",pstSuper->s_free_inodes_count);
	printf("Free Block count: [%d]\n",pstSuper->s_free_blocks_count);
	printf("First Data Block: [%d]\t\t",pstSuper->s_first_data_block);
	printf("Block Size: [%d]\n",pstSuper->s_log_block_size);
	printf("Blocks per Group: [%d]\t",pstSuper->s_blocks_per_group);
	printf("Inodes per Group: [%d]\n",pstSuper->s_inodes_per_group);
	printf("magic: [%d]\t\t",pstSuper->s_magic);
	printf("First Inode: [%d]\t\t",pstSuper->s_first_ino);
	printf("Inode Size: [%d]\n",pstSuper->s_inode_size);
	st_time = pstSuper->s_mtime;
	printf("last mount  time %s",ctime(&st_time));
	st_time = pstSuper->s_wtime;
	printf("last access time %s",ctime(&st_time));
	return;
}
