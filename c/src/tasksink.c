//
// Task sink
// Builds PULL socket to tcp://localhost:5558
// Collects results from workers via that socket
//
# include "zzz.h"

int main(int argc, char* argv[]) {
	// Prepare our context and socket
	zsock_t* receiver = zsock_new_pull("tcp://*:5558");
	assert(receiver);

	// Wait for start of batch
	char* string = zstr_recv(receiver);
	zstr_free(&string);

	// Start our clock now
	int64_t start_time = s_clock();

	// Process 100 confirmation
	int task_nbr;
	for (task_nbr = 0; task_nbr < 100; task_nbr++) {
		string = zstr_recv(receiver);
		zstr_free(&string);
		if (task_nbr % 10 == 0)
			printf(":");
		else
			printf(".");
		fflush(stdout);
	}

	// Calculate and report duration of batch
	printf("\nTotal elapsed time: %d msec\n", (int)(s_clock() - start_time));

	zsock_destroy(&receiver);
	return 0;
}
