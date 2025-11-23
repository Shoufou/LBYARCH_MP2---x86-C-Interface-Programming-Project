#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

extern void Asm_daxpy(int n, double A, double* vectorX, double* vectorY, double* vectorZ);
extern void daxpy_c(int n, double A, double* vectorX, double* vectorY, double* vectorZ);



int main(int argc, char* argv[]) {
	int n = 1; //ensures that memory can be allocated
	double A = 0.0; //scalar value A (is a float to work with xmm)
	clock_t start_time; //variables to time functions
	clock_t end_time;
	double time_used_c = 0.0;
	double time_used_asm = 0.0;


	//gets the length of the vectors
	printf("Enter the length of the vectors: ");
	scanf_s("%d", &n);
	printf("The value of n is %d \n", n);

	//gets the value of A
	printf("Enter Value of A: ");
	scanf_s("%lf", &A);
	printf("A value: %1.2lf \n", A);

	//initializes vector X in memory
	double* vectorX = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Y in memory
	double* vectorY = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Z in memory
	double* vectorZ_asm = (double*)_aligned_malloc(n * sizeof(double), 32);
	double* vectorZ_C = (double*)_aligned_malloc(n * sizeof(double), 32);


	//get a string that represents the values of vector X
	char input[2048];
	printf("Enter Vector X: ");
	getchar();
	fgets(input, sizeof(input), stdin);

	//tokenize the string
	char* token;
	char* context = NULL;
	token = strtok_s(input, " ", &context);

	//loop through the rest of the string (gets the first n values)
	int ctr = 0;
	double value;
	char* end;

	while (ctr < n) {
		//default sets value to 0
		if (token == NULL) {
			vectorX[ctr] = 0;
		}

		else {
			value = strtod(token, &end);
			vectorX[ctr] = value;
		}
		//tells the function to continue on the same string
		token = strtok_s(NULL, " ", &context);
		ctr++;
	}


	//get a string that represents the values of vector Y
	char inputY[2048];
	printf("Enter Vector Y: ");
	fgets(inputY, sizeof(inputY), stdin);
	//tokenize the string
	char* tokenY;
	char* contextY = NULL;
	tokenY = strtok_s(inputY, " ", &contextY);

	//loop through the rest of the string (gets the first n values)
	ctr = 0;
	value = 0.0;
	char* endY;

	while (ctr < n) {
		//default sets value to 0
		if (tokenY == NULL) {
			vectorY[ctr] = 0;
		}

		else {
			value = strtod(tokenY, &endY);
			vectorY[ctr] = value;
		}
		//tells the function to continue on the same string
		tokenY = strtok_s(NULL, " ", &contextY);
		ctr++;
	}

	Asm_daxpy(n, A, vectorX, vectorY, vectorZ_asm);
	daxpy_c(n, A, vectorX, vectorY, vectorZ_C);
	int correct = 1;

	if (n > 10 && n!=0) {
		printf("Vector Z calculated with asm code: ");
		for (int i = 0; i < 10; i++) {
			printf("%1.2lf ", vectorZ_asm[i]);
		}

		printf("\nVector Z calculated with C code: ");
		for (int i = 0; i < 10; i++) {
			printf("%1.2lf ", vectorZ_C[i]);
		}

		correct = 1;
		for (int i = 0; i < n; i++) {
			if (fabs(vectorZ_C[i] - vectorZ_asm[i]) > 1e-10) {
				correct = 0;
				break;
			}
		}
		printf("\nx86-64 Correct: %s\n", correct ? "YES" : "NO");
	}
	
	else if(n < 10 && n != 0) {
		printf("\nVector Z calculated with asm code: ");
		for (int i = 0; i < n; i++) {
			printf("%1.2lf ", vectorZ_asm[i]);
		}

		printf("\nVector Z calculated with C code: ");
		for (int i = 0; i < n; i++) {
			printf("%1.2lf ", vectorZ_C[i]);
		}

		correct = 1;
		for (int i = 0; i < n; i++) {
			if (fabs(vectorZ_C[i] - vectorZ_asm[i]) > 1e-10) {
				correct = 0;
				break;
			}
		}
		printf("\nx86-64 Correct: %s\n", correct ? "YES" : "NO");
		printf("C Correct: %s\n", correct ? "YES" : "NO");
	}

	//2^20 size input testing
	n = 1048576;
	A = 5.0;
	//initializes vector X in memory
	vectorX = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Y in memory
	vectorY = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Z in memory
	vectorZ_asm = (double*)_aligned_malloc(n * sizeof(double), 32);
	vectorZ_C = (double*)_aligned_malloc(n * sizeof(double), 32);
	for (int i = 0; i < n - 1; i++) {
		vectorX[i] = i;
		vectorY[i] = i;
	}

	for (int i = 0; i < 30; i++) {
		start_time = clock();
		Asm_daxpy(n, A, vectorX, vectorY, vectorZ_asm);
		end_time = clock();
		time_used_asm += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

		start_time = clock();
		daxpy_c(n, A, vectorX, vectorY, vectorZ_C);
		end_time = clock();
		time_used_c += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	}

	time_used_asm /= 30;
	time_used_c /= 30;


	printf("\nVector Z with 2^20 input (asm): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_asm[i]);
	}

	printf("\nVector Z with 2^20 input (C): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_C[i]);
	}

	correct = 1;
	for (int i = 0; i < n; i++) {
		if (fabs(vectorZ_C[i] - vectorZ_asm[i]) > 1e-10) {
			correct = 0;
			break;
		}
	}
	printf("\nx86-64 Correct: %s\n", correct ? "YES" : "NO");
	printf("xC Correct: %s\n", correct ? "YES" : "NO");
	printf("Time taken in assembly (averaged out over 30 runs): %lf seconds\n", time_used_asm);
	printf("Time taken in C (averaged out over 30 runs): %lf seconds\n", time_used_c);

	//2^24 size input testing
	n = 16777216;
	A = 5.0;
	time_used_asm = 0.0;
	time_used_c = 0.0;
	//initializes vector X in memory
	vectorX = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Y in memory
	vectorY = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Z in memory
	vectorZ_asm = (double*)_aligned_malloc(n * sizeof(double), 32);
	vectorZ_C = (double*)_aligned_malloc(n * sizeof(double), 32);
	for (int i = 0; i < n - 1; i++) {
		vectorX[i] = i;
		vectorY[i] = i;
	}

	for (int i = 0; i < 30; i++) {
		start_time = clock();
		Asm_daxpy(n, A, vectorX, vectorY, vectorZ_asm);
		end_time = clock();
		time_used_asm += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

		start_time = clock();
		daxpy_c(n, A, vectorX, vectorY, vectorZ_C);
		end_time = clock();
		time_used_c += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	}

	time_used_asm /= 30;
	time_used_c /= 30;


	printf("\nVector Z with 2^24 input (asm): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_asm[i]);
	}

	printf("\nVector Z with 2^24 input (C): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_C[i]);
	}

	correct = 1;
	for (int i = 0; i < n; i++) {
		if (fabs(vectorZ_C[i] - vectorZ_asm[i]) > 1e-10) {
			correct = 0;
			break;
		}
	}
	printf("\nx86-64 Correct: %s\n", correct ? "YES" : "NO");
	printf("C Correct: %s\n", correct ? "YES" : "NO");
	printf("Time taken in assembly (averaged out over 30 runs): %lf seconds", time_used_asm);
	printf("\nTime taken in C (averaged out over 30 runs): %lf seconds\n", time_used_c);

	//2^28 size input testing
	n = 268435456;
	A = 5.0;
	time_used_asm = 0.0;
	time_used_c = 0.0;
	//initializes vector X in memory
	vectorX = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Y in memory
	vectorY = (double*)_aligned_malloc(n * sizeof(double), 32);
	//initializes vector Z in memory
	vectorZ_asm = (double*)_aligned_malloc(n * sizeof(double), 32);
	vectorZ_C = (double*)_aligned_malloc(n * sizeof(double), 32);
	for (int i = 0; i < n - 1; i++) {
		vectorX[i] = i;
		vectorY[i] = i;
	}

	for (int i = 0; i < 30; i++) {
		start_time = clock();
		Asm_daxpy(n, A, vectorX, vectorY, vectorZ_asm);
		end_time = clock();
		time_used_asm += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

		start_time = clock();
		daxpy_c(n, A, vectorX, vectorY, vectorZ_C);
		end_time = clock();
		time_used_c += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	}

	time_used_asm /= 30;
	time_used_c /= 30;


	printf("\nVector Z with 2^28 input (asm): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_asm[i]);
	}

	printf("\nVector Z with 2^28 input (C): ");
	for (int i = 0; i < 10; i++) {
		printf("%1.2lf ", vectorZ_C[i]);
	}

	correct = 1;
	for (int i = 0; i < n; i++) {
		if (fabs(vectorZ_C[i] - vectorZ_asm[i]) > 1e-10) {
			correct = 0;
			break;
		}
	}
	printf("\nx86-64 Correct: %s\n", correct ? "YES" : "NO");
	printf("C Correct: %s\n", correct ? "YES" : "NO");
	printf("Time taken in assembly (averaged out over 30 runs): %lf seconds", time_used_asm);
	printf("\nTime taken in C (averaged out over 30 runs): %lf seconds\n", time_used_c);
	return 0;

}