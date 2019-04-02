/*
 * balloc.c
 *
 *  Created on: 2019. 3. 22.
 *      Author: DEWH
 */
#include "ext2.h"
#include "SectorIO.h"
#include "group.h"
extern int ext2_new_datablock (struct inode *target_inode)
{

}

extern int ext2_bg_has_super(struct super_block *sb, int group);
extern unsigned long ext2_bg_num_gdb(struct super_block *sb, int group);
extern int ext2_new_block (struct inode *, unsigned long,
			   __u32 *, __u32 *, int *);
extern void ext2_free_blocks (struct inode *, unsigned long,
			      unsigned long);
extern unsigned long ext2_count_free_blocks (struct super_block *);
extern unsigned long ext2_count_dirs (struct super_block *);
extern void ext2_check_blocks_bitmap (struct super_block *);
