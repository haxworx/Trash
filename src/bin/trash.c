//
// Created by Alastair Poole on 26/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

int main(int argc, char *argv[])
{
    char buffer[PATH_MAX * 2] = { 0 };
    if (argc < 2) {
        printf("Usage: trash <filename, ...>\n");
        return EXIT_FAILURE;
    }

    snprintf(buffer, sizeof(buffer), "mv");
    for (int i = 1; i < argc; i++) {
        strlcat(buffer, " ", sizeof(buffer));
        snprintf(buffer, sizeof(buffer), "%s%s", buffer, argv[i]);
    }

#if defined(__APPLE__) && defined(__MACH__)
    const char *home = getenv("HOME");
    snprintf(buffer, sizeof(buffer), "%s %s/.Trash", buffer, home);
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__)

#endif
    return !!system(buffer);
}