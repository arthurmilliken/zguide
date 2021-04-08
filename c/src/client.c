//
// Hello World client
//
#include <czmq.h>

int main(int argc, char* argv[])
{
    printf("C: Connecting to hello world server...\n");
    char bind_addr[] = "tcp://localhost:5555";
    zsock_t* requester = zsock_new_req(bind_addr);
    assert(requester);
    printf("C: Connected at %s\n", bind_addr);

    int request_nbr, rc;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char sending[] = "Hello";
        printf("C: Sending %s [%d]...\n", sending, request_nbr);
        rc = zstr_send(requester, sending);
        if (rc < 0) break;

        char* received = zstr_recv(requester);
        if (!received) break;
        printf("C: Received '%s' %d\n", received, request_nbr);
        zstr_free(&received);
    }

    zsock_destroy(&requester);
    puts("\nC: done.");
    return 0;
}