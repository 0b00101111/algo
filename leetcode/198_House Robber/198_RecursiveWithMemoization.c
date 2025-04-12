/**
 * Improve the recursive solution by storing computed results
 * Time Complexity: O(n)
 * Space Complexity: O(n) for memo array + O(n) for recursion = O(n)
 */
int robRecursive(int *nums, int i, int *memo) {
    // Base cases
    if (i < 0) return 0;

    // If already computed, return the stored result
    if (memo[i] >= 0) return memo[i];

    // Compute and store the result
    int result = fmax(robRecursive(nums, i - 2, memo) + nums[i], robRecursive(nums, i - 1, memo));
    memo[i] = result;

    return result;
}

int rob(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    // Initialize memoization array with -1 (indicating not calculated yet)
    int *memo = (int *)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        memo[i] = -1;
    }

    int result = robRecursive(nums, numsSize - 1, memo);

    free(memo);
    return result;
}