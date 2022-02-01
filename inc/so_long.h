/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:53:00 by fporto            #+#    #+#             */
/*   Updated: 2022/02/01 11:31:49 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "mlx_keys.h"
# include "map.h"

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_screen
{
	void	*win;
	int		width;
	int		height;
	int		frame_count;
	t_img	*img;
}				t_screen;

typedef struct s_entit
{
	int	x;
	int	y;
	int	dir;
	int	dead;
}				t_entit;

typedef struct s_game
{
	int			width;
	int			height;
	int			colls;
	int			exits;
	int			steps;
	char		**map;
	int			en_count;
	t_entit		player;
	t_entit		*enemy;
}				t_game;

typedef struct s_app
{
	void		*mlx;
	t_screen	screen;
	t_game		game;
}				t_app;

void	free_map(t_game *game);
void	err_exit(char *err, t_app *app);
int		stop(void *param);
int		key_hook(int keycode, void *param);

void	scan_line(t_app *app, char *line, int height);
void	map_height(t_app *app, const char *file);
void	load_map(t_app *app, const char *file);
void	read_map(t_app *app, const char *file);

void	render_bg(t_app *app);
void	render_out_walls(t_app *app);
void	render_in_walls(t_app *app);
void	render_coll(t_app *app);
void	render_enemies(t_app *app);
void	render_exit(t_app *app);
void	render_player(t_app *app);
void	render_rest(t_app *app);
int		update(t_app *app);

void	screen_init(t_app *app);
int		init(t_app *app);
void	first_frame(t_app *app);

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
t_img	*import_image(t_app *app, char a, int x, int y);
int		place_img(t_app *app, char tile, t_pos p);

void	check_sides(t_app *app, char *line);
void	check_h_wall(t_app *app, char *line, int bottom);
void	check_width(t_app *app);
void	check_chars(t_app *app, char *line);
void	map_check(t_app *app);

void	move(t_app *app, int keycode);
void	check_move(t_app *app, int keycode);

#endif
