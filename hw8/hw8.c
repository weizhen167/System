#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>


#define MAXLINE 200  /* This is how we declare constants in C */
#define MAXARGS 20
int z = 0;

/* In C, "static" means not visible outside of file.  This is different
* from the usage of "static" in Java.
* Note that end_ptr is an output parameter.
*/
static char * getword(char * begin, char **end_ptr) {
	char * end = begin;

	while (*begin == ' ')
		begin++;  /* Get rid of leading spaces. */
	end = begin;
	while (*end != '\0' && *end != '\n' && *end != ' ')
		end++;  /* Keep going. */
	if (end == begin)
		return NULL;  /* if no more words, return NULL */
	*end = '\0';  /* else put string terminator at end of this word. */
	*end_ptr = end;
	if (begin[0] == '%') { /* if this is a variable to be expanded */
		begin = getenv(begin + 1); /* begin+1, to skip past '$' */
		if (begin == NULL) {
			perror("getenv");
			begin = "UNDEFINED";
		}
	}
	return begin; /* This word is now a null-terminated string.  return it. */
}

/* In C, "int" is used instead of "bool", and "0" means false, any
* non-zero number (traditionally "1") means true.
*/
/* argc is _count_ of args (*argcp == argc); argv is array of arg _values_*/
static void getargs(char cmd[], int *argcp, char *argv[])
{
	char *cmdp = cmd;
	char *end;
	int i = 0;

	/* fgets creates null-terminated string. stdin is pre-defined C constant
	*   for standard intput.  feof(stdin) tests for file:end-of-file.
	*/
	if (fgets(cmd, MAXLINE, stdin) == NULL && feof(stdin)) {
		printf("Couldn't read from standard input. End of file? Exiting ...\n");
		exit(1);  /* any non-zero value for exit means failure. */
	}

	while ((cmdp = getword(cmdp, &end)) != NULL && *cmdp != '#'){
		if (*cmdp == '>') {
			cmdp = end + 1;
			cmdp = getword(cmdp, &end);
			freopen(cmdp, "w", stdout);
		}
		else if (*cmdp == '>') {
			cmdp = end + 1;
			cmdp = getword(cmdp, &end);
			freopen(cmdp, "r", stdin);
		}
		else if (*cmdp == '|') {
			z = 1;
		}
		else if (*cmdp == '&') {
			z = 2;
		}
		argv[i++] = cmdp;
		cmdp = end + 1;
	}
	argv[i] = NULL;
	*argcp = i;
}

static void execute(int argc, char *argv[])
{

	pid_t childpid; /* child process ID */
	int pfd[2];
	char *argvChildpid[2];
	int i = 0;

	if (pipe(pfd) == -1) { perror("pipe"); exit(1); }

	if (z == 1) {
		mypipe(argv[0], argv[2]);
		z = 0;
	}

	else if (z == 2) {
		if (!fork()) {
			argvChildpid[0] = argv[0];
			argvChildpid[1] = NULL;
			execvp(argv[0], argvChildpid);
		}
		z = 0;
	}

	else {
		childpid = fork();
		if (childpid == -1) { /* in parent (returned error) */
			perror("fork"); /* perror => print error string of last system call */
			printf("  (failed to execute command)\n");
		}
		if (childpid == 0) { /* child:  in child, childpid was set to 0 */
			/* Executes command in argv[0];  It searches for that file in
			*  the directories specified by the environment variable PATH.
			*/
			if (-1 == execvp(argv[0], argv)) {
				perror("execvp");
				printf("  (couldn't find command)\n");
			}
			/* NOT REACHED unless error occurred */
			exit(1);
		}
		else
			waitpid(childpid, NULL, 0);  /* wait until child process finishes */
		return;
	}
}

void interrupt_handler(int signum){
}


int main(int argc, char *argv[])
{
	char cmd[MAXLINE];
	char *childargv[MAXARGS];
	int childargc;
	signal(SIGINT, interrupt_handler);


	if (argc > 1) freopen(argv[1], "r", stdin);
	while (1) {
		freopen("/dev/tty", "r", stdin);
		freopen("/dev/tty", "w", stdout);
		printf("%% "); /* pri ntf uses %d, %s, %x, etc.  See 'man 3 printf' */
		fflush(stdout); /* flush from output buffer to terminal itself */
		getargs(cmd, &childargc, childargv); /* childargc and childargv are
											 output args; on input they have garbage, but getargs sets them. */
		/* Check first for built-in commands. */
		if (childargc > 0 && strcmp(childargv[0], "exit") == 0)
			exit(0);
		if (childargc > 0 && strcmp(childargv[0], "logout") == 0)
			exit(0);
		else
			execute(childargc, childargv);
	}
}

int mypipe(char* s1, char* s2) {
	int pipe_fd[2];
	int fd;
	pid_t child1, child2;
	char * argvChild[2];

	fflush(stdout);

	if (-1 == pipe(pipe_fd)) perror("pipe");
	child1 = fork();

	if (child1 > 0) child2 = fork();
	if (child1 == 0) {
		if (-1 == close(1)) perror("close");
		fd = dup(pipe_fd[1]);
		if (-1 == fd) perror("dup");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		argvChild[0] = s1;
		argvChild[1] = NULL;
		if (-1 == execvp(argvChild[0], argvChild)) perror("execvp");
	}
	else if (child2 == 0) {
		if (-1 == close(0)) perror("close");
		fd = dup(pipe_fd[0]);
		if (-1 == fd) perror("dup");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		argvChild[0] = s2;
		argvChild[1] = NULL;
		if (-1 == execvp(argvChild[0], argvChild)) perror("execvp");
	}
	else {
		int status;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (-1 == waitpid(child1, &status, 0)) perror("waitpid");
		if (WIFEXITED(status) == 0)
			printf("child1 returned w/ error code %d\n", WEXITSTATUS(status));
		if (-1 == waitpid(child2, &status, 0)) perror("waitpid");
		if (WIFEXITED(status) == 0)
			printf("child2 returned w/ error code %d\n", WEXITSTATUS(status));
	}
	return 0;
}
