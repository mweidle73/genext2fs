#include "genext2fs.h"

#include <stdio.h>
#include <string.h>

int
main(int argc, char **argv)
{
    const char *image_name;
    const char payload[] = "genext2fs embedding probe\n";
    filesystem *fs;
    FILE *input;

    if (argc != 2) {
        fprintf(stderr, "usage: embedding-probe IMAGE\n");
        return 2;
    }
    image_name = argv[1];

    if (set_blocksize(4096) != 0)
        return 1;

    fs = init_fs(256, 32, 0, 0, 946684800, 0, 0,
                 (char *) image_name);
    if (fs == NULL)
        return 1;

    fs_upgrade_rev1_largefile(fs);
    if (mkdir_fs(fs, EXT2_ROOT_INO, "etc", 0755, 0, 0,
                 946684800, 946684800) == 0)
        return 1;

    input = tmpfile();
    if (input == NULL)
        return 1;
    if (fwrite(payload, 1, strlen(payload), input) != strlen(payload))
        return 1;
    rewind(input);

    if (mkfile_fs(fs, find_dir(fs, EXT2_ROOT_INO, "etc"),
                  "payload", 0644, input, 0, 0,
                  946684800, 946684800) == 0)
        return 1;
    fclose(input);

    if (finish_fs(fs) != 1) {
        fprintf(stderr, "%s\n", get_genext2fs_error());
        return 1;
    }
    free_fs(fs);
    return 0;
}
