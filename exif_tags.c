#include "header.h"

extern Names *root;
char *extract_tag(ExifData *ed, ExifIfd eid, ExifTag tag, char *s)
{
    char *p=malloc(sizeof(char)*64);
    ExifEntry *entry = exif_content_get_entry(ed->ifd[eid], tag);
    if (entry)
    {
        exif_entry_get_value(entry,p,sizeof(char)*64);
        s=p;
        return s;
    }
    return NULL;
}

char *check(ExifData *d, ExifTag tag, char *s)
{
    if(d){
    s=extract_tag(d, EXIF_IFD_0, tag, s);
    if(!s) {s=malloc(sizeof(char)*64);s=extract_tag(d, EXIF_IFD_1, tag, s);}
    if(!s) {s=malloc(sizeof(char)*64);s=extract_tag(d, EXIF_IFD_EXIF, tag, s);}
    if(!s) {s=malloc(sizeof(char)*64);s=extract_tag(d, EXIF_IFD_GPS, tag, s);}
    if(!s) {s=malloc(sizeof(char)*64);s=extract_tag(d, EXIF_IFD_INTEROPERABILITY, tag, s);}}
    if(s) return s;
    return 0;
}

void add_new_comment(GtkButton *b, gpointer x)
{
    (void)b;
    New_tags *y=x;
    char *folder=getenv("PWD");
    if(y->arg==NULL) chdir("./photos/");
    else chdir(y->arg);
    char *exif_comm=malloc(sizeof(char)*128);
    const char *text=gtk_entry_get_text(GTK_ENTRY(y->entry[0]));
    strcpy(exif_comm,"exiftool -imagedescription='");
    if(strcmp(text,"")!=0)
    {
        strcat(exif_comm,text);
        strcat(exif_comm,"' ");
        strcat(exif_comm,root->T);
        int status = system(exif_comm);
        status = system("rm *.jpg_original");
        (void)status;
    }
    if(y->arg==NULL) chdir("..");
    else chdir(folder);
}

void add_new_rating(GtkButton *b, gpointer x)
{
    (void)b;
    New_tags *y=x;
    char *folder=getenv("PWD");
    if(y->arg==NULL) chdir("./photos/");
    else chdir(y->arg);
    char *exif_comm=malloc(sizeof(char)*128);
    const char *text=gtk_entry_get_text(GTK_ENTRY(y->entry[1]));
    strcpy(exif_comm,"exiftool -usercomment='");
    if(strcmp(text,"")!=0)
    {
        strcat(exif_comm,text);
        strcat(exif_comm,"' ");
        strcat(exif_comm,root->T);
        int status = system(exif_comm);
        status = system("rm *.jpg_original");
        (void)status;
    }
    if(y->arg==NULL) chdir("..");
    else chdir(folder);
}