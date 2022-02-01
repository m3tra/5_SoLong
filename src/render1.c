/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:38:32 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 08:39:11 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_bg(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (++y < (app->game.height - 1))
	{
		while (++x < (app->game.width - 1))
			place_img(app, BG, (t_pos){.x = x, .y = y});
		x = 0;
	}
}

void	render_out_walls(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->game.width)
		place_img(app, WALL, (t_pos){. x = i++, .y = 0});
	i = 0;
	while (i < app->game.width)
		place_img(app, WALL, (t_pos){.x = i++, .y = app->game.height - 1});
	i = 1;
	while (i < app->game.height - 1)
	{
		place_img(app, WALL, (t_pos){.x = 0, .y = i});
		place_img(app, WALL, (t_pos){.x = app->game.width - 1, .y = i++});
	}
}

void	render_in_walls(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (++y < (app->game.height - 1))
	{
		while (++x < (app->game.width - 1))
			if (app->game.map[y][x] == WALL)
				place_img(app, WALL, (t_pos){.x = x, .y = y});
		x = 0;
	}
}

void	render_coll(t_app *app)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < app->game.height)
	{
		while (++x < app->game.width)
			if (app->game.map[y][x] == COLL)
				place_img(app, COLL, (t_pos){.x = x, .y = y});
		x = 0;
	}
}

void	render_enemies(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (++y < (app->game.height - 1))
	{
		while (++x < (app->game.width - 1))
			if (app->game.map[y][x] == ENEMY)
				place_img(app, ENEMY, (t_pos){.x = x, .y = y});
		x = 0;
	}
}
