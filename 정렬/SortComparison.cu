#include <iostream>
#include <ctime>
using namespace std;

#include <cuda_runtime.h>       
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define THREADS pow(2,10)// 1024, 스레드 수 
#define BLOCKS pow(2,17) // 스레드를 모아 만든 블록의 수
#define NUM_VALS THREADS*BLOCKS // 블록 * 스레드 = 데이터셋 크기 (2^n)  

void swap(int arr[], int a, int b);
void QuickSort(int a[], int l, int r);
void InsertionSort(int a[], int front, int back, int gap);
void ShellSort(int a[], int n);
void checkSort(int a[], int n);
__global__ void bitonic_sort_step(int* dev_values, int j, int k);
void BitonicSort(int* values);

int main() {
	cout << "데이터셋 크기 : " << NUM_VALS << endl;
	cout << "쓰레드 수 : " << THREADS << endl;
	int* arr1 = new int[NUM_VALS]; // 동적할당
	int* arr2 = new int[NUM_VALS]; // 동적할당
	int* arr3 = new int[NUM_VALS]; // 동적할당


	srand(time(NULL));
	for (int i = 0; i < NUM_VALS; i++)
	{
		arr1[i] = rand() % (int)pow(2, 20); // 랜덤 수
		arr2[i] = arr1[i]; // 배열 원소값 통일
		arr3[i] = arr2[i]; // 배열 원소값 통일
	}


	//시간 
	clock_t start, end;
	//start = clock();
	//QuickSort(arr1, 0, NUM_VALS - 1); // 퀵 소트
	//end = clock();
	//cout << "Median-of-three Quick sort elapsed time: : " << end - start << "ms\n";
	//cout << "Median-of-three Quick sort is ";
	//checkSort(arr1, NUM_VALS);

	//start = clock();
	//ShellSort(arr2, NUM_VALS); // 퀵 소트
	//end = clock();
	//cout << "Shell sort elapsed time: : " << end - start << "ms\n";
	//cout << "Shell sort is ";
	//checkSort(arr2, NUM_VALS);

	start = clock();
	BitonicSort(arr3); // 퀵 소트
	end = clock();
	cout << "Bitonic sort used GUDA elapsed time: : " << end - start << "ms\n";
	cout << "Bitonic sort used GUDA sort is ";
	checkSort(arr3, NUM_VALS);

	cout << "12161783 전민규";

}



//배열은 주소를 받아오기 때문에 값을 바꿀 수 있다.
void swap(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void QuickSort(int a[], int l, int r) {
	int i, j, m, v; // v is pivot
	if (r - l > 1) {
		m = (l + r) / 2;
		/*
		중간값을 이용한 성능향상
		l,m,r을 선택해 우선적으로 정렬을 수행
		*/
		if (a[l] > a[m]) swap(a, l, m);
		if (a[l] > a[r]) swap(a, l, r);
		if (a[m] > a[r]) swap(a, m, r);
		swap(a, m, r - 1);  // m( l,m,r중 중간값)을 pivot자리 (r-1)로 옮김 r자리는 lmr중 최대값
							// 이때 퀵소트 알고리즘의 재귀호출로 인해서 r자리는 결국 최대값을 향하게 됨

		v = a[r - 1]; i = l; j = r - 1;

		for (; ; ) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;//i가j를 넘기면 
			swap(a, i, j);
		}
		swap(a, i, r - 1); // pivot과 i를 바꾼다
		//i을 기준(이전pivot)으로 좌, 우 퀵정렬 재귀호출
		QuickSort(a, l, i - 1);
		QuickSort(a, i + 1, r);
	}
	else if (a[l] > a[r])
		swap(a, l, r);
}

void InsertionSort(int a[], int front, int back, int gap) {
	for (int i = front + gap; i <= back; i += gap) {
		int j;
		int tmp = a[i]; // 위치를 찾는 
		for (j = i - gap; (j >= front) && (a[j] > tmp); j -= gap) {
			a[j + gap] = a[j]; // gap 만큼 뛰고 
		}
		a[j + gap] = tmp;
	}
}

void ShellSort(int a[], int n)
{
	int h, v;
	int gap[1000]; //gap을 담아두는 배열 

	gap[0] = 1;
	int gap_idx = 0;//gap인덱스
	while (gap[gap_idx] < n) {
		gap_idx++;
		gap[gap_idx] = pow(4, gap_idx) + 3 * pow(2, gap_idx - 1) + 1; // gap 크기를 식으로 작성 가능
	}


	for (; gap_idx >= 0; gap_idx--) {
		for (int i = 0; i < gap[gap_idx]; i++) {

			if (i + gap[gap_idx] < n) {
				InsertionSort(a, i, n - 1, gap[gap_idx]); //gap 사이즈대로 삽입정렬 실행
			}
		}
	}
}

void checkSort(int a[], int n) {
	int i, sorted;
	sorted = true;
	for (i = 0; i < n - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			sorted = false;
		}
		if (!sorted)
		{
			break;
		}
	}
	if (sorted)
	{
		cout << "Sorting complete!" << endl;
	}
	else
	{
		cout << "Error during sorting..." << endl;
	}
}


__global__ void bitonic_sort_step(int* dev_values, int j, int k)
{
	unsigned int i, ixj; // 스레드 분류를 위한 변수
	i = threadIdx.x + blockDim.x * blockIdx.x;//blockIdx.x 복사본 구분

	ixj = i ^ j;

	// 나눠서 정렬 수행
	if ((ixj) > i) {
		if ((i & k) == 0) {
			// 오름차순 정렬 
			if (dev_values[i] > dev_values[ixj]) {
				int temp = dev_values[i];	
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
		if ((i & k) != 0) {
			// 내림차순 정렬
			if (dev_values[i] < dev_values[ixj]) {
				int temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
	}
}


void BitonicSort(int* values) {
	int* dev_values;
	size_t size = NUM_VALS * sizeof(int);

	cudaMalloc((void**)&dev_values, size);
	cudaMemcpy(dev_values, values, size, cudaMemcpyHostToDevice);

	// <<<>>>>의 첫번째 인자에 3차원까지 지정가능 이것은 2차원인데 1이므로
	// BLOCKS*1 =BLOCKS수만큼들어감
	dim3 blocks(BLOCKS, 1);    /* Number of blocks   */
	dim3 threads(THREADS, 1);  /* Number of threads  */

	int j, k;
	/* Major step */
	for (k = 2; k <= NUM_VALS; k <<= 1) {
		/* Minor step */
		for (j = k >> 1; j > 0; j = j >> 1) {
			bitonic_sort_step << <blocks, threads >> > (dev_values, j, k);
			//blocks 만큼 복사본 생성(할당) 되고, 각각 block에 Threads개의 스레드가 실행함
		}
	}
	cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
	cudaFree(dev_values);
}