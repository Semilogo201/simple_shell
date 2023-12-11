#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for the read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for the command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - the singly linked list
 * @num: number field
 * @str: string
 * @next: the points to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfos - it contains the pseudo-arguments to pass into a function,
 *		allowing the uniform prototype for function pointer structure
 *@arg: string generated from the getline containing arguments
 *@argv: array of strings generated from the arguments
 *@path: string path for current command
 *@argc: argument count
 *@line_count: error count
 *@err_num: the error code for exit()s
 *@linecount_flag: count this line of input
 *@fname: program filename
 *@env: the linked list local copy of environ
 *@environ: the custom modified copy of environ from LL environ
 *@history: history node
 *@alias: alias node
 *@env_changed: on if the environ was changed
 *@status: return status of the last exec'd command
 *@cmd_buf: the address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read the line input
 *@histcount: history line number count
 */
typedef struct passinfos
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} infos_t;

#define INFOS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - it contains a builtin string and a related function
 *@type: builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infos_t *);
} builtin_table;


/* toem_shloops.c */
int hsh(infos_t *, char **);
int find_builtin(infos_t *);
void find_cmd(infos_t *);
void fork_cmd(infos_t *);

/* toem_parse.c */
int is_cmd(infos_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(infos_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_error.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_strings.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_strings1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_reallock.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memo.c */
int cfree(void **);

/* toem_atois.c */
int interactive(infos_t *);
int is_delims(char, char *);
int _isalpha(int);
int _atois(char *);

/* toem_error1.c */
int _erratois(char *);
void print_error(infos_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_built.c */
int _myexit(infos_t *);
int _mycd(infos_t *);
int _myhelp(infos_t *);

/* toem_built1.c */
int _myhistory(infos_t *);
int _myalias(infos_t *);

/*toem_getline.c */
ssize_t get_input(infos_t *);
int _getline(infos_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfos.c */
void clear_infos(infos_t *);
void set_infos(infos_t *, char **);
void free_infos(infos_t *, int);

/* toem_environs.c */
char *_getenv(infos_t *, const char *);
int _myenv(infos_t *);
int _mysetenv(infos_t *);
int _myunsetenv(infos_t *);
int populate_env_list(infos_t *);

/* toem_getenv.c */
char **get_environ(infos_t *);
int _unsetenv(infos_t *, char *);
int _setenv(infos_t *, char *, char *);

/* toem_history.c */
char *get_history_file(infos_t *infos);
int write_history(infos_t *infos);
int read_history(infos_t *infos);
int build_history_list(infos_t *infos, char *buf, int linecount);
int renumber_history(infos_t *infos);

/* toem_list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_list1.c */
size_t list_length(const list_t *);
char **list_to_str(list_t *);
size_t print_lists(const list_t *);
list_t *node_start_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(infos_t *, char *, size_t *);
void check_chain(infos_t *, char *, size_t *, size_t, size_t);
int replace_alias(infos_t *);
int replace_vars(infos_t *);
int replace_string(char **, char *);

#endif


