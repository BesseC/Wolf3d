/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:38:37 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/26 12:04:33 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		*ft_strintsplit(char *str, char c)
{
	int			*res;
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (!str || !(res = (int*)malloc(sizeof(int) * MAPSIZE)))
		return (NULL);
	while (j < MAPSIZE)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			j++;
		if (!str[i] ||
				(res[j - 1] = ft_atoi(&(str[i]))) > NB_TILES || res[j - 1] < 0)
			return (NULL);
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	if (str[i])
		return (NULL);
	return (res);
}

int		**ft_intsplit(char **tab)
{
	int		**points;
	int		i;
	int		j;

	i = 0;
	if (!tab)
		return (NULL);
	if (!(points = malloc(sizeof(int*) * MAPSIZE)))
		return (NULL);
	j = 0;
	while (j < MAPSIZE)
	{
		if (!(points[j] = (int*)ft_strintsplit(tab[j], ' ')))
			return (NULL);
		j++;
		ft_memdel((void**)&tab[j - 1]);
	}
	ft_memdel((void**)&tab[j]);
	ft_memdel((void**)&tab);
	return (points);
}

char	**ft_mise_en_tab(char *argv)
{
	char	**buffer;
	int		i;
	int		fd;

	i = 0;
	if ((fd = open(argv, O_RDONLY)) < 0)
		return (NULL);
	if (!(buffer = malloc(sizeof(char *) * (MAPSIZE + 1))))
		return (NULL);
	i = 0;
	while (get_next_line(fd, buffer + i) == 1 && i < MAPSIZE + 1)
		i++;
	if (i != MAPSIZE)
		return (NULL);
	close(fd);
	return (buffer);
}

int		init_env(t_wolf *env, char **argv, int argc)
{
	if (argc != 2)
		ft_quit("Usage : ./Wolf3d map");
	if (!(env->worldmap = ft_intsplit(ft_mise_en_tab(argv[1]))))
		ft_quit("Map non valide");
	if (env->worldmap[1][1])
		ft_quit("Bloc on player position");
	return (0);
}
