/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:42 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 12:08:42 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	intial_wall(t_cube *cube)
{
	cube->ray.next_horiz_hit_x = 0;
	cube->ray.next_horiz_hit_y = 0;
	cube->ray.horz_wall_hit_x = 0;
	cube->ray.horz_wall_hit_y = 0;
	cube->ray.next_vert_hit_x = 0;
	cube->ray.next_vert_hit_y = 0;
	cube->ray.vert_wall_hit_x = 0;
	cube->ray.vert_wall_hit_y = 0;
	cube->ray.there_is_wall_vert = 0;
	cube->ray.there_is_wall_horz = 0;
	cube->ray.wall_hit_x = 0;
	cube->ray.wall_hit_y = 0;
	cube->ray.was_hit_vert = 0;
}

void	intial_player(t_cube *cube)
{
	cube->player.angle = M_PI * 3 / 2;
	cube->player.move_right_left = 0;
	cube->player.move_up_down = 0;
	cube->player.move_up = 0;
	cube->player.move_down = 0;
	cube->player.move_right = 0;
	cube->player.move_left = 0;
	cube->player.rotate_left = 0;
	cube->player.rotate_right = 0;
	cube->player.new_player_x = 0;
	cube->player.new_player_y = 0;
	cube->player.player_x = 0;
	cube->player.player_y = 0;
}

void	initial_variabls(t_cube *cube)
{
	cube->cpt = 0;
	cube->ray.angle = 0;
	cube->ray.y_intercept = 0;
	cube->ray.xstep = 0;
	cube->ray.ystep = 0;
	cube->ray.x_intercept = 0;
	cube->ray.x_inter = 0;
	cube->tile_size = 32;
	cube->ray.isfaycingup = 1;
	cube->ray.isfaycingdown = 1;
	cube->ray.isfaycingright = 1;
	cube->ray.isfaycingleft = 1;
	cube->dest_project_plane = (cube->m.witdth / 2) / tan(30 * ANGLE_TO_RAD);
	cube->img_ptr = mlx_new_image(cube->ptr_mlx, cube->m.witdth,
	cube->m.height);
	cube->data = (int *)mlx_get_data_addr(cube->img_ptr,
	&cube->bpp, &cube->size_l, &cube->endian);
	intial_wall(cube);
	intial_player(cube);
}

void	print_error(int ret)
{
	if (ret == 2)
		write(1, "Error\npath error north", 22);
	if (ret == 3)
		write(1, "Error\npath error south", 22);
	if (ret == 1)
		write(1, "Error\nsprite path error", 23);
	if (ret == 4)
		write(1, "Error\npath error east", 21);
	if (ret == 5)
		write(1, "Error\npath error west", 21);
	exit(0);
}

void	intialise(t_cube *cube, int ret)
{
	initial_variabls(cube);
	if (!(cube->txt_sprit_file = mlx_xpm_file_to_image(cube->ptr_mlx,
	cube->m.s_path,
	&cube->sprit_w, &cube->sprit_h)) || !check_exte(cube->m.s_path, 1))
		ret = 1;
	if (!(cube->texture.texture_n = mlx_xpm_file_to_image(cube->ptr_mlx,
	cube->m.north, &cube->tex_w, &cube->tex_h))
	|| !check_exte(cube->m.north, 1))
		ret = 2;
	if (!(cube->texture.texture_s = mlx_xpm_file_to_image(cube->ptr_mlx,
	cube->m.south, &cube->tex_w, &cube->tex_h))
	|| !check_exte(cube->m.south, 1))
		ret = 3;
	if (!(cube->texture.texture_e = mlx_xpm_file_to_image(cube->ptr_mlx,
	cube->m.east, &cube->tex_w, &cube->tex_h)) || !check_exte(cube->m.east, 1))
		ret = 4;
	if (!(cube->texture.texture_w = mlx_xpm_file_to_image(cube->ptr_mlx,
	cube->m.west, &cube->tex_w, &cube->tex_h)) || !check_exte(cube->m.west, 1))
		ret = 5;
	if (ret != 0)
		print_error(ret);
	cube->txt_sprit_data = (int *)mlx_get_data_addr(cube->txt_sprit_file,
		&cube->bpp, &cube->size_l, &cube->endian);
}
