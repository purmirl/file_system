#include <stdio.h>

#define BLOCK_SIZE	1024

/* 경로에 저장된 HDD.img를 fopen하여 핸들을 저장할 변수 */
static FILE* image;
/* 핸들을 열고/반환한다. */
void init_IO();
int close_IO();

/* HDD.img를 블록 단위로, 몇 번 블록을 (읽는/쓰는)지(block_num), 블록 몇개를 (읽는/쓰는)지(block_count) */
int Block_Read(void* buffer, int block_num, int block_count);
int Block_Write(void* buffer, int block_num, int block_count);

