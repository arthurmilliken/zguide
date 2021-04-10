#include "zzz.h"

int main(void)
{
    s_console("Hello from test!");
    long interval;
    while(1) {
        interval = randto(1000);
        s_sleep(interval);
        s_console("ping");
    }
    return 0;
}