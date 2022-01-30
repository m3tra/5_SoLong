/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 05:26:09 by fporto            #+#    #+#             */
/*   Updated: 2022/01/28 02:55:23 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	err_exit(char *err, void (*del)(void *))
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(err, 1);
	ft_putchar_fd('\n', 1);
	if (del)
		del(err);
	exit(EXIT_FAILURE);
}

int	init(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		err_exit("mlx_init FAILED", NULL);
	app->screen.win = mlx_new_window(app->mlx, 1344, 768, "so_long");
	return (1);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void	paint(t_img *img, int x, int y, int color)
{
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			my_mlx_pixel_put(img, j, i, color);
}

int	stop(void *param)
{
	t_app *app;

	app = ((t_app *)param);
	mlx_destroy_window(app->mlx, app->screen.win);
	free(app);
	exit(EXIT_SUCCESS);
	return (1);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_app *app;
	(void)x;
	(void)y;
	(void)button;

	app = (t_app *)param;
	// printf("Button: %d\nX: %d\nY: %d\n", button, x, y);
	return (1);
}

int	key_hook(int keycode, void *param)
{
	t_app *app;

	app = (t_app *)param;
	// printf("Keycode: %d\n", keycode);
	if (keycode == MLX_KEY_ESC)
		stop(app);
	if (keycode == MLX_KEY_W)
		app->game.player.y -= 64;
	if (keycode == MLX_KEY_A)
		app->game.player.x -= 64;
	if (keycode == MLX_KEY_S)
		app->game.player.y += 64;
	if (keycode == MLX_KEY_D)
		app->game.player.x += 64;
	return (1);
}

void	*import_image(t_app *app, char a, int x, int y)
{
	app->screen.img = ft_calloc(1, sizeof(app->screen.img));
	if (a == BG)
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXBG, &x, &y);
	else if (a == WALL)
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXWALL, &x, &y);
	else if (a == COLL)
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXMIGUEL, &x, &y);
	else if (a == EXIT)
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXEXIT, &x, &y);
	else if (a == PLAYER)
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXPLAYER, &x, &y);
	else
		app->screen.img->img = mlx_xpm_file_to_image(app->mlx, TEXPHILL, &x, &y);
	if (!app->screen.img->img)
		err_exit("Failed to intake image", NULL);
	return (app->screen.img);
}

int	place_img(t_app *app, char tile, t_pos p)
{
	t_img	*img;
	int		i;
	int		j;

	printf("Test\n");
	img = import_image(app, tile, SIZE, SIZE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
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
	return (mlx_destroy_image(app->mlx, img->img) || 1);
}

void	put_img_to_win(t_app *app, int x, int y)
{
	void	*win;
	void	*img;

	win = app->screen.win;
	img = app->screen.img->img;
	mlx_put_image_to_window(app->mlx, win, img, x, y);
}

void	put_h_wall(t_app *app, int y)
{
	int	i;

	i = 0;
	while (i < app->game.width)
	{
		put_img_to_win(app, i * SIZE, y * SIZE);
		i++;
	}
}

void	put_outerwalls(t_app *app)
{
	int	i;
	int	j;

	j = 0;
	app->screen.img = ft_calloc(1, sizeof(app->screen.img));
	app->screen.img->img = mlx_new_image(app->mlx, SIZE, SIZE);
	app->screen.img = import_image(app, WALL, SIZE, SIZE);
	put_h_wall(app, j);
	while(++j < app->game.height - 1)
	{
		i = 0;
		while (i < app->game.width)
		{
			if (i == 0 || i == app->game.width - 1)
				put_img_to_win(app, i * SIZE, j * SIZE);
			i++;
		}
	}
	put_h_wall(app, j);
	free(app->screen.img->img);
	free(app->screen.img);
}

void	first_frame(t_app *app)
{
	int	fd;
	char	*line;
	int	ret;
	int	i;
	int	j;

	fd = open(MAP, O_RDONLY);
	if (fd < 4)
		err_exit("Invalid file path @first_frame", NULL);
	i = 1;
	j = 1;
	ret = get_next_line(fd, &line);
	// while (j < app->game.height - 1)
	while (j < 2)
	{
		ret = get_next_line(fd, &line);
		while (i < app->game.width - 1)
		{
			// if (!(line[i] == BG || line[i] == WALL))
			// {
			// 	import_image(app, BG, SIZE, SIZE);
			// 	put_img_to_win(app, i * SIZE, j * SIZE);
			// 	free(app->screen.img->img);
			// }
			// import_image(app, line[i], SIZE, SIZE);
			// put_img_to_win(app, i * SIZE, j * SIZE);
			// free(app->screen.img->img);
			printf("line[i]: %c\n", line[i]);
			if (!place_img(app, line[i], (t_pos){i, j}))
				err_exit("Bad return @place_img", NULL);
			i++;
		}
		j++;
	}
}

int	update(t_app *app)
{
	// t_img	img;
	(void)app;
	int	color;
	int	x;
	int	y;

	x = 0;
	y = 0;

	color = 0;
	// img.img = mlx_new_image(app->mlx, 1344, 768);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	// app->screen.img = &img;

	// printf("FrameCount: %d\n", app->screen.frame_count);

	// img = import_image(app, "coll", 64, 64);
	// free(img.img);
	// paint(&img, 64, 64, color);
	// put_img_to_win(app->mlx, app->screen.win, app->screen.img->img, x, y);

	sleep(1/2);
	return (1);
}

// int	ft_free(t_app *app)
// {
// 	free(app->screen.img);
// }

int	main()
{
	t_app	*app;

	app = ft_calloc(1, sizeof(t_app));
	init(app);

	read_map(app, MAP);

	// my_mlx_pixel_put(&img, 5, 5, 0x00FFFFFF);

	mlx_hook(app->screen.win, 17, (1L << 17), stop, app);
	mlx_mouse_hook(app->screen.win, mouse_hook, app);
	mlx_key_hook(app->screen.win, key_hook, app);

	put_outerwalls(app);
	first_frame(app);

	mlx_loop_hook(app->mlx, update, app);
	mlx_loop(app->mlx);

	return (0);
}
