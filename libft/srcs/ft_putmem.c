/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 09:51:40 by matheme           #+#    #+#             */
/*   Updated: 2022/04/11 08:43:17 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static	void	ft_putmem2(unsigned long long adr)
{
	char base[] = "0123456789abcdef\0";

	if (adr / 16 > 0)
		ft_putmem2(adr / 16);
	ft_putchar(base[adr % 16]);
}

void			ft_putmem(const void *adresse)
{
	unsigned long long adr;

	ft_putstr("0x");
	adr = (unsigned long long)adresse;
	ft_putmem2(adr);
}
