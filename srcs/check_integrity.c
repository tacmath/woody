/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_integrity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 07:19:39 by max               #+#    #+#             */
/*   Updated: 2022/04/20 10:54:52 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static int check_pload_header(Elf64_Ehdr  header, int fd, int file_len)
{
    Elf64_Phdr  pheader;
    int         i;
    int         npload;

    lseek(fd, header.e_phoff, SEEK_SET);
    i = 0;
    npload = 0;
    while (i < header.e_phnum)
    {
        if (read(fd, &pheader, sizeof(pheader)) < sizeof(pheader))
            return (1);
        i++;
        if (pheader.p_offset >= file_len) 
        {
            dprintf(1, "\n\033[0;31m!! woody_woodpacker error: PHEADER error (bad offset)\033[0;37m\n\n");
            usage(0, 0);
            return (1);
        }

        if (pheader.p_offset + pheader.p_filesz >= file_len) 
        {
            dprintf(1, "\n\033[0;31m!! woody_woodpacker error: PHEADER error (bad size)\033[0;37m\n\n");
            usage(0, 0);
            return (1);
        }
        if (pheader.p_type == 0x01)
        {
            // unsupported bourrage
            if (npload == 0 && pheader.p_filesz % 4096 > 4096 - 450)
            {
                dprintf(1, "\n\033[0;31m!! woody_woodpacker error: insufficient memory space (bad filler)\033[0;37m\n\n");
                usage(0, 0);
                return (1); 
            }
            npload += 1;
        }
    }

    if (npload < 4) 
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: bad pheader count\033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }
    return (0);
}

int check_sheader(Elf64_Ehdr  header, int fd, int file_len)
{
    Elf64_Shdr  sheader;
    Elf64_Shdr  sh_strtab;
    int         i;
    int         npload;


    i = 0;
    npload = 0;
    sh_strtab = getShStrTab(fd , header);
    lseek(fd, header.e_shoff, SEEK_SET);
    while (i < header.e_phnum)
    {
        if (read(fd, &sheader, sizeof(sheader)) < sizeof(sheader))
            return (1);
        i++;

        if (sheader.sh_offset > file_len)
        {
            dprintf(1, "\n\033[0;31m!! woody_woodpacker error: SHEADER error (bad offset)\033[0;37m\n\n");
            usage(0, 0);
            return (1);      
        }

        if (sheader.sh_offset + sheader.sh_size >= file_len) 
        {
            dprintf(1, "\n\033[0;31m!! woody_woodpacker error: SHEADER error (bad size)\033[0;37m\n\n");
            usage(0, 0);
            return (1);
        }

        if (sheader.sh_name > sh_strtab.sh_size)
        {
            dprintf(1, "\n\033[0;31m!! woody_woodpacker error: SHEADER error (bad shstrtab index)\033[0;37m\n\n");
            usage(0, 0);
            return (1);
        }
    }
    return (0);
}

int check_elf_header(Elf64_Ehdr  header, int fd)
{
    t_magic     *magic;
    int         file_len;
    char        buff[100];
    int         ret;

    magic = (t_magic *)header.e_ident;
    if (ft_memcmp(ELFMAG, &magic->magic_number, SELFMAG))
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: only ELF64 file is supported (MAGIC ERROR) \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    file_len = 0;
    lseek(fd, 0, SEEK_SET);
    while ((ret = read(fd, buff, sizeof(buff))))
        file_len += ret;

    if (header.e_shoff + (header.e_shnum) * header.e_shentsize != file_len)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: file integrity error \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    if (header.e_entry >= file_len || header.e_entry <= 0)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: wrong entrypoint \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    if (header.e_shnum < 20)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: ELF_HEADER invalide sheader number \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    if (header.e_phnum < 7)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: ELF_HEADER invalide pheader number \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    if (header.e_shstrndx >= header.e_shnum)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: ELF_HEADER invalide shstrndx \033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }


    if (header.e_phoff >= file_len || header.e_phoff < header.e_ehsize || header.e_shoff >= file_len || header.e_shoff <= header.e_phoff + header.e_phnum * header.e_phentsize)
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: ELF_HEADER error (bad offset)\033[0;37m\n\n");
        usage(0, 0);
        return (1);
    }

    if (check_pload_header(header, fd, file_len))
        return (1);

    if (check_sheader(header, fd, file_len))
        return (1);

    return (0);
}

int check_integrity(char *name , char *exec_name)
{
    int         fd;
    Elf64_Ehdr  header;


    if (!ft_strcmp("woody", exec_name))
    {
        dprintf(1, "\n\033[0;31m!! %s error: %s can't override himself!!\033[0;37m\n\n", exec_name, name);
        usage(0, 0);
        return (1); 
    }

    if ((fd = open(name, O_RDONLY)) < 0)
    {
        dprintf(1, "\n\033[0;31m!! %s error: %s is not a valid file (OPEN ERROR)!!\033[0;37m\n\n", exec_name, name);
        usage(0, 0);
        return (1);
    }

    if (read(fd, &header, sizeof(header)) < sizeof(header))
    {
        dprintf(1, "\n\033[0;31m!! %s error: %s is not a valid file (READ ERROR)!!\033[0;37m\n\n", exec_name, name);
        close (fd);
        usage(0, 0);
        return (1);
    }

    if (check_elf_header(header, fd))
    {
        close(fd);
        return (1);
    }
    close(fd);
    if ((fd = open("woody", O_RDWR | O_CREAT, 0755)) < 0)
    {
        dprintf(1, "\n\033[0;31m!! %s error: can't create file woody (RIGHT ERROR)!!\033[0;37m\n\n",exec_name, name);
        usage(0, 0);
        return (1);
    }
    close(fd);
    return (0);
}
