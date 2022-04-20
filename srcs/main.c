/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:56:36 by max               #+#    #+#             */
/*   Updated: 2022/04/20 08:15:32 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*
 ** void *usage(char c, char *reason)
 **
 ** le but de cette fonction est d'afficher le usage du programme woody woodpacker
 ** char c 'l'option defectueuse'
 ** char *reason la raison de ce default
*/

void *usage(char c, char *reason)
{
    c ? dprintf(1, "\n\033[0;31m!! woody_woodpacker error: %c %s !!\033[0;37m\n\n", c, reason) : 0;
    dprintf(1, "./woody_woodpacker [-k 'my key'] [-s 'section'] [-dh] ELF64_file\n");
    dprintf(1, " - h  usage\n");
    dprintf(1, " - d  disas a ELF file to show different header values\n");
    dprintf(1, " - s  disas the specified section\n");
    dprintf(1, " - k  take the given key to encrypt\n");
    return (NULL);
}

/*
 ** void Entry point du project woody_woodpacker
 **
 ** le but de cette fonction est de parser tous les argument afin d'en
 ** recuperer les options et le fichier a corrompre
*/

int main(int ac, char **av)
{
    char        *exec_name;
    int         option;
    t_option    opt;

    exec_name = ft_strrchr(*av, '/');
    exec_name++;
    if (ac < 2) return (usage(0, 0) == NULL);
    if (!(av = get_option(&av[1], &option, &opt))) return (1);
    if (H) return (usage(0, 0) == NULL);
    if (!*av) return (usage(' ', " must be follow by a file") == NULL);
    if (D) return (header_info(*av));
    if (check_integrity(*av, exec_name)) return (1);
    if (S) return (print_segment(*av, &opt));
    return (createexe(*av, opt));
}
