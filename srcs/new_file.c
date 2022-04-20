#include "woody.h"

int writeSection(t_fileData *fileData, t_fileData *oldFileData, int index) {
    static char buff[4000];
    int nb;
    
    lseek(oldFileData->fd, oldFileData->shead[index].sh_offset, SEEK_SET);
    nb = oldFileData->shead[index].sh_size;
    while (nb) {
        if (nb >= 4000) {
            read(oldFileData->fd, buff, 4000);
            write(fileData->fd, buff, 4000);
            nb -= 4000;
        }
        else {
            read(oldFileData->fd, buff, nb);
            write(fileData->fd, buff, nb);
            nb = 0;
        }
    }
}

void writeNothing(int fd, int size) {
    static char buff[4096];

    ft_bzero(buff, size);
    write(fd, buff, size);
}

int encodeSection(t_fileData *fileData, t_fileData *oldFileData, int index) {
    char *data;

    if (!(data = malloc(oldFileData->shead[index].sh_size)))
        return (0);
    lseek(oldFileData->fd, oldFileData->shead[index].sh_offset, SEEK_SET);
    read(oldFileData->fd, data, oldFileData->shead[index].sh_size);
    encrypt(data, oldFileData->shead[index].sh_size, fileData->key.data, fileData->key.size);
    write(fileData->fd, data, oldFileData->shead[index].sh_size);
    free(data);
    return (1);
}

int writeBody(t_fileData *fileData, t_fileData *oldFileData) {
    int n;
    int diff;

    n = 0;
    while (++n < fileData->head.e_shnum) {
        if (!ft_strcmp(&(fileData->ShStrTab[fileData->shead[n].sh_name]), ".bss")
            /*&& !ft_strcmp(&(fileData->ShStrTab[fileData->shead[n + 1].sh_name]), ".comment")
            && fileData->shead[n].sh_size < fileData->shead[n + 1].sh_size*/)          /*.bss n'est pas écrit mème avec une taille > .comment*/
            n++;
        if (!ft_strcmp(&(fileData->ShStrTab[fileData->shead[n].sh_name]), ".text"))
            encodeSection(fileData, oldFileData, n);
        else
            writeSection(fileData, oldFileData, n);
        if (n + 1 < fileData->head.e_shnum){
            diff = fileData->shead[n + 1].sh_offset - (fileData->shead[n].sh_offset + fileData->shead[n].sh_size);
            if (diff > 0) {
                if (!ft_strcmp(&(fileData->ShStrTab[fileData->shead[n + 1].sh_name]), ".init")) {
                    writeNothing(fileData->fd, 16);
                    write(fileData->fd, fileData->modif, fileData->modifSize);
                    writeNothing(fileData->fd, diff - 16 - fileData->modifSize);
                }
                else
                    writeNothing(fileData->fd, diff);
            }
        }
    }
    diff = fileData->head.e_shoff - (fileData->shead[--n].sh_offset + fileData->shead[n].sh_size);
    if (diff > 0)
            writeNothing(fileData->fd, diff);
}

int createFileDataCpy(t_fileData *cpy, t_fileData *fileData) {
    ft_memcpy(cpy,  fileData, sizeof(t_fileData));
    cpy->shead = malloc(fileData->head.e_shentsize * fileData->head.e_shnum);
    ft_memcpy(cpy->shead, fileData->shead, fileData->head.e_shentsize * fileData->head.e_shnum);
}

int createNewFile(t_fileData *fileData) {
    int fd;
    t_fileData oldFileData;

    if ((fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 0755)) < 0)
        return (0);
    createFileDataCpy(&oldFileData, fileData);
    fileData->fd = fd;
    write(fd, &fileData->head, sizeof(fileData->head));
    write(fd, fileData->phead, fileData->head.e_phentsize * fileData->head.e_phnum);
    writeBody(fileData, &oldFileData);
    write(fd, fileData->shead, fileData->head.e_shentsize * fileData->head.e_shnum);
    close(fd);
    free(oldFileData.shead);
    return (1);
}