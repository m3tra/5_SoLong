/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:37:29 by fporto            #+#    #+#             */
/*   Updated: 2022/03/14 15:07:28 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_sides(t_app *app, char *line)
{
	if (line[0] != WALL || line[app->game.width - 1] != WALL)
		err_exit("Bad vertical wall", app);
}

void	check_h_wall(t_app *app, char *line, int bottom)
{
	int	i;
	int	wall;

	i = 0;
	wall = 1;
	while (line[i])
		if (line[i++] != WALL)
			wall = 0;
	if (!wall)
	{
		if (bottom)
			err_exit("Bad bottom wall", app);
		else
			err_exit("Bad top wall", app);
	}
	if (!app->game.width)
		app->game.width = ft_strlen(line);
}

void	check_width(t_app *app)
{
	int		i;
	size_t	width;

	i = 0;
	width = ft_strlen(app->game.map[i]);
	while (i < app->game.height)
		if (width != ft_strlen(app->game.map[i++]))
			err_exit("Map not rectangular", app);
}

void	check_chars(t_app *app, char *line)
{
	int		i;
	int		k;
	int		bad;
	char	*chars;

	i = 0;
	chars = MAP_CHARS;
	while (line[i])
	{
		bad = 1;
		k = 0;
		while (chars[k])
			if (line[i] == chars[k++])
				bad = 0;
		i++;
		if (bad)
			err_exit("Bad tile in map", app);
	}
}

void	map_check(t_app *app)
{
	if (!app->game.colls)
		err_exit("Missing Collectible", app);
	if (!app->game.player.x || !app->game.player.y)
		err_exit("Missing Player", app);
	check_width(app);
}
