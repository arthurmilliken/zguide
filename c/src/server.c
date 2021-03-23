#include <czmq.h>

int main (void)
{
  // Socket to talk to clients
  char bind_addr[] = "tcp://*:5555";
  zsock_t *responder = zsock_new_rep (bind_addr);
  printf ("S: hello world server listening at %s\n", bind_addr);

  while (1) {
    char *received = zstr_recv(responder);
    printf ("S: Received: %s\n", received);
    zstr_free(&received);
    sleep (1); // Do some "work"
    char sending[] = "World";
    printf ("S: Sending: %s\n", sending);
    zstr_send (responder, sending);
  }

  zsock_destroy (&responder);
  return 0;
}
