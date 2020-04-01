#include "header.h"

extern Names *root;
extern GtkWidget *window;
void on_button1_clicked(GtkButton *b, gpointer x)
{
    (void)b;
    labels *label=x;
    gtk_label_set_text(GTK_LABEL(label->info),"");
    if(root!=NULL)
    {
        root=root->next;
        char *path=malloc(sizeof(char)*128);
        gtk_label_set_text(GTK_LABEL(label->image_name),root->T);
        if(label->arg==NULL)
        {
            strcpy(path, "./photos/");
            strcat(path, root->T);
        }
        else 
        {
            strcpy(path,label->arg);
            strcat(path,root->T);
        }
        change_properties(path,label);
        label->pixbuf=gdk_pixbuf_new_from_file_at_scale(path,750,550,0,&label->error);
        if(label->error==NULL)
        {
            if(label->T[0]==false) {gtk_widget_destroy(label->photo);}
            else { label->T[0]=false;}
            label->photo=gtk_image_new_from_pixbuf(label->pixbuf);
            gtk_container_add(GTK_CONTAINER(label->fixed2), label->photo);
            gtk_widget_show_all(window);
        }
        label->error=NULL;
    }
    else gtk_label_set_text(GTK_LABEL(label->info),"There are no photos matching your search!");
}

void on_button2_clicked(GtkButton *b, gpointer x)
{
    (void)b;
    labels *label=x;
    gtk_label_set_text(GTK_LABEL(label->info),"");
    if(root!=NULL)
    {
        root=root->prev;
        char *path=malloc(sizeof(char)*128);
        gtk_label_set_text(GTK_LABEL(label->image_name),root->T);
        if(label->arg==NULL)
        {
            strcpy(path, "./photos/");
            strcat(path, root->T);
        }
        else 
        {
            strcpy(path,label->arg);
            strcat(path,root->T);
        }
        change_properties(path,label);

        label->pixbuf=gdk_pixbuf_new_from_file_at_scale(path,750,550,0,&label->error);
        if(label->error==NULL)
        {
            if(label->T[0]==false) {gtk_widget_destroy(label->photo);}
            else { label->T[0]=false;}
            label->photo=gtk_image_new_from_pixbuf(label->pixbuf);
            gtk_container_add(GTK_CONTAINER(label->fixed2), label->photo);
            gtk_widget_show_all(window);
        }
        label->error=NULL;
    }
    else gtk_label_set_text(GTK_LABEL(label->info),"There are no photos matching your search!");
}

void apply_buttons(GtkButton *b, gpointer x, int k)
{
    labels *label=x;
    gtk_label_set_text(GTK_LABEL(label->info),"Press any arrow to begin!");
    if(label->T[0]==false) { gtk_widget_destroy(label->photo); label->T[0]=true; }
    const char *text;
    text=gtk_entry_get_text(GTK_ENTRY(label->Entry[k]));
    GdkPixbuf *pixbuf;
    pixbuf=gdk_pixbuf_new_from_file_at_scale("tick.png",30,30,0,&label->error);
    GtkWidget *icon=gtk_image_new_from_pixbuf(pixbuf);
    gtk_button_set_image(b,icon);
    gtk_widget_show_all(window);
    image_filter(GTK_COMBO_BOX(label->List[k]),1,text,label->arg);
}

void on_changed(GtkComboBox *List, gpointer x)
{
    labels *label=x;
    if(label->T[0]==false) { gtk_widget_destroy(label->photo); label->T[0]=true; }
    image_filter(List,0,NULL,label->arg);
    gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(List),GTK_SENSITIVITY_OFF);
    gtk_label_set_text(GTK_LABEL(label->info),"Press any arrow to begin!");
}

void on_l1_clicked(GtkButton *b, gpointer x){ apply_buttons(b,x,0);}
void on_l2_clicked(GtkButton *b, gpointer x){ apply_buttons(b,x,1);}
void on_l3_clicked(GtkButton *b, gpointer x){ apply_buttons(b,x,2);}
void on_l4_clicked(GtkButton *b, gpointer x){ apply_buttons(b,x,3);}
void on_l5_clicked(GtkButton *b, gpointer x){ apply_buttons(b,x,4);}

void on_reset_clicked(GtkButton *b, gpointer x)
{
    (void)b;
    labels *label=x;
    gtk_label_set_text(GTK_LABEL(label->brightness),"");
    gtk_label_set_text(GTK_LABEL(label->camera_model),"");
    gtk_label_set_text(GTK_LABEL(label->resolution),"");
    gtk_label_set_text(GTK_LABEL(label->flash),"");
    gtk_label_set_text(GTK_LABEL(label->focal_length),"");
    gtk_label_set_text(GTK_LABEL(label->image_name),"");
    gtk_label_set_text(GTK_LABEL(label->ISO),"");
    gtk_label_set_text(GTK_LABEL(label->shutter_speed),"");
    gtk_label_set_text(GTK_LABEL(label->exposure_time),"");
    gtk_label_set_text(GTK_LABEL(label->white_balance),"");
    gtk_label_set_text(GTK_LABEL(label->aperture),"");
    gtk_label_set_text(GTK_LABEL(label->date_time),"");
    for(int i=0,j=100;i<5;i++,j=j+100)
    {
        gtk_entry_set_text(GTK_ENTRY(label->Entry[i]),"");
        gtk_widget_destroy(label->Apply[i]);
        GtkWidget *t=gtk_button_new();
        label->Apply[i]=t;
        g_signal_connect(G_OBJECT(t),"clicked",G_CALLBACK(on_l1_clicked),label);
        gtk_fixed_put(GTK_FIXED(label->fixed_page_1),GTK_WIDGET(t),400,j);
        gtk_widget_show_all(window);
    }
    if(root==NULL) { free(root);}
    else
    {
        Names *start=root->prev;
        if(start!=root)
        {
            do
            {
                root=root->next;
                free(root->prev);
            }
            while(root!=start);
        }
        free(root);
    }
    build_list(label->arg);
    for(int i=0;i<5;i++)
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(label->List[i]),0);
        gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(label->List[i]),GTK_SENSITIVITY_ON);
    }
    if(label->T[0]==false) { gtk_widget_destroy(label->photo); label->T[0]=true; }
    gtk_label_set_text(GTK_LABEL(label->info),"Press any arrow to begin!");
}