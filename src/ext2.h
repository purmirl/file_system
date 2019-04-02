/* 	Spec Description of Our Target
 *
 *	<Block 0> We don't care about that... ------------------------|
 *  | byte 0 512 bytes boot record (if present)                   |
 *	| byte 512 512 bytes additional boot record data (if present) |
 *	--------------------------------------------------------------|
 *
 *	<Block Group 1>------------------------------------------------|
 *	| <Block 1>----------------------------------------------------||
 * 	| | byte 1024 1024 bytes superblock                            ||
 * 	| |------------------------------------------------------------||
 *  |                                                               |
 * 	| <Block 2>----------------------------------------------------||
 * 	| | block 2 1 block block group descriptor table               ||
 *  | |------------------------------------------------------------||
 *  |                                                               |
 *	| <Block 3>----------------------------------------------------||
 * 	| | block 3 1 block data block bitmap                          ||
 *  | -------------------------------------------------------------||
 *  |                                                               |
 *	| <Block 4>----------------------------------------------------||
 * 	| | block 4 1 block inode bitmap                               ||
 *  | |------------------------------------------------------------||
 *  |                                                               |
 * 	|block 5 214 blocks inode table                                 |
 * 	|block 219 7974 blocks data blocks                              |
 * 	|----------------------------------------------------------------
 */

#include "Types.h"
#include "super.h"
#include "inode.h"
/*
 * OFFSET 관련 매크로는 확장할 때 반드시 수정해야함!
 * 부트로더 포함 오프셋이기 때문
 */
#define KU_EXT2_BLOCK_SIZE					1024
#define KU_EXT2_BOOTLOASER_BLOCK_COUNT		1

#define KU_EXT2_SUPER_MAGIC					0xBEEF
#define KU_EXT2_SUPER_BLOCK_OFFSET			1
#define KU_EXT2_SUPER_BLOCK_COUNT			1

#define KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET	2
#define KU_EXT2_BLOCK_GROUP_BLOCK_COUNT		1
#define KU_EXT2_BLOCK_GROUP_COUNT			1

#define KU_EXT2_INODE_BITMAP_BLOCK_OFFSET	4
#define KU_EXT2_INODE_BITMAP_BLOCK_COUNT	1

#define KU_EXT2_BLOCK_BITMAP_BLOCK_OFSSET	3
#define KU_EXT2_BLOCK_BITMAP_BLOCK_COUNT	1

#define KU_EXT2_INODE_BLOCK_OFFSET			5
#define KU_EXT2_INODE_BLOCK_COUNT			214

#define KU_EXT2_DATA_BLOCK_OFFSET			219
#define KU_EXT2_DATA_BLOCK_COUNT			7974

#define KU_EXT2_BLOCK_GROUP_TOTAL_COUNT		(KU_EXT2_SUPER_BLOCK_COUNT + KU_EXT2_BLOCK_GROUP_BLOCK_COUNT +\
											KU_EXT2_BLOCK_BITMAP_BLOCK_COUNT + KU_EXT2_INODE_BITMAP_BLOCK_COUNT +\
											KU_EXT2_INODE_BLOCK_COUNT + KU_EXT2_DATA_BLOCK_COUNT)
/*
 * Function prototypes
 */

/* balloc.c */
extern int ext2_bg_has_super(struct super_block *sb, int group);
extern unsigned long ext2_bg_num_gdb(struct super_block *sb, int group);
extern int ext2_new_block (struct inode *, unsigned long,
			   __u32 *, __u32 *, int *);
extern void ext2_free_blocks (struct inode *, unsigned long,
			      unsigned long);
extern unsigned long ext2_count_free_blocks (struct super_block *);
extern unsigned long ext2_count_dirs (struct super_block *);
extern void ext2_check_blocks_bitmap (struct super_block *);
/*extern struct ext2_group_desc * ext2_get_group_desc(struct super_block * sb,
						    unsigned int block_group,
						    struct buffer_head ** bh);
*/
/* ialloc.c */
extern void ku_ext2_init_root(struct inode *root);
extern int ku_ext2_format_root();
extern int ext2_new_inode (struct inode *target_inode);
extern unsigned int ext2_check_inodes_bitmap (__u32 bg_block_bitmap);
extern long bit_search(unsigned long val,long size, long offset);
//extern struct inode * ext2_new_inode (struct inode *, int);
//extern void ext2_free_inode (struct inode *);
//extern unsigned long ext2_count_free_inodes (struct super_block *);
//extern unsigned int ext2_check_inodes_bitmap (__u32 bg_block_bitmap);
/*
extern unsigned long ext2_count_free (struct buffer_head *, unsigned);
*/

/* namei.c */
struct directory_entry *ext2_get_parent(struct directory_entry *child);

/* namei.c */
extern const struct inode_operations ext2_dir_inode_operations;
extern const struct inode_operations ext2_special_inode_operations;

/* symlink.c */
extern const struct inode_operations ext2_fast_symlink_inode_operations;
extern const struct inode_operations ext2_symlink_inode_operations;
