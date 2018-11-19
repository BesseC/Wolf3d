/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:40:01 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/26 12:00:43 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		uv_wall(t_text text, int x, int y)
{
	return (text.map[x * text.img_w + y]);
}

int		get_color(t_wolf *wolf, t_env *env, int x, int y)
{
	t_text color;

	if (!wolf->side && wolf->step.x == 1)
	{
		color = env->text[wolf->worldmap[(int)wolf->map.x][(int)wolf->map.y]
			% (NB_TEXT)];
		return (uv_wall(color, x, y));
	}
	if (!wolf->side && wolf->step.x == -1)
	{
		color = env->text[(wolf->worldmap[(int)wolf->map.x][(int)wolf->map.y]
				+ 1) % (NB_TEXT)];
		return (uv_wall(color, x, y));
	}
	if (wolf->side && wolf->step.y == 1)
	{
		color = env->text[(wolf->worldmap[(int)wolf->map.x][(int)wolf->map.y]
				+ 2) % (NB_TEXT)];
		return (uv_wall(color, x, y));
	}
	color = env->text[(wolf->worldmap[(int)wolf->map.x][(int)wolf->map.y] + 3)
		% (NB_TEXT)];
	return (uv_wall(color, x, y));
}

void	set_pixel(int x, int y, int color, SDL_Surface *s)
{
	int *pixels;

	pixels = s->pixels;
	if (x < s->w && y < s->h && x >= 0 && y >= 0)
		pixels[x + y * s->w] = color;
	s->pixels = pixels;
}

void	draw_wall(t_wolf *wolf, t_env *env, int x)
{
	int		color;
	int		y;
	int		d;

	y = wolf->draw_start;
	if (wolf->side == 0)
		wolf->wallx = wolf->pos.y + wolf->perp_wall_dist * wolf->ray_dir.y;
	else
		wolf->wallx = wolf->pos.x + wolf->perp_wall_dist * wolf->ray_dir.x;
	wolf->wallx -= floor((wolf->wallx));
	wolf->tex_x = (int)(wolf->wallx * (double)(env->text->img_w));
	if (wolf->side == 0 && wolf->ray_dir.x > 0)
		wolf->tex_x = env->text->img_w - wolf->tex_x - 1;
	if (wolf->side == 1 && wolf->ray_dir.y < 0)
		wolf->tex_x = env->text->img_w - wolf->tex_x - 1;
	while (y < wolf->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + wolf->line_height * 128;
		wolf->tex_y = ((d * env->text->img_h) / wolf->line_height) / 256;
		color = get_color(wolf, env, wolf->tex_y, wolf->tex_x);
		set_pixel(x, y, color, env->surf);
		y++;
	}
	draw_floor(wolf, env, x);
}

void	draw(t_wolf *wolf, t_env *env, int x)
{
	if (wolf->side == 0)
		wolf->perp_wall_dist = (wolf->map.x - wolf->pos.x + (1 - wolf->step.x)
				/ 2) / wolf->ray_dir.x;
	else
		wolf->perp_wall_dist = (wolf->map.y - wolf->pos.y + (1 - wolf->step.y)
				/ 2) / wolf->ray_dir.y;
	wolf->line_height = (int)(HEIGHT / wolf->perp_wall_dist);
	wolf->draw_start = -wolf->line_height / 2 + HEIGHT / 2;
	wolf->draw_start < 0 ? wolf->draw_start = 0 : wolf->draw_start;
	wolf->draw_end = wolf->line_height / 2 + HEIGHT / 2;
	wolf->draw_end >= HEIGHT ? wolf->draw_end = HEIGHT : wolf->draw_end;
	draw_wall(wolf, env, x);
}
