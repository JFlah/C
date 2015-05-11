#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void myrealloc(void *p, int newSize);
int length(int *p);
int *nextBlock(int *p);
void *myalloc2(int size);
void * myalloc(int size);
void unallocateBlock(int *p);
void myfree(void *p);

int *start;

int main() {

}

void myrealloc(void *p, int size){
	int newSize = ((size+3)/8 + 1) * 8;
	int oldSize = length(p); // * 4 if length returns bytes instead of bits

	if (newSize == oldSize){
		return p;
	}

	if (newSize < oldSize){
		int diff = oldSize - newSize;
		*(p-1) = newSize;
		*(nextBlock(p)-1) = diff;
		return p;
	}

	if (newSize > oldSize){
		int *p2 = myalloc(newSize);
		memcpy(p2, p, oldSize);
		myfree(p);
		return p2;
	}
}

void myfree(void *p) {
	unallocateBlock(p); 
}

void unallocateBlock(int *p) {
	*(p-1) = (*(p-1)-1); 
}

void * myalloc(int size) {
	void *myalloc(int size);

	void *ptr = myalloc2(size);

	if (ptr == NULL) {
		coalesce();
		ptr = myalloc2(size);
	}
	return ptr;
}

void *myalloc2(int size) {
    int mem_size = ((size+3)/8 + 1) * 8;

    int *ptr = start;

	int newSize=0;

	int oldsize = *(start-1);

	while(oldsize != 0){
		if (oldsize >= mem_size && !blockAllocated(ptr)){
			*(ptr-1) = mem_size; 	
			allocateBlock(ptr); 
			newSize = oldsize - mem_size;
			if (newSize > 0)
				*(nextBlock(ptr)-1) = newSize;
			return ptr;
		}
		ptr = nextBlock(ptr);

		oldsize = *(ptr-1);
	}
	fprintf(stderr, "No space to allocate more\n");
  	return NULL;
}

int length(int *p) {
	return (*(p-1)/8*8); // because div is floored, forces ctrl word to 000 leaving only size
}

int *nextBlock(int *p) {
	return (p + length(p)/4); 
}