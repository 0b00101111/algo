/**
* Note: The returned array must be malloced, assume caller calls free().
 */

 void heapify(int* arr, int arrSize, int i) {
     int max = i;
     int left = 2 * i + 1;
     int right = 2 * i + 2;

     if (left < arrSize && arr[left] > arr[max]) {
         max = left;
     }

     if (right < arrSize && arr[right] > arr[max]) {
         max = right;
     }

     if (max != i) {
         //swap max and i
         int temp = arr[i];
         arr[i] = arr[max];
         arr[max] = temp;

         heapify(arr, arrSize, max);
     }
 }
int* sortArray(int* nums, int numsSize, int* returnSize) {
     if (nums == NULL) return NULL;

     // create a new array as the result
     int *result = (int *)malloc(numsSize * sizeof(int));
     if (result == NULL) return NULL;

     // set the returnSize
     *returnSize = numsSize;

     // copy the input array to result array
     for (int i = 0; i < numsSize; i++) {
         result[i] = nums[i];
     }

     // build a heap
     for (int i = numsSize/2 -1; i >= 0; i--){
         heapify(result, numsSize, i);
     }

     //extract maxinum by swap root with the last element
     for (int i = numsSize - 1; i > 0; i--) {
         // swap root with tail
         int temp = result[0];
         result[0] = result[i];
         result[i] = temp;

         //heapify the unsorted rest
         heapify(result, i, 0);
     }

     return result;
 }