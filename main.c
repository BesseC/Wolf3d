/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 12:17:38 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/26 12:04:03 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move(t_wolf *wolf, t_env *env)
{
	if (env->state[SDL_SCANCODE_UP])
	{
		if (wolf->worldmap[(int)(wolf->pos.x + wolf->dir.x * MOVESPEED)]
				[(int)wolf->pos.y] == 0)
			wolf->pos.x += wolf->dir.x * MOVESPEED;
		if (wolf->worldmap[(int)wolf->pos.x]
				[(int)(wolf->pos.y + wolf->dir.y * MOVESPEED)] == 0)
			wolf->pos.y += wolf->dir.y * MOVESPEED;
	}
	if (env->state[SDL_SCANCODE_DOWN])
	{
		if (wolf->worldmap[(int)(wolf->pos.x - wolf->dir.x * MOVESPEED)]
				[(int)wolf->pos.y] == 0)
			wolf->pos.x -= wolf->dir.x * MOVESPEED;
		if (wolf->worldmap[(int)wolf->pos.x]
				[(int)(wolf->pos.y - wolf->dir.y * MOVESPEED)] == 0)
			wolf->pos.y -= wolf->dir.y * MOVESPEED;
	}
}

void	rot(t_wolf *wolf, t_env *env)
{
	if (env->state[SDL_SCANCODE_RIGHT])
	{
		wolf->tmp = wolf->dir.x;
		wolf->dir.x = wolf->dir.x * cos(-ROTSPEED) -
			wolf->dir.y * sin(-ROTSPEED);
		wolf->dir.y = wolf->tmp * sin(-ROTSPEED) +
			wolf->dir.y * cos(-ROTSPEED);
		wolf->tmp = wolf->plane.x;
		wolf->plane.x = wolf->plane.x * cos(-ROTSPEED) -
			wolf->plane.y * sin(-ROTSPEED);
		wolf->plane.y = wolf->tmp * sin(-ROTSPEED) +
			wolf->plane.y * cos(-ROTSPEED);
	}
	if (env->state[SDL_SCANCODE_LEFT])
	{
		wolf->tmp = wolf->dir.x;
		wolf->dir.x = wolf->dir.x * cos(ROTSPEED) - wolf->dir.y * sin(ROTSPEED);
		wolf->dir.y = wolf->tmp * sin(ROTSPEED)
			+ wolf->dir.y * cos(ROTSPEED);
		wolf->tmp = wolf->plane.x;
		wolf->plane.x = wolf->plane.x * cos(ROTSPEED)
			- wolf->plane.y * sin(ROTSPEED);
		wolf->plane.y = wolf->tmp * sin(ROTSPEED)
			+ wolf->plane.y * cos(ROTSPEED);
	}
}

int		main(int argc, char **argv)
{
	t_env		env;
	t_wolf		wolf;
	SDL_Event	e;

	ini_sdl(&env);
	iniwolf(&wolf);
	init_env(&wolf, argv, argc);
	set_map(&wolf);
	while (1)
	{
		dda(&wolf, &env);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
						e.key.keysym.sym == SDLK_ESCAPE))
				exit(1);
			move(&wolf, &env);
			rot(&wolf, &env);
		}
	}
}
