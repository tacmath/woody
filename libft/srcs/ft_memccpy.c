/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:14:17 by matheme           #+#    #+#             */
/*   Updated: 2022/04/11 09:56:52 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (NULL);
	while (((unsigned char*)src)[i] != (unsigned char)c && i < len)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	if (i == len)
		return (NULL);
	((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
	return (&(((unsigned char*)dest)[i + 1]));
}
