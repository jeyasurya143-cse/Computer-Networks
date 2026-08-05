#include <stdio.h>
#include <string.h>

#define MAX 100

int dataBytes[MAX];
int stuffedBytes[MAX];
int framedBytes[MAX];
int destuffedBytes[MAX];

int flagByte;
int escByte;

void printByteBinary(int byte)
{
    int i;

    for(i=7;i>=0;i--)
        printf("%d",(byte>>i)&1);
}

void printBytesAsBinary(char *label,int arr[],int n)
{
    int i;

    printf("%s : ",label);

    for(i=0;i<n;i++)
    {
        printByteBinary(arr[i]);
        printf(" ");
    }

    printf("\n");
}

int main()
{
    char input[100];
    int numBytes;
    int stuffedLen;
    int framedLen;
    int i,j,k,m;
    int error=0;
    int match=1;

    flagByte = 0x7E;
    escByte  = 0xA3;

    printf("FLAG (~) : ");
    printByteBinary(flagByte);

    printf("\nESC (#)  : ");
    printByteBinary(escByte);

    printf("\n\nEnter Data : ");
    scanf("%s",input);

    numBytes = strlen(input);

    for(i=0;i<numBytes;i++)
    {
        if(input[i]=='#')
            dataBytes[i]=escByte;
        else
            dataBytes[i]=(unsigned char)input[i];
    }

    printf("\nOriginal String : %s\n",input);

    printBytesAsBinary("ASCII Binary",dataBytes,numBytes);

    j=0;

    for(i=0;i<numBytes;i++)
    {
        if(dataBytes[i]==flagByte || dataBytes[i]==escByte)
        {
            stuffedBytes[j++]=escByte;
            stuffedBytes[j++]=dataBytes[i];
        }
        else
        {
            stuffedBytes[j++]=dataBytes[i];
        }
    }

    stuffedLen=j;

    printBytesAsBinary("Stuffed Data",stuffedBytes,stuffedLen);

    k=0;

    framedBytes[k++]=flagByte;

    for(i=0;i<stuffedLen;i++)
        framedBytes[k++]=stuffedBytes[i];

    framedBytes[k++]=flagByte;

    framedLen=k;

    printBytesAsBinary("Framed Data",framedBytes,framedLen);

    if(framedBytes[0]!=flagByte || framedBytes[framedLen-1]!=flagByte)
    {
        printf("\nFrame Error!\n");
        return 0;
    }

    m=0;
    for(i=1;i<framedLen-1;i++)
    {
        if(framedBytes[i]==escByte)
        {
            if(i+1>=framedLen-1)
            {
                printf("\nDangling ESC byte!\n");
                error=1;
                break;
            }

            i++;
            destuffedBytes[m++]=framedBytes[i];
        }
        else if(framedBytes[i]==flagByte)
        {
            printf("\nUnexpected FLAG byte inside frame!\n");
            error=1;
            break;
        }
        else
        {
            destuffedBytes[m++]=framedBytes[i];
        }
    }

    if(error)
        return 0;

    printBytesAsBinary("Destuffed Data",destuffedBytes,m);

    if(m!=numBytes)
    {
        printf("\nLength mismatch after destuffing.\n");
        return 0;
    }

    for(i=0;i<numBytes;i++)
    {
        if(destuffedBytes[i]!=dataBytes[i])
        {
            match=0;
            break;
        }
    }
    if(match)
    {
        printf("\nDestuffing Successful.\n");
    }
    else
    {
        printf("\nData mismatch.\n");
    }

    return 0;
}
