#include <err.h>
#include <fcntl.h>
#include <gelf.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <elf.h>

unsigned long sections[2][4];
int i = 0, j = 0;

int main(int argc, char **argv) {
    int i, fd, k;
    Elf *e;
    char *id, bytes[5];
    size_t n;
    GElf_Phdr phdr;

    FILE  *fd2 = fopen("a.out", "rb");
    FILE  *fd3 = fopen("ptload.txt", "w");

    if (fd2 == NULL || fd3 == NULL){
        return 1;
    }

    if (argc != 2)
        errx(EX_USAGE, " usage: %s file - name ", argv[0]);

    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EX_SOFTWARE, " ELF library initialization failed: %s ", elf_errmsg(-1));

    if ((fd = open(argv[1], O_RDONLY, 0)) < 0)
        err(EX_NOINPUT, " open \"%s \" failed ", argv[1]);

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EX_SOFTWARE, " elf_begin () failed: %s . ", elf_errmsg(-1));

    if (elf_kind(e) != ELF_K_ELF)
        errx(EX_DATAERR, " \"%s \" is not an ELF object . ", argv[1]);

    if (elf_getphdrnum(e, &n) != 0)
        errx(EX_DATAERR, " elf_getphdrnum() failed: %s. ", elf_errmsg(-1));

    if(fseek(fd2, 0x18, SEEK_SET)){
        return 1;
    }
    unsigned int entry[0];

    fread(entry, 1, 4, fd2);

    fprintf(fd3, "%u \n", entry[0]);

    for (k = 0; k < n; k++) {
        if (gelf_getphdr(e, k, &phdr) != &phdr)
            errx(EX_SOFTWARE, " getphdr() failed: %s . ",
                 elf_errmsg(-1));

        if (phdr.p_type == 0x1) {

            sections[j][0] = phdr.p_offset;
            sections[j][1] = phdr.p_vaddr;
            sections[j][2] = phdr.p_filesz;
            sections[j][3] = phdr.p_memsz;
            j++;

            unsigned int buffer[phdr.p_filesz/4];
            for(i = 0; i < phdr.p_filesz/4; i++){
                buffer[i] = 0;
            }

            if(fseek(fd2, phdr.p_offset, SEEK_SET)){
                return 1;
            }

            fread(buffer, 1, phdr.p_filesz, fd2);

            for(i = 0; i < phdr.p_filesz/4; i++){
                fprintf(fd3, "%ld %u \n", phdr.p_vaddr + i*4, buffer[i]);
            }
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++)
            printf("0x%jx ", sections[i][j]);
        printf("\n");
    }
    fclose(fd2);
    fclose(fd3);
    (void) elf_end(e);
    (void) close(fd);
    exit(EX_OK);
}
