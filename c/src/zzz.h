#pragma once

#ifndef __ZZZ_H_INCLUDED__
#define __ZZZ_H_INCLUDED__

#include <zmq.h>
#include <czmq.h>
#include <stdint.h>

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

static uint64_t rand64(void) {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = true;
    }
    uint64_t r = 0;
    for (int i = LOOP_COUNT; i > 0; i--) {
        r = r * (RAND_MAX + (uint64_t)1) + rand();
    }
    return r;
}

// Generate a random number between 0 and max.
static uint32_t randto(uint32_t max) {
    return (uint32_t)rand64() % max;
}

//  Print formatted string to stdout, prefixed by date/time and
//  terminated with a newline.
static void s_console(const char* format, ...)
{
    time_t curtime = time(NULL);
    struct tm* loctime = localtime(&curtime);
    char* formatted = (char*)malloc(20);
    if (formatted != NULL)
        strftime(formatted, 20, "%y-%m-%d %H:%M:%S ", loctime);
    printf("%s", formatted);
    free(formatted);

    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
    printf("\n");
}

//  Sleep for a number of milliseconds
static void s_sleep(int msecs) {
#if (defined (WIN32))
    Sleep(msecs);
#else
    struct timespec t;
    t.tv_sec = msecs / 1000;
    t.tv_nsec = (msecs % 1000) * 1000000;
    nanosleep(&t, NULL);
#endif
}

//  Return current system clock as milliseconds
static int64_t
s_clock(void)
{
#if (defined (WIN32))
    SYSTEMTIME st;
    GetSystemTime(&st);
    return (int64_t)st.wSecond * 1000 + st.wMilliseconds;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
}

//  Convert C string to 0MQ string and send to socket
static int s_send(void* socket, char* string) {
    int size = zmq_send(socket, string, strlen(string), 0);
    return size;
}

//  Sends string as 0MQ string, as multipart non-terminal
static int s_sendmore(void* socket, char* string) {
    int size = zmq_send(socket, string, strlen(string), ZMQ_SNDMORE);
    return size;
}

//  Receive 0MQ string from socket and convert into C string
//  Caller must free returned string. Returns NULL if the context
//  is being terminated.
static char* s_recv(void* socket) {
    enum { cap = 256 };
    char buffer[cap];
    int size = zmq_recv(socket, buffer, cap - 1, 0);
    if (size == -1)
        return NULL;
    buffer[size < cap ? size : cap - 1] = '\0';
    return strdup(buffer);
}

#endif  //  __ZZZ_H_INCLUDED__
