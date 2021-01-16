/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:53:41 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 13:59:47 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define FS 1
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define BUFFER_SIZE 3

typedef	struct		s_map
{
	char	**map;
	char	**filemap;
	int		rows;
	int		coloms;
	double	angle;
}					t_map;

typedef	struct		s_cubcolor
{
	int	r;
	int	g;
	int	b;
	int	f;
	int	c;
}					t_cubcolor;

typedef	struct		s_mlx
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	int					bnorth;
	int					bsouth;
	int					bwest;
	int					beast;
	int					bsprit;
	unsigned long long	height;
	unsigned long long	witdth;
	int					floor_c;
	int					ceil_c;
	int					n_player;
	int					n_sprit;
	char				*s_path;
	int					resolution;
	int					floor;
	int					ceil;
	t_map				s_map;
	t_cubcolor			ccolor;
}					t_mlx;

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_calloc(size_t count, size_t size);
int					get_next_line(int fd, char **line);
char				*str_get(char *rest, int i, char **line);
void				ft_bzero(void *s, size_t n);
char				*ft_chr(const char *s, int c);
unsigned long long	ft_atoi(const char *str);
unsigned long long	ft_atoi2(const char *str);
char				**ft_join_to_table(char **tab, char *str);
void				free_table(char **tab);
int					count_table(char **tab);
char				*ft_map_line_get_takeing(char *line, int i, int j);
int					ft_fill_mape(t_mlx *m, char *line);
int					parse(int ac, char **av, t_mlx *m);
int					count_width(char *line);
void				ft_get_player_angle(char angle, t_mlx *m);
int					the_longest_line_in_2d(char **tab);
void				initial_parse(t_mlx *m);
char				**new_tab(void);
int					ft_ceil(t_mlx *m, char *line, int i);
int					ft_floor(t_mlx *m, char *line, int i);
void				check_color_resolution(t_mlx *m, int *ret);
int					check_textures(t_mlx *mlx, char *line);
void				mlx_init1(t_mlx *mlx, int *i, int *ret);
int					check_sprite(t_mlx *mlx, char *line);
int					bypass_space(char *str, int *i);
char				**ft_remplir_tab(char **tab,
int the_longest_line, int nbr_rows, int i);
int					ft_res(t_mlx *mlx, char *line);
void				get_and_check(t_mlx *m, int *ret, char *line, int fd);
int					ft_check_sp_or_1_line(char **tab, int compar,
int compare_to);
int					check_player_nbr(t_mlx *m, int i, int nbrs_player);
int					ft_check_horizontal_line(char **tab,
int first, int befor_last, int lenght);
int					ft_check_vertical_line(char **tab, int first,
int last, int lenght_vert);
int					map_is_last(t_mlx *m);
int					ft_check_parse_file(t_mlx *m, char *line);
int					check_exte(char *str, int xpm);
#endif
