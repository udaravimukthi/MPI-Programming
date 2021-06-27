// 174083C_TH2_MPI_Merge_Sort_Sequential.c

#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 

void print_vector(char* prompt, int* vector, int no_elems);
void merge_sort(int* arr, int l, int r);
void merge(int* arr, int l, int m, int r);

int main(int argc, char** argv) {
	// Input 
	int elems = 10;
	if (argv[1])
		elems = atoi(argv[1]);

	int* unsorted = (int*)malloc(sizeof(int) * elems);

	//generate random numbers 
	srand(time(NULL));
	for (int i = 0; i < elems; i++) {
		unsorted[i] = rand() % 100;
	}

	printf("Total elements: %d\n", elems);
	print_vector((char*)"Unsorted", unsorted, elems);
	//Start measuring the time 
	clock_t begin = clock();
	merge_sort(unsorted, 0, elems - 1);
	clock_t end = clock();

	print_vector((char*)"Sorted", unsorted, elems);
	printf("\nExecution duration: %f s", (double)(end - begin) / (double)CLOCKS_PER_SEC);
}

void merge_sort(int* arr, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		// Sort first and second halves - divide 
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void merge(int* arr, int l, int m, int r) {
	int i, j, k; int n1 = m - l + 1;
	int n2 = r - m;
	int* L = (int*)malloc(sizeof(int) * n1);
	int* R = (int*)malloc(sizeof(int) * n2);

	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}

	i = 0;
	j = 0;
	k = l;

	// Sort subarray 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i]; i++;
		}
		else {
			arr[k] = R[j]; j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void print_vector(char* prompt, int* vector, int no_elems) {
	char* prompt_add = (char*)" :";
	if (no_elems > 20) {
		no_elems = 10;
		prompt_add = (char*)" first 10 elems: ";
	}
	printf("\n%s %s\n", prompt, prompt_add);

	for (int i = 0; i < no_elems; i++) {
		printf(" %d,", vector[i]);
	}
	printf("\n");
}