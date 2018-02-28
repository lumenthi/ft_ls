/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:01:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/23 10:54:28 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/types.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/errno.h>
# include <sys/stat.h>

typedef struct dirent	t_dir;
typedef struct stat		t_stat;

typedef struct			s_file
{
	mode_t				perm;
	unsigned long long	links;
	char				*owner;
	char				*group;
	char				*size;
	struct timespec		time;
	char				*name;
	unsigned long long	blocks;
	char				*link_name;
	struct s_file		*next;
}						t_file;

enum {USAGE};

void					l_print(t_file *files, int s);
void					ls_print(t_file *files);
t_file					*sort(t_file *file);
t_file					*sort_t(t_file *file);
t_file					*sort_r(t_file *file);
t_file					*file_fill(char *path);
t_file					*file_fill_a(char *path);
void					r_print(char *args, t_file *files, char *path);
void					apply_args(char *args, t_file **files, char *path);
void					ft_ls(int argc, char **argv, char *args, int i);
void					print_error(char *o_path, int error, int letter);
int						pass_args(int argc, char **argv, int i);
char					**sort_f(int argc, char **argv, char *args, int init);
t_file					*file_fill_single(char *path, char *single);
void					cpy(t_file *dest, t_file *src);
char					*time_conv(char *str);
int						max_userlen(t_file *file);
int						max_grouplen(t_file *file);
unsigned long long		block_count(t_file *files);
int						max_size(t_file *file);
int						max_link(t_file *file);
t_file					*fill_all(t_file *files, t_dir *content, char *path);
int						print_all_error(char argc, char **argv, int i);
int						invalid_path(char *str);
int						print_args(int argc, char **argv, char *args, int i);
char					*make_path(char *path, char *str);
void					file_del(t_file **files);
t_file					*file_init(t_file *file);
int						lst_len(t_file *file);
char					*get_path(char *arg);
int						get_valid_path(int argc, char **argv, int init);
int						valid_args_i(char **argv, int i);
int						valid_args_c(char **argv, int argc, int init);
struct timespec			get_time(char *arg);
void					print_date(t_file *files);
int						path_maker(char **argv, int *i, char **path, int argc);
void					first_perm(mode_t mode);
void					error_init(int *error, int *args_er);
int						is_sym(char **p);
void					l_print_total(t_file *files, int s, long long blocks);
void					ft_ls_init(t_file **files, int *check, int i);
int						is_sym(char **p);
void					separate(char *full, char **path, char **single);
void					make_path2(char **argv, int i, char **path);
char					*sp_si(int str1, int str2);
int						ferror(t_file *file, char **new_path, t_stat **stats);

#endif
