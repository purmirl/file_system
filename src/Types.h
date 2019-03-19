#ifndef __TYPES_H__
#define __TYPES_H__

#define BYTE 	unsigned char
#define WORD 	unsigned short
#define DWORD 	unsigned int
#define QWORD	unsigned long
#define BOOL	unsigned char

#define TRUE 	1
#define FALSE	0

/* ������ ext2.h ȣȯ�� ��ũ�� */
typedef DWORD	uid_t;
typedef DWORD	gid_t;

typedef BYTE	__u8;
typedef WORD	__u16;
typedef DWORD	__u32;
typedef QWORD	__u64;
#endif /* __TYPES_H__ */
