/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/5/21   0BitBiscuits  the first version
 */
#ifndef PORTING_FIO_H__
#define PORTING_FIO_H__

#include <sys/types.h>
#include <sys/stat.h>

int __mlibc_sys_fcntl(int fd, int cmd, ...);
int __mlibc_sys_ioctl(int fd, int cmd, ...);
int __mlibc_sys_open(const char *path, int flags, ...);
int __mlibc_sys_close(int fd);
ssize_t __mlibc_read(int fd, void* buf, size_t buf_size);
ssize_t __mlibc_write(int fd, const void* buf, size_t buf_size);
off_t __mlibc_lseek(int fd, off_t offset, int whence);
int __mlibc_fstat(int fd, struct stat* buf);
int __mlibc_stat(const char* pathname, struct stat* buf);

#endif
