#include <stdio.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libcli.h"

// vim:sw=4 tw=120 et

#define CLITEST_PORT                8000
#define MODE_CONFIG_INT             10

#ifdef __GNUC__
# define UNUSED(d) d __attribute__ ((unused))
#else
# define UNUSED(d) d
#endif

unsigned int regular_count = 0;
unsigned int debug_regular = 0;

struct my_context {
  int value;
  char* message;
};

#ifdef WIN32
typedef int socklen_t;

int winsock_init()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    // Start up sockets
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable WinSock DLL.
        return 0;
    }

    /*
     * Confirm that the WinSock DLL supports 2.2
     * Note that if the DLL supports versions greater than 2.2 in addition to
     * 2.2, it will still return 2.2 in wVersion since that is the version we
     * requested.
     * */
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        // Tell the user that we could not find a usable WinSock DLL.
        WSACleanup();
        return 0;
    }
    return 1;
}
#endif

int cmd_test(struct cli_def *cli, const char *command, char *argv[], int argc)
{
    int i;
    cli_print(cli, "called %s with \"%s\"", __func__, command);
    cli_print(cli, "%d arguments:", argc);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

    return CLI_OK;
}

int cmd_set(struct cli_def *cli, UNUSED(const char *command), char *argv[],
    int argc)
{
    if (argc < 2 || strcmp(argv[0], "?") == 0)
    {
        cli_print(cli, "Specify a variable to set");
        return CLI_OK;
    }

    if (strcmp(argv[1], "?") == 0)
    {
        cli_print(cli, "Specify a value");
        return CLI_OK;
    }

    if (strcmp(argv[0], "regular_interval") == 0)
    {
        unsigned int sec = 0;
        if (!argv[1] && !&argv[1])
        {
            cli_print(cli, "Specify a regular callback interval in seconds");
            return CLI_OK;
        }
        sscanf(argv[1], "%u", &sec);
        if (sec < 1)
        {
            cli_print(cli, "Specify a regular callback interval in seconds");
            return CLI_OK;
        }
        cli->timeout_tm.tv_sec = sec;
        cli->timeout_tm.tv_usec = 0;
        cli_print(cli, "Regular callback interval is now %d seconds", sec);
        return CLI_OK;
    }

    cli_print(cli, "Setting \"%s\" to \"%s\"", argv[0], argv[1]);
    return CLI_OK;
}

int cmd_config_int(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    if (argc < 1)
    {
        cli_print(cli, "Specify an interface to configure");
        return CLI_OK;
    }

    if (strcmp(argv[0], "?") == 0)
        cli_print(cli, "  test0/0");

    else if (strcasecmp(argv[0], "test0/0") == 0)
        cli_set_configmode(cli, MODE_CONFIG_INT, "test");
    else
        cli_print(cli, "Unknown interface %s", argv[0]);

    return CLI_OK;
}

