#include "./folder_sync_c.h"

void validations(char **av)
{
    // memory allocation
    t_folder_sync_c *data = prepare_structs();
    
    // validate sync interval
	if (is_digit(av[2]))
	{
		ft_putstr_fd(2, "Error: sync_interval must be a number\n");
        clean_n_exit(0);
	}
	data->launch_params->sync_interval = ft_atoi(av[2]);
    if (data->launch_params->sync_interval < 1)
    {
        ft_putstr_fd(2, "Error: sync_interval must be greater than 0\n");
        clean_n_exit(0);
    }
    data->launch_params->string_sync_interval = av[2];

    // validate folder_path
	data->launch_params->folder_path = av[1];
	if (access(data->launch_params->folder_path, F_OK == -1))
	{
		ft_putstr_fd(2, "Error: folder path is not a valid path\n");
        clean_n_exit(0);
	}

    // validate log_path
	data->launch_params->log_path = av[3];
	if (access(data->launch_params->log_path, F_OK == -1))
	{
		ft_putstr_fd(2, "Error: log path is not a valid path\n");
        clean_n_exit(0);
	}
}
