/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:47:29 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/10 09:43:16 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void	set_header(t_bitmap_file_header *bfh,
		t_bitmap_info_header *bih, unsigned short *bf_type, t_cube *cube)
{
	*bf_type = 0x4d42;
	bfh->bf_reserved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_size = 2 + sizeof(t_bitmap_file_header)
		+ sizeof(t_bitmap_info_header)
		+ cube->m.witdth * cube->m.height * 4;
	bfh->bf_off_bits = 0x36;
	bih->bi_size = sizeof(t_bitmap_info_header);
	bih->bi_width = cube->m.witdth;
	bih->bi_height = cube->m.height;
	bih->bi_planes = 1;
	bih->bi_bit_count = 32;
	bih->bi_compression = 0;
	bih->bi_size_image = 0;
	bih->bi_x_pels_per_meter = 5000;
	bih->bi_y_pels_per_meter = 5000;
	bih->bi_clr_used = 0;
	bih->bi_clr_important = 0;
}

void	set_body(int file, t_cube *cube, t_bitmap_info_header *bih)
{
	int				x;
	int				y;
	unsigned int	color;

	y = bih->bi_height;
	while (--y >= 0 && (x = -1))
		while (++x < bih->bi_width)
		{
			color = cube->data[bih->bi_width * y + x];
			write(file, &color, 4);
		}
}

void	write_file(int file, t_cube *cube)
{
	t_bitmap_file_header	bfh;
	t_bitmap_info_header	bih;
	unsigned short			bf_type;

	set_header(&bfh, &bih, &bf_type, cube);
	write(file, &bf_type, sizeof(bf_type));
	write(file, &bfh, sizeof(bfh));
	write(file, &bih, sizeof(bih));
	set_body(file, cube, &bih);
}

int		save_bmp(t_cube *cube)
{
	int						file;

	if (!(file = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)))
	{
		write(1, "Error\nCould not write file", 26);
		return (-1);
	}
	write_file(file, cube);
	close(file);
	return (1);
}

void	bmp(t_cube *cube, char *av)
{
	int		i;
	char	*str;

	str = ft_strdup("--save");
	i = 0;
	while (av[i])
	{
		if (av[i] != str[i])
		{
			write(1, "Error\nWRONG ARG --SAVE !", 17);
			exit(0);
		}
		i++;
	}
	free(str);
	cast_all_rays2(cube);
	save_bmp(cube);
	ft_close_window(cube, 0);
}
