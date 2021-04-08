//
// Shows how to handle Ctrl-C
//
#include "zzz.h"

static zsock_t* responder;

static void cleanup(void) {
    if (responder) {
        zsock_destroy(&responder);
        puts("S: done.");
    }
}

static void on_signal(int _) {
    puts("\nS: interrupt received.");
    cleanup();
}

// Signal handling example
int main(void) {
    int rc;
    char url[] = "tcp://*:5555";
    responder = zsock_new_rep(url);
    assert(responder);
    printf("S: listening to %s\n", url);

    zsys_handler_set(on_signal);

    while (1) {
        char* msg = zstr_recv(responder);
        if (!msg) break;
        printf("S: Received: %s\n", msg);
        // Now send message back.
        s_sleep(1000);
        if (!responder) break;
        char sending[] = "World";
        printf("S: Sending: %s\n", sending);
        rc = zstr_send(responder, sending);
        if (rc < 0) break;
    }
    cleanup();
}