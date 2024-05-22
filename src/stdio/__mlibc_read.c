/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/5/7   0Bitbiscuits  the first version
 */
#include <sys/syscall.h>
#include "../internal/stdio_impl.h"
#include <fcntl.h>


/**
 * @brief Read file data to user buffer
 * 
 * @param f  a pointer to a FILE structure
 * @param buf user buffer
 * @param len user buffer size
 * @return size_t the number of file data we read
 */
size_t __mlibc_read(FILE *f, unsigned char *buf, size_t len)
{
    size_t cnt = 0;
    /* read data into user buf first */
    iovec_t iov[2] = {
        { .buf = buf, .buf_size = len - !!f->buf_size },
        { .buf = f->buf, .buf_size = f->buf_size }
    };
    
    /** 
     * if user buf size equals 1, only call sys_read once to fill file buf
     * and then read one byte to user buf. otherwise, call sys_read twice to
     * fill user buf and file buf.
     */
    cnt = iov[0].buf_size ? __mlibc_sys_readv(f->fd, iov, 2)
        : __mlibc_sys_read(f->fd, iov[1].buf, iov[1].buf_size);
    if(cnt <= 0) 
    {
        /* when cnt equals 0 means read EOF, otherwise read ERR */
        f->flags |= cnt ? F_ERR : F_EOF;
        return 0;
    }

    /* user buffer is enough to store data */
    if(cnt <= iov[0].buf_size)
    {
        return cnt;
    }

    /* the file buffer also reads data */
    cnt -= iov[0].buf_size;
    f->rpos = f->buf;
    f->rend = f->buf + cnt;
    buf[len - 1] = *f->rpos++;

    return len;
}