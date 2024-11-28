#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SEARCH_COUNT 1000

// 배열 랜덤 숫자 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

// 퀵 정렬
void QuickSort(int* array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        QuickSort(array, low, pivotIndex - 1);
        QuickSort(array, pivotIndex + 1, high);
    }
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

// 배열의 처음과 마지막 20개 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n\n");
}

// 이진 탐색
int binarySearch(int* array, int key, int* compareCount) {
    int low = 0, high = SIZE - 1;
    *compareCount = 0;
    while (low <= high) {
        (*compareCount)++;
        int mid = low + (high - low) / 2;
        if (array[mid] == key) {
            return mid;
        }
        else if (array[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

// 이진 탐색 평균 비교
float getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < SEARCH_COUNT; i++) {
        int target = array[rand() % SIZE];
        int compareCount = 0;
        binarySearch(array, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / (float)SEARCH_COUNT;
}

// 보간 탐색
int interpolationSearch(int* array, int key, int* compareCount) {
    int low = 0, high = SIZE - 1;
    *compareCount = 0;
    while (low <= high && key >= array[low] && key <= array[high]) {
        (*compareCount)++;
        if (low == high) {
            if (array[low] == key) {
                return low;
            }
            return -1;
        }
        int pos = low + (((double)(high - low) / (array[high] - array[low])) * (key - array[low]));
        if (array[pos] == key) {
            return pos;
        }
        if (array[pos] < key) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return -1;
}

// 보간 탐색 평균 비교
float getAverageInterpolationSearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < SEARCH_COUNT; i++) {
        int target = array[rand() % SIZE];
        int compareCount = 0;
        interpolationSearch(array, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / (float)SEARCH_COUNT;
}

int main() {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);

    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n", 
        getAverageBinarySearchCompareCount(array));
    
    printf("Average Compare Count of Interpolation Search: %.2f\n", 
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}
