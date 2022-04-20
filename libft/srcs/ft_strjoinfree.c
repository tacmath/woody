/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:00:12 by max               #+#    #+#             */
/*   Updated: 2022/04/11 10:05:37 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_free(char **s1, char *s2)
{
	char *ret;

	if (!(ret = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1))))
	{
		ft_strdel(s1);
		return ;
	}
	ret[0] = '\0';
	ret = ft_strcat(ret, *s1);
	ret = ft_strcat(ret, (char *)s2);
	ft_strdel(s1);
	ft_strdel(&s2);
	*s1 = ret;
}