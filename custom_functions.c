#include "header.h"

long int get_file_size(FILE *file) 
{
    long curPos, endPos;
    curPos = ftell(file);
    fseek(file, 0, 2);
    endPos = ftell(file);
    fseek(file, curPos, 0);
    return endPos;
}

char *strdup(const char *p)
{
    char *np=(char*)malloc(strlen(p)+1);
    return np ? strcpy(np, p) : np;
}

int getScreenSize(int *w, int *h)
{
    Display* pdsp = NULL;
    Screen* pscr = NULL;
    pdsp = XOpenDisplay(NULL);
    if (!pdsp) return -1;
    pscr = DefaultScreenOfDisplay(pdsp);
    if (!pscr) return -2;

    *w = pscr->width;
    *h = pscr->height;

    XCloseDisplay(pdsp);
    return 0;
}

