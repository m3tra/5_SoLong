/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:00:44 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 09:30:38 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	scan_line(t_app *app, char *line, int height)
{
	int	i;
	int	exits;

	i = 0;
	exits = 0;
	check_chars(app, line);
	while (i < app->game.width)
	{
		if (line[i] == 'C')
			app->game.colls++;
		if (line[i] == 'P')
		{
			app->game.player.x = i;
			app->game.player.y = height;
		}
		if (line[i] == 'M')
			app->game.en_count++;
		if (line[i] == 'E')
			app->game.exits++;
		i++;
	}
}

void	map_height(t_app *app, const char *file)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd < 4)
		err_exit("Invalid file path @load_map", app);
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (line[0])
			app->game.height++;
		free(line);
		if (!ret)
			break ;
	}
	close(fd);
}

void	load_map(t_app *app, const char *file)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	map_height(app, file);
	fd = open(file, O_RDONLY);
	if (fd < 4)
		err_exit("Invalid file path @load_map", app);
	app->game.map = malloc(sizeof(char *) * app->game.height);
	if (!app->game.map)
		err_exit("Failed malloc of app->game.map", app);
	i = 0;
	while (i < app->game.height)
	{
		ret = get_next_line(fd, &line);
		app->game.map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
}

void	read_map(t_app *app, const char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	load_map(app, file);
	while (i < app->game.height)
	{
		if (i == 0)
			check_h_wall(app, app->game.map[i], 0);
		else if (i == app->game.height - 1)
			check_h_wall(app, app->game.map[i], 1);
		else
		{
			check_sides(app, app->game.map[i]);
			scan_line(app, app->game.map[i], i);
		}
		i++;
	}
	map_check(app);
	if (!app->game.exits)
		err_exit("Missing Exit", app);
	printf("Width: %d\nHeight: %d\n", app->game.width, app->game.height);
	printf("Exits: %d\n", app->game.exits);
	printf("Collectibles: %d\n", app->game.colls);
	printf("File: %s\n", file);
	printf("Starting pos: (x: %d y: %d)\n", app->game.player.x, app->game.player.y);
}
