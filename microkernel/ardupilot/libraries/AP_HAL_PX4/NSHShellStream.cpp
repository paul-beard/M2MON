/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
  implementation of NSH shell as a stream, for use in nsh over MAVLink

  See GCS_serial_control.cpp for usage
 */

#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_PX4
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <apps/nsh.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "Scheduler.h"

extern const AP_HAL::HAL& hal;

#include "Util.h"
using namespace PX4;

#ifdef __clang__
void NSHShellStream::shell_thread(void *self)
#else
void NSHShellStream::shell_thread(void)
#endif
{
#ifdef __clang__
    NSHShellStream *_this = (NSHShellStream *)self;
#endif
    close(0);
    close(1);
    close(2);
#ifdef __clang__
    dup2(_this->child.in, 0);
    dup2(_this->child.out, 1);
    dup2(_this->child.out, 2);
#else
    dup2(child.in, 0);
    dup2(child.out, 1);
    dup2(child.out, 2);
#endif

    nsh_consolemain(0, NULL);    

#ifdef __clang__
    _this->shell_stdin  = -1;
    _this->shell_stdout = -1;
    _this->child.in  = -1;
    _this->child.out = -1;
#else
    shell_stdin  = -1;
    shell_stdout = -1;
    child.in  = -1;
    child.out = -1;
#endif
}

void NSHShellStream::start_shell(void)
{
    if (hal.util->available_memory() < 8192) {
        if (!showed_memory_warning) {
            showed_memory_warning = true;
            hal.console->printf("Not enough memory for shell\n");
        }
        return;
    }
    if (hal.util->get_soft_armed()) {
        if (!showed_armed_warning) {
            showed_armed_warning = true;
            hal.console->printf("Disarm to start nsh shell\n");
        }
        // don't allow shell start when armed
        return;
    }

    int p1[2], p2[2];

    if (pipe(p1) != 0) {
        return;
    }
    if (pipe(p2) != 0) {
        return;
    }
    shell_stdin  = p1[0];
    shell_stdout = p2[1];
    child.in  = p2[0];
    child.out = p1[1];

    pthread_attr_t thread_attr;
    struct sched_param param;

    pthread_attr_init(&thread_attr);
    pthread_attr_setstacksize(&thread_attr, 2048);

    param.sched_priority = APM_SHELL_PRIORITY;
    (void)pthread_attr_setschedparam(&thread_attr, &param);
    pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);

    pthread_create(&shell_thread_ctx, &thread_attr, (pthread_startroutine_t)&PX4::NSHShellStream::shell_thread, this);
}

size_t NSHShellStream::write(uint8_t b)
{
    if (shell_stdout == -1) {
        start_shell();
    }
    if (shell_stdout != -1) {
        return ::write(shell_stdout, &b, 1);
    }
    return 0;
}

size_t NSHShellStream::write(const uint8_t *buffer, size_t size)
{
    size_t ret = 0;
    while (size > 0) {
        if (write(*buffer++) != 1) {
            break;
        }
        ret++;
        size--;
    }
    return ret;
}

int16_t NSHShellStream::read()
{
    if (shell_stdin == -1) {
        start_shell();
    }
    if (shell_stdin != -1) {
        uint8_t b;
        if (::read(shell_stdin, &b, 1) == 1) {
            return b;
        }
    }
    return -1;
}

int16_t NSHShellStream::available()
{
    int ret = 0;
    if (ioctl(shell_stdin, FIONREAD, (unsigned long)&ret) == OK) {
        return ret;
    }
    return 0;
}

int16_t NSHShellStream::txspace()
{
    int ret = 0;
    if (ioctl(shell_stdout, FIONWRITE, (unsigned long)&ret) == OK) {
        return ret;
    }
    return 0;
}

#endif // CONFIG_HAL_BOARD
