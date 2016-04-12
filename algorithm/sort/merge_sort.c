#include <stdio.h>
#include <limits.h>

void merge_sort(int a[], int p, int r);
void merge(int a[], int p, int q, int r);
void print_array(int a[], int len);


void merge_sort(int a[], int p, int r){
	if(p < r){
		int q = (r + p) / 2;
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);		
	}
}

void merge(int a[], int p, int q, int r){
	int	n1 = q - p + 1;
	int n2 = r - q;
	int L[n1 + 1], R[n2 + 1];
	int i, j;
	for(i = 0; i < n1; i++)
	   L[i] = a[p + i];	
	for(j = 0; j < n2; j++)
		R[j] = a[q + 1 + j];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	
	i = 0;
    j = 0;
	int k;
	for(k = p; k <= r; k++)
		if(L[i] <= R[j]){
			a[k] = L[i];
			i++;
		}else{
			a[k] = R[j];
			j++;
		}	
}

void print_array(int a[], int len){
	for(int i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\n");
}
int main(){
	int a[] = {3, 2, 1, 5, 9 ,6, 4};
	int len = 7;
	merge_sort(a, 0, len - 1);
	print_array(a, len);	
	return 0;
}
