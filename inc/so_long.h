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
	char	*title;
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
	int			coll_left;
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

void	err_exit(char *err, void (*del)(void *));
void	read_map(t_app *app, const char *file);

#endif
