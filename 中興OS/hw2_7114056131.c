#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>     
#include <sys/wait.h>   
#include <string.h>     
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#define MAX_ARGS 64     
#define MAX_PATH 1024   
#define MAX_BG_JOBS 64
#define MAX_COMMAND_NAME 100
struct bg_job {
    pid_t pid;
    char command_name[MAX_COMMAND_NAME];
    int is_active;
};
struct bg_job job_list[MAX_BG_JOBS];
int bg_job_count = 0;
int main() {
    char *line;
    char *args[MAX_ARGS];
    int running = 1;
    for(int i=0; i < MAX_BG_JOBS; i++) {
        job_list[i].is_active = 0;
    }
    while (running) {
        char *user = getenv("USER");
        if (user == NULL) {
            user = "user"; 
        }
        char host[256]; 
        if (gethostname(host, sizeof(host)) != 0) {
            strncpy(host, "host", sizeof(host)); 
        }
        char *home_dir = getenv("HOME");
        char cwd[MAX_PATH];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd failed");
            continue; 
        }
        char display_path[MAX_PATH];
        if (home_dir != NULL && strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
            snprintf(display_path, sizeof(display_path), "~%s", &cwd[strlen(home_dir)]);
        } else {
            strncpy(display_path, cwd, sizeof(display_path));
        }
        char prompt1[MAX_PATH * 2];
        snprintf(prompt1, sizeof(prompt1), "%s@%s:%s $ ", user, host, display_path);

        line = readline(prompt1);
        getcwd(cwd, sizeof(cwd)); 
        char prompt2[MAX_PATH + 100];
        snprintf(prompt2, sizeof(prompt2), "%s@%s:%s $ ", user, host, cwd);
        line = readline(prompt2);
        if (line == NULL) { 
            break;
        }
        if (strlen(line) == 0) { 
            free(line);
            continue;
        }
        add_history(line); 
        char *token;
        int i = 0;
        int is_background = 0;
        char *output_file = NULL;

        token = strtok(line, " \t\n"); 
        while (token != NULL) {
            if (strcmp(token, "&") == 0) { 
                is_background = 1;
                break; 
            } else if (strcmp(token, ">") == 0) { 
                token = strtok(NULL, " \t\n"); 
                if (token != NULL) {
                    output_file = token;
                }
                break;
            } else {
                args[i] = token;
                i++;
            }
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL; 
        if (args[0] == NULL) {
            free(line);
            continue;
        }
        if (strcmp(args[0], "exit") == 0) { 
            running = 0; 
        
        } else if (strcmp(args[0], "cd") == 0) { 
            if (args[1] == NULL) {
                chdir(getenv("HOME")); 
            } else {
                if (chdir(args[1]) != 0) { 
                    perror("cd failed");
                }
            }
        } else if (strcmp(args[0], "pwd") == 0) { 
            char pwd_buf[MAX_PATH];
            if (getcwd(pwd_buf, sizeof(pwd_buf)) != NULL) { 
                printf("%s\n", pwd_buf);
            } else {
                perror("pwd failed");
            }
        
        } else if (strcmp(args[0], "echo") == 0) { 
            for (int j = 1; args[j] != NULL; j++) {
                if(args[j][0] == '$') {
                    char *var_name = &args[j][1];
                    char *value = getenv(var_name);
                    if(value != NULL) {
                        printf("%s ", value);
                    }else {
                        printf(" ");
                    }
                }else {
                    printf("%s ", args[j]);
                }
            }
            printf("\n");
        
        } else if (strcmp(args[0], "export") == 0) { 
            if (args[1] == NULL) {
                fprintf(stderr, "Usage: export NAME=value\n");
                continue;
            }
            char *arg_copy = strdup(args[1]);
            if (arg_copy == NULL) {
                perror("strdup");
                continue;
            }
            char *name = strtok(arg_copy, "=");
            char *value_part = strtok(NULL, ""); 
            if (name == NULL || value_part == NULL) {
                fprintf(stderr, "Usage: export NAME=value\n");
                free(arg_copy);
                continue;
            }
            char new_value_buffer[MAX_PATH * 4]; 
            new_value_buffer[0] = '\0';
            if (value_part[0] == '$') {
                char *remainder = strchr(value_part, ':');
                char *var_name;
                if (remainder != NULL) {
                    int var_name_len = remainder - value_part - 1; 
                    var_name = (char*)malloc(var_name_len + 1);
                    strncpy(var_name, &value_part[1], var_name_len);
                    var_name[var_name_len] = '\0';
                    char *existing_val = getenv(var_name);
                    if (existing_val) {
                        snprintf(new_value_buffer, sizeof(new_value_buffer), "%s%s", existing_val, remainder);
                    } else {
                        snprintf(new_value_buffer, sizeof(new_value_buffer), "%s", remainder);
                    }
                    free(var_name);
                } else {
                    var_name = &value_part[1];
                    char *existing_val = getenv(var_name);
                    if (existing_val) {
                        strncpy(new_value_buffer, existing_val, sizeof(new_value_buffer) - 1);
                    }
                }
                setenv(name, new_value_buffer, 1);
            } else {
                setenv(name, value_part, 1);
            }

            free(arg_copy);
        } else if (strcmp(args[0], "history") == 0) { 
            HISTORY_STATE *hist_state = history_get_history_state();
            HIST_ENTRY **hist_list = history_list();
            
            if (hist_list != NULL) {
                for (int j = 0; hist_list[j] != NULL; j++) {
                    printf("%d: %s\n", j + 1, hist_list[j]->line);
                }
            }
        } else if (strcmp(args[0], "sbg") == 0) { 
            int any_active_jobs = 0;
            for (int i = 0; i < MAX_BG_JOBS; i++) {
                if(job_list[i].is_active == 1) {
                    int status;
                    pid_t result = waitpid(job_list[i].pid, &status, WNOHANG); 

                    if (result == 0) {
                        if(any_active_jobs == 0) {
                            printf("Background processes:\n");
                        }
                        printf("[%d] PID: %d, Command: %s\n", i + 1, job_list[i].pid, job_list[i].command_name);
                        any_active_jobs = 1;
                    } else if (result == job_list[i].pid) {
                        job_list[i].is_active = 0;
                    } else {
                        job_list[i].is_active = 0;
                    }
                }
            }
            if(any_active_jobs == 0) {
                printf("No background processes running.\n");
            }
        } else {
           pid_t pid = fork();
           if(pid == -1) {
            perror("fork failed");
           } else if(pid == 0) {
            if(output_file != NULL) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd < 0) {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO); 
                close(fd);
            }
            if(execvp(args[0], args) == -1) {
                perror("exec failed");
                exit(1);
            }
           }else {
            if(is_background) {
                printf("[Process running in background with PID %d]\n", pid);
                int found_slot = 0;
                for (int i = 0; i < MAX_BG_JOBS; i++) {
                    if (job_list[i].is_active == 0) {
                        job_list[i].pid = pid;
                        strncpy(job_list[i].command_name, args[0], MAX_COMMAND_NAME - 1);
                        job_list[i].command_name[MAX_COMMAND_NAME - 1] = '\0'; 
                        job_list[i].is_active = 1;
                        found_slot = 1;
                        break;
                    }
                }
                if (found_slot == 0) {
                    fprintf(stderr, "myShell: Error: Max background jobs reached.\n");
                }
            }else {
                wait(NULL);
            }
           }
        }
        free(line);
    }
    return 0;
}