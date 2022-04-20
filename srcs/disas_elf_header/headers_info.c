/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:24:46 by max               #+#    #+#             */
/*   Updated: 2022/04/19 10:04:47 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
** int header_info(char *file)
**
** cette fonction a pour but de decompiler un fichier ELF file et d'en retirer
** les headers de program + headers de section
*/

int header_info(char *file)
{
    Elf64_Ehdr  header;
    int         fd;

    if ((fd = open(file, O_RDONLY)) < 0)
        return (1);

    print_header(fd, &header);
    print_pheaders(fd, header);
    print_sheaders(fd, header);
    close(fd);
    return (0);
}