#ifndef SERIAL_H
#define SERIAL_H

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>

int fd;

/**
 *
 */
void serial_setup(char *port)
{

        /* int ret; */


        fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY);
        if (fd == -1) {
                fprintf(stderr, "- Error: open() -> %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        /*
        ret = tcgetattr(fd, &options);
        if (ret == -1) {
                fprintf(stderr, "- Error: tcgetattr() -> %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        cfsetispeed(&options, B9600);
        cfsetispeed(&options, B9600);
        */

        /*
        9600 baud
        8 databits
        1 stopbit
        no parity
        */
        /*
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        options.c_cflag &= ~CRTSCTS;

        options.c_cflag |= CREAD|CLOCAL;
        options.c_iflag &= ~(IXON|IXOFF|IXANY);

        options.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);
        options.c_oflag &= ~OPOST;

        options.c_cc[VMIN] = 0;
        options.c_cc[VTIME] = 0;

        ret = tcsetattr(fd, TCSAFLUSH, &options);
        if (ret == -1) {
                fprintf(stdout, "- Error: tcsetattr() -> %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
        */
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