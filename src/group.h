/*
 * group.h
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */

#ifndef __FILE_SYSTEM_SRC_GROUP_H_
#define __FILE_SYSTEM_SRC_GROUP_H_
#include "Types.h"

struct block_group{
	__u32 bg_block_bitmap;			/* block id of the first block of the ¡°block bitmap¡± for the group represented */
	__u32 bg_inode_bitmap;			/* block id of the first block of the ¡°inode bitmap¡± for the group represented */
	__u32 bg_inode_table;			/* block id of the first block of the ¡°inode table¡± for the group represented */
	__u16 bg_free_blocks_count;
	__u16 bg_free_inodes_count;
	__u16 bg_used_dirs_count;
	__u16 bg_pad;
	__u32 bg_reserved[3];
};

#endif /* FILE_SYSTEM_SRC_GROUP_H_ */
