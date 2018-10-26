/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:12:49 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/24 12:44:35 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	do_dda(t_wolf *wolf)
{
	while (wolf->hit == 0)
	{
		if (wolf->side_dist.x < wolf->side_dist.y)
		{
			wolf->side_dist.x += wolf->delta_dist.x;
			wolf->map.x += wolf->step.x;
			wolf->side = 0;
		}
		else
		{
			wolf->side_dist.y += wolf->delta_dist.y;
			wolf->map.y += wolf->step.y;
			wolf->side = 1;
		}
		if (wolf->worldmap[(int)(wolf->map.x)][(int)(wolf->map.y)] > 0)
			wolf->hit = 1;
	}
}

void	set_step(t_wolf *wolf)
{
	if (wolf->ray_dir.x < 0)
	{
		wolf->step.x = -1;
		wolf->side_dist.x = (wolf->pos.x - wolf->map.x) * wolf->delta_dist.x;
	}
	else
	{
		wolf->step.x = 1;
		wolf->side_dist.x = (wolf->map.x + 1.0 - wolf->pos.x) *
			wolf->delta_dist.x;
	}
	if (wolf->ray_dir.y < 0)
	{
		wolf->step.y = -1;
		wolf->side_dist.y = (wolf->pos.y - wolf->map.y) * wolf->delta_dist.y;
	}
	else
	{
		wolf->step.y = 1;
		wolf->side_dist.y = (wolf->map.y + 1.0 - wolf->pos.y) *
			wolf->delta_dist.y;
	}
}

void	setdda(t_wolf *wolf, int x)
{
	double	w;

	w = WIDTH;
	wolf->camera_x = 2 * x / (double)w - 1;
	wolf->ray_dir.x = wolf->dir.x + wolf->plane.x * wolf->camera_x;
	wolf->ray_dir.y = wolf->dir.y + wolf->plane.y * wolf->camera_x;
	wolf->map.x = (int)(wolf->pos.x);
	wolf->map.y = (int)(wolf->pos.y);
	wolf->delta_dist.x = fabs(1 / wolf->ray_dir.x);
	wolf->delta_dist.y = fabs(1 / wolf->ray_dir.y);
	wolf->hit = 0;
	set_step(wolf);
}

void	dda(t_wolf *wolf, t_env *env)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setdda(wolf, x);
		do_dda(wolf);
		draw(wolf, env, x);
		x++;
	}
	SDL_UpdateWindowSurface(env->window);
	ft_memset(env->surf->pixels, 0xb0,
			(sizeof(int) * env->surf->w * env->surf->h) / 2);
	ft_memset(&(env->surf->pixels[(sizeof(int) * env->surf->w * env->surf->h)
				/ 2]), 0x00, (sizeof(int) * env->surf->w * env->surf->h) / 2);
}
