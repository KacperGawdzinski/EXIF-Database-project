#include "header.h"

extern Names *root;
Names *new(Names *actual)
{
    Names *another;
    another=malloc(sizeof(Names));
    another->T=malloc(sizeof(char)*64);
    actual->next=another;
    another->prev=actual;
    return another;
}

void build_list(char *arg)
{
    Names *start;
    bool guard=false;
    struct dirent *de;
    DIR *dr;
    if(arg!=NULL) dr=opendir(arg);
    else dr = opendir("photos");
    if (dr==NULL)
    { 
        printf("Could not open current directory\n");
    }
    else
    {
        de = readdir(dr);
        while (de != NULL) 
        {
            if(strstr(de->d_name,".jpg"))
            {
                if(guard==false)
                {
                    guard=true;
                    root=malloc(sizeof(Names));
                    root->T=malloc(sizeof(char)*64);
                    strcpy(root->T,de->d_name);
                    start=root;
                }
                else
                {
                    root=new(root);
                    strcpy(root->T,de->d_name);
                }
            }
            de = readdir(dr);
        }
        if(guard==true)
        {
            root->next=start;
            start->prev=root;
            root=root->next;
        }
    }
    free(dr);
}