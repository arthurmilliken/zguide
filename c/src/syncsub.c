//
// Synchronized subscriber
//
#include "zzz.h"
#include <unistd.h>

int main (void)
{
    int rc;
    void* context = zmq_ctx_new();

    // First, connect our subscriber socket
    char sub_url[] = "tcp://localhost:5561";
    // char sub_url[] = "ipc:///tmp/zguide-publisher.ipc";
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    rc = zmq_connect(subscriber, sub_url);
    assert(rc == 0);
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    assert(rc == 0);
    // s_console("SUB: subscribed to %s", sub_url);

    // 0MQ is SO FAST, we need to wait a while...
    sleep(1);

    // Second, synchronize with publisher
    char sync_url[] = "tcp://localhost:5562";
    // char sync_url[] = "ipc:///tmp/zguide-syncservice.ipc";
    void* syncclient = zmq_socket(context, ZMQ_REQ);
    rc = zmq_connect(syncclient, sync_url);
    assert(rc == 0);
    // s_console("SUB: connected to %s", sync_url);

    // - send a synchronization request
    s_send(syncclient, "");

    // - wait for synchronization reply
    char* string = s_recv(syncclient);
    free(string);

    // Third, get our updates and report how many we got
    int update_nbr = 0;
    while(1) {
        char* string = s_recv(subscriber);
        assert(string);
        if (strcmp(string, "END") == 0) {
            free(string);
            break;
        }
        free(string);
        update_nbr++;
    }
    s_console("SUB: Received %d updates", update_nbr);
    zmq_close(subscriber);
    zmq_close(syncclient);
    zmq_ctx_destroy(context);
    return 0;
}
