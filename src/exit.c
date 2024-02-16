#include "./folder_sync_c.h"

void clean_n_exit(int sig)
{
    (void)sig;

    // get struct
    t_folder_sync_c *data = NULL;
    data = get_struct(NULL);

    ft_putstr_fd(1, "\nCleaning and exiting\n");
    
    if (data->fd_logfile)
	    close(data->fd_logfile);
    //if (data->launch_params->folder_path)
    //    free(data->launch_params->folder_path);
    //if (data->launch_params->string_sync_interval)
    //    free(data->launch_params->string_sync_interval);
    //if (data->launch_params->log_path)
    //    free(data->launch_params->log_path);
    if (data->replica_path)
        free(data->replica_path);
    if (data->launch_params)
        free(data->launch_params);
    if (data)
        free(data);

    exit(1);
}
