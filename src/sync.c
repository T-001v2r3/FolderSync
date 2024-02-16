#include "./folder_sync_c.h"

int copy_source_to_destination(char *dst_file_path, FILE *src_file)
{    
    // Copy the source file to the destination
    FILE *dst_file = fopen(dst_file_path, "w");
    if (dst_file == NULL)
    {
        generate_log("Error opening destination file for writing\n");
        return (1);
    }
    rewind(src_file);
    char buffer[8192];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0)
        fwrite(buffer, 1, bytes, dst_file);
    fclose(dst_file);
	return (0);
}

int file_comparisson(FILE *src_file, FILE *dst_file, int *files_differ, char *src_file_path)
{
    // Compare the files
    char src_buffer[512], dst_buffer[512];
    size_t src_bytes, dst_bytes;

    while (!feof(src_file) || !feof(dst_file))
    {
        src_bytes = fread(src_buffer, 1, sizeof(src_buffer), src_file);
        dst_bytes = fread(dst_buffer, 1, sizeof(dst_buffer), dst_file);
        if (src_bytes != dst_bytes || ft_memcmp(src_buffer, dst_buffer, src_bytes) != 0)
        {
            char *prefix = "File Updated: ";
            char *message = ft_strjoin(prefix, src_file_path);
            char *logmsg = ft_strjoin(message, "\n");
            free(message);
            generate_log(logmsg);
            free(logmsg);
            *files_differ = 1;
            fclose(dst_file);
            return 1;
        }
    }
    fclose(dst_file);
    return 0;
}

void delete_extra(char *src_path, char *replica_path)
{
    DIR *dir = opendir(replica_path);
    if (dir == NULL)
    {
        ft_putstr_fd(2, "Error opening replica directory");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            continue;

        char src_file_path[4096];
        snprintf(src_file_path, sizeof(src_file_path), "%s/%s", src_path, entry->d_name);

        char replica_file_path[4096];
        snprintf(replica_file_path, sizeof(replica_file_path), "%s/%s", replica_path, entry->d_name);

        struct stat st;
            // if source file doesnt exist delete from replica
        if (stat(src_file_path, &st) == -1)
        {
            remove(replica_file_path);
            char *prefix = "File Deleted: ";
            char *message = ft_strjoin(prefix, replica_file_path);
            char *logmsg = ft_strjoin(message, "\n");
            free(message);
            generate_log(logmsg);
            free(logmsg);
            continue;
        }
        if (S_ISDIR(st.st_mode))
            delete_extra(src_file_path, replica_file_path);
    }
    closedir(dir);
}

void copy_directory(char *src_path, char *replica_path)
{    
    DIR *dir = opendir(src_path);
    if (dir == NULL)
    {
        ft_putstr_fd(2, "Error opening source directory");
        return;
    }
    if (access(replica_path, F_OK) == -1 && mkdir(replica_path, 0777) == -1)
    {
        ft_putstr_fd(2, "Error creating destination directory");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            continue;

        // Generate the source and destination file paths
        char src_file_path[4096];
        snprintf(src_file_path, sizeof(src_file_path), "%s/%s", src_path, entry->d_name);

        char dst_file_path[4096];
        snprintf(dst_file_path, sizeof(dst_file_path), "%s/%s", replica_path, entry->d_name);

        struct stat st;
        if (stat(src_file_path, &st) == -1)
        {
            ft_putstr_fd(2, "Error getting source file status");
            continue;
        }
        // verify if it is a directory and make recursion
        if (S_ISDIR(st.st_mode))
            copy_directory(src_file_path, dst_file_path);
        else
        {
            // compare and copy if different
            FILE *src_file = fopen(src_file_path, "r");
            FILE *dst_file = fopen(dst_file_path, "r");

            if (src_file == NULL || (dst_file == NULL && errno != ENOENT))
            {
                ft_putstr_fd(2, "Error opening file");
                continue;
            }
            int files_differ = 0;
            if (dst_file == NULL)
            {
                char *prefix = "File Deleted: ";
                char *message = ft_strjoin(prefix, src_file_path);
                char *logmsg = ft_strjoin(message, "\n");
                free(message);
                generate_log(logmsg);
                free(logmsg);
                // destination file differs
                files_differ = 1;
            }
            else
                file_comparisson(src_file, dst_file, &files_differ, src_file_path);
            if (files_differ && copy_source_to_destination(dst_file_path, src_file) == 1)
				continue;
            fclose(src_file);
        }
        delete_extra(src_path, replica_path);
    }
    closedir(dir);
}
