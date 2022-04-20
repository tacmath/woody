/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:42:55 by max               #+#    #+#             */
/*   Updated: 2022/04/13 09:19:56 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_print_color(int idx, int *color_size)
{
    char color[][8] = {"\033[0;31m\0", "\033[0;32m\0", "\033[0;33m\0", "\033[0;34m\0", "\033[0;35m\0", "\033[0;36m\0", "\e[0;91m\0", "\e[0;92m", "\e[0;93m", "\e[0;94m", "\e[0;95m", "\e[0;96m", "\e[0;97m", "\e[1;91m", "\e[1;92m", "\e[1;93m", "\e[1;94m", "\e[1;95m", "\e[1;96m", "\e[1;97m"};
    int i;
    int local_idx;

    i = -1;
    local_idx = 0;
    while (local_idx <= idx)
        local_idx += color_size[++i];
    ft_putstr(color[i]);
}


static void hexdumpAsciiColor(char *dump, int offset, char dump_size, int end_dump, int *color_size)
{
	int		i;
	char	c;

	i = -1;
	ft_putstr("   ");
	while (++i < (15 - dump_size))
		ft_putstr("   ");
	i = -1;
	while (++i <= dump_size)
	{
        ft_print_color(offset + i, color_size);
		c = dump[offset + i];
		if (i % 16 == 0)
			ft_putchar('|');
		ft_putchar(ft_isprint(c) ? c : '.');
		if (i % 16 == 15)
			ft_putchar('|');
	}
	ft_putnchar(' ', 16 - i);
	if (end_dump && (i % 16) != 0)
		ft_putchar('|');
}


void ft_hexdump_color(char *dump, int dump_size, int *color_size)
{
	int i;
	char *addr;

    color_size = (void*)color_size;
	addr = ft_utoa_base((unsigned long long)0, 16, 8);
	ft_putstr("\033[0;37m\0");
    ft_putstr(addr);
	free(addr);
	i = -1;
	while (++i < dump_size)
	{
        ft_print_color(i, color_size);
		ft_putstr(" ");
		addr = ft_utoa_base(dump[i], 16, 2);
		ft_putstr(addr);
		free(addr);
        if (i % 8 == 7 && (i % 16) != 15)
			ft_putchar(' ');
		if ((i % 16 == 15 && i != 0) || (dump_size == i + 1))
		{
			hexdumpAsciiColor(dump, i - (i % 16), (i % 16), (dump_size == i + 1), color_size);
			ft_putchar('\n');
			if (dump_size != i + 1) {
                ft_putstr("\033[0;37m\0");
				addr = ft_utoa_base((unsigned long long)i + 1, 16, 8);
				ft_putstr(addr);
				free(addr);
			}
		}
        
	}
    ft_putstr("\033[0;37m\0");
}