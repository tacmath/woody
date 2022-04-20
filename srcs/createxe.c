#include "woody.h"

int getFileData(t_fileData *fileData) {
    read(fileData->fd, &fileData->head, sizeof(fileData->head));
    fileData->shead = malloc(fileData->head.e_shentsize * fileData->head.e_shnum);
    fileData->phead = malloc(fileData->head.e_phentsize * fileData->head.e_phnum);
    read(fileData->fd, fileData->phead, fileData->head.e_phentsize * fileData->head.e_phnum);
    lseek(fileData->fd, fileData->head.e_shoff, SEEK_SET);
    read(fileData->fd, fileData->shead, fileData->head.e_shentsize * fileData->head.e_shnum);
    getShStrTabData(fileData);
    return (1);
}

void freeStruct(t_fileData *fileData) {
    free(fileData->shead);
    free(fileData->phead);
    free(fileData->ShStrTab);
    free(fileData->modif);
    free(fileData->key.data);
}

void addModif(t_fileData *fileData) {
    int n;
    int m;
    int entry;
    Elf64_Shdr shead;
    
    entry = fileData->head.e_entry;
    shead = getShHead(fileData, ".rela.plt");
    if (!shead.sh_name) 
        shead = getShHead(fileData, ".rela.dyn");
    fileData->head.e_entry = shead.sh_offset + shead.sh_size + 16;
    virus(fileData, entry - fileData->head.e_entry);
    n = -1;
    m = 0;
    while (++n < fileData->head.e_phnum){
        if (fileData->phead[n].p_type == 1) {
            if (++m == 2) {
                fileData->phead[n].p_flags = 7;
                break ;
            }
            else {
                fileData->phead[n].p_flags = 5;
                fileData->phead[n].p_filesz += 16 + fileData->modifSize;
                fileData->phead[n].p_memsz += 16 + fileData->modifSize;
            }
        }
    } 
}

int getKey(t_fileData *fileData, t_option option) {
    char *base64;

    if (option.key) {
        fileData->key.size = ft_strlen(option.key);
        fileData->key.data = ft_strdup(option.key);
        ft_putstr("Key = ");
        ft_putendl(option.key);
    }
    else {
        fileData->key.size = 255;
        if (!(fileData->key.data = malloc(fileData->key.size)))
            return(0);
        ft_random(fileData->key.data, fileData->key.size);
         base64 = base64_encode(fileData->key.data, fileData->key.size);
        ft_putstr("Key = ");
        ft_putendl(base64);
        free(base64);
    }
    return (1);
}

int createexe(char *file, t_option option) {
    t_fileData fileData;

    ft_bzero(&fileData, sizeof(t_fileData));
    if ((fileData.fd = open(file, O_RDONLY)) < 0)
        return (1);
    getFileData(&fileData);
    getKey(&fileData, option);
    addModif(&fileData);
    createNewFile(&fileData);
    close(fileData.fd);
    freeStruct(&fileData);
    return (0);
}
