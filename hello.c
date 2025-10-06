#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <sys/stat.h>
#include <libgen.h>

// Creating a global dirpath and defaulting it to .
char *dir_path = ".";

// File counting 
int file_count = 0;
typedef struct {
    char *file_path;
    time_t creation_time;
} File;
File files[25];

// File sorting and printing
int compare(const void *a, const void *b) {
    time_t t1 = ((File *)a)->creation_time;
    time_t t2 = ((File *)b)->creation_time;
    return t2 - t1;
}
void sort_files() {
    qsort(files, file_count, sizeof(File), compare);
}
void print_files() {
    printf("Files in reverse order\n");
    for (int i = 0; i < file_count; i++) {
        char *time_str = ctime(&files[i].creation_time);
        // time_str[strlen(time_str) - 1] = '\0';  // Remove newline
        printf("%s: %s", files[i].file_path, time_str);
    }
}

// Counting files in directory
int fd_count = 0;
void print_file_count_in_dir() {
    printf("Total number of files in directory is: %d\n", fd_count);
}

// Counting files of particular type
char *global_file_type;
int global_file_type_count = 0;
void print_file_type_count() {
    printf("Total number of file types is: %d\n", global_file_type_count);
}

// Searching file of particular file type
char *global_file_name;
int file_name_count = 0;
char *filename[25];
void print_file_name() {
    if(file_name_count == 0) {
        printf("File not found\n");
    } else {
        for(int i = 0; i < file_name_count; i++) {
            printf("%s\n", filename[i]);
        }
    }
}

// Listing sub-directories
char *global_sub_dir;
int sub_dir_count = 0;
char *subdir[25];
void print_sub_dir_name() {
    if(sub_dir_count == 0) {
        printf("Sub-directory not found\n");
    } else {
        for(int i = 0; i < sub_dir_count; i++) {
            printf("%s\n", subdir[i]);
        }
    }
}

// Counting all files
int fdCount = 0;
void print_file_count() {
    printf("Total number of files is: %d\n", fdCount);
}

// Counting all directories
int count_all_dir = 0;
void print_dir_count() {
    printf("Total number of directories is: %d\n", count_all_dir);
}

// Sum of all file sizes
int total_size = 0;
void print_total_size() {
    printf("Total size of files is: %d bytes\n", total_size);
}

// Listing files of a particular extension
char *listextn_type;
int listextn_type_count =0;


// Copying directory and moving directory
char *source_dir_path;
char *destination_dir_path;


// Deleting files of a particular extension
char *file_extension;



/*
======Functions======
*/



// 1. Listing files (no subdirectories)
int dirlist(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D) {
        if (ftwbuf->level >= 1) {
            return FTW_SKIP_SUBTREE;
        }
    }
    if (typeflag == FTW_F) {
        files[file_count].file_path = strdup(file_path);
        files[file_count].creation_time = sb->st_ctime;
        file_count++;
    }
    return 0;
}

// 2. Counting files (no subdirectories)
int countfd(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D) {
        if (ftwbuf->level >= 1) {
            return FTW_SKIP_SUBTREE;
        }
    }
    if (typeflag == FTW_F) {
        fd_count++; 
    }
    return 0;
} 

// 3. Counting files of particular type (no subdirectories)
int countype(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D) {
        if (ftwbuf->level >= 1) {
            return FTW_SKIP_SUBTREE;
        }
    }
    if (typeflag == FTW_F) {
        char *ext = strrchr(file_path, '.');
        if (strcmp(global_file_type, ext) == 0) {
            global_file_type_count++;
        }
    }
    return 0;
}

// 4. Searching file of particular file type
int filesrch(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_F) {
        char *file = basename((char *)file_path);
        if (strcmp(file, global_file_name) == 0) {
            filename[file_name_count++] = strdup(file_path);
        }
    }
    return 0;
}

// 5. Listing sub-directories
int dirlst(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D) {
        char *sub_dir = basename((char *)file_path);
        if (strcmp(sub_dir, global_sub_dir) == 0) {
            subdir[sub_dir_count++] = strdup(file_path);
        }
    }
    return 0;
}

