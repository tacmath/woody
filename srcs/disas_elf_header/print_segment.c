/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:50:55 by max               #+#    #+#             */
/*   Updated: 2022/04/20 08:59:29 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int hexdump_sheader(int fd, t_option *option)
{
    Elf64_Shdr header;
    char *dump;
    char *sectname;

    if (read(fd, &header, sizeof(Elf64_Shdr)) < sizeof(Elf64_Shdr))
        return (1);

    if (!(sectname = getShName(0, header.sh_name, 0, 0)))
    {
        dprintf(1, "\n\033[0;31m!! woody_woodpacker error: Can't find the given section\033[0;37m\n\n");
        usage(0, 0);
    }
    if (!ft_strcmp(option->section_name, sectname))
    {
        dump = malloc(header.sh_size);
        lseek(fd, header.sh_offset, SEEK_SET);
        if (read(fd, dump, header.sh_size) == header.sh_size)
            ft_hexdump(dump, header.sh_size);
        free(dump);
    }
    
}

int print_segment(char *file, t_option *option)
{

    Elf64_Ehdr  header;
    int         fd;
    int         n;
    char        *p;

    if ((fd = open(file, O_RDONLY)) < 0)
        return (1);
        
    if (read(fd, &header, sizeof(header)) < sizeof(Elf64_Ehdr))
        return (1);

    getShName(fd, 0, &header, 1);
    lseek(fd, header.e_shoff, SEEK_SET);
    n = -1;
    while (++n < header.e_shnum)
    {
        hexdump_sheader(fd, option);
        lseek(fd, header.e_shoff + (n + 1) * header.e_shentsize , SEEK_SET);
    }
    return (0);
}
