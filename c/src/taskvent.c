//
// Task ventilator
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket
//
#include "zzz.h"

int main (void) 
{
    void *context = zmq_ctx_new ();

    //  Socket to send messages on
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_bind (sender, "tcp://*:5557");

    //  Socket to send start of batch message on
    void *sink = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sink, "tcp://localhost:5558");

    printf ("Press Enter when the workers are ready: ");
    getchar ();
    printf ("Sending tasks to workers...\n");

    //  The first message is "0" and signals start of batch
    s_send (sink, "0");

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));

    //  Send 100 tasks
    int task_nbr;
    int total_msec = 0;     //  Total expected cost in msecs
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload;
        //  Random workload from 1 to 100msecs
        workload = randto (100) + 1;
        total_msec += workload;
        char string [10];
        sprintf (string, "%d", workload);
        s_send (sender, string);
    }
    printf ("Total expected cost: %d msec\n", total_msec);

    zmq_close (sink);
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}

// int main(int argc, char* argv[])
// {
// 	int rc;
// 	// Socket to send messages on
// 	// zsock_t* sender = zsock_new_push("tcp://*:5557");
// 	zsock_t* sender = zsock_new(ZMQ_PUSH);
// 	assert(sender);
// 	rc = zsock_bind(sender, "tcp://*:5557");
// 	assert(rc == 0);

// 	// Socket to send start of batch message on
// 	zsock_t* sink = zsock_new_push("tcp://localhost:5558");
// 	assert(sink);

// 	printf("Press enter when the workers are ready: ");
// 	rc = getchar();
// 	printf("Sending tasks to workers...\n");

// 	// The first message is "0" and signals start of batch
// 	rc = zstr_send(sink, "0");
// 	assert(rc == 0);

// 	// Send 100 tasks
// 	int total_msec = 0; // Total expected cost in msecs
// 	for (int task_nbr = 0; task_nbr < 100; task_nbr++) {
// 		// Random workload from 1 to 100 msecs
// 		int workload = randto(100) + 1;
// 		total_msec += workload;
// 		char string[10];
// 		sprintf(string, "%d", workload);
// 		rc = zstr_send(sender, string);
// 		assert(rc == 0);
// 	}
// 	printf("Total expected cost: %d msec\n", total_msec);
// 	zsock_destroy(&sink);
// 	zsock_destroy(&sender);
// 	return 0;
// }
