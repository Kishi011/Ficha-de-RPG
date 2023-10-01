#define ARQLOG "log.txt"
#include <time.h>
#ifndef ARQLOGIN
    #include <stdio.h>
#else
    #ifndef ARQFICHA
        #include <stdio.h>
    #endif
#endif

void gravaLog(FILE*, char[]);

void gravaLog(FILE* arq, char msg[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    arq = fopen(ARQLOG, "a");
    fprintf(arq, "%s [%d-%02d-%02d %02d:%02d:%02d]\n", msg, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(arq);
}