#include <stdint.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <dirent.h>

struct __using("filesys/fs9p/fs9p_internal.c") FS;

// receive 1 byte
static unsigned int zdoGet1()
{
    int c;
    do {
        c = _rxraw();
    } while (c < 0);
    return c;
}

// receive an unsigned long
static unsigned int zdoGet4()
{
    unsigned r;
    r = zdoGet1();
    r = r | (zdoGet1() << 8);
    r = r | (zdoGet1() << 16);
    r = r | (zdoGet1() << 24);
    return r;
}

// send a buffer to the host
// then receive a reply
// returns the length of the reply, which is also the first
// longword in the buffer
//
// startbuf is that start of the buffer (used for both send and
// receive); endbuf is the end of data to send; maxlen is maximum
// size
static int basic_sendrecv(uint8_t *startbuf, uint8_t *endbuf, int maxlen)
{
    int len = endbuf - startbuf;
    uint8_t *buf = startbuf;
    int i = 0;
    int left;
    
    startbuf[0] = len & 0xff;
    startbuf[1] = (len>>8) & 0xff;
    startbuf[2] = (len>>16) & 0xff;
    startbuf[3] = (len>>24) & 0xff;

    if (len <= 4) {
        return -1; // not a valid message
    }
    // loadp2's server looks for magic start sequence of $FF, $01
    _tx(0xff);
    _tx(0x01);
    while (len>0) {
        _tx(*buf++);
        --len;
    }
    len = zdoGet4();
    startbuf[0] = len & 0xff;
    startbuf[1] = (len>>8) & 0xff;
    startbuf[2] = (len>>16) & 0xff;
    startbuf[3] = (len>>24) & 0xff;
    buf = startbuf+4;
    left = len - 4;
    while (left > 0 && i < maxlen) {
        buf[i++] = zdoGet1();
        --left;
    }
    return len;
}

struct vfs *
_vfs_open_host(void)
{
    int r;

    r = FS.fs_init(&basic_sendrecv);
    if (r != 0) {
#ifdef DEBUG
       __builtin_printf("fs_init failed: result=[%d]\n", r);
       waitms(1000);
#endif      
       _seterror(-r);
       return 0;
    }
    return FS.get_vfs();
}