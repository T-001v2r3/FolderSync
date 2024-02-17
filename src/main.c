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
    // check paramaters
	if (ac != 4)
	{
		ft_putstr_fd(2, "Usage: Folder_Sync_C <folder_path> <sync_interval> <log_path>\n");
		exit(1);
	}
        
    // hanlde exit signals
    signal_handler();

    // verify launch parameters
    validations(av);

    //init logs
    init_log();
	
    // start up the sync process
    if (start_sync())
		ft_putstr_fd(2, "Error: sync process interrupted\n");

	// free up memory and exit program
	clean_n_exit(0);

	return (0);
}
