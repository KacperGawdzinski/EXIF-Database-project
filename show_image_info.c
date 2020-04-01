#include "header.h"

extern Names *root;
extern ExifData *d;
extern GtkWidget *window;
void change_properties(char *path, labels *label)
{
    ExifLoader *load=exif_loader_new();
    gtk_label_set_text(GTK_LABEL(label->camera_model),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->date_time),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->shutter_speed),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->resolution),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->exposure_time),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->aperture),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->focal_length),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->flash),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->brightness),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->white_balance),"Unknown");
    gtk_label_set_text(GTK_LABEL(label->ISO),"Unknown");

    exif_loader_write_file(load,path);
    d=exif_loader_get_data(load);
    
    if(d)
    {
        char *s=malloc(sizeof(char)*64);
        if((s=check(d,EXIF_TAG_MODEL,s))) { gtk_label_set_text(GTK_LABEL(label->camera_model),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_DATE_TIME,s))) { gtk_label_set_text(GTK_LABEL(label->date_time),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_SHUTTER_SPEED_VALUE,s))) { gtk_label_set_text(GTK_LABEL(label->shutter_speed),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_APERTURE_VALUE,s))) { gtk_label_set_text(GTK_LABEL(label->aperture),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_FOCAL_LENGTH,s))) { gtk_label_set_text(GTK_LABEL(label->focal_length),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_FLASH,s))) { gtk_label_set_text(GTK_LABEL(label->flash),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_BRIGHTNESS_VALUE,s))) { gtk_label_set_text(GTK_LABEL(label->brightness),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_WHITE_BALANCE,s))) { gtk_label_set_text(GTK_LABEL(label->white_balance),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_EXPOSURE_TIME,s))) { gtk_label_set_text(GTK_LABEL(label->exposure_time),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_ISO_SPEED_RATINGS,s))) { gtk_label_set_text(GTK_LABEL(label->ISO),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_PIXEL_X_DIMENSION,s))) { gtk_label_set_text(GTK_LABEL(label->resolution),s);free(s);s=malloc(sizeof(char)*64); }
        if((s=check(d,EXIF_TAG_PIXEL_Y_DIMENSION,s)))
        {
            const char *res=gtk_label_get_text(GTK_LABEL(label->resolution));
            char *p = malloc(strlen(res) + 256);
            strcpy(p, res);
            strcat(p," x ");
            strcat(p,s);
            gtk_label_set_text(GTK_LABEL(label->resolution),p);
            free(s); s=malloc(sizeof(char)*64);
        }
    }
}

void image_filter(GtkComboBox *List, bool writing, const char *text, char *path)
{
    bool guard=0;
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(List))!=0)
    {
        if(root!=NULL)
        {
            Names *start=root;
            char *photo_path,*s,*list = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(List));
            do
            {
                guard=0;
                ExifLoader *load=exif_loader_new();
                photo_path=malloc(sizeof(char)*128), s=NULL;
                if(path==NULL) strcpy(photo_path,"./photos/");
                else strcpy(photo_path,path);
                strcat(photo_path,root->T);
                
                Names *temp=root;
                exif_loader_write_file(load,photo_path);
                d=exif_loader_get_data(load);
                if(strcmp(list,"Camera")==0) s=check(d,EXIF_TAG_MODEL,s);
                if(strcmp(list,"Shutter Speed")==0) s=check(d,EXIF_TAG_SHUTTER_SPEED_VALUE,s);
                if(strcmp(list,"Date/Time")==0) s=check(d,EXIF_TAG_DATE_TIME,s);
                if(strcmp(list,"Focal Length")==0) s=check(d,EXIF_TAG_FOCAL_LENGTH,s);
                if(strcmp(list,"Aperture")==0) s=check(d,EXIF_TAG_APERTURE_VALUE,s);
                if(strcmp(list,"Flash")==0) s=check(d,EXIF_TAG_FLASH,s);
                if(strcmp(list,"Brightness")==0) s=check(d,EXIF_TAG_BRIGHTNESS_VALUE,s);
                if(strcmp(list,"White Balance")==0) s=check(d,EXIF_TAG_WHITE_BALANCE,s);
                if(strcmp(list,"ISO")==0) s=check(d,EXIF_TAG_ISO_SPEED_RATINGS,s);
                if(strcmp(list,"Exposure Time")==0) s=check(d,EXIF_TAG_EXPOSURE_TIME,s);
                if(strcmp(list,"Comment")==0) s=check(d,EXIF_TAG_IMAGE_DESCRIPTION,s);
                if(strcmp(list,"Rating")==0) s=check(d,EXIF_TAG_USER_COMMENT,s);
                if(s!=0 && writing==true)
                {
                    char *p=s, *buf=strdup(text);
                    for (;*p;++p) *p = tolower(*p);
                    for (;*buf;++buf) *buf = tolower(*buf);
                    if(!strstr(s,text)) s=NULL;
                }
                if(s==0)
                {
                    if(temp==start)
                    {
                        if(start->next!=start)
                        {
                            start=start->next; guard=1;
                        }
                    }
                    root->prev->next=root->next;
                    root->next->prev=root->prev;
                    root=root->next;
                    if(root==temp) root=NULL;
                    else free(temp);
                }
                else root=root->next; 
                free(photo_path);
                s=0;
            }
            while((root!=start || guard==1) && root!=NULL);
        }
    }
}