// 6. Counting all files 
int fcountrt(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_F) {
        fdCount++; 
   }
    return 0;
}

// 7. Count all directories
int dircnt(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D) {
        count_all_dir++;
    }
    return 0;
}

// 8. Sum of all file sizes
int sumfilesize(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if(typeflag==FTW_F){
        total_size = total_size + sb->st_size;
    }
    return 0;
}

// 9. Listing all files and directories
int rootlist(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_D || typeflag == FTW_F) {
        char *allfiles = basename((char *)file_path);
        printf("File: %s Path: %s\n", allfiles, file_path);
    }
    return 0;
}

// 10. Listing files of a particular extension
int listextn(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_F) {
        char *ext = strrchr(file_path, '.');
        if (strcmp(listextn_type, ext) == 0) {
            listextn_type_count++;
        }
        char *allfiles = basename((char *)file_path);
        printf("File: %s Path: %s\n", allfiles, file_path);
    }
    return 0;
}

// 11. Copying directory
int copyd(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    
}

// 12. Moving directory
int dmove(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {

}

// 13. Deleting files of a particular extension
int remd(const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_F) {
        char *ext = strrchr(file_path, '.');
        if (strcmp(file_extension, ext) == 0) {
            // Delete the file
            printf("File Deleted\n");
        }
    }
    return 0;
}





/*
======Main Function======
*/




int main(int num_args, char *arguments[]) {

    if (num_args < 2) {
        printf("Invalid command\n");
        return 1;
    }

    // Array of valid commands
    const char *commands[] = {
        "-dirlist", "-countfd", "-countype", "-filesrch", "-dirlst", "-fcountrt", "-dircnt", "-sumfilesize", "-rootlist", "-Listextn", "-copyd", "-dmove", "-remd"};

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {

        if (strcmp(arguments[1], commands[i]) == 0) {

            switch (i + 1) {
            case 1:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, dirlist, 20, FTW_PHYS | FTW_ACTIONRETVAL);
                sort_files(); 
                print_files();
                break;

            case 2:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, countfd, 20, FTW_PHYS | FTW_ACTIONRETVAL);
                print_file_count_in_dir();
                break;

            case 3:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                global_file_type = arguments[2];
                dir_path = arguments[3];
                char *file_type_target = arguments[2];
                nftw(dir_path, countype, 20, FTW_PHYS | FTW_ACTIONRETVAL);
                print_file_type_count();
                break;

            case 4:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                global_file_name = arguments[2];
                dir_path = arguments[3];
                nftw(dir_path, filesrch, 20, FTW_PHYS);
                print_file_name();
                break;

            case 5:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                global_sub_dir = arguments[2];
                dir_path = arguments[3];
                nftw(dir_path, dirlst, 20, FTW_PHYS);
                print_sub_dir_name();
                break;

            case 6:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, fcountrt, 20, FTW_PHYS);
                print_file_count();
                break;

            case 7:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, dircnt, 20, FTW_PHYS);
                print_dir_count();
                break;  

            case 8:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, sumfilesize, 20, FTW_PHYS);
                print_total_size();
                break;

            case 9:
                if (num_args != 3) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                nftw(dir_path, rootlist, 20, FTW_PHYS);
                break;  

            case 10:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                dir_path = arguments[2];
                listextn_type = arguments[3];
                nftw(dir_path, listextn, 20, FTW_PHYS);
                break;

            case 11:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                source_dir_path = arguments[2];
                destination_dir_path = arguments[3];
                nftw(source_dir_path, copyd, 20, FTW_PHYS);
                break;

            case 12:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                source_dir_path = arguments[2];
                destination_dir_path = arguments[3];
                nftw(source_dir_path, dmove, 20, FTW_PHYS);
                break;

            case 13:
                if (num_args != 4) {
                    printf("Too much arguments\n");
                    return 1;
                }
                source_dir_path = arguments[2];
                file_extension = arguments[3];
                nftw(source_dir_path, remd, 20, FTW_PHYS);
                break;

            default:
                printf("Invalid command\n");
            }
            return 0;
        }
    }
    printf("Invalid command: %s\n", arguments[1]);
    return 1;
}
