#ifndef FOLDER_SYNC_C_H
#define FOLDER_SYNC_C_H

# include <unistd.h> // to use write
# include <stdio.h> // to use sprintf
# include <fcntl.h> // to use open
# include <time.h> // to use time
# include <dirent.h> // to use opendir, readdir, closedir
# include <sys/types.h> // to use stat
# include <sys/stat.h> // to use stat
# include <errno.h> // to use errno
# include <stdlib.h> // to use malloc
# include <signal.h> // to use signals

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_launch_params
{
	char *folder_path;
	int sync_interval;
	char *string_sync_interval;
	char *log_path;
} t_launch_params;

typedef struct s_folder_sync_c
{
	// launch parameters
	t_launch_params *launch_params;
	int fd_logfile;
	char *replica_path;
} t_folder_sync_c;

// utils.c
int	ft_strcmp(const char *s1, const char *s2);
int	ft_memcmp(const void *s1, const void *s2, size_t n);
char *ft_strcat(char *dest, char *src);
long ft_strlen(char *str);
void ft_putstr_fd(int fd, char *str);
int is_digit(char *str);
int ft_atoi(char *str);
char *ft_strjoin(char *s1, char *s2);
char *ft_itoa(int n);

// data_init.c
t_folder_sync_c *get_struct(t_folder_sync_c *new_data);
t_folder_sync_c *prepare_structs(void);

// logs.c
void generate_log(char *str);
void init_log();

// sync.c
void copy_directory(char *src_path, char *replica_path);

//exit.c
void clean_n_exit(int sig);

// signals.c
void signal_handler(void);

#endif