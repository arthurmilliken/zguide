#include "zzz.h"

void print_bin(uint32_t bin[10]) {
    for (int i = 0; i < 10; i++) {
        s_console("S: bin[%d]: %d", i, bin[i]);
    }
    printf("\n");
}

int main()
{
    uint32_t bin[10] = { 0,0,0,0,0,0,0,0,0,0 };

    // while (true) {
    for (uint32_t i = 0; i < 10000000; i++) {
        // Get values that will fool the boss
        uint32_t zipcode, temperature, relhumidity;
        zipcode = randto(100000);
        temperature = randto(215) - 80;
        relhumidity = randto(50) + 10;

        if (i % 1000000 == 0) {
            print_bin(bin);
        }
        int idx = (int)(zipcode / 10000);
        bin[idx]++;
    }
    print_bin(bin);
    return 0;
}
