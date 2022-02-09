/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 08:52:58 by fporto            #+#    #+#             */
/*   Updated: 2022/02/05 04:45:53 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "so_long.h"

# define SIZE 64

// # define FOLDER "../textures/xpm/test"

// # define VOID_XPM "grass64.xpm"
// # define WALL_XPM "wall64.xpm"
// # define EXIT_XPM "exit64.xpm"
// # define COLL_XPM "coin64.xpm"
// # define ENEM_XPM "enemy64.xpm"
// # define PLAY_XPM "player64.xpm"

# define MAP_CHARS "01ECPB"

# define MAP "./map.ber"

# define BG '0'
# define WALL '1'
# define EXIT 'E'
# define COLL 'C'
# define PLAYER 'P'
# define ENEMY 'B'

// DEFAULT VERSION

// # define TEXCOLL0 "./textures/xpm/test/coin.xpm"
// # define TEXCOLL1 "./textures/xpm/test/coin.xpm"
// # define TEXCOLL2 "./textures/xpm/test/coin.xpm"
// # define TEXCOLL3 "./textures/xpm/test/coin.xpm"
// # define TEXENEMY0 "./textures/xpm/test/enemy.xpm"
// # define TEXENEMY1 "./textures/xpm/test/enemy.xpm"
// # define TEXEXIT "./textures/xpm/test/exit.xpm"
// # define TEXBG "./textures/xpm/test/grass.xpm"
// # define TEXPLAYER "./textures/xpm/test/mario.xpm"
// # define TEXWALL "./textures/xpm/test/wall.xpm"

// MEME VERSION

# define TEXCOLL0 "./textures/xpm/miguel64_0.xpm"
# define TEXCOLL1 "./textures/xpm/miguel64_1.xpm"
# define TEXCOLL2 "./textures/xpm/miguel64_2.xpm"
# define TEXCOLL3 "./textures/xpm/miguel64_3.xpm"
# define TEXENEMY0 "./textures/xpm/phill64_0.xpm"
# define TEXENEMY1 "./textures/xpm/phill64_1.xpm"
# define TEXEXIT "./textures/xpm/trapdoor64.xpm"
# define TEXBG "./textures/xpm/grass64.xpm"
# define TEXPLAYER "./textures/xpm/lilbroom.xpm"
# define TEXWALL "./textures/xpm/wall.xpm"

#endif
