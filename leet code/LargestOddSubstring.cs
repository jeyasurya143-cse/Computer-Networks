void findLargestOddSubstring(char* num) {
    int len = strlen(num);
    
    for (int i = len - 1; i >= 0; i--) {
        int digit = num[i] - '0';
        if (digit % 2 != 0) {
            num[i + 1] = '\0';
            printf("%s\n", num);
            return;
        }
    }
    printf("-1\n");
}
