char *templariPath;

int getPathState(char *path) {
    struct stat st = {0};
    return stat(path, &st);
}

char *getTemplariPath() {
    char *path = malloc(sizeof(char) * 255);
    sprintf(path, "%s/.config/templari", getenv("HOME"));
    mkdir(path, 0755);

    if (getPathState(path) != 0) {
        printf("Templari path not found at %s\n", path);
        path = "";
    }

    return path;
}

void removeTrailingNewLine(char *input) {
    if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n'))
        input[strlen (input) - 1] = '\0';
}

void removeTrailingSlash(char *input) {
    if ((strlen(input) > 0) && (input[strlen (input) - 1] == '/'))
        input[strlen (input) - 1] = '\0';
}

char* pickFile() {
    FILE* fp;
    char* path = malloc(sizeof(char) * 1024);
    char fzfCommand[200];

    sprintf(
        fzfCommand,
        "ls -1N %s | fzf",
        templariPath
    );

    fp = popen(fzfCommand, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return "";
    }

    while (fgets(path, 1024 * sizeof(char), fp) != NULL) {
    }

    pclose(fp);

    if(strcmp(path, "") == 0) {
        printf("Nothing selected.\n");
        return "";
    }

    removeTrailingNewLine(path);
    removeTrailingSlash(path);

    char* r = malloc(sizeof(char)*1024);
    sprintf(r, "%s/%s", templariPath, path);
    return r;
}
