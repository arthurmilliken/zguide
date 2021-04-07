//
// Simple message queueing broker
// Same as request-reply broker but using shared queue proxy
//
#include "zzz.h"

int main (void)
{
    int rc;
    zactor_t* proxy = zactor_new(zproxy, NULL);
    assert(proxy);
    char fe_endpoint[] = "tcp://*:5559";
    char be_endpoint[] = "tcp://*:5560";
    rc = zstr_sendx(proxy, "FRONTEND", "ROUTER", fe_endpoint, NULL);
    assert(rc == 0);
    rc = zsock_wait(proxy);
    assert(rc >= 0);
    rc = zstr_sendx(proxy, "BACKEND", "DEALER", be_endpoint, NULL);
    assert(rc == 0);
    rc = zsock_wait(proxy);
    assert(rc >= 0);
    s_console("P: proxy bound %s (FE) -> (BE) %s ", fe_endpoint, be_endpoint);
    // Run until interrupted
    zsock_wait(proxy);
    s_console("P: proxy interrupted. closing down.");
    zactor_destroy(&proxy);
    return 0;
}

// int main (void)
// {
//     void* context = zmq_ctx_new();
//     int rc;

//     // Socket facing clients
//     void* frontend = zmq_socket(context, ZMQ_ROUTER);
//     rc = zmq_bind(frontend, "tcp://*:5559");
//     assert(rc == 0);

//     // Socket facing services
//     void* backend = zmq_socket(context, ZMQ_DEALER);
//     rc = zmq_bind(backend, "tcp://*:5560");
//     assert(rc == 0);

//     // Start the proxy
//     zmq_proxy(frontend, backend, NULL);

//     // We never get here...
//     zmq_close(frontend);
//     zmq_close(backend);
//     zmq_ctx_destroy(context);
//     return 0;
// }