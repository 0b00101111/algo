//Count the frequency of each number in the array
//Sort these frequencies in descending order
//Greedily pick the most frequent elements until you've removed at least half the array

#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort frequencies in descending order
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int minSetSize(int* arr, int arrSize) {
    // Find the maximum value in the array to determine hash table size
    int max_val = 0;
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Count frequency of each number using a hash table approach
    int* freq = (int*)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]]++;
    }

    // Collect non-zero frequencies
    int count = 0;
    for (int i = 1; i <= max_val; i++) {
        if (freq[i] > 0) {
            count++;
        }
    }

    // Create an array of non-zero frequencies
    int* frequencies = (int*)malloc(count * sizeof(int));
    int index = 0;
    for (int i = 1; i <= max_val; i++) {
        if (freq[i] > 0) {
            frequencies[index++] = freq[i];
        }
    }

    // Sort frequencies in descending order
    qsort(frequencies, count, sizeof(int), compare);

    // Greedily pick elements until we remove at least half
    int removed = 0;
    int target = arrSize / 2;
    int result = 0;

    for (int i = 0; i < count; i++) {
        removed += frequencies[i];
        result++;
        if (removed >= target) {
            break;
        }
    }

    // Clean up
    free(freq);
    free(frequencies);

    return result;
}

