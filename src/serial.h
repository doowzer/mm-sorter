#ifndef SERIAL_H
#define SERIAL_H

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int fd;

/**
 *
 */
void serial_setup(char *port)
{
        fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY);
        if (fd == -1) {
                fprintf(stderr, "- Error: open() -> %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
}

/**
 *
 */
void serial_send(char *command)
{
        write(fd, command, strlen(command));
}

/**
 *
 */
void serial_close(void)
{
        close(fd);
}

#endif
