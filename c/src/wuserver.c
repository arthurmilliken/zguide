// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates
#include "zhelpers.h"

int main (void)
{
  // Publisher socket
  char bind_addr[] = "tcp://*:5556";
  zsock_t *publisher = zsock_new_pub (bind_addr);
  assert(publisher);
  printf ("S: wuserver bound to %s\n", bind_addr);

  // Initialize random number generator
  srandom ((unsigned) time (NULL));
  while (true) {
    // Get values that will fool the boss
    int zipcode, temperature, relhumidity;
    zipcode =     randof (100000);
    temperature = randof (215) - 80;
    relhumidity = randof (50) + 10;

    // Send message to all subscribers
    char update [15];
    sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
    int rc = zstr_send (publisher, update);
    assert(rc == 0);
  }
  zsock_destroy(&publisher);
  return 0;
}
