#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 1

float getRandNum()
{
	return (float)rand() / (float)(RAND_MAX);
}

void procTimeResearch()
{
	float vecA[4], vecB[4], res;
	vecA[0] = getRandNum();
	vecA[1] = getRandNum();
	vecA[2] = getRandNum();
	vecA[3] = getRandNum();
	
	vecB[0] = getRandNum();
	vecB[1] = getRandNum();
	vecB[2] = getRandNum();
	vecB[3] = getRandNum();
	
	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < MAX_LEN; i++)
	{
		res = 0;
		for (int j = 0; j < 4; j++)
			res += vecA[j] * vecB[j];
	}
	endTime = clock();
	//printf("[%f %f %f %f] * [%f %f %f %f] = %f\n", vecA[0], vecA[1], vecA[2], vecA[3], vecB[0], vecB[1], vecB[2], vecB[3], res);
	
	printf("Proc time: %lf ms\n", (double)(endTime - startTime) / MAX_LEN);
}

void asmTimeResearch()
{
	float vecA[4], vecB[4], res;
	vecA[0] = getRandNum();
	vecA[1] = getRandNum();
	vecA[2] = getRandNum();
	vecA[3] = getRandNum();
	
	vecB[0] = getRandNum();
	vecB[1] = getRandNum();
	vecB[2] = getRandNum();
	vecB[3] = getRandNum();
	
	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < MAX_LEN; i++)
	{
		asm(
			"movaps xmm1, %1\n"
			"movaps xmm2, %2\n"
			"mulps xmm1, xmm2\n"
			"addps xmm0, xmm1\n"
			
			"movss %0, xmm0\n"
			: "=m"(res)
			: "m"(vecA), "m"(vecB)
			: "xmm0", "xmm1", "xmm2"
		);
	}
	endTime = clock();
	//printf("[%f %f %f %f] * [%f %f %f %f] = %f\n", vecA[0], vecA[1], vecA[2], vecA[3], vecB[0], vecB[1], vecB[2], vecB[3], res);
	
	printf("FPU extension time: %lf ms\n", (double)(endTime - startTime) / MAX_LEN);
}

int main(void)
{
	procTimeResearch();
	asmTimeResearch();
	return EXIT_SUCCESS;
}