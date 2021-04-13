#include <iostream>
using namespace std;
#include <ctime>


//1과 2사이 왜 복잡도 차이나는지 잘 모르겠음..
void ShellSort1(int arr[], int n);
void ShellSort2(int arr[], int n);
void PrintArr(int arr[], int n);


int main() {
	int arr[10] = { 9,8,7,6,5,4,3,2,1,0 };
	ShellSort1(arr, 10);
	PrintArr(arr, 10);

}


void ShellSort1(int arr[], int n) {
	int i, j, key;
	//(3^k-1)/2의 gap을 갖는 Shell sort
	int h = 4;
	//for (h = 0; h < n; h = 3 * h + 1) {
	//	//점화식에 의해 n보다 작은 최대의 h값 찾기
	//}
	for (; h > 0; h /= 3) {
		for (int k = 0; k < h; k++) {
			for (i = h + k; i < n; i += h) { // index = 0 은 이미 정렬된 카드, 1부터시작
				key = arr[i];  // 현재 key값

				//key(i)이전카드 (i-1) 까지는 정렬이 된것
				for (j = i - h; arr[j] > key&& j >= 0; j -= h) { // 이미 정렬된 카드들로부터 key카드 자리찾기 
					arr[j + h] = arr[j];//key값보다 큰 arr[j]는 한칸씩 옆으로
				}

				//탈출 할때 --되므로 arr[j]가아닌 arr[j+1]임
				arr[j + h] = key;
			}
		}
	}
}

void ShellSort2(int a[], int n)
{
	int h, i, j, v, k;
	int gap[1000];

	gap[0] = 1;
	k = 0;
	while (gap[k] < n) {
		k++;
		gap[k] = pow(4, k) + 3 * pow(2, k - 1) + 1;
	}

	for (; k >= 0; k--) {
		for (i = gap[k]; i < n; i++) {
			v = a[i];
			j = i;
			while (j >= gap[k] && a[j - gap[k]] > v) {
				a[j] = a[j - gap[k]];
				j = j - gap[k];
			}
			a[j] = v;
		}
	}
}

void PrintArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}





