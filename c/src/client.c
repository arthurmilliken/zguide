#include <czmq.h>

int main (void)
{
  printf ("C: Connecting to hello world server...\n");
  char bind_addr[] = "tcp://localhost:5555";
  zsock_t *requester = zsock_new_req (bind_addr);
  printf ("C: Connected at %s\n", bind_addr);

  int request_nbr;
  char *msg;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    char sending[] = "Hello";
    printf ("C: Sending %s [%d]...\n", sending, request_nbr);
    zstr_send (requester, sending);

    char *received = zstr_recv (requester);
    printf ("C: Received '%s' %d\n", received, request_nbr);
    zstr_free(&received);
  }

  zsock_destroy (&requester);
  puts ("C: done.");
}
