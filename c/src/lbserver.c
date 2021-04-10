#include "zzz.h"

int main(int argc, char* argv[]) {
    int rc;
    char url[] = "ipc:///tmp/zguide-backend.ipc";
    zsock_t* reply = zsock_new(ZMQ_REP);
    assert(reply);
    rc = zsock_connect(reply, "%s", url);
    assert(rc >= 0);
    s_console("S: connected to %s.", url);

    while(1) {
        char* msg_server = zstr_recv(reply);
        assert(msg_server);
        s_console("S: received request: %s. sleeping...", msg_server);
        zclock_sleep(atoi(msg_server));
        s_console("S: sending reply: %s", msg_server);
        rc = zstr_send(reply, msg_server);
        assert(rc == 0);
        zstr_free(&msg_server);
    }
    zsock_destroy(&reply);
}