/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_hexdump.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 05:08:24 by max               #+#    #+#             */
/*   Updated: 2022/04/13 09:24:49 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void ft_linear_hexdump(char *dump, int dump_size)
{
	int i;
	char *addr;

	i = -1;
	while (++i < dump_size)
	{
		ft_putstr(" ");
		addr = ft_utoa_base(dump[i], 16, 2);
		ft_putstr(addr);
		free(addr);
        if (i % 8 == 7)
			ft_putchar(' ');
	}
}