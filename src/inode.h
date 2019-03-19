/*
 * inode.h
 *
 *  Created on: 2019. 3. 19.
 *      Author: DEWH
 */

#ifndef __FILE_SYSTEM_SRC_INODE_H_
#define __FILE_SYSTEM_SRC_INODE_H_
#include "Types.h"
/*
 *      i_mode
 */
#define KU_EXT2_S_IFSOCK 0xC000 //socket
#define KU_EXT2_S_IFLNK 0xA000  //symbolic link
#define KU_EXT2_S_IFREG 0x8000  //regular file
#define KU_EXT2_S_IFBLK 0x6000  //block device
#define KU_EXT2_S_IFDIR 0x4000  //directory
#define KU_EXT2_S_IFCHR 0x2000  //character device
#define KU_EXT2_S_IFIFO 0x1000  //fifo
/* -- process execution user/group override -- */
#define KU_EXT2_S_ISUID 0x0800  //Set process User ID
#define KU_EXT2_S_ISGID 0x0400  //Set process Group ID
#define KU_EXT2_S_ISVTX 0x0200  //sticky bit
/* -- access rights -- */
#define KU_EXT2_S_IRUSR 0x0100  //user read
#define KU_EXT2_S_IWUSR 0x0080  //user write
#define KU_EXT2_S_IXUSR 0x0040  //user execute
#define KU_EXT2_S_IRGRP 0x0020  //group read
#define KU_EXT2_S_IWGRP 0x0010  //group write
#define KU_EXT2_S_IXGRP 0x0008  //group execute
#define KU_EXT2_S_IROTH 0x0004  //others read
#define KU_EXT2_S_IWOTH 0x0002  //others write
#define KU_EXT2_S_IXOTH 0x0001  //others execute


struct inode{
	__u16 i_mode;
	__u16 i_uid;
	__u32 i_size;
	__u32 i_atime;		/* last time this inode was accessed. */
	__u32 i_ctime;		/* when the inode was created.*/
	__u32 i_mtime;		/* last time this inode was modified. */
	__u32 i_dtime;		/* when the inode was deleted. */
	__u16 i_gid;
	__u16 i_links_count;
	__u32 i_blocks;		/* total number of blocks reserved to contain the data of this inode */
	__u32 i_block[15];	/* each block points to the blocks containing the data for this inode. */
};

struct directory_entry{
	__u32 inode;
	__u16 rec_len;
	__u8  name_len;
	__u8  file_type;
	/* name */
};

extern void ku_ext2_read_inode (struct inode *);
extern int ku_ext2_write_inode (struct inode *, int);
extern void ku_ext2_put_inode (struct inode *);
extern void ku_ext2_delete_inode (struct inode *);
extern int ku_ext2_sync_inode (struct inode *);
extern void ku_ext2_discard_prealloc (struct inode *);
//extern int ext2_get_block(struct inode *, sector_t, struct buffer_head *, int);
extern void ku_ext2_truncate (struct inode *);
//extern int ext2_setattr (struct directory_entry *, struct iattr *);
extern void ku_ext2_set_inode_flags(struct inode *inode);
/*
extern const struct address_space_operations ext2_aops;
extern const struct address_space_operations ext2_aops_xip;
extern const struct address_space_operations ext2_nobh_aops;
*/


#endif /* FILE_SYSTEM_SRC_INODE_H_ */
