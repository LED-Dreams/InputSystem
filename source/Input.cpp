#include "ImageProcessor.hpp"
#include <time.h>
#include <pthread.h>

static void *fetchCursor( void * arg);
ImageProcessor processor(256,256);

int main (int argc, char *argv[])
{
	int c;
	int thread_flag= 0;
	
	while((c = getopt(argc, argv, "t")) != -1)
	{
		switch(c)
		{
			case 't': //threaded
				printf("running with threads\n");
				break;
		}
	}

	if(thread_flag == 1)
	{
		pthread_t pid[2];
	
		pthread_create(&pid[0], NULL, fetchCursor, (void*) NULL);
		pthread_create(&pid[1], NULL, fetchCursor, (void*) NULL);
		
		pthread_join(pid[0], NULL);
		pthread_join(pid[1], NULL);
	}
	else
	{
		while(1)
		{
			processor.sendCursor();
		}
	}
	
	return 0;
}


static void *fetchCursor( void * arg)
{
	while(1)
	{
		processor.sendCursor();
		//std::cout << "Finished calling processor.sendCursor()" << std::endl;
	}
}
