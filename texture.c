/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:32:31 by cbesse            #+#    #+#             */
/*   Updated: 2018/10/26 12:22:02 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32			getpixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER != SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void			cpy_px_map(t_text *texture, SDL_Surface *img)
{
	int			x;
	int			y;

	x = 0;
	while (x < img->w)
	{
		y = 0;
		while (y < img->h)
		{
			texture->map[x + y * img->w] = getpixel(img, x, y);
			y++;
		}
		x++;
	}
}

t_text			get_texture_datas(char *path)
{
	SDL_Surface	*img;
	t_text		texture;

	img = NULL;
	if (!(img = IMG_Load(path)))
	{
		ft_putendl("image load failed");
		exit(1);
	}
	else
	{
		texture.img_w = img->w;
		texture.img_h = img->h;
		if (!(texture.map = malloc(sizeof(int) * (img->w * img->h))))
			exit(1);
		SDL_LockSurface(img);
		cpy_px_map(&texture, img);
		SDL_UnlockSurface(img);
		SDL_FreeSurface(img);
	}
	return (texture);
}

t_text			*get_texture(void)
{
	static t_text textures[NB_TEXT + 2];

	textures[0] = get_texture_datas("./textures/cells02.jpg");
	textures[1] = get_texture_datas("./textures/images-2.jpeg");
	textures[2] =
		get_texture_datas("./textures/GoldGlass.jpg");
	textures[3] = get_texture_datas("./textures/images.jpeg");
	textures[4] = get_texture_datas("./textures/images2.jpg");
	textures[5] = get_texture_datas("./textures/Vert.jpg");
	textures[6] = get_texture_datas("./textures/woodfloor.jpg");
	textures[7] = get_texture_datas("./textures/images copy.jpeg");
	return (textures);
}
