/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:15:04 by fporto            #+#    #+#             */
/*   Updated: 2022/02/05 04:46:26 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_app *app, int keycode)
{
	if (keycode == MLX_KEY_W)
		app->game.player.y -= 1;
	if (keycode == MLX_KEY_A)
		app->game.player.x -= 1;
	if (keycode == MLX_KEY_S)
		app->game.player.y += 1;
	if (keycode == MLX_KEY_D)
		app->game.player.x += 1;
	app->game.steps++;
	render_out_walls(app);
	render_steps(app);
}

void	can_move(t_app *app, int keycode, int x, int y)
{
	char	**map;

	map = app->game.map;
	if (map[y][x] != WALL)
	{
		if (map[y][x] == EXIT && !app->game.colls)
			stop(app);
		if (map[y][x] == COLL)
		{
			map[y][x] = '0';
			app->game.colls--;
		}
		if (map[y][x] == BG || map[y][x] == PLAYER || map[y][x] == ENEMY)
			move(app, keycode);
	}
}

void	check_move(t_app *app, int keycode)
{
	int		x;
	int		y;

	x = app->game.player.x;
	y = app->game.player.y;
	if (keycode == MLX_KEY_W)
		can_move(app, keycode, x, y - 1);
	if (keycode == MLX_KEY_A)
		can_move(app, keycode, x - 1, y);
	if (keycode == MLX_KEY_S)
		can_move(app, keycode, x, y + 1);
	if (keycode == MLX_KEY_D)
		can_move(app, keycode, x + 1, y);
}
