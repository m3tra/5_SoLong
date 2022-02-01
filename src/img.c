/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:44:05 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 08:45:21 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_img	*import_image(t_app *app, char a, int x, int y)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(*img));
	if (a == BG)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXBG, &x, &y);
	else if (a == WALL)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXWALL, &x, &y);
	else if (a == COLL)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXMIGUEL, &x, &y);
	else if (a == EXIT)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXEXIT, &x, &y);
	else if (a == PLAYER)
		img->img = mlx_xpm_file_to_image(app->mlx, TEXPLAYER, &x, &y);
	else
		img->img = mlx_xpm_file_to_image(app->mlx, TEXPHILL, &x, &y);
	if (!img)
		err_exit("Failed to intake image", app);
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
