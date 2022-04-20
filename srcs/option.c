
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/06 15:05:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 15:36:57 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "woody.h"

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    -   -   -   -    -   -   -   s   k   d   h
**    0   0   0   0    0   0   0   0   0   0   0
**
** Lors d'ajout d'option penser a rajouter l'option dans la liste des options
*/


/*
** liste des options
** pour rajouter une option il suffit de recopier le pattern suivant
*/

static int	ft_listing_option(char c, int option)
{
	c == 'h' ? option = option | 1 : 0;
	c == 'd' ? option = option | 2 : 0;
	c == 'k' ? option = option | 4 : 0;
	c == 's' ? option = option | 8 : 0;
	return (option);
}

static char **complexe_option(char c, char d, char **av, t_option *complexe)
{
	if (c == 's') {
		if (!av[1])
			return (usage(c, "must be follow by a section [.text .name]"));
		complexe->section_name = av[1];
	}
	if (c == 'k') {
		if (!av[1])
			return (usage(c, "must be follow by a key [QWDTF+=asdVSFSDFvwER-/]]"));
		if (ft_strlen(av[1]) > MAX_KEY_LEN || ft_strlen(av[1]) < 1)
			return (usage(c, " the given key must be upper 0 and under 255 char"));
		complexe->key = av[1];
	}
	if (c == 's' || c == 'k')
		return (&av[1]);
	return (av);
}

/*
** permet de scruter les options
** aussi bien sur le meme arg que sur plusieur arg
*/

static char	**ft_option(char **av, int *option, t_option *complexe)
{
	int		i;
	char	**rcv;

	while (*av)
	{
		i = 0;
		if ((*av)[0] != '-' || !(*av))
			return (av);
		while ((*av)[++i])
		{
			if (ft_strchr(LIST_OPTION, (*av)[i]) == NULL)
				return (usage((*av)[i], "is not an option"));
			*option = ft_listing_option((*av)[i], *option);
			if (!(rcv = complexe_option((*av)[i], (*av)[i], av, complexe)))
				return (NULL);
			if (av != rcv)
			{
				av = rcv;
				break;	
			}
		}
		av = av ? &av[1] : av;
	}
	return (av);
}

/*
** fonction visible de l'exterieur
** elle permet de recuperer les options via ...
** ...l'adresse d'un int que l'on passe en parametre
** et elle retourne l'argument qui suit les options
*/

char **get_option(char **av, int *option, t_option *complexe)
{
	*option = 0;
	ft_bzero(complexe, sizeof(*complexe));

	if (!(av) || !(*av))
		return (av);
	return (ft_option(av, option, complexe));
}

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    -   -   -   -    -   -   -   s   k   d   h
**    0   0   0   0    0   0   0   0   0   0   0
**
** Lors d'ajout d'option penser a rajouter l'option dans la liste des options
*/