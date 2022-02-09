/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:44:05 by fporto            #+#    #+#             */
/*   Updated: 2022/02/05 18:11:17 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	frame(t_app *app)
{
	static int	frame = 1;

	if (app->screen.frame_count % 37 == 0)
	{
		frame++;
		app->screen.frame_count++;
	}
	if (frame == 5)
		frame = 1;
	return (frame);
}

t_img	*import_image(t_app *app, char tile, int x, int y)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(*img));
	if (tile == BG)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXBG, &x, &y);
	else if (tile == WALL)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXWALL, &x, &y);
	else if (tile == COLL && frame(app) == 1)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXCOLL0, &x, &y);
	else if (tile == COLL && frame(app) == 2)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXCOLL1, &x, &y);
	else if (tile == COLL && frame(app) == 3)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXCOLL2, &x, &y);
	else if (tile == COLL && frame(app) == 4)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXCOLL3, &x, &y);
	else if (tile == EXIT)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXEXIT, &x, &y);
	else if (tile == PLAYER)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXPLAYER, &x, &y);
	else if (tile == ENEMY && (frame(app) % 2 == 0))
		img->img = mlx_xpm_file_to_image(app->mlx, TEXENEMY0, &x, &y);
	else if (tile == ENEMY && (frame(app) % 2 != 0))
		img->img = mlx_xpm_file_to_image(app->mlx, TEXENEMY1, &x, &y);
	return (img);
}

int	place_img(t_app *app, char tile, t_pos p)
{
	t_img	*img;
	int		i;
	int		j;

	img = import_image(app, tile, SIZE, SIZE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, \
		&img->endian);
	i = -1;
	while (++i < SIZE)
	{
		j = -1;
		while (++j < SIZE)
			if ((*(int *)(img->addr + (i * img->line_len + j * (img->bpp / 8)))
				& 0xff000000) != 0xff000000)
				my_mlx_pixel_put(app->screen.img, p.x * SIZE + j,
					p.y * SIZE + i, *(int *)(img->addr + (i * img->line_len + j
							* (img->bpp / 8))));
	}
	mlx_destroy_image(app->mlx, img->img);
	free(img);
	return (1);
}
