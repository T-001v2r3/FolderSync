#include "./folder_sync_c.h"

int start_sync()
{
    // get struct
    t_folder_sync_c *data = NULL;
    data = get_struct(NULL);
    
    //char *data->replica_path;
    int replica_num = 0;
    char *replica_num_str = ft_itoa(replica_num);
    char *suffix;
    
    if (replica_num == 0)
        suffix = "_replica";
    else
        suffix = ft_strjoin("_replica_", replica_num_str);
    data->replica_path = ft_strjoin(data->launch_params->folder_path, suffix);
    if (replica_num != 0)
        free(suffix);
    replica_num++;

    while (access(data->replica_path, F_OK) != -1)
    {
        free(data->replica_path);
        free(replica_num_str);
        replica_num_str = ft_itoa(replica_num);
        if (replica_num == 0)
            suffix = "_replica";
        else
            suffix = ft_strjoin("_replica_", replica_num_str);
        data->replica_path = ft_strjoin(data->launch_params->folder_path, suffix);
        if (replica_num != 0)
            free(suffix);
        replica_num++;
    }
    free(replica_num_str);

    if (mkdir(data->replica_path, 0777) == -1)
    {
        ft_putstr_fd(2, "Error creating replica directory");
        free(data->replica_path);
        return (1);
    }
    char *prefix = "Replica folder created: ";
    char *message = ft_strjoin(prefix, data->replica_path);
    char *logmsg = ft_strjoin(message, "\n");
    free(message);
    generate_log(logmsg);
    free(logmsg);

    // Start the sync loop
    while (1)
    {
        generate_log("Checking for updates\n");
        copy_directory(data->launch_params->folder_path, data->replica_path);
        // Wait for sync_interval
        sleep(data->launch_params->sync_interval);
    }
    free(data->replica_path);
    return(0);
}

int main(int ac, char **av)
{
    // hanlde exit signals
    signal_handler();
    // check paramaters
	if (ac != 4)
	{
		ft_putstr_fd(2, "Usage: Folder_Sync_C <folder_path> <sync_interval> <log_path>\n");
		exit(1);
	}
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

	// open log file
	char *log_file_name = "log.txt";
    if (data->launch_params->log_path[ft_strlen(data->launch_params->log_path) - 1] != '/')
    {
        data->launch_params->log_path = ft_strcat(data->launch_params->log_path, "/");
    }
	char *log_file_path_name = ft_strcat(data->launch_params->log_path, log_file_name);
	data->fd_logfile = open(log_file_path_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->fd_logfile == -1)
	{
		ft_putstr_fd(2, "Error: could not open log file\n");
        clean_n_exit(0);
	}

	// write date and time to log file
	init_log();
	if (start_sync())
	{
		ft_putstr_fd(2, "Error: sync process interrupted\n");
        clean_n_exit(0);
	}

	// close log file
	clean_n_exit(0);
	return (0);
}
