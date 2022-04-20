/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:14:11 by matheme           #+#    #+#             */
/*   Updated: 2022/04/11 09:57:20 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (NULL);
	while (i < len && ((unsigned char*)b)[i] != (unsigned char)c)
		i++;
	if (i == len)
		return (NULL);
	return (&(((unsigned char*)b)[i]));
}
