//
// Synchronized publisher
//
#include "zzz.h"
#define SUBSCRIBERS_EXPECTED 5 // We wait for 10 subscribers

int main(void)
{
    int rc;
    void* context = zmq_ctx_new();

    // Socket to talk to clients
    void* publisher = zmq_socket(context, ZMQ_PUB);

    char pub_url[] = "tcp://*:5561";
    // char pub_url[] = "ipc:///tmp/zguide-publisher.ipc";
    int sndhwm = 1100000;
    zmq_setsockopt(publisher, ZMQ_SNDHWM, &sndhwm, sizeof(int));
    rc = zmq_bind(publisher, pub_url);
    assert(rc >= 0);
    s_console("PUB: bound publisher to %s", pub_url);

    // Socket to receive signals
    char sync_url[] = "tcp://*:5562";
    // char sync_url[] = "ipc:///tmp/zguide-syncservice.ipc";
    void* syncservice = zmq_socket(context, ZMQ_REP);
    rc = zmq_bind(syncservice, sync_url);
    assert(rc >= 0);
    s_console("PUB: bound syncservice to %s", sync_url);

    // Get synchronization from subscribers
    s_console("PUB: Waiting for subscribers...");
    int subscribers = 0;
    while (subscribers < SUBSCRIBERS_EXPECTED) {
        // - wait for synchronization request
        char* string = s_recv(syncservice);
        free (string);
        // - send synchronization reply
        s_send(syncservice, "");
        subscribers++;
    }
    // Now broadcast exactly 1M updates followed by END
    s_console("PUB: Subscribers synced. Broadcasting messages");
    int update_nbr;
    for (update_nbr = 0; update_nbr < 1000000; update_nbr++) {
        rc = s_send(publisher, "Rhubarb");
        assert(rc >= 0);
    }
    
    s_console("PUB: Done broadcasting. Sending END signal");
    s_send(publisher, "END");
    s_console("PUB: Done.");

    zmq_close(publisher);
    zmq_close(syncservice);
    zmq_ctx_destroy(context);
    return 0;
}