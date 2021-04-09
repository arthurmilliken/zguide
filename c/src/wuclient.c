//
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
//
#include "zzz.h"

static zsock_t* subscriber;
static int update_nbr;

static void cleanup(void) {
    if (subscriber) {
        zsock_destroy(&subscriber);
        if (update_nbr < 100) {
            s_console("C: %d updates processed.", update_nbr);
        }
        s_console("C: done.");
    }
}

static void on_signal(int _) {
    puts("");
    s_console("C: interrupt received.");
    cleanup();
}

int main(int argc, char* argv[]) {
    char* filter = (argc > 1) ? argv[1] : "10001";
    char* conn_url = (argc > 2) ? argv[2] : "tcp://localhost:5556";

    // Subscriber socket
    subscriber = zsock_new_sub(conn_url, filter);
    assert(subscriber);
    s_console("C: wuclient connected to %s", conn_url);

    zsys_handler_set(on_signal);
    s_console("C: Collecting updates for '%s' from weather server...", filter);

    // Process 100 updates
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {
        if (!subscriber) break;
        char* msg = zstr_recv(subscriber);
        if (!msg) break;
        int zipcode, temperature, relhumidity;
        int rc = sscanf(msg, "%d %d %d", &zipcode, &temperature, &relhumidity);
        assert(rc > 0);
        total_temp += temperature;
        zstr_free(&msg);
    }
    if (update_nbr == 100) {
        s_console(
            "C: Average temperature for zipcode '%s' was %dF",
            filter,
            (int)(total_temp / update_nbr)
        );
    }

    cleanup();
    return 0;
}
