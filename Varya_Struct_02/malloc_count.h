#pragma once
#include "config.h"

int mallocCount = 0;
int reallocCount = 0;
int callocCount = 0;
int freeCount = 0;

void saveStats()
{
	FILE* file = fopen("memstat.txt", "w");
	if (file == NULL)
	{
		exit(MALLOC_SAVE_FAILURE);
	}

	fprintf("malloc:%d\nrelloc:%d\ncalloc:%d\nfree:%d", mallocCount, reallocCount, callocCount, freeCount);

}