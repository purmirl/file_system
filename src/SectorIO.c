#include "SectorIO.h"

void init_IO(){
	image = fopen("HDD.img","rb+");
	if(image == NULL)
		fprintf(stderr,"fopen failed...!\n");
}
int Block_Read(void* buffer, int block_num, int block_count){
	if(fseek(image, block_num * BLOCK_SIZE,SEEK_SET)<0){
		fprintf(stderr,"fseek failed...!\n");
		return -1;
	}
	return fread(buffer, 1, BLOCK_SIZE* block_count, image) / BLOCK_SIZE;
}
int Block_Write(void* buffer, int block_num,  int block_count){
	if(fseek(image, block_num * BLOCK_SIZE,SEEK_SET)<0){
			fprintf(stderr,"fseek failed...!\n");
			return -1;
	}
	return fwrite(buffer, 1, BLOCK_SIZE* block_count, image) / BLOCK_SIZE;
}
int close_IO(){
	return fclose(image);
}
