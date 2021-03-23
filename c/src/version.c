// Report 0MQ version

#include <zmq.h>
#include <czmq.h>

int main (void)
{
  int major, minor, patch;
  zmq_version (&major, &minor, &patch);
  printf ("Current 0MQ version is %d.%d.%d\n", major, minor, patch);
  zsys_version (&major, &minor, &patch);
  printf ("Current CZMQ version is %d.%d.%d\n", major, minor, patch);
  return 0;
}
