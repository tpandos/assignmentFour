#include <stdlib.h> 
#include <time.h> 
#include <stdio.h>

// array of 1000 requests random 
#define ELEMENTS 10000  
#define LAST 9999
#define FIRST 0

int fcfs(int arr[], int heads);
int sstf(int arr[], int heads);
int scanA(int arr[], int heads);
int cscan(int arr[], int heads);
int clook(int d[], int heads);
void copyArr(int original[], int temp[]);
void headMovsTable(int fc, int ss, int sc, int cs, int cl); 

int main(int argc, char* argv[])
{
    int h = atoi(argv[1]); // argument for head 

    srand(time(NULL)); 
    int requests[ELEMENTS]; 

    // populate array
    for(int i = 0; i < ELEMENTS; i++)
    {
        requests[i] = rand() % 10000; 
    }
    //head move variables 
    int fcfsMovs, sstfMovs, scanMovs, cscanMovs, clookMovs; 

    // for testign 
    int q[] = {98, 183, 37, 122, 14, 124, 65, 67}; // for testing

    //functions to disk schedule requests 
    fcfsMovs = fcfs(requests,h); 
    sstfMovs = sstf(requests,h);
    scanMovs = scanA(requests,h); 
    cscanMovs = cscan(requests,h); 
    clookMovs = clook(requests,h); 

    //print table 
    headMovsTable(fcfsMovs,sstfMovs,scanMovs,cscanMovs,clookMovs); 

    return 0; 
}
//============================================================== FCFS
int fcfs(int arr[], int heads)
{
    int headMovs = 0; //heads 
    headMovs = abs(heads - arr[0]); 

    for(int i = 0; i < ELEMENTS-1;  i++)  // calculates head moves 
    {
            headMovs = headMovs + abs(arr[i+1] - arr[i]); 
    }
    return headMovs;
}

//================================================================= SSTF
int sstf(int arr[], int heads)
{
    int temp[ELEMENTS]; 
    copyArr(arr,temp); 

    int cylMovs = 0; 
    int index[ELEMENTS]; 
    int min, minIndex; 
    int a[ELEMENTS]; 
    int j = 0;
    int cp1 = heads;
    
    for(int k = 0; k < ELEMENTS; k++) // gets indexes of order 
    {
        for(int i = 0; i < ELEMENTS; i++)
        {
            index[i] = abs(heads - temp[i]);   
        }      
    // find shortest path
        min = index[0];
        minIndex = 0;

        for(int i = 1; i < ELEMENTS; i++)
        {   
            if(min > index[i])
            {
                min = index[i];
                minIndex = i;
            }
        }

        a[j] = temp[minIndex];  // 
        j++;
        heads = temp[minIndex]; 
        temp[minIndex] = 99999;
    } 
    cylMovs = cylMovs + abs(cp1 - a[0]);     // add in the order of ssft
    for(int i = 1; i < ELEMENTS; i++)
    {
        cylMovs = cylMovs + abs(a[i] - a[i-1]); 
    }   
    return cylMovs; 
}

