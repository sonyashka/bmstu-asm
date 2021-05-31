#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define A 100.1
#define B 200.2
#define COUNT 1e6

void floatTimeResearch()
{
	printf("\nFloat is %ld bit\n", sizeof(float) * CHAR_BIT);
	clock_t startTime, endTime;
	long runTime;
	float a = A, b = B, res = 0;
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		res = a + b;
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Sum float: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"flds %1\n"
			"flds %2\n"
			"faddp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Sum ASM float: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		res = a * b;
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Mult float: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"flds %1\n"
			"flds %2\n"
			"fmulp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Mult ASM float: %lf ns\n", runTime / COUNT);
}

void doubleTimeResearch()
{
	printf("\nDouble is %ld bit\n", sizeof(double) * CHAR_BIT);
	clock_t startTime, endTime;
	long runTime;
	double a = A, b = B, res = 0;
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		res = a + b;
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Sum double: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"fldl %1\n"
			"fldl %2\n"
			"faddp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Sum ASM double: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		res = a * b;
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Mult double: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"fldl %1\n"
			"fldl %2\n"
			"fmulp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Mult ASM double: %lf ns\n", runTime / COUNT);
}

void longDoubleTimeResearch()
{
	printf("\nLong double is %ld bit\n", sizeof(long double) * CHAR_BIT);
	clock_t startTime, endTime;
	long runTime;
	long double a = A, b = B, res = 0;
	
	//for (int i = 0; i < COUNT; i++)
	//{
		//startTime = clock();
		//res = a + b;
		//endTime = clock() - startTime;
		//runTime += endTime;
	//}
	//printf("Sum long double: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"fldt %1\n"
			"fldt %2\n"
			"faddp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Sum ASM long double: %lf ns\n", runTime / COUNT);
	
	//for (int i = 0; i < COUNT; i++)
	//{
		//startTime = clock();
		//res = a * b;
		//endTime = clock() - startTime;
		//runTime += endTime;
	//}
	//printf("Mult long double: %lf ns\n", runTime / COUNT);
	
	for (int i = 0; i < COUNT; i++)
	{
		startTime = clock();
		asm(
			"fldt %1\n"
			"fldt %2\n"
			"fmulp\n"
			"fstps %0\n"
			: "=m" (res)
			: "m" (a), "m" (b)
		);
		endTime = clock() - startTime;
		runTime += endTime;
	}
	printf("Mult ASM long double: %lf ns\n", runTime / COUNT);
}

void sinPiTimeResearch()
{
	float half = 0.5, res;
	
	printf("\n");
	printf("Library-func sin(3.14): %lf\n", sin(3.14));
	printf("Library-func sin(3.141596): %lf\n", sin(3.141596));
	asm(
		"fldpi\n"
        "fsin\n"
        "fstps %0\n" 
        : "=m" (res)
	);
	printf("FPU sin(pi): %f\n", res);
	
	printf("\nLibrary-func sin(3.14 / 2): %lf\n", sin(3.14 / 2));
	printf("Library-func sin(3.141596 / 2): %lf\n", sin(3.141596 / 2));
	asm(
		"flds %1\n"
		"fldpi\n"
		"fmulp\n"
        "fsin\n"
        "fstps %0\n" 
        : "=m" (res)
		: "m" (half)
	);
	printf("FPU sin(pi / 2): %f\n", res);
}

int main(void)
{
	floatTimeResearch();
	doubleTimeResearch();
	//longDoubleTimeResearch();
	sinPiTimeResearch();
	return EXIT_SUCCESS;
}