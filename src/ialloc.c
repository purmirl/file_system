/*
 * ialloc.c
 *
 *  Created on: 2019. 3. 22.
 *      Author: DEWH
 */
#include <time.h>
#include <string.h>
#include "ext2.h"
#include "SectorIO.h"
#include "group.h"

extern struct ext2_manager my_manager;

extern void ku_ext2_init_root(struct inode *root)
{
	time_t current_time;
	time(&current_time);
	root->i_mode = 0x777;
	root->i_uid = 0;
	root->i_atime= current_time;
	root->i_ctime= current_time;
	root->i_mtime= current_time;
	root->i_dtime= (__u64)NULL;
	root->i_gid = 0;
	root->i_links_count = 0;
	root->i_blocks = 1;
	root->i_block[0] = my_manager.g_first_data_block;
	/*
	 * balloc 을 통해 디렉토리를 설정해줘야 함.
	 * */
	for(int i=1;i<15;i++){
		root->i_block[i] = 0;
	}
	root->i_size = 32;
}
extern int ku_ext2_format_root()
{
	char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	struct block_group *pst_group;
	char inode_buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	struct inode *root = (struct inode *)inode_buffer;
	__u32 temp;
	if(Block_Read(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET, 1) < 0)
		return -1;

	pst_group = (struct block_group *)buffer;
	temp = pst_group->bg_inode_table;
	ku_ext2_init_root(root);
	memcpy(buffer,root,KU_EXT2_BLOCK_SIZE);
	if(Block_Write(buffer, temp, 1) < 0)
		return -1;
	return 1;
}
extern int ext2_new_inode (struct inode *target_inode)
{
	/*
	 * Parameter: Inode structre that we want to write on disk
	 * Desciption: Find the appropriate space of inode table, and write it down.
	 * return: On success return 1, Fail return 0
	 * */
	char buffer[KU_EXT2_BLOCK_SIZE] = {0,};
	struct block_group *pst_group;
	int i;
	int j = 0;
	__u32 inode_offset;
	pst_group = (struct block_group *)buffer;
	while(1){
		/* Referencing the group descriptor */
		Block_Read(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET + j, 1);
		for(i = 0; i * sizeof(struct block_group) < KU_EXT2_BLOCK_SIZE; i++){
			/* 마지막 디스크립터를 발견*/
			if(pst_group[i].bg_block_bitmap == 0 && pst_group[i].bg_inode_bitmap == 0){
				printf("No free inode...\n");
				return -1;
			}
			if(pst_group[i].bg_free_inodes_count!=0){
				inode_offset = ext2_check_inodes_bitmap(pst_group[i].bg_inode_bitmap);
				pst_group[i].bg_free_inodes_count--;
				/* 그룹 디스크립터를 갱신 */
				Block_Write(buffer, KU_EXT2_BLOCK_GROUP_BLOCK_OFFSET + j, 1);
				if(inode_offset == -1)
					return -1;
				memcpy(buffer,target_inode,KU_EXT2_BLOCK_SIZE);
				/* inode table을 갱신 */
				Block_Write(buffer, pst_group[i].bg_inode_table + inode_offset, 1);
				return 1;
			}
		}
		j++;
	}
}
//extern void ext2_free_inode (struct inode *);
//extern unsigned long ext2_count_free_inodes (struct super_block *);
/* 비트맵 시작 블록 오프셋을 받고, 빈 곳을 서치한다. */
extern int ext2_check_inodes_bitmap (__u32 bg_block_bitmap)
{
	/*
	 * Parameter: block offset of the bitmap
	 * Desciption: Search the usable inode from indoe bitmap and renew the bitmap
	 * return: On success return 1, Fail return 0
	 * */
	char buffer[KU_EXT2_BLOCK_SIZE];
	char eightbit;
	int bit_offset;
	/* 한 블럭짜리 inode 비트맵을 읽는다. */
	if(Block_Read(buffer, bg_block_bitmap, 1)<0){
		printf("Bitmap read failed...\n");
		return -1;
	}
	/*1을 세팅할 오프셋을 찾고 갱신*/
	for(int i =0; i < KU_EXT2_BLOCK_SIZE;i++){
		eightbit = *((char*)(buffer+i));
		bit_offset = simple_bit_search(eightbit);
		if(bit_offset < 8){
			*((char*)(buffer+i)) |= (0x1 << (bit_offset));
			bit_offset = 8*i + bit_offset;
			if(Block_Write(buffer, bg_block_bitmap, 1) <0){
				printf("Bitmap allocate failed...\n");
				return -1;
			}
			return bit_offset;
		}
	}
	/* First inode is for root */
	printf("Can't find free inode...\n");
	return -1;
}
/* 간단한 버전 */
int simple_bit_search(char eightbit){
	int temp = 0;
	while(((eightbit & 0x1) == 0x0)&& (temp < 8)){
		eightbit >>= 1;
		temp++;
	}
	return temp;
}
/* 바이너리 서치로 0인 비트를 찾아낸다. */
extern long bit_search(unsigned long val,long size, long offset)
{
	unsigned long temp;
	if(size == 1)
		return offset;
	else{
		temp = ~0;
		temp >>= sizeof(val)* 8 - size/2;
		if((val & temp) != temp){
			return bit_search( val, size/2, offset);
		}else{
			return bit_search( val >> (size/2),size/2,offset + size/2);
		}
	}
}

