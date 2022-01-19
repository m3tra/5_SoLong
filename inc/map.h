#ifndef MAP_H
# define MAP_H

# include "so_long.h"

# define SIZE 64

# define FOLDER "../textures/xpm/test"

# define VOID_XPM "grass64.xpm"
# define WALL_XPM "wall64.xpm"
# define EXIT_XPM "exit64.xpm"
# define COLL_XPM "coin64.xpm"
# define ENEM_XPM "enemy64.xpm"
# define PLAY_XPM "player64.xpm"

# define MAP_CHARS "01CEPB"

# define VOID '0'
# define WALL 'W'
# define EXIT 'E'
# define COLL 'C'
# define PLAY 'P'
# define ENEM 'B'

// int		parseMap(t_game *game, const char *map);

// int		checkBorder(char **map);
// void	err_exit(char *err);

#endif
