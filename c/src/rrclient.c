//
// Hello World client
// Connects REQ socket to tcp://localhost:5559
// Sends "Hello" to server, expects "World" back
//
#include "zzz.h"

int main (int argc, char* argv[]) {
    char* name = (argc > 1) ? argv[1] : "C";
    void* context = zmq_ctx_new();
    
    // Socket to talk to server
    void* requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5559");

    int request_nbr;
    for(request_nbr = 0; request_nbr != 10; request_nbr++) {
        s_send (requester, "Hello");
        char* string = s_recv(requester);
        printf("%s: Received reply %d [%s]\n", name, request_nbr, string);
        free(string);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}