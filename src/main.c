#include "so_long.h"

void	err_exit(char *err)
{
	ft_putstr_fd("EXIT: ", 1);
	ft_putstr_fd(err, 1);
	ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int	init(t_app *app)
{
	t_screen	*screen;

	app->mlx = mlx_init();
	if (!app->mlx)
		err_exit("mlx_init FAILED");
	app->screen.win = mlx_new_window(app->mlx, 1344, 768, "so_long");

}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void paint(t_img *img, int x, int y, int color)
{
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			my_mlx_pixel_put(img, j, i, color);
}

void	stop(void *param)
{
	t_app *app;

	app = ((t_app *)param);
	mlx_destroy_window(app->mlx, app->screen.win);
	free(app);
	exit(EXIT_SUCCESS);
}

void	mouse_hook(int button, int x, int y, void *param)
{
	t_app *app;

	app = (t_app *)param;
	// printf("Button: %d\nX: %d\nY: %d\n", button, x, y);
}

void	key_hook(int keycode, void *param)
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
}

void	put_image(t_img *img, int x, int y)
{

}

void	update(t_app *app)
{
	t_img	img;
	int color;
	int x;
	int y;

	x = app->game.player.x;
	y = app->game.player.y;

	img.img = mlx_new_image(app->mlx, 1344, 768);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	app->screen.img = &img;
	// printf("FrameCount: %d\n", app->screen.frame_count);
	if (!app->screen.frame_count)
		color = 0x00FF0000;
	else if (app->screen.frame_count == 1)
		color = 0x0000FF00;
	else if (app->screen.frame_count == 2)
		color = 0x000000FF;
	if (app->screen.frame_count == 2)
		app->screen.frame_count = 0;
	else
		app->screen.frame_count++;
	paint(&img, 64, 64, color);
	mlx_put_image_to_window(app->mlx, app->screen.win, app->screen.img->img, x, y);
	sleep(1);

}

int	main()
{
	t_app	*app;

	app = calloc(1, sizeof(t_app));
	init(app);

	// my_mlx_pixel_put(&img, 5, 5, 0x00FFFFFF);

	mlx_hook(app->screen.win, 17, (1L << 17), stop, app);
	mlx_mouse_hook(app->screen.win, mouse_hook, app);
	mlx_key_hook(app->screen.win, key_hook, app);

	read_map(app, "./map.ber");

	mlx_loop_hook(app->mlx, update, app);
	mlx_loop(app->mlx);

	return (0);
}
