#include "header.h"

extern Names *root;
extern GtkWidget *window;
void open_dialog(GtkWidget *b, gpointer x)
{
    (void)b;
    labels *label=x;
    if(label->T[0]==false) {gtk_widget_destroy(label->photo); label->T[0]=true; }
    bool test=true, extension=true;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(window),action,"Cancel",GTK_RESPONSE_CANCEL,"Open",GTK_RESPONSE_ACCEPT,NULL);
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        int k=0, l=0;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);

        char *temp=filename;
        char *just_name=filename;
        FILE *inFile, *outFile;
        inFile = fopen(filename, "rb");
        while(*filename!='\0')
        {
            if(*filename=='/') {k++;}
            filename++;
        }
        while(*temp!='\0')
        {
            if(*temp=='/') {l++;}
            temp++; just_name++;
            if(l==k) {break;}
        }
        while(*just_name!='.') { just_name++;}
        just_name++;
        if(*just_name!='j') {extension=false;}
        just_name++;
        if(*just_name!='p') {extension=false;}
        just_name++;
        if(*just_name!='g' && *just_name!='e') {extension=false;}
        just_name++;
        if(*just_name!='g' && *just_name!='\0') {extension=false;}

        if(extension==true)
        {
            char *folder=getenv("PWD");
            if(label->arg==NULL) chdir("./photos/");
            else chdir(label->arg);
            outFile = fopen(temp, "wb");

            size_t bufferLength = get_file_size(inFile);
            uint8_t *buffer = malloc(bufferLength);

            fread(buffer, bufferLength, 1, inFile);
            fwrite(buffer, bufferLength, 1, outFile);
            fclose(inFile);
            fclose(outFile);
            if(label->arg==NULL) chdir("..");
            else chdir(folder);

            if(root!=NULL)
            {
                Names *start=root->next;
                while(start!=root)
                {
                    if(strcmp(start->T,temp)==0) {test=false;}
                    start=start->next;
                }
                if(strcmp(start->T,temp)==0) {test=false;}
                start=start->next;
            }
            if(test)
            {
                if(root!=NULL)
                {
                    Names *add;
                    add=malloc(sizeof(Names));
                    add->T=malloc(sizeof(char)*64);
                    strcpy(add->T,temp);
                    root->prev->next=add;
                    add->prev=root->prev;
                    add->next=root;
                    root->prev=add;
                }
                else
                {
                    root=malloc(sizeof(Names));
                    root->T=malloc(sizeof(char)*64);
                    strcpy(root->T,temp);
                    root->next=root;
                    root->prev=root;
                }
            }
            show_info();
        }
        else { fclose(inFile); show_error();}
    }
    gtk_widget_destroy (dialog);
}

void remove_photo(GtkButton *b, gpointer x)
{
    (void)b;
    labels *label=x;
    gtk_label_set_text(GTK_LABEL(label->info),"Press any arrow to begin!");
    if(label->T[0]==false) {gtk_widget_destroy(label->photo); label->T[0]=true; }
    char *filename;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    dialog = gtk_file_chooser_dialog_new ("Open File",GTK_WINDOW(window),action,"Cancel",GTK_RESPONSE_CANCEL,"Open",GTK_RESPONSE_ACCEPT,NULL);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        remove(filename);
        show_remove_info();
        char *temp=filename;
        int k=0, l=0;
        bool waiter=true;
        while(*filename!='\0')
        {
            if(*filename=='/') {k++;}
            filename++;
        }
        while(*temp!='\0')
        {
            if(*temp=='/') {l++;}
            temp++;
            if(l==k) {break;}
        }

        Names *start=root;
        char *folder=getenv("PWD");
        if(label->arg==NULL) chdir("./photos/");
        else chdir(label->arg);
        while(strcmp(start->T,temp)!=0)
        {
            start=start->next;
            if(start==root) { waiter=false;break;}
        }
        if(waiter==true)
        {
            start->prev->next=start->next;
            start->next->prev=start->prev;
            if(start==root)
            {
                if(root->prev!=root) {root=root->prev; free(start);}
                else root=NULL;
            }
        }
        if(label->arg==NULL) chdir("..");
        else chdir(folder);
    }
    gtk_widget_destroy (dialog);
}