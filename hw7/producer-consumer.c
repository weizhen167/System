
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZE 100000
int stack[MAXSIZE];
int result;

int size = 0;

typedef struct {
	int count;
	int pending_posts;
} mysem_t;


pthread_mutex_t mut;
pthread_mutex_t mutex;

///////////////////////////////part 1///////////////////////////////////
void new_sem_init(mysem_t *sem, int pshared, unsigned int value) {
	sem->count = value;
	sem->pending_posts = 0;
}

void new_sem_post(mysem_t *sem) {
	pthread_mutex_lock(&mut);
	sem->count++;
	if (sem->count <= 0) sem->pending_posts++;
	pthread_mutex_unlock(&mut);
}

void new_sem_wait(mysem_t *sem) {
	pthread_mutex_lock(&mut);
	int done;
	sem->count--;
	if (sem->count < 0) {
		pthread_mutex_unlock(&mut);
	sleep:
		while (sem->pending_posts <= 0) {
			sleep(1);
		}
		pthread_mutex_lock(&mutex);
		if (sem->pending_posts > 0) {
			done = 1;
			sem->pending_posts--;
		}
		else {
			done = 0;
		}
		pthread_mutex_unlock(&mutex);
		if (!done) {
			goto sleep;
		}
		pthread_mutex_lock(&mut);
	}
	pthread_mutex_unlock(&mut);
}


//////////////////////////Part 2/////////////////////////////////
mysem_t sem;
#define N 4

int buf[N];
int first_occupied_slot = 0;
int first_empty_slot = 0;


void add(int val) {
	buf[first_empty_slot] = val;
	first_empty_slot++;
	if (first_empty_slot >= N)
		first_empty_slot = 0;
}
int rem() {
	int val = buf[first_occupied_slot];
	first_occupied_slot++;
	if (first_occupied_slot >= N)
		first_occupied_slot = 0;
	return val;
}

void Provider_data(void) {
	int i;
	for (i = 0; i< MAXSIZE; i++) {
		sleep(rand() % 5);
		stack[i] = i;
		new_sem_post(&sem); 
	}
}


void Customer_data(void) { 
	int i;
	while ((i = size++) < MAXSIZE) {		
		new_sem_wait(&sem);
		printf("%d\n", stack[i]);
		sleep(rand() % 5);
	}
}

int main(void) {

	pthread_t Customer, Provider;

	new_sem_init(&sem, 0, 0); 
	pthread_create(&Provider, NULL, (void *)Customer_data, NULL);
	pthread_create(&Customer, NULL, (void *)Provider_data, NULL);
	pthread_join(Provider, NULL);
	pthread_join(Customer, NULL);
	return 0;
}

