/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:24 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/03 10:59:44 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_detect_h_hit(t_cube *cube, double xstep, double ystep)
{
	while (cube->ray.next_horiz_hit_x >= 0 && cube->ray.next_horiz_hit_x
	< (cube->tile_size * cube->m.s_map.coloms) && cube->ray.next_horiz_hit_y
	>= 0 && cube->ray.next_horiz_hit_y < (cube->tile_size * cube->m.s_map.rows))
	{
		if (hass_wall_ray(cube->ray.next_horiz_hit_x,
		(cube->ray.next_horiz_hit_y - cube->ray.isfaycingup), '1', cube))
		{
			cube->ray.there_is_wall_horz = 1;
			cube->ray.horz_wall_hit_x = cube->ray.next_horiz_hit_x;
			cube->ray.horz_wall_hit_y = cube->ray.next_horiz_hit_y;
			break ;
		}
		cube->ray.next_horiz_hit_x += xstep;
		cube->ray.next_horiz_hit_y += ystep;
	}
}

void	found_horz_intercept(t_cube *cube, double xstep, double ystep)
{
	cube->ray.y_intercept = floor(cube->player.player_y
	/ cube->tile_size) * cube->tile_size;
	cube->ray.there_is_wall_horz = 0;
	if (cube->ray.isfaycingdown == 1)
		cube->ray.y_intercept += cube->tile_size;
	cube->ray.x_intercept = cube->player.player_x +
	(cube->ray.y_intercept - cube->player.player_y) / tan(cube->ray.angle);
	ystep = cube->tile_size;
	if (cube->ray.isfaycingup == 1)
		ystep *= -1;
	xstep = cube->tile_size / tan(cube->ray.angle);
	if (cube->ray.isfaycingleft == 1 && xstep > 0)
		xstep *= -1;
	else if (cube->ray.isfaycingright == 1 && xstep < 0)
		xstep *= -1;
	cube->ray.next_horiz_hit_x = cube->ray.x_intercept;
	cube->ray.next_horiz_hit_y = cube->ray.y_intercept;
	ft_detect_h_hit(cube, xstep, ystep);
}

void	ft_detect_vhit(t_cube *cube, double xstep, double ystep)
{
	while (cube->ray.next_vert_hit_x >= 0 && cube->ray.next_vert_hit_x
	< (cube->tile_size * cube->m.s_map.coloms) && cube->ray.next_vert_hit_y
	>= 0 && cube->ray.next_vert_hit_y < (cube->tile_size * cube->m.s_map.rows))
	{
		if (hass_wall_ray((cube->ray.next_vert_hit_x - cube->ray.isfaycingleft),
		cube->ray.next_vert_hit_y, '1', cube))
		{
			cube->ray.there_is_wall_vert = 1;
			cube->ray.vert_wall_hit_x = cube->ray.next_vert_hit_x;
			cube->ray.vert_wall_hit_y = cube->ray.next_vert_hit_y;
			break ;
		}
		else
		{
			cube->ray.next_vert_hit_x += xstep;
			cube->ray.next_vert_hit_y += ystep;
		}
	}
}

void	found_vert_intercept(t_cube *cube, double xstep, double ystep)
{
	cube->ray.there_is_wall_vert = 0;
	cube->ray.x_intercept = floor(cube->player.player_x
	/ cube->tile_size) * cube->tile_size;
	if (cube->ray.isfaycingright == 1)
		cube->ray.x_intercept += cube->tile_size;
	cube->ray.y_intercept = cube->player.player_y +\
	((cube->ray.x_intercept - cube->player.player_x) * tan(cube->ray.angle));
	xstep = cube->tile_size;
	if (cube->ray.isfaycingleft == 1)
		xstep *= -1;
	ystep = cube->tile_size * tan(cube->ray.angle);
	if (cube->ray.isfaycingup == 1 && ystep > 0)
		ystep *= -1;
	else if (cube->ray.isfaycingdown == 1 && ystep < 0)
		ystep *= -1;
	cube->ray.next_vert_hit_y = cube->ray.y_intercept;
	cube->ray.next_vert_hit_x = cube->ray.x_intercept;
	ft_detect_vhit(cube, xstep, ystep);
}

void	cast_ray(t_cube *cube)
{
	double horz_distance;
	double vert_distance;

	vert_distance = 0;
	horz_distance = 0;
	cube->ray.angle = normalize_angle(cube->ray.angle);
	is_facing_what(cube);
	found_horz_intercept(cube, 0, 0);
	found_vert_intercept(cube, 0, 0);
	if (cube->ray.there_is_wall_horz == 1)
		horz_distance = distance_btw_point(cube->player.player_x,
		cube->player.player_y, cube->ray.horz_wall_hit_x,
		cube->ray.horz_wall_hit_y);
	else
		horz_distance = __INT32_MAX__;
	if (cube->ray.there_is_wall_vert == 1)
		vert_distance = distance_btw_point(cube->player.player_x,
		cube->player.player_y, cube->ray.vert_wall_hit_x,
		cube->ray.vert_wall_hit_y);
	else
		vert_distance = __INT32_MAX__;
	wall_hit(cube, vert_distance, horz_distance);
}
