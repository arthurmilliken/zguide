//
// Reading from multiple sockets
// This version uses a simple recv loop
//
#include "zzz.h"

int main(void) {
    // Connect to task ventilator
    void* context = zmq_ctx_new();
    void* receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    // Connect to weather server
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "10001", 5);

    // Process missages from both sockets
    // We prioritize traffic from the task ventilator
    while(1) {
        char msg[255];
        memset(msg, 0, 255);
        while(1) {
            memset(msg, 0, 255);
            int size = zmq_recv(receiver, msg, 255, ZMQ_DONTWAIT);
            if (size != -1) {
                // Process task
                printf("received from ventilator: %s\n", msg);
            }
            else break;
        }
        while(1) {
            memset(msg, 0, 255);
            int size = zmq_recv(subscriber, msg, 255, ZMQ_DONTWAIT);
            if (size != -1) {
                // Process weather update
                printf("Received from wuserver: %s\n", msg);
            }
            else break;
        }
        // No activity, so sleep for 1 msec
        s_sleep(1);
    }
    zmq_close(receiver);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}