//
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
//
#include "zzz.h"

int main(int argc, char* argv[]) {
    char* filter = (argc > 1) ? argv[1] : "10001";

    // Subscriber socket
    char conn_url[] = "tcp://localhost:5556";
    zsock_t* subscriber = zsock_new_sub(conn_url, filter);
    assert(subscriber);
    printf("C: wuclient connected to %s\n", conn_url);
    printf("C: Collecting updates for '%s' from weather server...\n", filter);

    // Process 100 updates
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {
        char* msg = zstr_recv(subscriber);

        int zipcode, temperature, relhumidity;
        int rc = sscanf(msg, "%d %d %d", &zipcode, &temperature, &relhumidity);
        assert(rc > 0);
        total_temp += temperature;
        zstr_free(&msg);
    }
    printf(
        "C: Average temperature for zipcode '%s' was %dF\n",
        filter,
        (int)(total_temp / update_nbr)
    );
    zsock_destroy(&subscriber);
    return 0;
}
