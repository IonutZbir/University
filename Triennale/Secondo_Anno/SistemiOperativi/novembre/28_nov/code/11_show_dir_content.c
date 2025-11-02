#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void printFileInfo(const char *dirName, const char *fileName) {
    struct stat fileInfo;
    char filePath[1024];
    // concatena all'interno di filePath, dirName e fileName:
    // filePath = dirName + fileName
    snprintf(filePath, sizeof(filePath), "%s/%s", dirName, fileName);

    // /code, 11_show_dir_content.c

    // /code/11_show_dir_content.c

    // memorizza all'interno della struct fileInfo tutti gli attributi relativi al file
    if (stat(filePath, &fileInfo) < 0) {
        perror("Errore nel recupero delle informazioni del file");
        return;
    }

    printf("%ld ", fileInfo.st_size); // Dimensione del file

    // Permessi del file
    printf((S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
    // user permission
    printf((fileInfo.st_mode & S_IRUSR) ? "r" : "-"); // IRUSR -> user read only
    printf((fileInfo.st_mode & S_IWUSR) ? "w"
                                        : "-");       // IWUSR -> user write only
    printf((fileInfo.st_mode & S_IXUSR) ? "x" : "-"); // IXUSR -> user exec only
    // group permission
    printf((fileInfo.st_mode & S_IRGRP) ? "r"
                                        : "-"); // IRGRP -> group read only
    printf((fileInfo.st_mode & S_IWGRP) ? "w"
                                        : "-"); // IWGRP -> group write only
    printf((fileInfo.st_mode & S_IXGRP) ? "x"
                                        : "-"); // IXGRP -> group exec only
    // other permission
    printf((fileInfo.st_mode & S_IROTH) ? "r"
                                        : "-"); // IROTH -> other read only
    printf((fileInfo.st_mode & S_IWOTH) ? "w"
                                        : "-"); // IWOTH -> other write only
    printf((fileInfo.st_mode & S_IXOTH) ? "x"
                                        : "-"); // IXOTH -> other exec only

    printf("\n ---------------- \n");

    printf("[INFO] %d -> %08b, %b \n", fileInfo.st_mode, fileInfo.st_mode, S_ISDIR(fileInfo.st_mode));
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IRUSR, S_IRUSR);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IWUSR, S_IWUSR);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IXUSR, S_IXUSR);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IRGRP, S_IRGRP);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IWGRP, S_IWGRP);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IXGRP, S_IXGRP);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IROTH, S_IROTH);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IWOTH, S_IWOTH);
    printf("[INFO] %d -> %08b AND %03d -> %09b \n", fileInfo.st_mode, fileInfo.st_mode, S_IXOTH, S_IXOTH);

    printf("\n ---------------- \n");

    // Proprietario e gruppo
    struct passwd *pw = getpwuid(fileInfo.st_uid);
    struct group *gr = getgrgid(fileInfo.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    // Data di ultima modifica
    char dateStr[128];
    strftime(dateStr, sizeof(dateStr), "%B %D %H:%M", localtime(&fileInfo.st_mtime));
    printf(" %s", dateStr);

    // Nome del file
    printf(" %s\n", fileName);
    printf("################################\n");
}

int main(int argc, char *argv[]) {
    DIR *dirp;             // puntatore alla directory che deve essere aperta
    struct dirent *dirent; // punatore ad un singolo elemento della directory

    if (argc != 2) {
        fprintf(stderr, "Errore: manca inputfile. Uso: %s <directory>\n", argv[0]);
        return 1;
    }

    dirp = opendir(argv[1]);
    if (dirp == NULL) {
        perror("Errore nell'apertura della directory");
        return 1;
    }

    dirent = readdir(dirp);
    // leggo il primo elemento all'interno della directory
    while (dirent != NULL) {
        // affinche ci sono ancora elementi dentro la directory
        printFileInfo(argv[1], dirent->d_name);
        // leggo le informazioni dell'elemento

        // corrente (sia file che directory)
        dirent = readdir(dirp);
        // leggo il prossimo elemento
    }

    closedir(dirp); // chiudo la directory
    return 0;
}
