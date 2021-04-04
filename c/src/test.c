#include "zzz.h"

int main(void)
{
    s_console("Hello from test!");
    s_sleep(500);
    s_console("randto(10000) = %d", randto(10000));
    return 0;
}