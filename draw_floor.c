/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:09:48 by cbesse            #+#    #+#             */
/*   Updated: 2018/11/19 15:26:30 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	setdraw_floor(t_wolf *wolf)
{
	if (wolf->side == 0 && wolf->ray_dir.x > 0)
	{
		wolf->floor_wall.x = wolf->map.x;
		wolf->floor_wall.y = wolf->map.y + wolf->wallx;
	}
	else if (wolf->side == 0 && wolf->ray_dir.x < 0)
	{
		wolf->floor_wall.x = wolf->map.x + 1.0;
		wolf->floor_wall.y = wolf->map.y + wolf->wallx;
	}
	else if (wolf->side == 1 && wolf->ray_dir.y > 0)
	{
		wolf->floor_wall.x = wolf->map.x + wolf->wallx;
		wolf->floor_wall.y = wolf->map.y;
	}
	else
	{
		wolf->floor_wall.x = wolf->map.x + wolf->wallx;
		wolf->floor_wall.y = wolf->map.y + 1.0;
	}
	wolf->dist_wall = wolf->perp_wall_dist;
	wolf->dist_player = 0.0;
	if (wolf->draw_end < 0)
		wolf->draw_end = HEIGHT;
}

void	draw_floor(t_wolf *wolf, t_env *env, int x)
{
	int color;
	int y;

	y = wolf->draw_end;
	setdraw_floor(wolf);
	while (y < HEIGHT)
	{
		wolf->current_dist = HEIGHT / (2.0 * y - HEIGHT);
		wolf->weight = (wolf->current_dist - wolf->dist_player) /
			(wolf->dist_wall - wolf->dist_player);
		wolf->current_floor.x = wolf->weight * wolf->floor_wall.x +
			(1.0 - wolf->weight) * wolf->pos.x;
		wolf->current_floor.y = wolf->weight * wolf->floor_wall.y +
			(1.0 - wolf->weight) * wolf->pos.y;
		wolf->floortex_x = (int)(wolf->current_floor.x * env->text->img_w) %
			env->text->img_w;
		wolf->floortex_y = (int)(wolf->current_floor.y * env->text->img_h) %
			env->text->img_h;
		color = uv_wall(env->text[6], wolf->floortex_x, wolf->floortex_y);
		set_pixel(x, y, color, env->surf);
		color = uv_wall(env->text[7], wolf->floortex_x, wolf->floortex_y);
		set_pixel(x, HEIGHT - y, color, env->surf);
		y++;
	}
}
