/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:00:44 by fporto            #+#    #+#             */
/*   Updated: 2022/01/27 23:10:41 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_horizontal_wall(char *line)
{
	while (*line)
		if (*line++ != '1')
			return (0);
	return (1);
}

void	check_sides(t_app *app, char *line)
{
	char	*str;

	if (line[0] != '1')
	{
		str = ft_strjoin("No left wall at line ", ft_itoa(app->game.height));
		err_exit(str, free);
	}
	if (line[app->game.width - 1] != '1')
	{
		str = ft_strjoin("Bad width at line ", ft_itoa(app->game.height));
		err_exit(str, free);
	}
}

void	check_h_line(t_app *app, char *line, int bottom)
{
	if (!is_horizontal_wall(line))
	{
		if (bottom)
			err_exit("Bad bottom wall", NULL);
		else
			err_exit("Bad top wall", NULL);
	}
	if (!app->game.width)
		app->game.width = ft_strlen(line);
}

int	read_line(t_app *app, char *line)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (i < app->game.width)
	{
		if (line[i] == 'C')
			app->game.coll_left++;
		if (line[i] == 'P')
		{
			app->game.player.x = i;
			app->game.player.y = app->game.height - 1;
		}
		if (line[i] == 'M')
			app->game.en_count++;
		if (line[i] == 'E')
			e++;
		i++;
	}
	if (!e)
		return (0);
	return (1);
}

void	map_check(t_app *app)
{
	if (!app->game.coll_left)
		err_exit("Missing Collectible", NULL);
	if (!app->game.player.x || !app->game.player.y)
		err_exit("Missing Player", NULL);
}

int	has_exit(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
		if (line[i++] == 'E')
			return (1);
	return (0);
}

void	read_map(t_app *app, const char *file)
{
	int		fd;
	char	*line;
	int		exits;
	int		ret;

	exits = 0;
	fd = open(file, O_RDONLY);
	if (fd < 4)
		err_exit("Invalid file path @read_map", NULL);
	while (1)
	{
		ret = get_next_line(fd, &line);
		++app->game.height;
		if (app->game.height == 1)
			check_h_line(app, line, 0);
		check_sides(app, line);
		read_line(app, line);
		if (!exits)
			exits += has_exit(line);
		if (is_horizontal_wall(line) && app->game.height > 1)
			check_h_line(app, line, 1);

		printf("Line: %s\nHeight: %d\n", line, app->game.height);

		free(line);
		if (ret == 0)
			break;
	}
	// printf("Line: %s", line);
	close(fd);

	printf("Width: %d\n\n", app->game.width);

	printf("Exits: %d\n", exits);
	if (!exits)
		err_exit("Missing Exit", NULL);

	printf("FD: %d\nFile: %s\n", fd, file);
	printf("x: %d\ty: %d\n", app->game.player.x, app->game.player.y);
}
