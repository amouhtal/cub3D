/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:33 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/08 13:52:43 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_close_window(t_cube *cube, int check_free)
{
	if (check_free != -2)
	{
		if (cube->m.south)
			free(cube->m.south);
		if (cube->m.west)
			free(cube->m.west);
		if (cube->m.east)
			free(cube->m.east);
		if (cube->m.north)
			free(cube->m.north);
		if (cube->m.s_path)
			free(cube->m.s_path);
		if (cube->sprits)
			free(cube->sprits);
		if (cube->ray.dist_tab)
			free(cube->ray.dist_tab);
	}
	exit(0);
}

int		check_walls(int x, int y, t_cube *cube)
{
	int	dist;
	int	ret;

	dist = 4;
	ret = 0;
	if (hass_walll(x - dist, y - dist, cube) == '1'
	|| hass_walll(x - dist, y - dist, cube) == '2')
		ret = 1;
	if (hass_walll(x + dist, y - dist, cube) == '1'
	|| hass_walll(x + dist, y - dist, cube) == '2')
		ret = 1;
	if (hass_walll(x - dist, y + dist, cube) == '1'
	|| hass_walll(x - dist, y + dist, cube) == '2')
		ret = 1;
	if (hass_walll(x + dist, y + dist, cube) == '1'
	|| hass_walll(x + dist, y + dist, cube) == '2')
		ret = 1;
	return (ret);
}

void	update_player(t_cube *cube)
{
	double movestep;
	double movestep2;

	movestep = (cube->player.move_up_down * 2);
	cube->player.angle += (0.03 * cube->player.rotate_right);
	movestep2 = cube->player.move_right_left * 2;
	cube->player.new_player_x = cube->player.player_x
	+ cos(cube->player.angle) * movestep;
	cube->player.new_player_y = cube->player.player_y
	+ sin(cube->player.angle) * movestep;
	cube->player.new_player_x += cos(cube->player.angle
	- (90 * ANGLE_TO_RAD)) * movestep2;
	cube->player.new_player_y += sin(cube->player.angle
	- (90 * ANGLE_TO_RAD)) * movestep2;
	if (check_walls(cube->player.new_player_x, cube->player.player_y,
	cube) == 0)
		cube->player.player_x = cube->player.new_player_x;
	if (check_walls(cube->player.player_x, cube->player.new_player_y,
	cube) == 0)
		cube->player.player_y = cube->player.new_player_y;
}

int		keypress(int keycode, t_cube *cube)
{
	if (keycode == 53)
		ft_close_window(cube, 0);
	if (keycode == W_KEY)
		cube->player.move_up_down = 1;
	if (keycode == S_KEY)
		cube->player.move_up_down = -1;
	if (keycode == D_KEY)
		cube->player.move_right_left = -1;
	if (keycode == A_KEY)
		cube->player.move_right_left = 1;
	if (keycode == RIGHT_KEY)
		cube->player.rotate_right = 1;
	if (keycode == LEFT_KEY)
		cube->player.rotate_right = -1;
	return (0);
}

int		keyrelease(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->player.move_up_down = 0;
	if (keycode == S_KEY)
		cube->player.move_up_down = 0;
	if (keycode == D_KEY)
		cube->player.move_right_left = 0;
	if (keycode == A_KEY)
		cube->player.move_right_left = 0;
	if (keycode == RIGHT_KEY)
		cube->player.rotate_right = 0;
	if (keycode == LEFT_KEY)
		cube->player.rotate_right = 0;
	return (0);
}
