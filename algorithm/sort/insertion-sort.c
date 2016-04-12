#include <stdio.h>
#include <string.h>

void swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
// mine
void insertion_sort_my(int a[], int len){
	if(len <= 1) return;
	for(int i = 1; i < len; i++){
		int j = i;	
		while(j > 0){
			if(a[j - 1] > a[j])
				swap(a, j-1, j);
			j--;
		}
	}	
}
// offical
void insertion_sort(int a[], int len){
	for(int i = 1; i < len; i++){
		int key = a[i];
		int j = i - 1;
		while(j >= 0 && a[j] > key){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}


void print_array(int a[], int len){
	for(int i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(void){
	int a[] = {2, 1, 4, 7, 5, 6, 10, 8};
	int len = 8;
	//insertion_sort_my(a, len);
	insertion_sort(a, len);
	print_array(a, len);
	return 0;
}
