#include "zzz.h"

int main(int argc, char* argv[]) {
    int rc;
    int workload;
    if (argc > 1) {
        workload = atoi(argv[1]);
    }
    else {
        workload = randto(1000);
    }
    s_console("C: workoad: %d", workload);

    char url[] = "ipc:///tmp/zguide-frontend.ipc";
    zsock_t* request = zsock_new_req(url);
    assert(request);
    s_console("C: connected to %s", url);

    while (1) {
        char msg[10];
        sprintf(msg, "%d", workload);
        s_console("C: sending request: %s", msg);
        rc = zstr_send(request, msg);
        assert(rc >= 0);
        char* reply = zstr_recv(request);
        assert(reply);
        s_console("C: received reply: %s", reply);
        zstr_free(&reply);
    }

    zsock_destroy(&request);
}