/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:54:20 by cbesse            #+#    #+#             */
/*   Updated: 2018/11/19 15:26:44 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft/includes/libft.h"
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define MOVESPEED 0.25
# define ROTSPEED 0.1
# define NB_TILES 15
# define WIDTH 1024
# define HEIGHT 1024
# define NB_TEXT 6
# define MAPSIZE 64
# include <SDL.h>
# include <SDL_image.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_text
{
	int			*map;
	int			img_w;
	int			img_h;
}				t_text;

typedef struct	s_env
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Event	e;
	Uint8		*state;
	t_text		*text;
}				t_env;

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_wolf
{
	t_vec2		dir;
	t_vec2		floor_wall;
	t_vec2		current_floor;
	t_vec2		map;
	t_vec2		ray_dir;
	t_vec2		side_dist;
	t_vec2		plane;
	t_vec2		pos;
	t_vec2		delta_dist;
	double		perp_wall_dist;
	t_vec2		step;
	int			hit;
	int			side;
	double		camera_x;
	double		tmp;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	int			color;
	double		weight;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			tex_x;
	int			tex_y;
	int			floortex_x;
	int			floortex_y;
	int			**worldmap;
	double		wallx;
}				t_wolf;

void			iniwolf(t_wolf *wolf);
void			ini_sdl(t_env *env);
void			setdda(t_wolf *wolf, int x);
void			set_step(t_wolf *wolf);
void			draw(t_wolf *wolf, t_env *env, int x);
void			dda(t_wolf *wolf, t_env *env);
t_text			*get_texture(void);
int				init_env(t_wolf *env, char **argv, int argc);
void			set_map(t_wolf *wolf);
void			ft_quit(char *str);
int				uv_wall(t_text text, int x, int y);
void			set_pixel(int x, int y, int color, SDL_Surface *s);
void			draw_floor(t_wolf *wolf, t_env *env, int x);
#endif
