/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:08 by max               #+#    #+#             */
/*   Updated: 2022/04/20 04:15:14 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** Elf64_Shdr getShStrTab(int fd, Elf64_Ehdr header)
**
** permet de recuperer la section header shstrtab d'un ELF file
*/

Elf64_Shdr getShStrTab(int fd, Elf64_Ehdr header) {
    Elf64_Shdr sheader;

    ft_bzero(&sheader, sizeof(Elf64_Shdr));
    lseek(fd, header.e_shoff + header.e_shstrndx * header.e_shentsize, SEEK_SET);
    read(fd, &sheader, sizeof(Elf64_Shdr));
    return (sheader);
}

/*
** int getShStrTabData(t_fileData *fileData)
**
** permet de recuperer les datas correspondant a la table shstrtab
*/

int getShStrTabData(t_fileData *fileData) {
    lseek(fileData->fd, fileData->shead[fileData->head.e_shstrndx].sh_offset, SEEK_SET);
    if (!(fileData->ShStrTab = malloc(fileData->shead[fileData->head.e_shstrndx].sh_size)))
        return (0);
    read(fileData->fd, fileData->ShStrTab, fileData->shead[fileData->head.e_shstrndx].sh_size);
    return (1);
}

/*
** Elf64_Shdr getShHead(t_fileData *fileData, char *name)
**
** permet de recuperer le section header a partir de son nom
** si il n'existe par renvoie un Elf64_Shdr header vide
*/

Elf64_Shdr getShHead(t_fileData *fileData, char *name) {
    int n;
    Elf64_Shdr shead;

    ft_bzero(&shead, sizeof(shead));
    n = -1;
    while (++n < fileData->head.e_shnum && ft_memcmp(&fileData->ShStrTab[fileData->shead[n].sh_name], name, ft_strlen(name)))
        ;
    if (!ft_memcmp(&fileData->ShStrTab[fileData->shead[n].sh_name], name, ft_strlen(name)))
        shead = fileData->shead[n];
    return(shead);
}

/*
** char *GetShName(t_fileData *fileData, int index)
**
** permet de recuperer une section header en fonction
** de son index dans la table shstrtab
*/

char *GetShName(t_fileData *fileData, int index) {
    return (ft_strdup(&fileData->ShStrTab[index]));
}


/*
** char *getShName(int fd, int index, Elf64_Ehdr *header, int mode)
**
** permet de recuperer une section header en fonction
** de son index dans la table shstrtab
*/

char *getShName(int fd, int index, Elf64_Ehdr *header, int mode) {
    static char *data = 0;
    Elf64_Shdr shStrTab;

    if (mode == 1) {
        shStrTab = getShStrTab(fd, *header);
        lseek(fd, shStrTab.sh_offset, SEEK_SET);
        data = malloc(shStrTab.sh_size);
        read(fd, data, shStrTab.sh_size);
        return (0);
    }
    if (mode == 2) {
        free(data);
        return (0);
    }
    if (data)
        return (ft_strdup(&data[index]));
    return (0);
}