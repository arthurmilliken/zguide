//
// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates
//
#include "zzz.h"

static zsock_t* publisher;

static void cleanup(void) {
    if (publisher) {
        zsock_destroy(&publisher);
        s_console("S: done.");
    }
}

static void on_signal(int _) {
    puts("");
    s_console("S: interrupt received.");
    cleanup();
}

int main(int argc, char* argv[]) {
    // Publisher socket
    char bind_addr[] = "tcp://*:5556";
    publisher = zsock_new_pub(bind_addr);
    assert(publisher);
    s_console("S: wuserver bound to %s", bind_addr);

    zsys_handler_set(on_signal);

    while (true) {
        // Get values that will fool the boss
        uint32_t zipcode, temperature, relhumidity;
        zipcode = randto(100000);
        temperature = randto(215) - 80;
        relhumidity = randto(50) + 10;

        // Send message to all subscribers
        char update[15];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        if (!publisher) break;
        int rc = zstr_send(publisher, update);
        if (rc < 0) break;
    }
    cleanup();
    return 0;
}
