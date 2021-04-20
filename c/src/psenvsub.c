//
// Pubsub enelope subscriber
//
#include "zzz.h"

int main (void)
{
    // Prepare our context and subscriber
    char addr[] = "tcp://localhost:5563";
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, addr);
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "B", 1);
    s_console ("connected to %s", addr);

    while (1) {
        // Read envelope with address
        char *address = s_recv (subscriber);
        // Read message contents
        char *contents = s_recv (subscriber);
        s_console ("[%s] %s", address, contents);
        free (address);
        free (contents);
    }
    // We never get here, but clean up anyhow
    s_console ("we never get here (:");
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
}