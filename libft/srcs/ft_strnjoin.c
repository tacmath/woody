/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:03:05 by max               #+#    #+#             */
/*   Updated: 2022/04/11 10:03:13 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int s1_len, int s2_len)
{
	char	*str;
	int		l_s1;
	int		l_s2;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strsub((char*)s1, 0, s1_len));
	if (!s1 && s2)
		return (ft_strsub((char*)s2, 0, s2_len));
	str = NULL;
	if ((str = (char *)malloc(sizeof(char) * ((s1_len + s2_len) + 1))) == NULL)
		return (NULL);
	l_s1 = -1;
	while (++l_s1 < s1_len)
		str[l_s1] = s1[l_s1];
	l_s2 = -1;
	while (++l_s2 < s2_len)
		str[l_s1 + l_s2] = s2[l_s2];
	str[l_s1 + l_s2] = '\0';
	return (str);
}