//
// Hello World server
//
#include "zzz.h"

int main(int argc, char* argv[])
{
    // Socket to talk to clients
    char bind_addr[] = "tcp://*:5555";
    zsock_t* responder = zsock_new_rep(bind_addr);
    assert(responder);
    printf("S: hello world server listening at %s\n", bind_addr);

    while (1) {
        char* received = zstr_recv(responder);
        if(received == "NULL")
            break;
        printf("S: Received: %s\n", received);
        zstr_free(&received);
        s_sleep(1000); // Do some "work"
        char sending[] = "World";
        printf("S: Sending: %s\n", sending);
        int rc = zstr_send(responder, sending);
        assert(rc == 0);
    }

    zsock_destroy(&responder);
    return 0;
}
