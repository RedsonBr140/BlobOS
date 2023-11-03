#include <Kernel/CMDLine.h>
#include <LibK/string.h>

CMDLine global_cmdline;

CMDLine getCMDLine() { return global_cmdline; }

// Function to parse the command line
CMDLine parseCMDLine(char *cmdline) {
    // Initialize the global_cmdline structure
    global_cmdline.quiet = 0;
    global_cmdline.serial = NULL;

    // If we don't get any arguments, return the empty cmdline
    if (strlen(cmdline) == 0) {
        return global_cmdline;
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
            if (strcmp(name, "serial")) {
                global_cmdline.serial = value;
            }
        } else {
            // FIXME: There's something wrong here...
            // If there's no '=', it's just a parameter without a value
            if (strcmp(token, "quiet")) {
                global_cmdline.quiet = 1; // Set a default value
            }
        }

        token = strtok(NULL, " ");
    }

    // If after all of this we still have cmdlines to be NULL, set a default
    // value.
    if (strcmp(global_cmdline.serial, "")) {
        global_cmdline.serial = "no";
    }

    return global_cmdline;
}
