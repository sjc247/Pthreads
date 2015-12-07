#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
cd#define NP	3	
#define NC 3	

sem_t S;
sem_t mutex;


int readcount = 0;
			
	void *Producer(void *arg){
				//Writer
		int i, item, index;
		index = (int)arg;
		item = i;
		printf("Writer %d is trying to write\n", index);
		sem_wait(&S); //Only one reader/writer in CR at a time
		printf("Writer %d is writing...\n", index);
		sleep(1);
		printf("Writer %d is done writing\n", index);
		sem_post(&S); //Done in CR
	return NULL;
}



	void *Consumer(void *arg){
		//Reader (has priority
		int i, item, index;
		index = (int)arg;
		item = i;
		printf("Reader %d is trying to get into CR\n", index);
		sem_wait(&mutex);
		/*Wait on the mutex so only one reader can adjust readercount at a time*/
			readcount++;
	
	if(readcount == 1) sem_wait(&S); //If 1 reader, wait on S to get into CR
	sem_post(&mutex);
	printf("Reader %d is reading...\n", index);
	sleep(1);
	printf("Reader %d is done reading\n", index);
	sem_wait(&mutex);
	
readcount--;
		if(readcount == 0) sem_post(&S); /	
		sem_post(&mutex);
		return NULL;
	}
	

	int main(){
	pthread_t idPro, idCon;
	int index;
	sem_init(&S, 0, 1); 	
	sem_init(&mutex, 0, 1); //Initialize mutex
	
		for (index = 0; index < NP; index++){
		
		pthread_create(&idPro, NULL, Producer, (void*)index);
		}
		for (index = 0; index < NC; index++){
		/* Create a new consumer */
		pthread_create(&idCon, NULL, Consumer, (void*)index);
		}

pthread_exit(NULL);
}