int cmd_config_int_exit(struct cli_def *cli, UNUSED(const char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    cli_set_configmode(cli, MODE_CONFIG, NULL);
    return CLI_OK;
}

int cmd_show_regular(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(cli, "cli_regular() has run %u times", regular_count);
    return CLI_OK;
}

int cmd_debug_regular(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    debug_regular = !debug_regular;
    cli_print(cli, "cli_regular() debugging is %s", debug_regular ? "enabled" : "disabled");
    return CLI_OK;
}

int cmd_context(struct cli_def *cli, UNUSED(const char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    struct my_context *myctx = (struct my_context *)cli_get_context(cli);
    cli_print(cli, "User context has a value of %d and message saying %s", myctx->value, myctx->message);
    return CLI_OK;
}

int check_auth(const char *username, const char *password)
{
    if (strcasecmp(username, "fred") != 0)
        return CLI_ERROR;
    if (strcasecmp(password, "nerk") != 0)
        return CLI_ERROR;
    return CLI_OK;
}

int regular_callback(struct cli_def *cli)
{
    regular_count++;
    if (debug_regular)
    {
        cli_print(cli, "Regular callback - %u times so far", regular_count);
        cli_reprompt(cli);
    }
    return CLI_OK;
}

int check_enable(const char *password)
{
    return !strcasecmp(password, "topsecret");
}

int idle_timeout(struct cli_def *cli)
{
    cli_print(cli, "Custom idle timeout");
    return CLI_QUIT;
}

void pc(UNUSED(struct cli_def *cli), const char *string)
{
    printf("%s\n", string);
}

int main()
{
    struct cli_def *cli;
    struct cli_command cmd_test_s = {(char *) "test", cmd_test, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_simple_s = {(char *) "simple", NULL, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_simon_s = {(char *) "simon", NULL, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_set_s = {(char *) "set", NULL, 0, NULL, PRIVILEGE_PRIVILEGED, MODE_EXEC, NULL, NULL, NULL};

    struct cli_command cmd_show_s = {(char *) "show", NULL, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_show_regular_s = {(char *) "regular", cmd_show_regular, 0,
					     (char *) "Show the how many times cli_regular has run",
					     PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_show_counters_s = {(char *) "counters", cmd_test, 0,
					      (char *) "Show the counters that the system uses",
					      PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_show_junk_s = {(char *) "junk", cmd_test, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};

    struct cli_command cmd_config_int_s = {(char *) "interface", cmd_config_int, 0,
					   (char *) "Configure an interface",
					   PRIVILEGE_PRIVILEGED, MODE_CONFIG, NULL, NULL, NULL};
    struct cli_command cmd_config_int_exit_s = {(char *) "exit", cmd_config_int_exit, 0,
						(char *) "Exit from interface configuration",
						PRIVILEGE_PRIVILEGED, MODE_CONFIG_INT, NULL, NULL, NULL};
    struct cli_command cmd_config_int_address_s = {(char *) "address", cmd_test, 0,
						   (char *) "Set IP address",
						   PRIVILEGE_PRIVILEGED, MODE_CONFIG_INT, NULL, NULL, NULL};
    struct cli_command cmd_debug_s = {(char *) "debug", NULL, 0, NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_debug_regular_s = {(char *) "regular", cmd_debug_regular, 0,
					      (char *) "Enable cli_regular() callback debugging",
					      PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};
    struct cli_command cmd_context_s = {(char *) "context", cmd_context, 0,
					(char *) "Test a user-specified context",
					PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL, NULL, NULL};


    int s, x;
    struct sockaddr_in addr;
    int on = 1;

#ifndef WIN32
    signal(SIGCHLD, SIG_IGN);
#endif
#ifdef WIN32
    if (!winsock_init()) {
        printf("Error initialising winsock\n");
        return 1;
    }
#endif

    // Prepare a small user context
    static char mymessage[] = "I contain user data!";
    static char banner[] = "libcli test environment";
    static char hostname[] = "router";
    struct my_context myctx;
    myctx.value = 5;
    myctx.message = mymessage;

    if (!(cli = calloc(sizeof(struct cli_def), 1)))
        return 0;

    if (! cli_init(cli)) {
        printf("Error initialising CLI\n");
        return 1;
    }
    cli_set_banner(cli, banner);
    cli_set_hostname(cli, hostname);
    cli_telnet_protocol(cli, 1);
    //cli_regular(cli, regular_callback);
    //cli_regular_interval(cli, 5); // Defaults to 1 second
    cli_set_idle_timeout_callback(cli, 60, idle_timeout); // 60 second idle timeout
    cli_register_command2(cli, &cmd_test_s, NULL);
    cli_register_command2(cli, &cmd_simple_s, NULL);
    cli_register_command2(cli, &cmd_simon_s, NULL);
    cli_register_command2(cli, &cmd_set_s, NULL);

    cli_register_command2(cli, &cmd_show_s, NULL);
    cli_register_command2(cli, &cmd_show_regular_s, &cmd_show_s);
    cli_register_command2(cli, &cmd_show_counters_s, &cmd_show_s);
    cli_register_command2(cli, &cmd_show_junk_s, &cmd_show_s);

    cli_register_command2(cli, &cmd_config_int_s, NULL);
    cli_register_command2(cli, &cmd_config_int_exit_s, NULL);
    cli_register_command2(cli, &cmd_config_int_address_s, NULL);

    cli_register_command2(cli, &cmd_debug_s, NULL);
    cli_register_command2(cli, &cmd_debug_regular_s, &cmd_debug_s);

    // Set user context and its command
    cli_set_context(cli, (void*)&myctx);
    cli_register_command2(cli, &cmd_context_s, NULL);

    cli_set_auth_callback(cli, check_auth);
    cli_set_enable_callback(cli, check_enable);
    // Test reading from a file
    /*
    {
        FILE *fh;

        if ((fh = fopen("clitest.txt", "r")))
        {
            // This sets a callback which just displays the cli_print() text to stdout
            cli_print_callback(cli, pc);
            cli_file(cli, fh, PRIVILEGE_UNPRIVILEGED, MODE_EXEC);
            cli_print_callback(cli, NULL);
            fclose(fh);
        }
    }
    */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(CLITEST_PORT);
    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(s, 50) < 0)
    {
        perror("listen");
        return 1;
    }

    printf("Listening on port %d\n", CLITEST_PORT);
    while ((x = accept(s, NULL, 0)))
    {
#ifndef WIN32
        int pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return 1;
        }

        /* parent */
        if (pid > 0)
        {
            socklen_t len = sizeof(addr);
            if (getpeername(x, (struct sockaddr *) &addr, &len) >= 0)
                printf(" * accepted connection from %s\n", inet_ntoa(addr.sin_addr));

            close(x);
            continue;
        }

        /* child */
        close(s);
        cli_loop(cli, x);
        exit(0);
#else
        cli_loop(cli, x);
        shutdown(x, SD_BOTH);
        close(x);
#endif
    }

    cli_done(cli);
    return 0;
}