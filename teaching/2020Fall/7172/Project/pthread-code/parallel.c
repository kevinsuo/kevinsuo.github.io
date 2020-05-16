#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1024
#define NUM_THREADS  5

int n1,n2;
char *s1,*s2;
FILE *fp;
int countArray[NUM_THREADS]={0};


int readf(FILE *fp)
{
	if((fp=fopen("strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
	return 0;
}

void num_substring(int t)
{
	int i,j,k;
	int count;
    int lenSearch;

    if(t < NUM_THREADS - 1){
        lenSearch = n1/NUM_THREADS;
    }else{
        lenSearch = n1/NUM_THREADS - n2;
    }

	for(i=0; i<=lenSearch; i++){
		count=0;
		for(j = i + t*(n1/NUM_THREADS), k = 0; k < n2; j++, k++){
			if (*(s1+j)!=*(s2+k)){
				break;
			}else{
				count++;
			}

			if(count==n2){  
				countArray[t]++;
			}                       
		}
	}
}

void *calSubStringThread(void *threadid){
    long tid;
    tid = (long)threadid;
    printf("This is thread %ld\n", tid);
    num_substring(tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int t, rc;
    int totalNum = 0;

	readf(fp);

	for(t=0; t<NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, calSubStringThread, (void *) (size_t)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
        totalNum = totalNum + countArray[t];
    }

 	printf("The number of substrings is: %d\n", totalNum);
	return 1;
}











