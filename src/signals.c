#include "./folder_sync_c.h"

void signal_handler(void)
{
    signal(SIGINT, clean_n_exit);
    signal(SIGQUIT, clean_n_exit);
}
