#include <pthread.h>
#include <stdio.h>
// #include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <process.h>
#include <sys/resource.h>


int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
clock_t start1, end1, start2, end2, s, e, s1, e1, s2, e2;
double time_use1, time_use2;
struct rusage usage;

void *thread_1(void *arg) {
    pthread_mutex_lock(&mutex);
    s = clock();
    printf("\nTime 1 : %lf\n", (double)s/CLOCKS_PER_SEC);
    printf("Enter Critical Section 1...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 1...\n");
    e = clock();
    printf("Time 1 : %lf\n", (double)e/CLOCKS_PER_SEC);
    

    pthread_mutex_unlock(&mutex);
    
}

void *thread_2(void *arg) {
    pthread_mutex_lock(&mutex);
    s1 = clock();
    printf("\nTime 2 : %lf\n", (double)s1/CLOCKS_PER_SEC);
    printf("Enter Critical Section 2...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 2...\n");
    e1 = clock();
    printf("Time 2 : %lf\n", (double)e1/CLOCKS_PER_SEC);
    pthread_mutex_unlock(&mutex);
   
}

void *thread_3(void *arg) {
    pthread_mutex_lock(&mutex);
    s2 = clock();
    printf("\nTime 3 : %lf\n", (double)s2/CLOCKS_PER_SEC);
    printf("Enter Critical Section 3...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 3...\n");
    e2 = clock();
    printf("Time 3 : %lf\n", (double)e2/CLOCKS_PER_SEC);


    pthread_mutex_unlock(&mutex);
   
}
int main() {
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