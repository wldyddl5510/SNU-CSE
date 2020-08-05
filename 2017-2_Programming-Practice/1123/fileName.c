#include <stdio.h>
#include <stdlib.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i = 0;
	int j = 0;
	int a = l;
	int *arr1 = (int*) malloc((m - l + 1) * sizeof(int));
	int *arr2 = (int*) malloc((r - m) * sizeof(int));

	for(int k = l ; k < (m + 1) ; k++) {
		arr1[(k - l)] = arr[k];
	}
	for(int k = (m+1) ; k <= r ; k++) {
		arr2[(k - (m + 1))] = arr[k];
	}

	while(i < (m - l + 1) && j < (r - m) ) {
		if(arr1[i] < arr2[j])
			arr[a++] = arr1[i++];
		else 
			arr[a++] = arr2[j++];
	}

	while(i < (m - l + 1)) 
		arr[a++] = arr1[i++];
	while(j < (r - m))
		arr[a++] = arr2[j++];
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
	int m;
	m = (l + r) / 2;

	if(l != r) {
		mergeSort(arr, l , m);
		mergeSort(arr, (m+1), r);
		merge(arr, l, m, r);
	}
}
/*
{
	int *divide1;
	int *divide2;
	int *result;
	int m;

	m = l + (r - l) / 2;

	if(m > l) {

		divide1 = (int*) malloc((m - l + 1) * sizeof(int));
		divide2 = (int*) malloc((r - m) * sizeof(int));
		result = (int*) malloc((r - l + 1) * sizeof(int));

		for(int i = l ; i <= m ; i++) {
			divide1[(i - l)] = arr[i];
		}
		for(int i = (m+1) ; i <= r ; i++) {
			divide2[(i - m -1)] = arr[i];
			printf("%d ",divide2[i-m-1]);
		}
	
		mergeSort(divide1, 0, (m - l));
		mergeSort(divide2, 0, (r - m - 1));

		for(int i = 0; i <= (m - l); i++) {
			result[i] = divide1[i];
//			printf("%d ", result[i]);
		}
		for(int i = (m - l + 1) ; i <= (r - m - 1); i++) {
			result[i] = divide2[i];
//			printf("%d ", result[i]);
		}

		for(int i = l ; i <= r ; i++) {
			arr[i] = result[(i - l)];
		}

		merge(arr, l, m, r);
	}
}
*/

//comment below when submit

int main()
{
    int n;
    scanf("%d",&n);
    
    int* arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0 ; i < n ; i++){
    scanf("%d", &arr[i]);
    }

    mergeSort(arr, 0, n-1);

    for(int i = 0 ; i < n ; i++){
    printf("%d ", arr[i]);
    }
 
    return 0;
}

