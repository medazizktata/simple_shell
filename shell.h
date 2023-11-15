#ifndef SHELL_H
#define SHELL_H

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

/* for read/write buffers */
/*Read buffer*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
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
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hshsh(info_t *, char **);
int find_builting(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* path.c */
int is_command(info_t *, char *);
char *dupp_chars(char *, int, int);
char *find_path_(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs_(char *);
int _eputchar_(char);
int _putfd_(char c, int fd);
int _putsfd_(char *str, int fd);

/* string_functions.c */
int _strlen_(char *);
int _strcmp_(char *, char *);
char *tebda_with(const char *, const char *);
char *_strcat_(char *, char *);

/* string_functions2.c */
char *_strcpy_(char *, char *);
char *_strdup_(const char *);
void _puts_(char *);
int _putchar_(char);

/* string_functions3.c */
char *_strncpy_(char *, char *, int);
char *_strncat_(char *, char *, int);
char *_strchr_(char *, char);

/* string_functions4.c */
char **strtoww(char *, char *);
char **strtoww22(char *, char);

/* memory_functions */
char *_memset_(char *, char, unsigned int);
void fffree(char **);
void *_realloc_(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfreee(void **);

/* more_functions.c */
int interactif(info_t *);
int is_delim_(char, char *);
int _isalpha_(int);
int _atoi_(char *);

/* more_functions2.c */
int _erratoi_(char *);
void print_8alta(info_t *, char *);
int print_ddd(int, int);
char *convert_nombre(long int, int, int);
void remove_cmnts(char *);

/* builtin_emulators.c */
int _myexit_(info_t *);
int _mycd_(info_t *);
int _myhelp_(info_t *);

/* builtin_emulators2.c */
int _myhistory_(info_t *);
int _myaliaas_(info_t *);

/* getline.c module */
ssize_t get_3input(info_t *);
int _getline_(info_t *, char **, size_t *);
void sigint3Handler(int);

/* info.c module */
void clear_information(info_t *);
void set_information(info_t *, char **);
void free_information(info_t *, int);

/* env.c module */
char *_getenv_(info_t *, const char *);
int _myenv_(info_t *);
int _mysetenv_(info_t *);
int _myunsetenv_(info_t *);
int populate_env_lista(info_t *);

/* env2.c module */
char **get_environment(info_t *);
int _unsetenv_(info_t *, char *);
int _setenv_(info_t *, char *, char *);

/* file_io_functions.c */
char *get_histoire_fichier(info_t *info);
int write_histoire(info_t *info);
int read_histoire(info_t *info);
int build_histoire_list(info_t *info, char *buf, int linecount);
int renumber_histoire(info_t *info);

/* liststr.c module */
list_t *add_noda(list_t **, const char *, int);
list_t *add_noda_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_node_at_ind(list_t **, unsigned int);
void free_lista(list_t **);

/* liststr2.c module */
size_t list_length(const list_t *);
char **lista_to_strings(list_t *);
size_t print_lista(const list_t *);
list_t *node_yebda_with(list_t *, char *, char);
ssize_t get_node_ind(list_t *, list_t *);

/* chain.c */
int is_chaiin(info_t *, char *, size_t *);
void check_chaiin(info_t *, char *, size_t *, size_t, size_t);
int replace_aliaas(info_t *);
int replace_varss(info_t *);
int replace_str(char **, char *);

#endif
