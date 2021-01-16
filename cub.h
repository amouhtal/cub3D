/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:52 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/10 10:07:28 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define FOV 60.
# define ANGLE_TO_RAD 0.01745329251
# define NUMRAYS WIN_WIDTH
# define TEXTURE_DEM 64
# define UP_KEY 126
# define DOWN_KEY 125
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define A_KEY 0
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "./pars/cube3d.h"
# include <stdio.h>

typedef	struct	s_wall
{
	double wall_hit_x;
	double wall_hit_y;
	double distance;
	double vert_wall_hit_x;
	double vert_wall_hit_y;
	double horz_wall_hit_x;
	double horz_wall_hit_y;
	double next_horiz_hit_x;
	double next_horiz_hit_y;
	double next_vert_hit_x;
	double next_vert_hit_y;
}				t_wall;

typedef struct	s_ray
{
	t_wall	wall;
	double	angle;
	int		there_is_wall_horz;
	int		there_is_wall_vert;
	int		isfaycingup;
	int		isfaycingdown;
	int		isfaycingright;
	int		isfaycingleft;
	int		was_hit_vert;
	float	x_intercept;
	float	y_intercept;
	float	xstep;
	float	ystep;
	float	x_inter;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	next_horiz_hit_x;
	double	next_horiz_hit_y;
	double	next_vert_hit_x;
	double	next_vert_hit_y;
	int		*dist_tab;
}				t_ray;

typedef struct	s_player
{
	double player_x;
	double player_y;
	double new_player_x;
	double new_player_y;
	double move_up_down;
	double move_up;
	double move_down;
	double move_left;
	double move_right;
	double move_right_left;
	double rotate_left;
	double rotate_right;
	double angle;
	double walkdirection;
	double right_left;
	double turndirection;
}				t_player;

typedef struct	s_sprit
{
	double	sprite_x;
	double	sprite_y;
	double	ag;
	double	sprite_angle;
	double	dist_to_player;
	double	hight;
	int		color;
	double	x_star_wind;
}				t_sprit;

typedef struct	s_texture
{
	void	*texture_n;
	void	*texture_s;
	void	*texture_w;
	void	*texture_e;
	void	*initial_txt;
	int		*texture_n_data;
	int		*texture_s_data;
	int		*texture_w_data;
	int		*texture_o_data;
	int		*initial_txt_data;
}				t_texture;

typedef struct	s_cube
{
	int			cpt;
	int			x;
	int			y;
	int			end;
	int			start;
	void		*ptr_win;
	void		*ptr_mlx;
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	void		*xpm_file_img;
	int			tex_w;
	int			tex_h;
	int			*tex;
	int			*txt_wall_file;
	int			*txt_wall_data;
	void		*txt_sprit_file;
	int			*txt_sprit_data;
	int			color;
	int			first;
	int			sprit_w;
	int			sprit_h;
	double		dest_project_plane;
	int			tile_size;
	int			nbrofsprites;
	t_player	player;
	t_sprit		*sprits;
	t_ray		ray;
	t_texture	texture;
	t_mlx		m;
}				t_cube;

int				abs(int n);
void			intialise(t_cube *cube, int ret);
double			distance_btw_point(double x1, double y1, double x2, double y2);
double			normalize_angle(double angle);
void			is_facing_what(t_cube *cube);
char			hass_walll(int x, int y, t_cube *cube);
void			draw_sprite(t_cube *cube, int count);
void			find_sprits(t_cube *cube);
int				count_sprit(t_cube *cube);
void			ft_sort_sprite(t_cube *cube, double spx, double spy, int count);
void			find_player(t_cube *cube);
int				keypress(int keycode, t_cube *cube);
int				keyrelease(int keycode, t_cube *cube);
int				cast_all_rays(t_cube *cube);
void			write_to_file(char *str, char *val, int end);
void			file_empty();
int				ft_close_window(t_cube *cube, int check_free);
void			cast_ray(t_cube *cube);
int				hass_wall_ray(int x, int y, char m, t_cube *cube);
void			ft_draw_sky(t_cube *cube, int start, int x_start);
void			fill_image(t_cube *cube, int x_start,
int wall_strip_heigh, int hit);
void			ft_detect_h_hit(t_cube *cube, double xstep, double ystep);
void			found_horz_intercept(t_cube *cube, double xstep, double ystep);
void			check_texture(t_cube *cube);
void			found_vert_intercept(t_cube *cube, double xstep, double ystep);
int				save_bmp(t_cube *cube);
void			ft_draw_sky(t_cube *cube, int wall_strip_heigh, int x_start);
void			ft_draw_floor(t_cube *cube, int x_start, int wall_strip_heigh);
void			ft_draw_wall(t_cube *cube, int x_start,
int wall_strip_heigh, int hit);
void			bmp(t_cube *cube, char *av);
int				cast_all_rays2(t_cube *cube);
void			count_sprites(t_cube *cube, int i, int j);
void			update_player(t_cube *cube);
void			wall_hit(t_cube *cube, double vert_distance,
double horz_distance);
int				sprite_visible(t_cube *cube, int sprite_indice);
void			found_sprite_angle(t_cube *cube, int i);
#endif
