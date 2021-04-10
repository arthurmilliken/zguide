#include "zzz.h"

int main (void)
{
    int rc;
    zactor_t* proxy = zactor_new(zproxy, NULL);
    assert(proxy);
    char fe_endpoint[] = "ipc:///tmp/zguide-frontend.ipc";
    char be_endpoint[] = "ipc:///tmp/zguide-backend.ipc";
    rc = zstr_sendx(proxy, "FRONTEND", "ROUTER", fe_endpoint, NULL);
    assert(rc == 0);
    rc = zsock_wait(proxy);
    assert(rc >= 0);
    rc = zstr_sendx(proxy, "BACKEND", "DEALER", be_endpoint, NULL);
    assert(rc == 0);
    rc = zsock_wait(proxy);
    assert(rc >= 0);
    s_console("P: proxy bound %s (FE) -> (BE) %s ", fe_endpoint, be_endpoint);
    // Run until interrupted
    zsock_wait(proxy);
    s_console("P: proxy interrupted. closing down.");
    zactor_destroy(&proxy);
    return 0;
}