//=============================================================SCAN
// takes in array and head location 
int scanA(int arr[], int heads)
{
    int scanArr[ELEMENTS]; 
    copyArr(arr, scanArr); 

    int n = ELEMENTS; 
    int cylMovs = 0;

    int temp, max = 0;  
    int loc;  // head location 
   
    scanArr[n] = heads;
    n = n + 1;
    for(int i = 0; i < n; i++)  //sort for algorithm scan
    {
        for(int j = i; j < n; j++)
        {
            if(scanArr[i] > scanArr[j])
            {
                temp = scanArr[i];
                scanArr[i] = scanArr[j];
                scanArr[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)  // get head location 
    {
        if(heads == scanArr[i]) 
        { 
            loc = i; 
            break;  
        }
    }
    for(int i = loc; i > 0; i--)
    {
        max = max + abs(scanArr[i] - scanArr[i-1]); //get one side
    }
    // one side requests
    max = max + abs(scanArr[loc+1]);

    for(int i = loc + 2; i < n; i++)
    {
          cylMovs = cylMovs + abs(scanArr[i-1] - scanArr[i]); 
    }
    //total requests 
    cylMovs = cylMovs + max;
    return cylMovs; 
}
//=======================================================CSCAN
int cscan(int arr[], int heads)
{
    int scanArr[ELEMENTS]; 
    copyArr(arr, scanArr); 
    int n = ELEMENTS; 
    int cylMovs = 0;

    int temp, max = 0;  
    int loc;  
   
    scanArr[n] = heads;     // locate the head at end of array
    n = n + 1;
    for(int i = 0; i < n; i++)  
    {
        for(int j = i; j < n; j++)
        {
            if(scanArr[i] > scanArr[j])
            {
                temp = scanArr[i];
                scanArr[i] = scanArr[j];
                scanArr[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++) // location of head in array
    {
        if(heads == scanArr[i]) 
        { 
            loc = i; 
            break;  
        }
    }

    for(int i = loc + 1; i < n; i++)    // one side 
    {
        cylMovs = cylMovs + abs(scanArr[i-1] - scanArr[i]); 
    }

    cylMovs = cylMovs + abs(LAST - scanArr[ELEMENTS]);
    max =  abs(FIRST - scanArr[0]);// go all the way to the beginning to go to 0

    for(int i = 0;i < loc-1; i++)
    {
        max = max + abs(scanArr[i] - scanArr[i+1]);
    }
  
    cylMovs = cylMovs + max;
    return cylMovs; 
  
}

//=========================================================CLOOK 
int clook(int arr[], int heads)
{
     //printf("\n*** C-LOOK ***\n");
    int scanArr[ELEMENTS]; 
    copyArr(arr,scanArr); 
    int n = ELEMENTS; 
    int cylMovs = 0;
    int temp, max = 0;  
    int loc;  
    scanArr[n] = heads;
    n = n + 1;

    for(int i = 0; i < n; i++)  
    {
        for(int j = i; j < n; j++)
        {
            if(scanArr[i] > scanArr[j])
            {
                temp = scanArr[i];
                scanArr[i] = scanArr[j];
                scanArr[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)  // head location in array
    {
        if(heads == scanArr[i]) 
        { 
            loc = i; 
            break;  
        }
    }

    for(int i = loc+1; i < n; i++)
    {
        cylMovs = cylMovs + abs(scanArr[i-1] - scanArr[i]); 
    }
    cylMovs = cylMovs + abs(scanArr[n-1] - scanArr[0]); //wrap arraound

    for(int i = 0; i < loc-1; i++)
    {
        max = max + abs(scanArr[i] - scanArr[i+1]);
    }

    cylMovs = cylMovs + max;
    return cylMovs; 
}

//========================= COPY ARRAY CONTENTS 
void copyArr(int original[], int temp[])
{
    for(int i = 0; i < ELEMENTS; i++)
    {
        temp[i] = original[i]; 
    }
}

void headMovsTable(int fc, int ss, int sc, int cs, int cl)
{
    printf("\t\t=========================================\n"); 
    printf("\t\t|    ALGORITHM\t\t|  HEAD MOVES\t|\n"); 
    printf("\t\t=========================================\n");
    printf("\t\t|     FCFS\t\t|  %d\t|\n", fc); 
    printf("\t\t=========================================\n");
    printf("\t\t|     SSTF\t\t|  \t%d\t|\n", ss); 
    printf("\t\t=========================================\n"); 
    printf("\t\t|     SCAN\t\t|  \t%d\t|\n", sc); 
    printf("\t\t=========================================\n");
    printf("\t\t|    C-SCAN\t\t|  \t%d\t|\n", cs); 
    printf("\t\t=========================================\n"); 
    printf("\t\t|    C-LOOK\t\t|  \t%d\t|\n", cl); 
    printf("\t\t=========================================\n");
}