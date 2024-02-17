# Notes:
- This program crates a replica folder in the directory it runs from.
- This program was built in Linux a envoirnment;

# Usage:
```
use 'make' to complile the program, the parameters 'clean', 'fclean' and 're' are also available

./Folder_Sync <folder_to_sync> <sync_frequency_in_seconds> <folder_to_save_log>
ex.: ./Folder_Sync_C src 5 .
```

<folder_to_sync> is the path for the folder to make the copy from.

<sync_frequency_in_seconds> is the time between each sync.

<folder_to_save_log> is the path for the file with logs to be saved at.
