int findMaximumXOR(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    int max_xor = 0;
    
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            int current_xor = nums[i] ^ nums[j];
            if (current_xor > max_xor) {
                max_xor = current_xor;
            }
        }
    }
    return max_xor;
}
