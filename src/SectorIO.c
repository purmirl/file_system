/**
 * 2019 EXT2 Study
 * SectorIO.h
 */

#include "SectorIO.h"

static FILE* image;

/** 
 * init_IO() : File open function.
 */
void init_IO(){
	image = fopen("HDD.img","rb+");
	if(image == NULL)
		fprintf(stderr,"fopen failed...!\n");
}

/**
 * Block_Read(void* buffer, int block_num, int block_count) : Read one block function.
 */
int Block_Read(void* buffer, int block_num, int block_count){
	if(fseek(image, block_num * KU_EXT2_BLOCK_SIZE,SEEK_SET)<0){
		fprintf(stderr,"fseek failed...!\n");
		return -1;
	}
	return fread(buffer, 1, KU_EXT2_BLOCK_SIZE* block_count, image) / KU_EXT2_BLOCK_SIZE;
}

/**
 * Block_Write(void* buffer, int block_num, int block_count) : Write one block function.
 */
int Block_Write(void* buffer, int block_num,  int block_count){
	if(fseek(image, block_num * KU_EXT2_BLOCK_SIZE,SEEK_SET)<0){
			fprintf(stderr,"fseek failed...!\n");
			return -1;
	}
	return fwrite(buffer, 1, KU_EXT2_BLOCK_SIZE* block_count, image) / KU_EXT2_BLOCK_SIZE;
}

/**
 * close_IO() : File close function.
 */
int close_IO(){
	return fclose(image);
}
