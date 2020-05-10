#include <sys/vfs.h>
#include <string.h>
#include <errno.h>

int stat(const char *orig_name, struct stat *buf)
{
    struct vfs *v;
    char *name = __getfilebuffer();
    int r;
    
#ifdef _DEBUG
    __builtin_printf("stat(%s)\n", name);
#endif    
    v = __getvfsforfile(name, orig_name);
    if (!v || !v->stat) {
#ifdef _DEBUG
        __builtin_printf("stat: ENOSYS\n");
#endif        
        return _seterror(ENOSYS);
    }
    memset(buf, 0, sizeof(*buf));
#ifdef _DEBUG
    {
        unsigned *ptr = (unsigned *)v->stat;
        __builtin_printf("calling v->stat %x (%x : %x)\n", (unsigned)ptr, ptr[0], ptr[1]);
    }
#endif    
    r = v->stat(name, buf);
#ifdef _DEBUG
    __builtin_printf("stat: returning %d\n", r);
#endif    
    return r;
}
