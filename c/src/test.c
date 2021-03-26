#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if RAND_MAX/256 >= 0xFFFFFFFFFFFFFF
#define LOOP_COUNT 1
#elif RAND_MAX/256 >= 0xFFFFFF
#define LOOP_COUNT 2
#elif RAND_MAX/256 >= 0x3FFFF
#define LOOP_COUNT 3
#elif RAND_MAX/256 >= 0x1FF
#define LOOP_COUNT 4
#else
#define LOOP_COUNT 5
#endif

uint64_t
rand64(void) {
    uint64_t r = 0;
    for (int i = LOOP_COUNT; i > 0; i--) {
        r = r * (RAND_MAX + (uint64_t)1) + rand();
    }
    return r;
}

bool seeded = false;

uint32_t
randto(uint32_t max) {
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    return (uint32_t)rand64() % max;
}

void
print_bucket(uint32_t bucket[10]) {
    for (int i = 0; i < 10; i++) {
        printf("S: bucket[%d]: %d\n", i, bucket[i]);
    }
    printf("\n");
}

void
main()
{
    uint32_t bucket[10] = { 0,0,0,0,0,0,0,0,0,0 };

    // Initialize random number generator
    srandom((unsigned)time(NULL));
    // while (true) {
    for (uint32_t i = 0; i < 10000000; i++) {
        // Get values that will fool the boss
        uint32_t zipcode, temperature, relhumidity;
        zipcode = randto(100000);
        temperature = randto(215) - 80;
        relhumidity = randto(50) + 10;

        if (i % 1000000 == 0) {
            print_bucket(bucket);
        }
        int idx = (int)(zipcode / 10000);
        bucket[idx]++;
    }
    print_bucket(bucket);
}
