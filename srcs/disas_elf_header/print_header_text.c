/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:15:25 by max               #+#    #+#             */
/*   Updated: 2022/04/14 03:04:25 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void print_header_text(char *dump, int *size_def, char **info, int size_info, char (*color)[8], int (*pf)(int, int), int end)
{
    int                 offset;
    int                 i;
    char                *value;
    unsigned long long  addr;

    ft_putstr("\033[0;37m\0");
    ft_putstr("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    ft_putstr("┃ Designation                     decimal     ┃         correspondance        ┃                 hexdump                          ┃\n");
    ft_putstr("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");

    offset = 0;
    i = -1;
    while (++i < size_info)
    {
        ft_putstr(color[i]);
        ft_putstr("\033[0;37m┃ ");
        ft_putstr(color[i]);
        ft_putstr(info[i]);
        ft_putnstr(" ", 4);
        addr = 0;
        ft_memcpy(&addr, dump + offset, size_def[i]);
	    value = ft_utoa_base(addr, 10, size_def[i]);
        ft_putnstr(i != 0 || ft_strlen(value) <= 12 ? value : "too long...", 12);
        ft_putstr("\033[0;37m┃ ");
        ft_putstr(color[i]);
		free(value);
        if (pf(i, addr))
        {
            value = ft_utoa_base(addr, 16, size_def[i]);
            ft_putstr("0x");
            ft_putnstr(value, 28);
            free(value);
        }
        ft_putstr("\033[0;37m┃");
        ft_putstr(color[i]);
        ft_linear_hexdump(dump + offset, size_def[i]);
        ft_putnstr("", (((16 - size_def[i]) % 16)) * 3 + (23 - size_def[i]) / 8);
        offset += size_def[i];
        if (i + 1 == size_info && end)
            ft_putstr("\033[0;37m┃\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
        else
             ft_putstr("\033[0;37m┃\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    }
}
