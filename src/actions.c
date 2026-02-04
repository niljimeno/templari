int openTemplate() {
    char *path = pickFile();
    if (strcmp(path, "") == 0)
        return 1;

    char command[1024];
    sprintf(command, "cp -r \"%s\"/* ./", path);
    printf("%s\n", command);

    system(command);
    return 0;
}

int removeTemplate() {
    char *path = pickFile();
    if (strcmp(path, "") == 0)
        return 1;

    char command[1024];
    sprintf(command, "rm -rf \"%s\"", path);
    printf("%s\n", command);

    system(command);
    return 0;
}

int displayHelp() {
    printf("\n======= Templari (beta) =======\n");
    printf("- templari: open template picker\n");
    printf("- templari -h: open help\n");
    printf("- templari <path>: create template from path\n");
    printf("::templates location: %s\n\n", templariPath);

    return 0;
}

int createTemplate(char *path) {
    removeTrailingSlash(path);

    struct stat st = {0};

    if (stat(path, &st) != 0) {
        printf("Failed to create template from %s\n", path);
        path = "";
        return 1;
    }

    char *templateName = malloc(sizeof(char) * 255);
    printf("Template name: ");

    fgets(templateName, 255, stdin);
    removeTrailingNewLine(templateName);
    removeTrailingSlash(templateName);

    printf("%s\n", templateName);
    printf("%s\n", path);

    char *command = malloc(sizeof(char) * 255);

    sprintf(command, "mkdir %s/\"%s\"", templariPath, templateName);
    system(command);

    if (S_ISDIR(st.st_mode))
        sprintf(command, "cp -r \"%s\"/* %s/\"%s\"/", path, templariPath, templateName);
    else
        sprintf(command, "cp -r \"%s\" %s/\"%s\"/", path, templariPath, templateName);

    printf("%s\n", command);
    system(command);

    /* remove .git */
    sprintf(command, "rm -rf %s/\"%s\"/.git", templariPath, templateName);



    return 0;
}
