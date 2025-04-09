/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Merge two sorted subarrays into one sorted array
void merge(int* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(L);
    free(R);
}

// Recursive function to sort an array using merge sort
void mergeSortRecursive(int* arr, int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    // Allocate memory for the result array
    int* result = (int*)malloc(numsSize * sizeof(int));
    if (!result) return NULL;

    // Set the return size
    *returnSize = numsSize;

    // Copy input array to result array
    for (int i = 0; i < numsSize; i++) {
        result[i] = nums[i];
    }

    // Sort the array using merge sort
    mergeSortRecursive(result, 0, numsSize - 1);

    return result;
}