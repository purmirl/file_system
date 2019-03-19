/*
 * super.c
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */
#include "SectorIO.h"
#include "ext2.h"
extern void ku_ext2_write_super (struct super_block *pstSuper)
{
	Block_Write(pstSuper, KU_EXT2_SUPER_BLOCK_OFFSET, KU_EXT2_SUPER_BLOCK_COUNT);
}
extern void ku_ext2_read_super (struct super_block *pstSuper)
{
	Block_Read(pstSuper, KU_EXT2_SUPER_BLOCK_OFFSET, KU_EXT2_SUPER_BLOCK_COUNT);
}
extern void ku_ext2_init_super(struct super_block *pstSuper)
{

}
extern void ku_ext2_info_super(struct super_block *pstSuper)
{
	if(pstSuper->s_magic != KU_EXT2_SUPER_MAGIC){
		printf("We don't support this format...\n");
		return;
	}
	printf("Total Inode count: [%d]\n",pstSuper->s_inodes_count);
	printf("Total Block count: [%d]\n",pstSuper->s_blocks_count);

	printf("Free Inode count: [%d]\n",pstSuper->s_free_inodes_count);
	printf("Free Block count: [%d]\n",pstSuper->s_free_blocks_count);
	printf("First Data Block: [%d]\n",pstSuper->s_first_data_block);
	printf("Block Size: [%d]\n",pstSuper->s_log_block_size);
	printf("Blocks per Group: [%d]\n",pstSuper->s_blocks_per_group);
	printf("Inodes per Group: [%d]\n",pstSuper->s_inodes_per_group);
	printf("magic: [%d]\n",pstSuper->s_magic);
	printf("First Inode: [%d]\n",pstSuper->s_first_ino);
	printf("Inode Size: [%d]\n",pstSuper->s_inode_size);

	return;
}
