/*
 * memcheck.h
 *
 *  Created on: 2013-11-13
 *      Author: aaaa
 */

#ifndef MEMCHECK_H_
#define MEMCHECK_H_

//g++ tt.c -o tt  -I ~/Bullet/bullet-read-only/src -lBulletCollision -lLinearMath
#include "stdio.h"
#define _DEBUG
#define __cdecl
#include "stdlib.h"

#include <list>
#include "string.h"
using namespace std;
#ifdef _DEBUG

void AddTrack(unsigned int addr, unsigned int asize, const char *fname,
		unsigned int lnum);

void RemoveTrack(unsigned int addr);
void * __cdecl operator new(size_t size, const char * file, int line) {
	void* p = malloc(size);
	//      void * p = malloc(size);
	printf("new==%d, %s, %d, size:%d==\n", *(int *) &p, file, line, size);

	AddTrack(*(unsigned int *) &p, size, file, line);
	return p;
}

void __cdecl operator delete(void *p) {
	printf("delete====%d\n", *(int *) &p);
	RemoveTrack(*(unsigned int *) &p);
	free(p);
	p = NULL;

}

void __cdecl operator delete[](void *p) {

	RemoveTrack(*(unsigned int *) &p);
	free(p);
	p = NULL;
}
void* operator new[](size_t size, const char * file, int line) {
	printf("new[]:%d\n", size);

	void *p = malloc(size);

	AddTrack(*(unsigned int *) &p, size, file, line);

	printf("new==%d, %s, %d, size:%d==\n", *(int *) &p, file, line, size);

	return p;
}
/*
 void* operator new  ( size_t count, const std::nothrow_t& )
 {
 }
 void* operator new[]( size_t count, const std::nothrow_t& )
 {
 }
 void* operator new  ( size_t, void* ptr )
 {
 }
 void* operator new[]( size_t, void* ptr )
 {
 }
 */

#endif

//#include "btBulletCollisionCommon.h"
struct aa {
	aa() {
		printf("aaaaaaaa\n");
	}
	~aa() {
		printf("bbbbbbbb\n");
	}
};

typedef struct memcheck {
	unsigned int address;
	unsigned int size;
	char file[64];
	unsigned int line;
} ALLOC_INFO;

typedef list<ALLOC_INFO*> AllocList;

AllocList allocList;

void AddTrack(unsigned int addr, unsigned int asize, const char *fname,
		unsigned int lnum) {
	ALLOC_INFO *info;

	info = (ALLOC_INFO *) malloc(sizeof(ALLOC_INFO));
	info->address = addr;
	strncpy(info->file, fname, 63);
	info->line = lnum;
	info->size = asize;
	allocList.insert(allocList.begin(), info);
}
;

void RemoveTrack(unsigned int addr) {
	AllocList::iterator i;

	for (i = allocList.begin(); i != allocList.end(); i++)

	{
		if ((*i)->address == addr) {
			allocList.remove((*i));
			break;
		}
	}
}

void DumpUnfreed() {
	AllocList::iterator i;
	unsigned int totalSize = 0;
	char buf[1024];

	printf("------------------------------------------------------------\n");

	for (i = allocList.begin(); i != allocList.end(); i++) {
		sprintf(buf, "%-50s: LINE %d, ADDRESS %d %d unfreed ", (*i)->file,
				(*i)->line, (*i)->address, (*i)->size);
		printf("%s\n", buf);
		totalSize += (*i)->size;
	}
	sprintf(buf,
			"----------------------------------------------------------- ");
	printf("%s\n", buf);
	sprintf(buf, "Total Unfreed: %d bytes ", totalSize);
	printf("%s\n", buf);
}

#ifdef _DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#define new DEBUG_NEW

/*
 new==13516816, tt.c, 71==
 aaaaaaaa
 new==13516848, tt.c, 75==
 bbbbbbbb
 delete====13516816

 */

//int main()
//{
//        struct aa * p = new (struct aa);
//
//        //      delete p;
//
//        int * p1 = new int[3];
//
//        delete p;
//        return 0;
//}
#endif /* MEMCHECK_H_ */
