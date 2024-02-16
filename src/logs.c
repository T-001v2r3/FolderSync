#include "./folder_sync_c.h"

void generate_log(char *str)
{
    // get struct
    t_folder_sync_c *data = NULL;
    data = get_struct(NULL);

    // write to log file
    ft_putstr_fd(data->fd_logfile, "----------- Action Performed: -----------\n");
    ft_putstr_fd(1, "----------- Action Performed: -----------\n");

    // write date and time to log file
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);char *year = ft_itoa(tm.tm_year + 1900);
    char *month = ft_itoa(tm.tm_mon + 1);
    char *day = ft_itoa(tm.tm_mday);
    char *hour = ft_itoa(tm.tm_hour);
    char *min = ft_itoa(tm.tm_min);
    char *sec = ft_itoa(tm.tm_sec);

    char *date = ft_strjoin(year, "-");
    free(year);
    char *date_month = ft_strjoin(date, month);
    free(date);
    free(month);
    char *date_month_day = ft_strjoin(date_month, day);
    free(date_month);
    free(day);
    char *date_month_day_hour = ft_strjoin(date_month_day, hour);
    free(date_month_day);
    free(hour);
    char *date_month_day_hour_min = ft_strjoin(date_month_day_hour, min);
    free(date_month_day_hour);
    free(min);
    char *date_time = ft_strjoin(date_month_day_hour_min, sec);
    free(date_month_day_hour_min);
    free(sec);
    ft_putstr_fd(data->fd_logfile, date_time);
    ft_putstr_fd(1, date_time);
    free(date_time);

    // write launch parameters to log file
    ft_putstr_fd(data->fd_logfile, str);
    ft_putstr_fd(1, str);
    ft_putstr_fd(data->fd_logfile, "------------------- / -------------------\n");
    ft_putstr_fd(1, "------------------- / -------------------\n");
}

void init_log()
{
    // get struct
    t_folder_sync_c *data;
    data = get_struct(NULL);

    // write to log file
    ft_putstr_fd(data->fd_logfile, "----------- Program started -----------\n");
    ft_putstr_fd(1, "----------- Program started -----------\n");

    // write date and time to log file
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);char *year = ft_itoa(tm.tm_year + 1900);
    char *month = ft_itoa(tm.tm_mon + 1);
    char *day = ft_itoa(tm.tm_mday);
    char *hour = ft_itoa(tm.tm_hour);
    char *min = ft_itoa(tm.tm_min);
    char *sec = ft_itoa(tm.tm_sec);

    char *date = ft_strjoin(year, "-");
    free(year);
    char *date_month = ft_strjoin(date, month);
    free(date);
    free(month);
    char *date_month_day = ft_strjoin(date_month, day);
    free(date_month);
    free(day);
    char *date_month_day_hour = ft_strjoin(date_month_day, hour);
    free(date_month_day);
    free(hour);
    char *date_month_day_hour_min = ft_strjoin(date_month_day_hour, min);
    free(date_month_day_hour);
    free(min);
    char *date_time = ft_strjoin(date_month_day_hour_min, sec);
    free(date_month_day_hour_min);
    free(sec);
    ft_putstr_fd(data->fd_logfile, date_time);
    ft_putstr_fd(1, date_time);
    free(date_time);

    // write launch parameters to log file
    char *s_launch_params = ft_strjoin("Folder path: ", data->launch_params->folder_path);
    char *temp = ft_strjoin(s_launch_params, "\nSync interval: ");
    free(s_launch_params);
    s_launch_params = temp;
    temp = ft_strjoin(s_launch_params, data->launch_params->string_sync_interval);
    free(s_launch_params);
    s_launch_params = temp;
    temp = ft_strjoin(s_launch_params, "\nLog path: ");
    free(s_launch_params);
    s_launch_params = temp;
    temp = ft_strjoin(s_launch_params, data->launch_params->log_path);
    free(s_launch_params);
    s_launch_params = temp;
    ft_putstr_fd(data->fd_logfile, s_launch_params);
    ft_putstr_fd(1, s_launch_params);
    free(s_launch_params);
    ft_putstr_fd(data->fd_logfile, "------------------- / -------------------\n");
    ft_putstr_fd(1, "------------------- / -------------------\n");
}
