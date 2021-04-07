//
// Simple request-reply broker
//
#include "zzz.h"

int main(int argc, char* argv[]) {
    char* name = (argc > 1) ? argv[1]: "B";

    // Prepare our sockets
    char fendpoint[] = "tcp://*:5559";
    zsock_t* frontend = zsock_new_router(fendpoint);
    assert(frontend);
    s_console("%s: rrbroker bound front-end: %s", name, fendpoint);

    char bendpoint[] = "tcp://*:5560";
    zsock_t* backend = zsock_new(ZMQ_DEALER);
    int rc = zsock_bind(backend, "%s", bendpoint);
    assert(rc >= 0);
    s_console("%s: rrbroker bound back-end: %s", name, bendpoint);

    // Initialize poll set
    zpoller_t* poller = zpoller_new(frontend, backend, NULL);
    assert(poller);

    // Switch messages between sockets
    while (1) {
        zsock_t* from = (zsock_t*) zpoller_wait(poller, -1);
        if (!from) break;
        zsock_t* to = (from == frontend ? backend : frontend);
        zmsg_t* msg = zmsg_recv(from);
        rc = zmsg_send(&msg, to);
        assert(rc == 0);
    }
    zsock_destroy(&frontend);
    zsock_destroy(&backend);
    s_console("%s: rrbroker done.", name);
    return 0;
}