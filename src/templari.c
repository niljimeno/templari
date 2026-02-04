#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "core.c"
#include "actions.c"

int setup() {
    templariPath = getTemplariPath();
    if (!strcmp(templariPath, "")) {
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (setup() != 0) return -1;

    if (argc == 1)
        return openTemplate();

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        return displayHelp();
    if (!strcmp(argv[1], "remove"))
        return removeTemplate();

    return createTemplate(argv[1]);
}
