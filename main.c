#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <features.h>



FILE * fp;
int count = 0;
int i;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct rusage usage;
clock_t start1, end1, start2, end2, s, e, s1, e1, s2, e2;
double time_use1, time_use2;

void *thread_1(void *arg) {
    pthread_mutex_lock(&mutex);

    double * buffer;
    char * str1;
    char * str2;
    void * testMemoryLeak;

    str1 = (char *)calloc(10, 1);
    str2 = (char *)calloc(10, 1);
    buffer = (double *)calloc(2, sizeof(double));
    testMemoryLeak = malloc(20*1024*1024);
    memset(testMemoryLeak,0,20*1024*1024);
    
    s = clock();
    buffer[0] = (double)s/CLOCKS_PER_SEC;
    printf("\nThời gian 1 : %lf\n", (double)s/CLOCKS_PER_SEC);
    printf("Enter Critical Section 1...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    sleep(1);

    printf("Exit Critical Section 1...\n");
    e = clock();
    buffer[1] = (double)e/CLOCKS_PER_SEC;
    getrusage(RUSAGE_THREAD, &usage);
    sprintf(str1, "%f", buffer[0]);
    sprintf(str2, "%f", buffer[1]);
    fprintf(fp, "%ld, %s\n%ld, %s\n", usage.ru_maxrss, str1, usage.ru_maxrss, str2);
    
    printf("Thời gian 1 : %lf\n", (double)e/CLOCKS_PER_SEC);
    printf("::RAM usage::%ld::\n", usage.ru_maxrss);
    free(buffer);
    free(str1);
    free(str2);

    pthread_mutex_unlock(&mutex);

}

void *thread_2(void *arg) {
    pthread_mutex_lock(&mutex);
    double * buffer;
    char * str1;
    char * str2;
    void * testMemoryLeak;

    str1 = (char *)calloc(10, 1);
    str2 = (char *)calloc(10, 1);
    buffer = (double *)calloc(2, sizeof(double));
    testMemoryLeak = malloc(20*1024*1024);
    memset(testMemoryLeak,0,20*1024*1024);
    
    s1 = clock();
    buffer[0] = (double)s1/CLOCKS_PER_SEC;
    printf("\nThời gian 2 : %lf\n", (double)s1/CLOCKS_PER_SEC);
    printf("Enter Critical Section 2...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    sleep(1);

    printf("Exit Critical Section 2...\n");
    e1 = clock();
    buffer[1] = (double)e1/CLOCKS_PER_SEC;
    getrusage(RUSAGE_THREAD, &usage);
    sprintf(str1, "%f", buffer[0]);
    sprintf(str2, "%f", buffer[1]);
    fprintf(fp, "%ld, %s\n%ld, %s\n", usage.ru_maxrss, str1, usage.ru_maxrss, str2);

    printf("Thời gian 2 : %lf\n", (double)e1/CLOCKS_PER_SEC);
    printf("::RAM usage::%ld::\n", usage.ru_maxrss);
    free(buffer);
    free(str1);
    free(str2);

    pthread_mutex_unlock(&mutex);

}

void *thread_3(void *arg) {
    pthread_mutex_lock(&mutex);

    double * buffer;
    char * str1;
    char * str2;
    void * testMemoryLeak;

    str1 = (char *)calloc(10, 1);
    str2 = (char *)calloc(10, 1);
    buffer = (double *)calloc(2, sizeof(double));
    testMemoryLeak = malloc(20*1024*1024);
    memset(testMemoryLeak,0,20*1024*1024);
    
    s2 = clock();
    buffer[0] = (double)s2/CLOCKS_PER_SEC;
    fprintf(fp, buffer);
    printf("\nThời gian 3 : %lf\n", (double)s2/CLOCKS_PER_SEC);
    printf("Enter Critical Section 3...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    sleep(1);

    printf("Exit Critical Section 3...\n");
    e2 = clock();
    buffer[1] = (double)e2/CLOCKS_PER_SEC;
    getrusage(RUSAGE_THREAD, &usage);
    sprintf(str1, "%f", buffer[0]);
    sprintf(str2, "%f", buffer[1]);
    fprintf(fp, "%ld, %s\n%ld, %s\n", usage.ru_maxrss, str1, usage.ru_maxrss, str2);

    printf("Thời gian 3 : %lf\n", (double)e2/CLOCKS_PER_SEC);
    printf("::RAM usage::%ld::\n", usage.ru_maxrss);
    free(buffer);
    free(str1);
    free(str2);

    pthread_mutex_unlock(&mutex);
 
}

int main() {
    fp = fopen("dataTime.csv", "w");
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;


    pthread_create(&thread1, NULL, thread_1, NULL);
    pthread_create(&thread2, NULL, thread_2, NULL);
    pthread_create(&thread3, NULL, thread_3, NULL);
    
    pthread_join(thread1, NULL);
    
    pthread_join(thread2, NULL);
        
    pthread_join(thread3, NULL);   

    pthread_mutex_destroy(&mutex);

    printf("count = %d\n", count);
    


    return 0;
}