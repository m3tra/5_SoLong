#include "so_long.h"

static int	parse_map(t_game *game, int fd)
{
	// int		fd;
	int		i;
	int		ret;
	char	*line;

	i = 0;
	// fd = open(map, O_RDONLY);
	ret = 1;
	game->map = ft_calloc(game->height, sizeof(char *));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_strlen(line) > 0)
			game->map[i++] = line;
		else
			free(line);
	}
	// printf("Width: %d\nHeight: %d\n", game->width, game->height);
	// for (int j = 0; i < game->height; i++)
	// {
	// 	printf("%s\n", game->map[j]);
	// }
	close(fd);
	return (ret);
}

int		is_horizontal_wall(char *line)
{
	while (*line)
		if (*line++ != '1')
			return (0);
	return (1);
}

int		check_border(t_app *app, char *line)
{
	while (app->game.height == 1 && *line == '1')
	{
		if (*line != '1')
			err_exit("Map ERROR1");
		*line++;
	}
}

void	read_map(t_app *app, const char *file)
{
	int		fd;
	char	*line;
	int		nLines;
	int		len;

	nLines = 0;
	fd = open(file, O_RDONLY);
	app->game.width = 0;
	app->game.height = 0;
	while (get_next_line(fd, &line) >= 0)
	{
		++nLines;
		while (nLines == 1 && *line == '1')
		{
			if (*line != '1')
				err_exit("Map ERROR1");
			*line++;
		}
		printf("FD: %d\nLine: %s\n", fd, line);
		if (*line == '1')
		{
			app->game.height++;
			len = ft_strlen(line);
			if (*line + len - 1 != '1')
				err_exit("Map ERROR2");
			if (app->game.width && len != app->game.width)
				err_exit("Map ERROR3");
			app->game.width = len;
		}
		else
		{
			printf("%d\n", nLines);
			printf("%s\n", file);
			err_exit("Map ERROR4");
		}
		free(line);
		printf("Width: %d\nHeight: %d\n", app->game.width, app->game.height);
	}
	// parseMap(&app->game, fd);
}
