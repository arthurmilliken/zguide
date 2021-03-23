// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
#include "zhelpers.h"

int main (int argc, char *argv [])
{
  // Subscribe to zipcode, default is NYC, 10001
  const char *filter = (argc > 1) ? argv[1] : "10001";

  // Subscriber socket
  char bind_addr[] = "tcp://localhost:5556";
  zsock_t *subscriber = zsock_new_sub (bind_addr, filter);
  assert(subscriber);
  printf ("C: wuclient connected to %s\n", bind_addr);
  printf ("C: Collecting updates for '%s' from weather server...\n", filter);

  // Process 100 updates
  int update_nbr;
  long total_temp = 0;
  for (update_nbr = 0; update_nbr < 100; update_nbr++) {
    char *msg = zstr_recv (subscriber);

    int zipcode, temperature, relhumidity;
    sscanf (msg, "%d %d %d", &zipcode, &temperature, &relhumidity);
    total_temp += temperature;
    zstr_free (&msg);
  }
  printf (
    "C: Average temperature for zipcode '%s' was %dF\n",
    filter,
    (int) (total_temp / update_nbr)
  );

  zsock_destroy (&subscriber);
  return 0;
}

// #include "zhelpers.h"
// int main (int argc, char *argv [])
// {
//   // Socket to talk to server
//   printf ("Collecting updates from weather server...\n");
//   void *context = zmq_ctx_new ();
//   void *subscriber = zmq_socket (context, ZMQ_SUB);
//   int rc = zmq_connect (subscriber, "tcp://localhost:5556");
//   assert (rc == 0);
//
//   // Subscribe to zipcode, default is NYC, 10001
//   const char *filter = (argc > 1) ? argv[1] : "10001";
//   rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
//   assert (rc == 0);
//
//   // Process 100 updates
//   int update_nbr;
//   long total_temp = 0;
//   for (update_nbr = 0; update_nbr < 100; update_nbr++) {
//     char *string = s_recv (subscriber);
//
//     int zipcode, temperature, relhumidity;
//     sscanf (string, "%d %d %d", &zipcode, &temperature, &relhumidity);
//     total_temp += temperature;
//     free (string);
//   }
//   printf (
//     "Average temperature for zipcode '%s' was %dF\n",
//     filter,
//     (int) (total_temp / update_nbr)
//   );
//
//   zmq_close (subscriber);
//   zmq_ctx_destroy (context);
//   return 0;
// }
