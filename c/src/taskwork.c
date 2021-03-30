//
// Task worker
// Connects PULL socket to tcp://localhost:5557
// Collects workloads from ventilator via that socket
// Connects PUSH socket to tcp://localhost:5558
// Sends results to sink via that socket
//
#include "zzz.h"

int main (void) 
{
    //  Socket to receive messages on
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Socket to send messages to
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sender, "tcp://localhost:5558");

    //  Process tasks forever
    while (1) {
        char *string = s_recv (receiver);
        printf ("%s.", string);     //  Show progress
        fflush (stdout);
        s_sleep (atoi (string));    //  Do the work
        free (string);
        s_send (sender, "");        //  Send results to sink
    }
    zmq_close (receiver);
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}

// int main(int argc, char* argv[]) {
// 	// Socket to receive messages on
// 	// zsock_t* receiver = zsock_new_pull("tcp://localhost:5557");
// 	// assert(receiver);
// 	zsock_t* receiver = zsock_new(ZMQ_PULL);
// 	assert(receiver);
// 	int rc = zsock_connect(receiver, "tcp://localhost:5557");
// 	assert(rc == 0);

// 	// Socket to send messages to
// 	zsock_t* sender = zsock_new_push("tcp://localhost:5558");
// 	assert(sender);

// 	// Process tasks forever
// 	while (1) {
// 		char* string = zstr_recv(receiver);
// 		printf("%s.", string); // Show progress
// 		fflush(stdout);
// 		s_sleep(atoi(string)); // Do the work
// 		zstr_free(&string);
// 		zstr_send(sender, ""); // Send results to sink
// 	}

// 	zsock_destroy(&receiver);
// 	zsock_destroy(&sender);
// 	return 0;
// }
