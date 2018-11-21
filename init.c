/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:41:05 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/26 12:20:16 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_quit(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	set_map(t_wolf *wolf)
{
	int i;

	i = 0;
	while (i < MAPSIZE)
		if (wolf->worldmap[0][i++] == 0)
			wolf->worldmap[0][i - 1] = 1;
	i = 0;
	while (i < MAPSIZE)
		if (wolf->worldmap[MAPSIZE - 1][i++] == 0)
			wolf->worldmap[MAPSIZE - 1][i - 1] = 1;
	i = 0;
	while (i < MAPSIZE)
		if (wolf->worldmap[i++][0] == 0)
			wolf->worldmap[i - 1][0] = 1;
	i = 0;
	while (i < MAPSIZE)
		if (wolf->worldmap[i++][MAPSIZE - 1] == 0)
			wolf->worldmap[i - 1][MAPSIZE - 1] = 1;
}

void	ini_sdl(t_env *env)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(env->text = get_texture()))
	{
		ft_putendl("fail");
		exit(1);
	}
	env->window = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_INPUT_GRABBED);
	env->surf = SDL_GetWindowSurface(env->window);
	ft_memset(env->surf->pixels, 0, WIDTH * HEIGHT * 4);
	env->state = (Uint8*)SDL_GetKeyboardState(NULL);
}

void	iniwolf(t_wolf *wolf)
{
	wolf->pos.x = 1.5;
	wolf->pos.y = 1.5;
	wolf->dir.x = 1;
	wolf->dir.y = 0;
	wolf->plane.x = 0;
	wolf->plane.y = -0.66;
}
