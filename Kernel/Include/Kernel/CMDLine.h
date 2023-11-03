#pragma once

typedef struct {
    // Set to debug if you want things on the screen to be on the serial port
    // too.
    char *serial;
    // If 1, we're in quiet mode, if 0, nope!
    int quiet;
} CMDLine;

CMDLine getCMDLine();
CMDLine parseCMDLine(char *cmdline);
