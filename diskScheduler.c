#include <stdlib.h> 
#include <time.h> 
#include <stdio.h>


void fcfs(int arr[], int heads);
void sstf(int arr[], int heads);
void scanA(int arr[], int heads);
void cscan(int arr[], int heads);
void clook(int d[], int heads);

#define ELEMENTS 8 

int main(int argc, char** argv[])
{

    int h = argv[1]; // argument for head 
    //int h = 50; // head 

    srand(time(NULL)); 
    int random = rand() % 1000; 
    printf("random number is : %d\n", random); 

    // get a list of 10 random numbers 
    int q[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int s[] = {176, 79, 34, 60 , 92, 11, 41, 114};

    //fcfs(q,h); 
   
    //sstf(q,h); 
    //scanA(s,h); 
    //cscan(s,h); 
    clook(s,h); 

    return 0; 

}
// first come first serve FCFS
void fcfs(int arr[], int heads)
{

    int cylinders = 0; 

    //initial cylinders 
    cylinders = abs(heads - arr[0]); 
    printf("Cyclinders: %d\n", abs(heads - arr[0])); 
    
    for(int i = 0; i < ELEMENTS -1;  i++)  // i < (array length - 1)
    {
        
            cylinders = cylinders + abs(arr[i+1] - arr[i]); 
            // printf("Cyclinders: %d\n", abs(arr[i+1] - arr[i] )); 

    }

    printf("Total Cyclinders FCFS: %d\n", cylinders); 
}

// SSTF

void sstf(int arr[], int heads)
{
    int  mov = 0, index[ELEMENTS], min, mini, a[ELEMENTS], cp1, j = 0; 
    cp1 = heads;
    
    for(int k = 0; k < ELEMENTS; k++)
    {
        for(int i = 0; i < ELEMENTS; i++)
        {
            index[i] = abs(heads - arr[i]); // calculate distance of each request from current position
               
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

        a[j] = arr[mini];
        j++;
        heads = arr[mini]; // change the current position value to next request
        arr[mini] = 999;
    } // the request that is processed its value is changed so that it is not processed again
     
    mov = mov + abs(cp1 - a[0]);    // head movement

    for(int i = 1; i < ELEMENTS; i++)
    {
        mov = mov + abs(a[i] - a[i-1]); ///head movement
        printf(" -> %d",a[i]);
    }   

    printf("\n");
    printf("Cylinders SSFT %d\n",mov);
}

void scanA(int d[], int heads)
{
    int n = ELEMENTS; 
    int sum = 0;
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
        printf("%d -->",d[i]);
    }
    //max=d[n];

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        printf("i %d\n",i); 
            break;  
        }
    }
    for(int i=dloc;i>0;i--)
    {
       // printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i-1]);
        printf("d[i]: %d - d[i-1]: %d\n",d[i], d[i-1]); 

    }

    printf("max %d\n",max);
    max = max + abs(d[0]);
    max = max + abs(d[dloc+1]);
    
    printf("max %d\n",max);
    printf("\n"); 
   
    for(int i=dloc+2;i<n;i++)
    {
        //printf("%d-->",d[i]);
          printf("d[i+1]: %d - d[i]: %d\n",d[i-1], d[i]);
          sum = sum + abs(d[i-1] - d[i]); 
    }

    sum=sum +max;
    printf("\nmovement of total cylinders SCAN %d\n",sum);
    //getch();
}

void cscan(int d[], int heads)
{
     int n = ELEMENTS; 
    int sum = 0;
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
        printf("%d -->",d[i]);
    }
    //max=d[n];

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        printf("i %d\n",i); 
            break;  
        }
    }


    //printf("max %d\n",max);
    //max = max + abs(d[0]);
    //max = max + abs(d[dloc+1]);
    
    //printf("max %d\n",max);
    printf("\n"); 
   
    for(int i=dloc+1;i<n;i++)
    {
        //printf("%d-->",d[i]);
          printf("d[i-1]: %d - d[i]: %d\n",d[i-1], d[i]);
          sum = sum + abs(d[i-1] - d[i]); 
    }
          printf("199 - %d\n", d[n-1]); 
    sum = sum + abs(200 - d[n-1]);
    //sum = sum + 199;
    max =  d[0];
    printf("d[0]: %d\n", d[0]); 
    //sum = sum + 199; 
        for(int i=0;i<dloc-1;i++)
    {
       // printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i+1]);
        //abs(arr[i+1] - arr[i]); 
        printf("d[i]: %d - d[i+1]: %d\n",d[i], d[i+1]); 
    }

    max=sum +max;
    printf("\nmovement of total cylinders SCAN %d\n",sum);
    //getch();
}


void clook(int d[], int heads)
{
     int n = ELEMENTS; 
    int sum = 0;
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
        printf("%d -->",d[i]);
    }
    //max=d[n];

    for(int i=0;i<n;i++)  // to find loc of disc in array
    {
        if(heads==d[i]) 
        { dloc=i; 
        printf("i %d\n",i); 
            break;  
        }
    }


    //printf("max %d\n",max);
    //max = max + abs(d[0]);
    //max = max + abs(d[dloc+1]);
    
    //printf("max %d\n",max);
    printf("\n"); 
   
    for(int i=dloc+1;i<n;i++)
    {
        //printf("%d-->",d[i]);
          printf("d[i-1]: %d - d[i]: %d\n",d[i-1], d[i]);
          sum = sum + abs(d[i-1] - d[i]); 
    }
    sum = sum + abs(d[n-1] - d[0]);
    printf("%d - %d\n", d[n-1],d[0]); 
    //sum = sum + abs(200 - d[n-1]);
    //sum = sum + 199;
    //max =  d[0];
    //printf("d[0]: %d\n", d[0]); 
    printf("\n"); 
    //sum = sum + 199; 
        for(int i=0;i<dloc-1;i++)
    {
       // printf("%d -->",d[i]);
        max = max + abs(d[i] - d[i+1]);
        //abs(arr[i+1] - arr[i]); 
        printf("d[i]: %d - d[i+1]: %d\n",d[i], d[i+1]); 
    }

    sum=sum +max;
    printf("\nmovement of total cylinders SCAN %d\n",sum);
    //getch();
}