#include <Kernel/CMDLine.h>
#include <LibK/string.h>

/*
 * FIXME: We need a memory allocator for being able to store this in memory in a
 * safe way.
 */
CMDLine *g_cmdline = NULL;

CMDLine *getCMDLine() { return g_cmdline; }

// Function to parse the command line
CMDLine *parseCMDLine(char *cmdline) {
    CMDLine l_cmdline = {.quiet = 0, .serial = "no"};
    g_cmdline = &l_cmdline;

    // If we don't get any arguments, return the empty cmdline
    if (strlen(cmdline) == 0) {
        return g_cmdline;
    }

    // Tokenize the cmdline based on spaces
    char *token = strtok(cmdline, " ");

    while (token != NULL) {
        // Check if the token contains '='
        char *equal_sign = strchr(token, '=');

        if (equal_sign != NULL) {
            // Split the token into name and value
            char *name = token;
            char *value = equal_sign + 1;

            // Check the name and store the value accordingly
            if (strcmp(name, "serial") == 0) {
                /*
                 * FIXME: It's not safe to write a string literal to a pointer.
                 We shall implement functions for that as well.
                */
                // g_cmdline->serial = value;
            }
        } else {
            // If there's no '=', it's just a parameter without a value
            if (strcmp(token, "quiet") == 0) {
                g_cmdline->quiet = 1; // Set a default value
            }
        }
    }

    return g_cmdline;
}
