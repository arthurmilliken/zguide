//
// Task sink - design 2
// Adds pub-sub flot to send kill signal to workers
//
#include "zzz.h"

int main(void) {
    int rc;
    // Socket to receive messages
    void* context = zmq_ctx_new();
    void* receiver = zmq_socket(context, ZMQ_PULL);
    rc = zmq_bind(receiver, "tcp://*:5558");
    assert(rc >= 0);

    // Socket for worker control
    void* controller = zmq_socket(context, ZMQ_PUB);
    rc = zmq_bind(controller, "tcp://*:5559");
    assert(rc >= 0);

    // Wait for start of batch
    char* string = s_recv(receiver);
    free(string);

    // Start our clock now
    int64_t start_time = s_clock();

    // Process 100 confirmations
    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        char* string = s_recv(receiver);
        free(string);
        if (task_nbr % 10 == 0) printf("|");
        else printf(".");
        fflush(stdout);
    }
    printf("\nTotal elapsed time: %d msec\n", (int) (s_clock() - start_time));

    // Send KILL signal to workers.
    rc = s_send(controller, "KILL");
    assert(rc >= 0);

    zmq_close(receiver);
    zmq_close(controller);
    zmq_ctx_destroy(context);
    return 0;
}