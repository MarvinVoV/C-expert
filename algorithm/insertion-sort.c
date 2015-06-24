#include <stdio.h>
#include <stdlib.h>

void insertionSort(int a[], int len){
    int i, j, k;
    for( i = 1; i < len; i++ ){
        k = a[i];
        j = i - 1;
        while( j >= 0 && k < a[j] ){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = k;
    }
}

void printArray(int a[], int len){
    while(len > 0){
        printf("%d ", *a++);
        len--;
    }
    printf("\n");
}

int main(void){
    int a[] = {3, 5, 2, 1, 7, 9, 8, 6, 4};
    insertionSort(a, 9); 
    printArray(a, 9);

    exit(0);
}
