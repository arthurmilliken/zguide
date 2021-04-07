//
// Weather proxy device
//
#include "zzz.h"

int main(void) {
    int rc;
    void* context = zmq_ctx_new();

    // This is where the weather server sits
    char fe_endpoint[] = "tcp://localhost:5556";
    void* frontend = zmq_socket(context, ZMQ_XSUB);
    rc = zmq_connect(frontend, fe_endpoint);
    assert(rc >= 0);
    s_console("P: wuproxy frontend: %s", fe_endpoint);

    // This is our public endpoint for subscribers
    char be_endpoint[] = "tcp://*:5557";
    void* backend = zmq_socket(context, ZMQ_XPUB);
    rc = zmq_bind(backend, be_endpoint);
    assert(rc >= 0);
    s_console("P: wuproxy backend: %s", be_endpoint);

    // Run the proxy until the user interrupts us
    zmq_proxy(frontend, backend, NULL);

    zmq_close(frontend);
    zmq_close(backend);
    zmq_ctx_destroy(context);
    return 0;
}