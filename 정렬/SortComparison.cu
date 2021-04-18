#include <iostream>
#include <ctime>
using namespace std;

#include <cuda_runtime.h>       
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define THREADS pow(2,10)// 1024, ������ �� 
#define BLOCKS pow(2,17) // �����带 ��� ���� ����� ��
#define NUM_VALS THREADS*BLOCKS // ��� * ������ = �����ͼ� ũ�� (2^n)  

void swap(int arr[], int a, int b);
void QuickSort(int a[], int l, int r);
void InsertionSort(int a[], int front, int back, int gap);
void ShellSort(int a[], int n);
void checkSort(int a[], int n);
__global__ void bitonic_sort_step(int* dev_values, int j, int k);
void BitonicSort(int* values);

int main() {
	cout << "�����ͼ� ũ�� : " << NUM_VALS << endl;
	cout << "������ �� : " << THREADS << endl;
	int* arr1 = new int[NUM_VALS]; // �����Ҵ�
	int* arr2 = new int[NUM_VALS]; // �����Ҵ�
	int* arr3 = new int[NUM_VALS]; // �����Ҵ�


	srand(time(NULL));
	for (int i = 0; i < NUM_VALS; i++)
	{
		arr1[i] = rand() % (int)pow(2, 20); // ���� ��
		arr2[i] = arr1[i]; // �迭 ���Ұ� ����
		arr3[i] = arr2[i]; // �迭 ���Ұ� ����
	}


	//�ð� 
	clock_t start, end;
	//start = clock();
	//QuickSort(arr1, 0, NUM_VALS - 1); // �� ��Ʈ
	//end = clock();
	//cout << "Median-of-three Quick sort elapsed time: : " << end - start << "ms\n";
	//cout << "Median-of-three Quick sort is ";
	//checkSort(arr1, NUM_VALS);

	//start = clock();
	//ShellSort(arr2, NUM_VALS); // �� ��Ʈ
	//end = clock();
	//cout << "Shell sort elapsed time: : " << end - start << "ms\n";
	//cout << "Shell sort is ";
	//checkSort(arr2, NUM_VALS);

	start = clock();
	BitonicSort(arr3); // �� ��Ʈ
	end = clock();
	cout << "Bitonic sort used GUDA elapsed time: : " << end - start << "ms\n";
	cout << "Bitonic sort used GUDA sort is ";
	checkSort(arr3, NUM_VALS);

	cout << "12161783 ���α�";

}



//�迭�� �ּҸ� �޾ƿ��� ������ ���� �ٲ� �� �ִ�.
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
		�߰����� �̿��� �������
		l,m,r�� ������ �켱������ ������ ����
		*/
		if (a[l] > a[m]) swap(a, l, m);
		if (a[l] > a[r]) swap(a, l, r);
		if (a[m] > a[r]) swap(a, m, r);
		swap(a, m, r - 1);  // m( l,m,r�� �߰���)�� pivot�ڸ� (r-1)�� �ű� r�ڸ��� lmr�� �ִ밪
							// �̶� ����Ʈ �˰����� ���ȣ��� ���ؼ� r�ڸ��� �ᱹ �ִ밪�� ���ϰ� ��

		v = a[r - 1]; i = l; j = r - 1;

		for (; ; ) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;//i��j�� �ѱ�� 
			swap(a, i, j);
		}
		swap(a, i, r - 1); // pivot�� i�� �ٲ۴�
		//i�� ����(����pivot)���� ��, �� ������ ���ȣ��
		QuickSort(a, l, i - 1);
		QuickSort(a, i + 1, r);
	}
	else if (a[l] > a[r])
		swap(a, l, r);
}

void InsertionSort(int a[], int front, int back, int gap) {
	for (int i = front + gap; i <= back; i += gap) {
		int j;
		int tmp = a[i]; // ��ġ�� ã�� 
		for (j = i - gap; (j >= front) && (a[j] > tmp); j -= gap) {
			a[j + gap] = a[j]; // gap ��ŭ �ٰ� 
		}
		a[j + gap] = tmp;
	}
}

void ShellSort(int a[], int n)
{
	int h, v;
	int gap[1000]; //gap�� ��Ƶδ� �迭 

	gap[0] = 1;
	int gap_idx = 0;//gap�ε���
	while (gap[gap_idx] < n) {
		gap_idx++;
		gap[gap_idx] = pow(4, gap_idx) + 3 * pow(2, gap_idx - 1) + 1; // gap ũ�⸦ ������ �ۼ� ����
	}


	for (; gap_idx >= 0; gap_idx--) {
		for (int i = 0; i < gap[gap_idx]; i++) {

			if (i + gap[gap_idx] < n) {
				InsertionSort(a, i, n - 1, gap[gap_idx]); //gap �������� �������� ����
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
	unsigned int i, ixj; // ������ �з��� ���� ����
	i = threadIdx.x + blockDim.x * blockIdx.x;//blockIdx.x ���纻 ����

	ixj = i ^ j;

	// ������ ���� ����
	if ((ixj) > i) {
		if ((i & k) == 0) {
			// �������� ���� 
			if (dev_values[i] > dev_values[ixj]) {
				int temp = dev_values[i];	
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
		if ((i & k) != 0) {
			// �������� ����
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

	// <<<>>>>�� ù��° ���ڿ� 3�������� �������� �̰��� 2�����ε� 1�̹Ƿ�
	// BLOCKS*1 =BLOCKS����ŭ��
	dim3 blocks(BLOCKS, 1);    /* Number of blocks   */
	dim3 threads(THREADS, 1);  /* Number of threads  */

	int j, k;
	/* Major step */
	for (k = 2; k <= NUM_VALS; k <<= 1) {
		/* Minor step */
		for (j = k >> 1; j > 0; j = j >> 1) {
			bitonic_sort_step << <blocks, threads >> > (dev_values, j, k);
			//blocks ��ŭ ���纻 ����(�Ҵ�) �ǰ�, ���� block�� Threads���� �����尡 ������
		}
	}
	cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
	cudaFree(dev_values);
}