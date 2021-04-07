//
// Hello World worker
// Connects REP socket to tcp://localhost:5560
// Expects "Hello" from client, replies with "World"
//
#include "zzz.h"

int main (int argc, char* argv[]) {
    char* name = (argc > 1) ? argv[1] : "W";

    int rc;
    // Socket to talk to clients
    char conn_url[] = "tcp://localhost:5560";
    zsock_t* responder = zsock_new(ZMQ_REP);
    rc = zsock_connect(responder, "%s", conn_url);
    assert(rc >= 0);
    s_console("%s: rrworker connected to %s", name, conn_url);

    while (1) {
        // Wait for next request from client
        char* string = zstr_recv(responder);
        if (!string) break;
        s_console("%s: Received request: '%s'", name, string);
        zstr_free(&string);
        
        // Do some "work"
        sleep (1);

        // Send reply back to client
        string = "World";
        s_console("%s: Sending reply: '%s'", name, string);
        rc = zstr_send(responder, "World");
        assert(rc == 0);
    }
    // We never get here, but clean up anyhow
    zsock_destroy(&responder);
    return 0;
}

// int main (int argc, char* argv[]) {
//     char* name = (argc > 1) ? argv[1] : "W";
//     void* context = zmq_ctx_new();

//     // Socket to talk to clients
//     void* responder = zmq_socket(context, ZMQ_REP);
//     zmq_connect(responder, "tcp://localhost:5560");

//     while(1) {
//         // Wait for next request from client
//         char* string = s_recv(responder);
//         if (string == NULL) break;
//         printf("%s: Received request: [%s]\n", name, string);
//         free(string);
        
//         // Do some "work"
//         sleep (1);

//         // Send reply back to client
//         s_send(responder, "World");
//     }
//     // We never get here, but clean up anyhow
//     zmq_close(responder);
//     zmq_ctx_destroy(context);
//     return 0;
// }