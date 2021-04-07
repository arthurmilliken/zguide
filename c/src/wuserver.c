//
// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates
//
#include "zzz.h"

int main(int argc, char* argv[]) {
    // Publisher socket
    char bind_addr[] = "tcp://*:5556";
    zsock_t* publisher = zsock_new_pub(bind_addr);
    assert(publisher);
    s_console("S: wuserver bound to %s", bind_addr);

    while (true) {
        // Get values that will fool the boss
        uint32_t zipcode, temperature, relhumidity;
        zipcode = randto(100000);
        temperature = randto(215) - 80;
        relhumidity = randto(50) + 10;

        // Send message to all subscribers
        char update[15];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        int rc = zstr_send(publisher, update);
        assert(rc == 0);
    }
    s_console("S: done");
    zsock_destroy(&publisher);
    return 0;
}
