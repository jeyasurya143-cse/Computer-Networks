#include <stdlib.h>

int* countBits(int n, int* returnSize)
{
    *returnSize = n + 1;
    int *ans = (int *)malloc((n + 1) * sizeof(int));
    int i, j;
    for(i = 0; i <= n; i++)
    {
        int count = 0;
        for(j = 0; j < 32; j++)
        {
            if((i >> j) & 1)
            {
                count++;
            }
        }
        ans[i] = count;
    }

    return ans;
}
