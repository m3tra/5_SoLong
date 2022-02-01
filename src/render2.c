/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:40:26 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 08:46:28 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_exit(t_app *app)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < app->game.height)
	{
		while (++x < app->game.width)
			if (app->game.map[y][x] == EXIT)
				place_img(app, EXIT, (t_pos){.x = x, .y = y});
		x = 0;
	}
}

void	render_player(t_app *app)
{
	static int	ff = 1;
	static int	x = 0;
	static int	y = 0;

	if (ff)
	{
		ff = 0;
		x = app->game.player.x;
		y = app->game.player.y;
	}
	if (x != app->game.player.x || y != app->game.player.y)
	{
		place_img(app, BG, (t_pos){x, y});
		x = app->game.player.x;
		y = app->game.player.y;
	}
	place_img(app, PLAYER, (t_pos){x, y});
}

void	render_rest(t_app *app)
{
	render_player(app);
	mlx_put_image_to_window(app->mlx, app->screen.win, app->screen.img->img, \
		0, 0);
}

//////////////////// LOGIC ////////////////////

int	update(t_app *app)
{
	int	color;
	int	x;
	int	y;

	x = 0;
	y = 0;
	color = 0;
	render_rest(app);
	return (1);
}
