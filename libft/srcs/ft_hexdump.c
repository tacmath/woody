/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:42:55 by max               #+#    #+#             */
/*   Updated: 2022/04/15 11:36:58 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void hexdumpAscii(char *dump, int offset, char dump_size, int end_dump)
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

void ft_hexdump(char *dump, int dump_size)
{
	int i;
	char *addr;

	addr = ft_utoa_base((unsigned long long)0, 16, 8);
	ft_putstr(addr);
	free(addr);
	i = -1;
	while (++i < dump_size)
	{
		ft_putstr(" ");
		addr = ft_utoa_base(dump[i], 16, 2);
		ft_putstr(addr);
		free(addr);
		if ((i % 8 == 7 && (i % 16) != 15) || (dump_size == i + 1 && (i % 8 < 7)))
			ft_putchar(' ');

		if ((i % 16 == 15 && i != 0) || (dump_size == i + 1))
		{
			hexdumpAscii(dump, i - (i % 16), (i % 16), (dump_size == i + 1));
			ft_putchar('\n');
			if (dump_size != i + 1) {
				addr = ft_utoa_base((unsigned long long)i + 1, 16, 8);
				ft_putstr(addr);
				free(addr);
			}
		}
	}
}