/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 04:49:20 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 13:34:57 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//////////////////// FREE ////////////////////

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (i < game->height)
			free(game->map[i++]);
		free(game->map);
	}
}

//////////////////// ERROR ////////////////////

void	err_exit(char *err, t_app *app)
{
	(void)app;
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(err, 1);
	ft_putchar_fd('\n', 1);
	// free_map(&app->game);
	exit(EXIT_FAILURE);
}

//////////////////// HOOKS ////////////////////

int	stop(void *param)
{
	t_app	*app;

	app = ((t_app *)param);
	if (!app->game.steps)
		free(app->screen.img);
	free_map(&app->game);
	mlx_destroy_window(app->mlx, app->screen.win);
	free(app);
	exit(EXIT_SUCCESS);
	return (1);
}

int	key_hook(int keycode, void *param)
{
	t_app	*app;
	char	**map;

	app = (t_app *)param;
	map = app->game.map;
	if (keycode == MLX_KEY_ESC)
		stop(app);
	check_move(app, keycode);
	if (map[app->game.player.y][app->game.player.x] == ENEMY)
		stop(app);
	return (1);
}

// int	key_hook(int keycode, void *param)
// {
// 	t_app	*app;
// 	int		x;
// 	int		y;

// 	app = (t_app *)param;
// 	x = app->game.player.x;
// 	y = app->game.player.y;
// 	if (keycode == MLX_KEY_ESC)
// 		stop(app);
// 	if (keycode == MLX_KEY_W)
// 		if (app->game.map[y - 1][x] != WALL)
// 			app->game.player.y -= 1;
// 	if (keycode == MLX_KEY_A)
// 		if (app->game.map[y][x - 1] != WALL)
// 			app->game.player.x -= 1;
// 	if (keycode == MLX_KEY_S)
// 		if (app->game.map[y + 1][x] != WALL)
// 			app->game.player.y += 1;
// 	if (keycode == MLX_KEY_D)
// 		if (app->game.map[y][x + 1] != WALL)
// 			app->game.player.x += 1;
// 	app->game.steps++;
// 	if (app->game.map[app->game.player.y][app->game.player.x] == ENEMY)
// 		stop(app);
// 	return (1);
// }

//////////////////// MAIN ////////////////////

int	main(void)
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	if (init(app))
		err_exit("init FAILED", app);
	first_frame(app);
	mlx_hook(app->screen.win, 17, (1L << 17), stop, app);
	mlx_key_hook(app->screen.win, key_hook, app);
	mlx_loop_hook(app->mlx, update, app);
	mlx_loop(app->mlx);
	return (0);
}
