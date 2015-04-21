#include "mymalloc.h"

#define MAXSIZE 25000

struct MemoryAccess
{
	int isUsed;
	int memSize;
	struct MemoryAccess *prevMem, *nextMem;
}; 

static char sizeOfBlock[MAXSIZE];
static const int sizeOfEntry = MAXSIZE/sizeof(struct MemoryAccess)+1;
static void *accessEntries[MAXSIZE/sizeof(struct MemoryAccess)+1] = {0};


static int indexPeek()
{
	int j;
	for (j = 0; j < sizeOfEntry; j++)
		if (accessEntries[j] == 0)
			return j;
	return 1;
}


void *mymalloc(unsigned int range, char *file, int line)
{
	static int created = 0;
	struct MemoryAccess *b;
	struct MemoryAccess *next;
	static struct MemoryAccess *source;

	if (range == 0)
	{
		fprintf(stderr, "Unable to allocate enough memory in FILE: '%s' on LINE: '%d'\n", file, line);
		return 0;
	}

	if(!created)
	{
		source = (struct MemoryAccess*) sizeOfBlock;
		source->prevMem = source->nextMem = 0;
		source->memSize = MAXSIZE - sizeof(struct MemoryAccess);
		source->isUsed = 1;
		created = 1;
		accessEntries[indexPeek()] = sizeOfBlock;
	}

	b = source;
	do
	{
		if(b->memSize < range || !b->isUsed)
		{
			b = b->nextMem;
		}
		else if(b->memSize < (range + sizeof(struct MemoryAccess)))
		{
			b->isUsed = 0;
			return (char*)b + sizeof(struct MemoryAccess);
		}
		else
		{
			next = (struct MemoryAccess*)((char*)b + sizeof(struct MemoryAccess) + range);
			next->prevMem = b;
			next->nextMem = b->nextMem;
			next->memSize = b->memSize - sizeof(struct MemoryAccess) - range;
			next->isUsed = 1;
			accessEntries[indexPeek()] = next;
			b->memSize = range;
			b->isUsed = 0;
			b->nextMem = next;
			return (char*)b + sizeof(struct MemoryAccess);
		}
	} while (b != 0);

	fprintf(stderr, "The memory space requested is insufficient (%d bytes) in the FILE: '%s' on LINE: '%d'\n", range, file, line);
	return 0;
}

void myfree(void *b, char *file, int line)
{

	struct MemoryAccess *nextMem;
	struct MemoryAccess *prevMem;
	struct MemoryAccess *ptr;

	if (b == NULL)
	{
		fprintf(stderr, "NULL pointer in file, causing free to fail in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	ptr = (struct MemoryAccess*)((char*)b - sizeof(struct MemoryAccess));

	int k;
	int istrue = 0;
	for (k = 0; k < sizeOfEntry; k++)
	{
		if (ptr == accessEntries[k] && !ptr->isUsed)
		{
			istrue = 1;
			break;
		}
	}
	if (!istrue)
	{
		fprintf(stderr, "Trying to free memory that was not previously allocated in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	if((prevMem = ptr->prevMem) != 0 && prevMem->isUsed)
	{
		prevMem->memSize += sizeof(struct MemoryAccess) + ptr->memSize;
		accessEntries[k] = 0;
	}
	else
	{
		ptr->isUsed = 1;
		prevMem = ptr;
	}
	if((nextMem = ptr->nextMem) != 0 && nextMem->isUsed)
	{
		prevMem->memSize += sizeof(struct MemoryAccess) + nextMem->memSize;
		prevMem->nextMem = nextMem->nextMem;
		for (k = 0; k < sizeOfEntry; k++) 
		{
			if (nextMem == accessEntries[k])
			 {
				accessEntries[k] = 0; 
				break;
			}
		}
	}
}
