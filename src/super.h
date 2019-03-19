/*
 * super.h
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */

#ifndef __FILE_SYSTEM_SRC_SUPER_H_
#define __FILE_SYSTEM_SRC_SUPER_H_
#include "Types.h"

struct super_block{
	__u32 s_inodes_count; 			/* Inodes count */
	__u32 s_blocks_count; 			/* Blocks count */
	__u32 s_r_blocks_count;			/* Reserved blocks count */
	__u32 s_free_blocks_count; 		/* Free blocks count */
	__u32 s_free_inodes_count; 		/* Free inodes count */
	__u32 s_first_data_block; 		/* First Data Block */
	__u32 s_log_block_size; 		/* Block size */
	__u32 s_blocks_per_group; 		/* # Blocks per group */
	__u32 s_inodes_per_group; 		/* # Inodes per group */
	__u16 s_magic; 					/* Magic signature */
	__u32 s_first_ino; 				/* First non-reserved inode */
	__u16 s_inode_size; 			/* size of inode structure */
};

extern void ku_ext2_write_super (struct super_block *);
extern void ku_ext2_read_super (struct super_block *);
#endif /* FILE_SYSTEM_SRC_SUPER_H_ */
