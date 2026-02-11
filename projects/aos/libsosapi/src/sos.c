/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sos.h>

#include <sel4/sel4.h>

static size_t sos_debug_print(const void *vData, size_t count)
{
#ifdef CONFIG_DEBUG_BUILD
    size_t i;
    const char *realdata = vData;
    for (i = 0; i < count; i++) {
        seL4_DebugPutChar(realdata[i]);
    }
#endif
    return count;
}

int sos_open(const char *path, fmode_t mode)
{
    assert(!"You need to implement this");
    return -1;
}

int sos_close(int file)
{
    assert(!"You need to implement this");
    return -1;
}

int sos_read(int file, char *buf, size_t nbyte)
{
    assert(!"You need to implement this");
    return -1;
}

int sos_write(int file, const char *buf, size_t nbyte)
{
    /* TODO MILESTONE 0: implement this to use your syscall and
     * writes to the network console!
     * Writing to files will come in later milestones.
     */

    seL4_IPCBuffer *ipc_buf = seL4_GetIPCBuffer();
    size_t bytes_sent = 0;

    // batching
    while (bytes_sent < nbyte) {
        size_t max_chunk_size = seL4_MsgMaxLength * sizeof(seL4_Word);
        size_t remaining = nbyte - bytes_sent;
        size_t current_chunk_len = (remaining > max_chunk_size) ? max_chunk_size : remaining;

        memcpy(&ipc_buf->msg[2], buf + bytes_sent, current_chunk_len);

        seL4_Word words_to_send = (current_chunk_len + sizeof(seL4_Word) - 1) / sizeof(seL4_Word);
        
        seL4_SetMR(0, SOS_SYSCALL_WRITE);
        seL4_SetMR(1, current_chunk_len); //First message register 
        seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2 + words_to_send);
        // tag:
        // label: SYSCALL ID
        // no caps
        // length = 1 + words_to_send

        seL4_MessageInfo_t reply = seL4_Call(SOS_IPC_EP_CAP, tag);

        bytes_sent += current_chunk_len;
    }
     
    return bytes_sent;
    // return sos_debug_print(buf, nbyte);
}

int sos_getdirent(int pos, char *name, size_t nbyte)
{
    assert(!"You need to implement this");
    return -1;
}

int sos_stat(const char *path, sos_stat_t *buf)
{
    assert(!"You need to implement this");
    return -1;
}

pid_t sos_process_create(const char *path)
{
    assert(!"You need to implement this");
    return -1;
}

int sos_process_delete(pid_t pid)
{
    assert(!"You need to implement this");
    return -1;
}

pid_t sos_my_id(void)
{
    assert(!"You need to implement this");
    return -1;

}

int sos_process_status(sos_process_t *processes, unsigned max)
{
    assert(!"You need to implement this");
    return -1;
}

pid_t sos_process_wait(pid_t pid)
{
    assert(!"You need to implement this");
    return -1;

}

void sos_usleep(int msec)
{
    assert(!"You need to implement this");
}

int64_t sos_time_stamp(void)
{
    assert(!"You need to implement this");
    return -1;
}
