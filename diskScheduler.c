#include <stdlib.h> 
#include <time.h> 
#include <stdio.h>


int fcfs(int arr[], int heads);
int sstf(int arr[], int heads);
int scanA(int arr[], int heads);
int cscan(int arr[], int heads);
int clook(int d[], int heads);
void copyArr(int original[], int temp[]);
void headMovsTable(int fc, int ss, int sc, int cs, int cl); 

#define ELEMENTS 1000 

// 10000 cylinders disk 0 - 9999
// array of 1000 requests random 
int main(int argc, char* argv[])
{
    int h = atoi(argv[1]); // argument for head 
    //int h = 50; // head 

    srand(time(NULL)); 
    int requests[ELEMENTS]; 
    // populate array
    int random;
    for(int i = 0; i < ELEMENTS; i++)
    {
        requests[i] = rand() % 10000; 
    }
    
    printf("random number is : %d\n", random); 
    int fcfsMovs, sstfMovs, scanMovs, cscanMovs, clookMovs; 

    // get a list of 10 random numbers 
    int q[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int s[] = {176, 79, 34, 60 , 92, 11, 41, 114};

    fcfsMovs = fcfs(q,h); // doesn't change array 
    //fcfs(q,h); // doesn't change array 
   
    sstfMovs = sstf(requests,h); // changes array
    scanMovs = scanA(requests,h); 
    cscanMovs = cscan(requests,h); 
    clookMovs = clook(requests,h); 

    printf("fcfs = %d\nsstf = %d\nscan = %d\ncscan = %d\nclook = %d\n", fcfsMovs, sstfMovs, scanMovs, cscanMovs, clookMovs); 
 
    headMovsTable(fcfsMovs,sstfMovs,scanMovs,cscanMovs,clookMovs); 

    return 0; 

}
//============================================================== FCFS
int fcfs(int arr[], int heads)
{
    //printf("\n*** FCFS ***\n");
    int headMovs = 0; 
    headMovs = abs(heads - arr[0]); 

    //printf("Cyclinders: %d\n", abs(heads - arr[0])); 
    //printf("%d -->",heads);
    for(int i = 0; i < ELEMENTS-1;  i++)  // i < (array length - 1)
    {
            //printf("%d -->",arr[i]);
            headMovs = headMovs + abs(arr[i+1] - arr[i]); 
            // printf("Cyclinders: %d\n", abs(arr[i+1] - arr[i] )); 
    }
    printf("%d",arr[ELEMENTS - 1]);
    printf("\nTotal head moves for FCFS: %d\n", headMovs); 
    return headMovs;
}

//================================================================= SSTF
int sstf(int arr[], int heads)
{
    //printf("\n*** SSTF ***\n"); 
    int temp[ELEMENTS]; 
    copyArr(arr,temp); 

    int cylMovs = 0; 
    int index[ELEMENTS]; 
    int min, mini; 
    int a[ELEMENTS]; 
    int j = 0;
    int cp1 = heads;
    
    for(int k = 0; k < ELEMENTS; k++)
    {
        for(int i = 0; i < ELEMENTS; i++)
        {
            index[i] = abs(heads - temp[i]); // calculate distance of each request from current position
               
        }      
    // to find the nearest request
        min = index[0];
        mini = 0;
        for(int i = 1; i < ELEMENTS ;i++)
        {   
            if(min > index[i])
            {
                min = index[i];
                mini = i;
            }
        }

        a[j] = temp[mini];
        j++;
        heads = temp[mini]; // change the current position value to next request
        temp[mini] = 9999;
    } // the request that is processed its value is changed so that it is not processed again
    //printf("%d -->",cp1);
    cylMovs = cylMovs + abs(cp1 - a[0]);    // head movement
    //printf("%d -->",a[0]);
    for(int i = 1; i < ELEMENTS; i++)
    {
        cylMovs = cylMovs + abs(a[i] - a[i-1]); ///head movement
        //printf("%d -->",a[i]);
        //printf(" -> %d",a[i]);
    }   
    //printf("\n");
    printf("\nTotal head moves for SSFT %d\n",cylMovs);
    return cylMovs; 
}

//=============================================================SCANA
int scanA(int arr[], int heads)
{
    // printf("\n*** SCAN ***\n");
    int d[ELEMENTS]; 
    copyArr(arr, d); 

    int n = ELEMENTS; 
    int cylMovs = 0;
    //int d[20];
    //int disk;  //loc of head
    int temp, max = 0;  
    int dloc;  //loc of disk in array
   
    d[n] = heads;
    n = n + 1;
    for(int i = 0; i < n; i++)  // sorting disk locations
    {
        for(int j = i; j < n; j++)
        {
            if(d[i] > d[j])
            {
                temp = d[i];
                d[i] = d[j];
                d[j] = temp;
            }
        }
        
    }

    for(int i = 0; i < n; i++)
    {
        //printf("%d -->",d[i]);
    }

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        //printf("i %d\n",i); 
            break;  
        }
    }
    for(int i=dloc;i>0;i--)
    {
       //printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i-1]);
        //printf("d[i]: %d - d[i-1]: %d\n",d[i], d[i-1]); 

    }
    //printf("%d -->",d[0]);
    //printf("%d -->",0);
    //printf("max %d\n",max);
    max = max + abs(d[0]);
    max = max + abs(d[dloc+1]);
    //printf("%d -->",d[dloc +1]);
    //printf("max %d\n",max);
    //printf("\n"); 
   
    for(int i=dloc+2;i<n;i++)
    {
        //printf("%d-->",d[i]);
          //printf("d[i+1]: %d - d[i]: %d\n",d[i-1], d[i]);
          cylMovs = cylMovs + abs(d[i-1] - d[i]); 
    }

    cylMovs = cylMovs + max;
    printf("\nTotal head moves for SCAN %d\n",cylMovs);
    return cylMovs; 
    //getch();
}
//=======================================================CSCAN
int cscan(int arr[], int heads)
{
    // printf("\n*** C-SCAN ***\n");
    int d[ELEMENTS]; 
    copyArr(arr, d); 
     int n = ELEMENTS; 
    int cylMovs = 0;
    //int d[20];
    //int disk;  //loc of head
    int temp, max = 0;  
    int dloc;  //loc of disk in array

   
    d[n] = heads;
    n = n + 1;
    for(int i = 0; i < n; i++)  // sorting disk locations
    {
        for(int j = i; j < n; j++)
        {
            if(d[i] > d[j])
            {
                temp = d[i];
                d[i] = d[j];
                d[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        //printf("%d -->",d[i]);
    }

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        //printf("i %d\n",i); 
            break;  
        }
    }

    //printf("\n"); 
    //printf("%d -->",heads);
    for(int i=dloc+1;i<n;i++)
    {
        //printf("%d-->",d[i]);
        //printf("d[i-1]: %d - d[i]: %d\n",d[i-1], d[i]);
        cylMovs = cylMovs + abs(d[i-1] - d[i]); 
    }
    cylMovs = cylMovs + abs(9999 - d[ELEMENTS]);
    //printf("%d\n", d[dloc]); 
   // printf("199 - %d\n", d[ELEMENTS]); 
    //cylMovs = cylMovs + abs(0 - d[0]);
    //printf("%d -->",199);
    //printf("%d -->",0);
    //printf("%d -->",d[0]);
    //sum = sum + 199;
    //printf("first sum %d\n", cylMovs); 
    max =  abs(0 - d[0]);
    //printf("second sum%d\n",max);
    //printf("0 - d[0]: %d\n", d[0]); 

    for(int i=0;i<dloc-1;i++)
    {
        //printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i+1]);
        //printf("d[i]: %d - d[i+1]: %d\n",d[i], d[i+1]); 
    }
    //printf("%d",d[dloc -1]);
    cylMovs=cylMovs +max;
    printf("\nTotal head moves for C-SCAN %d\n",cylMovs);
    return cylMovs; 
    //getch();
}

//=========================================================CLOOK 
int clook(int arr[], int heads)
{
     //printf("\n*** C-LOOK ***\n");
    int d[ELEMENTS]; 
    copyArr(arr,d); 
    int n = ELEMENTS; 
    int cylMovs = 0;
    //int d[20];
    //int disk;  //loc of head
    int temp, max = 0;  
    int dloc;  //loc of disk in array

    d[n] = heads;
    n = n + 1;
    for(int i = 0; i < n; i++)  // sorting disk locations
    {
        for(int j = i; j < n; j++)
        {
            if(d[i] > d[j])
            {
                temp = d[i];
                d[i] = d[j];
                d[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        //printf("%d -->",d[i]);
    }

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        //printf("i %d\n",i); 
            break;  
        }
    }

    //printf("\n"); 
   //printf("%d -->",heads);
    for(int i=dloc+1;i<n;i++)
    {
        //printf("%d-->",d[i]);
        //printf("d[i-1]: %d - d[i]: %d\n",d[i-1], d[i]);
        cylMovs = cylMovs + abs(d[i-1] - d[i]); 
    }
    cylMovs = cylMovs + abs(d[n-1] - d[0]);
    //printf("%d - %d\n", d[n-1],d[0]); 
    
    //printf("\n"); 
    //sum = sum + 199; 
    for(int i=0;i<dloc-1;i++)
    {
        //printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i+1]);
        //abs(arr[i+1] - arr[i]); 
        //printf("d[i]: %d - d[i+1]: %d\n",d[i], d[i+1]); 
    }
    //printf("%d -->",d[dloc -1]);

    cylMovs=cylMovs +max;
    printf("\nTotal head moves for SCAN %d\n",cylMovs);
    //getch();
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
    printf("\t\t|     FCFS\t\t|  \t%d\t|\n", fc); 
    printf("\t\t=========================================\n");
    printf("\t\t|     SSTF\t\t|  \t%d\t|\n", ss); 
    printf("\t\t=========================================\n"); 
    printf("\t\t|     SCAN\t\t|  \t%d\t|\n", sc); 
    printf("\t\t=========================================\n");
    printf("\t\t|    C-SCAN\t\t|  \t%d\t|\n", cs); 
    printf("\t\t=========================================\n"); 
    printf("\t\t|    C-LOOK\t\t|  \t%d\t|\n", cl); 
    printf("\t\t=========================================\n");
    int as = 218; 
    printf("%c\n", as); 
}