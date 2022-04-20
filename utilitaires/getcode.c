#include "woody.h"

int getFileData(t_fileData *fileData) {
    read(fileData->fd, &fileData->head, sizeof(fileData->head));
    fileData->shead = malloc(fileData->head.e_shentsize * fileData->head.e_shnum);
    lseek(fileData->fd, fileData->head.e_shoff, SEEK_SET);
    read(fileData->fd, fileData->shead, fileData->head.e_shentsize * fileData->head.e_shnum);
    getShStrTabData(fileData);
    return (1);
}

void printCode(char *code, int size) {
    int n;

    printf("0x%02x", code[0] & 0xff);
    n = 0;
    while (++n < size)
        printf(", 0x%02x", code[n] & 0xff);
}

int getSymTab(t_fileData *fileData, char **function, int nb) {
    Elf64_Shdr sym;
    Elf64_Shdr str;
    Elf64_Sym *data;
    char    *strtab;
    char    *buf;
    int n;
    int m;
    int min;
    int i;

    sym = getShHead(fileData, ".symtab");
    data = malloc(sym.sh_size);
    lseek(fileData->fd, sym.sh_offset, SEEK_SET);
    read(fileData->fd, data, sym.sh_size);    
    str = getShHead(fileData, ".strtab");
    strtab = malloc(str.sh_size);
    lseek(fileData->fd, str.sh_offset, SEEK_SET);
    read(fileData->fd, strtab, str.sh_size);    
    m = -1;
    while(++m < nb) {
        n = -1;
        while(++n < sym.sh_size / sizeof(Elf64_Sym)) {
            if (data[n].st_name && !ft_strcmp(&strtab[data[n].st_name], function[m])) {
                
                lseek(fileData->fd, data[n].st_value, SEEK_SET);
                if (data[n].st_size == 0) {
                    i = -1;
                    min = -1;
                    while (++i < sym.sh_size / sizeof(Elf64_Sym))
                        if (i != n && data[i].st_value > data[n].st_value && (min == -1 || (data[i].st_value < min)))
                            min = data[i].st_value;
                    data[n].st_size = min - data[n].st_value;
                }
                buf = malloc(data[n].st_size);
                read(fileData->fd, buf, data[n].st_size);
                printCode(buf, data[n].st_size);
                if (m + 1 < nb)
                    printf(", ");
                free(buf);
            }
        }
    }
    free(strtab);
    free(data);
    return (1);
}

void freeStruct(t_fileData *fileData) {
    free(fileData->shead);
    free(fileData->ShStrTab);
}

int main(int ac, char **av)
{
    t_fileData fileData;
	
    if (ac < 3)
        return (1);
    ft_bzero(&fileData, sizeof(t_fileData));
    if ((fileData.fd = open(av[1], O_RDONLY)) < 0)
        return (1);
    getFileData(&fileData);
    getSymTab(&fileData, &av[2], ac - 2);
    close(fileData.fd);
    freeStruct(&fileData);
    return (0);
}
