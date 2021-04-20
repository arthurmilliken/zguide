//
// Pubsub enveloper publisher
// Note that zzz.h also provides s_sendmore
//
#include "zzz.h"
#include <unistd.h>

int main (void)
{
    // Prepare our context and publisher
    char addr[] = "tcp://*:5563";
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind (publisher, addr);
    s_console("bound to %s", addr);

    while (1) {
        // Write two messages, each with an envelope and content
        s_sendmore (publisher, "A");
        s_send (publisher, "We don't want to see this");
        s_sendmore (publisher, "B");
        s_send (publisher, "We would like to see this");
        sleep (1);
    }
    // We never get here, but clean up anyhow
    s_console("we never get here (:");
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}