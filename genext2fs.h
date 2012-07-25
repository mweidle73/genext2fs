#include <config.h>
#include <stdio.h>

#if HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#define EXT2_ROOT_INO 2 // Root inode

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;

typedef struct filesystem filesystem;

// initialize an empty filesystem
filesystem *
init_fs(int nbblocks, int nbinodes, int nbresrvd, int holes,
	uint32 fs_timestamp, uint32 creator_os, int swapit, char *fname);

void free_fs(filesystem *fs);

void finish_fs(filesystem *fs);

// find an entry in a directory
uint32
find_dir(filesystem *fs, uint32 nod, const char * name);

// make a full-fledged directory (i.e. with "." & "..")
inline uint32
mkdir_fs(filesystem *fs, uint32 parent_nod, const char *name, uint32 mode,
	uid_t uid, gid_t gid, uint32 ctime, uint32 mtime);

// create a simple inode
uint32
mknod_fs(filesystem *fs, uint32 parent_nod, const char *name, uint16 mode, uint16 uid, uint16 gid, uint8 major, uint8 minor, uint32 ctime, uint32 mtime);

// make a symlink
uint32
mklink_fs(filesystem *fs, uint32 parent_nod, const char *name, size_t size, uint8 *b, uid_t uid, gid_t gid, uint32 ctime, uint32 mtime);

// make a file from a FILE*
uint32
mkfile_fs(filesystem *fs, uint32 parent_nod, const char *name, uint32 mode, FILE *f, uid_t uid, gid_t gid, uint32 ctime, uint32 mtime);

// link an entry (inode #) to a directory
void
add2dir(filesystem *fs, uint32 dnod, uint32 nod, const char* name);
