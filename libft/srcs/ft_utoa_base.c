/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:05:06 by max               #+#    #+#             */
/*   Updated: 2022/04/11 09:59:04 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned long long nb, int bx, int champ)
{
	static char base[17] = "0123456789abcdef\0";
	char		*str;

	if ((nb / bx > 0 && champ > 1) || champ > 1) {
		str = ft_utoa_base(nb / bx, bx, champ - 1);
		ft_strjoin_free(&str, ft_strsub(&base[nb % bx],0 , 1));
		return (str);
	}
	return (ft_strsub(&base[nb % bx],0 , 1));
}
