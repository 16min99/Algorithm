#include <iostream>
using namespace std;


void InsertionSort(int arr[], int n);
void PrintArr(int arr[],int n);


int main() {
	int arr[10] = { 9,8,7,6,5,4,3,2,1,0 };
	InsertionSort(arr, 10);
	PrintArr(arr, 10);
}


void InsertionSort(int arr[], int n) {
	int i, j, key; 

	for (i = 1; i < n; i++) { // index = 0 은 이미 정렬된 카드, 1부터시작
		key = arr[i];  // 현재 key값

		//key(i)이전카드 (i-1) 까지는 정렬이 된것
		for (j = i -1 ; arr[j]>key && j>=0; j--) { // 이미 정렬된 카드들로부터 key카드 자리찾기 
			arr[j + 1] = arr[j];//key값보다 큰 arr[j]는 한칸씩 옆으로
			}
		
		//탈출 할때 --되므로 arr[j]가아닌 arr[j+1]임
		arr[j + 1] = key;
	}
}

void PrintArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}





