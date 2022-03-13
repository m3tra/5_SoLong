/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 04:49:20 by fporto            #+#    #+#             */
/*   Updated: 2022/03/13 13:38:48 by fporto           ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

//////////////////// HOOKS ////////////////////

int	stop(void *param)
{
	t_app	*app;

	app = ((t_app *)param);
	if (!app->game.steps || app->screen.img->img)
		mlx_destroy_image(app->mlx, app->screen.img->img);
	if (app->screen.img)
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

//////////////////// MAIN ////////////////////

int	main(int argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
	{
		err_exit("Error\nWrong number of parameter.\n", NULL);
		return (1);
	}
	app = ft_calloc(1, sizeof(t_app));
	if (init(app, argv[1]))
		err_exit("init FAILED", app);
	first_frame(app);
	mlx_hook(app->screen.win, 17, (1L << 17), stop, app);
	mlx_key_hook(app->screen.win, key_hook, app);
	mlx_loop_hook(app->mlx, update, app);
	mlx_loop(app->mlx);
	return (0);
}
