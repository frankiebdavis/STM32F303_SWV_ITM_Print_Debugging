#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "stm32f3xx.h"

/* ITM (Instrumentation Trace Macrocell) for SWV printf debugging */
#define ITM_TRACE_EN           (*((volatile uint32_t*) 0xE0000E00))
#define DEMCR                  (*((volatile uint32_t*) 0xE000EDFC))
#define ITM_STIMULUS_PORT0     (*((volatile uint32_t*) 0xE0000000))

/**
  * @brief Sends a single character via ITM (SWV)
  */
void ITM_SendChar(uint8_t ch)
{
    DEMCR |= (1 << 24);          // Enable trace (TRCENA)
    ITM_TRACE_EN |= (1 << 0);    // Enable ITM Stimulus Port 0

    while (!(ITM_STIMULUS_PORT0 & 1));  // Wait until ready
    ITM_STIMULUS_PORT0 = ch;
}

/* Minimal re-targeting of newlib syscalls for printf support */
int _write(int file, char *ptr, int len)
{
    (void)file;
    for (int i = 0; i < len; i++)
    {
        ITM_SendChar((uint8_t)ptr[i]);
    }
    return len;
}

/* Stubs for unused syscalls */
int _read(int file, char *ptr, int len) { return 0; }
int _close(int file) { return -1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _getpid(void) { return 1; }
int _kill(int pid, int sig) { errno = EINVAL; return -1; }
void _exit(int status) { while (1); }
int _open(char *path, int flags, ...) { return -1; }
int _wait(int *status) { errno = ECHILD; return -1; }
int _unlink(char *name) { errno = ENOENT; return -1; }
int _times(struct tms *buf) { return -1; }
int _stat(char *file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _link(char *old, char *new) { errno = EMLINK; return -1; }
int _fork(void) { errno = EAGAIN; return -1; }
int _execve(char *name, char **argv, char **env) { errno = ENOMEM; return -1; }
