//
// Multithreaded Hello World server
//
#include "zzz.h"
#include <pthread.h>
#include <unistd.h>

static void*
worker_routine (void* context) {
    // Socket to talk to dispatcher
    void* receiver = zmq_socket(context, ZMQ_REP);
    zmq_connect(receiver, "inproc://workers");

    while (1) {
        char* string = s_recv(receiver);
        printf("Received request: [%s]\n", string);
        free(string);
        // Do some "work"
        sleep(1);
        // Send reply back to client
        s_send(receiver, "World");
    }
    zmq_close(receiver);
    return NULL;
}

// static zsock_t* router;
// static zsock_t* dealer;

int main (void)
{
    int rc;
    void* context = zmq_ctx_new();

    // Socket to talk to clients
    void* router = zmq_socket(context, ZMQ_ROUTER);
    zmq_bind(router, "tcp://*:5555");

    // Socket to talk to workers
    void* dealer = zmq_socket(context, ZMQ_DEALER);
    zmq_bind(dealer, "inproc://workers");

    // Launch pool of worker threads
    int thread_nbr;
    for (thread_nbr = 0; thread_nbr < 5; thread_nbr++) {
        pthread_t worker;
        pthread_create(&worker, NULL, worker_routine, context);
    }
    // Connect work threads to client threads via a queue proxy
    rc = zmq_proxy(router, dealer, NULL);
    assert(rc == 0);
    printf("after zmq_proxy\n");

    // We never get here, but clean up anyhow
    zmq_close(router);
    zmq_close(dealer);
    zmq_ctx_destroy(context);
    return 0;
}
