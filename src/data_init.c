#include "./folder_sync_c.h"

t_folder_sync_c *get_struct(t_folder_sync_c *new_data)
{
	static t_folder_sync_c *data;
	if (new_data)
		data = new_data;
	return (data);
}

t_folder_sync_c *prepare_structs(void)
{
    t_folder_sync_c *data = NULL;
    data = malloc(sizeof(t_folder_sync_c));
    if (data == NULL)
    {
        ft_putstr_fd(2, "Error: malloc failed\n");
        exit(1);
    }
    data->launch_params = malloc(sizeof(struct s_launch_params));
    if (data->launch_params == NULL)
    {
        ft_putstr_fd(2, "Error: malloc failed\n");
        free(data);
        exit(1);
    }

    // init all values to 0
    data->launch_params->folder_path = 0;
    data->launch_params->sync_interval = 0;
    data->launch_params->string_sync_interval = 0;
    data->launch_params->log_path = 0;
    data->fd_logfile = 0;
    
    // save struct
    get_struct(data);
    return (data);
}
