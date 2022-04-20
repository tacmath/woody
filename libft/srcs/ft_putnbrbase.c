/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:08:44 by max               #+#    #+#             */
/*   Updated: 2022/04/11 10:05:25 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putnbrbase(long long nb, int bx) {
    static char base[] = "0123456789abcdef\0";


	if (nb / bx > 0) {
		ft_putnbrbase(nb / bx, bx);
	}
	ft_putchar(base[nb % bx]);
}