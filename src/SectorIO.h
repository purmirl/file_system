#include <stdio.h>

#define BLOCK_SIZE	1024

/* ��ο� ����� HDD.img�� fopen�Ͽ� �ڵ��� ������ ���� */
static FILE* image;
/* �ڵ��� ����/��ȯ�Ѵ�. */
void init_IO();
int close_IO();

/* HDD.img�� ��� ������, �� �� ����� (�д�/����)��(block_num), ��� ��� (�д�/����)��(block_count) */
int Block_Read(void* buffer, int block_num, int block_count);
int Block_Write(void* buffer, int block_num, int block_count);

