/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:50:57 by amouhtal          #+#    #+#             */
/*   Updated: 2021/01/16 15:58:28 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		hass_wall_ray(int x, int y, char m, t_cube *cube)
{
	int newx;
	int newy;

	newx = x / cube->tile_size;
	newy = y / cube->tile_size;
	if (cube->m.s_map.map[newy][newx] == m)
		return (1);
	return (0);
}

void	check_texture(t_cube *cube)
{
	if (!cube->ray.was_hit_vert && cube->ray.isfaycingup == 1)
		cube->texture.initial_txt = cube->texture.texture_s;
	if (!cube->ray.was_hit_vert && cube->ray.isfaycingdown == 1)
		cube->texture.initial_txt = cube->texture.texture_n;
	if (cube->ray.was_hit_vert && cube->ray.isfaycingleft == 1)
		cube->texture.initial_txt = cube->texture.texture_e;
	if (cube->ray.was_hit_vert && cube->ray.isfaycingright == 1)
		cube->texture.initial_txt = cube->texture.texture_w;
}

int		cast_all_rays(t_cube *cube)
{
	int		i;
	double	wall_strip_hieght;

	i = 0;
	cube->player.angle = normalize_angle(cube->player.angle);
	while (i < (int)cube->m.witdth)
	{
		cube->ray.angle = cube->player.angle +
		atan((i - ((int)cube->m.witdth / 2)) / cube->dest_project_plane);
		cast_ray(cube);
		cube->ray.dist_tab[i] = cube->ray.distance;
		cube->ray.distance = cube->ray.distance *
		cos(cube->ray.angle - cube->player.angle);
		wall_strip_hieght = (cube->tile_size / cube->ray.distance)
		* (cube->dest_project_plane);
		if (!cube->ray.was_hit_vert)
			fill_image(cube, i, wall_strip_hieght, cube->ray.wall_hit_x);
		else
			fill_image(cube, i, wall_strip_hieght, cube->ray.wall_hit_y);
		i++;
	}
	find_sprits(cube);
	mlx_put_image_to_window(cube->ptr_mlx, cube->ptr_win, cube->img_ptr, 0, 0);
	return (0);
}

int		update(t_cube *cube)
{
	if (cube->player.move_up_down || cube->player.move_right_left ||
	cube->player.move_left || cube->player.rotate_left ||
	cube->player.rotate_right)
	{
		update_player(cube);
		cast_all_rays(cube);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_cube	cube;
	int		ret_pars;

	if ((ret_pars = parse(ac, av, &cube.m)) != 0)
		ft_close_window(&cube, ret_pars);
	cube.nbrofsprites = count_sprit(&cube);
	cube.sprits = malloc(sizeof(t_sprit) * (cube.nbrofsprites));
	cube.ray.dist_tab = (int *)malloc(sizeof(cube.ray.dist_tab)
	* cube.m.witdth);
	cube.ptr_mlx = mlx_init();
	intialise(&cube, 0);
	cube.player.angle = cube.m.s_map.angle;
	find_player(&cube);
	count_sprites(&cube, 0, 0);
	if (ac == 3)
		bmp(&cube, av[2]);
	cube.ptr_win = mlx_new_window(cube.ptr_mlx, cube.m.witdth,
	cube.m.height, "cube3D");
	cast_all_rays(&cube);
	mlx_hook(cube.ptr_win, 2, (1L << 0), keypress, &cube);
	//mlx_hook(cube.ptr_win, 3, (1L >> 1), keyrelease, &cube);
	mlx_hook(cube.ptr_win, 17, (1L << 5), ft_close_window, &cube);
	mlx_loop_hook(cube.ptr_mlx, update, &cube);
	mlx_loop(cube.ptr_mlx);
	return (0);
}
