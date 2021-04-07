//
// Task worker
// Connects PULL socket to tcp://localhost:5557
// Collects workloads from ventilator via that socket
// Connects PUSH socket to tcp://localhost:5558
// Sends results to sink via that socket
//
#include "zzz.h"

int main(int argc, char* argv[]) {
	// Socket to receive messages on
	zsock_t* receiver = zsock_new(ZMQ_PULL);
	int rc = zsock_connect(receiver, "tcp://localhost:5557");
	assert(rc >= 0);

	// Socket to send messages to
	zsock_t* sender = zsock_new_push("tcp://localhost:5558");
	assert(sender);

	// Process tasks forever
	while (1) {
		char* string = zstr_recv(receiver);
		if (!string) break;
		printf("%s.", string); // Show progress
		fflush(stdout);
		s_sleep(atoi(string)); // Do the work
		zstr_free(&string);
		zstr_send(sender, ""); // Send results to sink
	}
	zsock_destroy(&receiver);
	zsock_destroy(&sender);
	return 0;
}