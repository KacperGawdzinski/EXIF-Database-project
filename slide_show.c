#include "header.h"

extern Names *root;
int changer(void *x)
{
    slide_data *xx=x;
    if(xx->slide==NULL) return 0;
    GError *error=NULL;
    GdkPixbuf *pix;
    if(xx->guard!=0) gtk_widget_destroy(xx->picture);
    char *path=malloc(sizeof(char)*128);
    if(xx->path==NULL)
    {
        strcpy(path,"photos/");
        strcat(path,xx->copy->T);
        pix=gdk_pixbuf_new_from_file_at_scale(path,1200,800,0,&error);
        free(path);
    }
    else 
    {
        strcpy(path,xx->path);
        strcat(path,xx->copy->T);
        pix=gdk_pixbuf_new_from_file_at_scale(path,1200,800,0,&error);
    }
    if(error==NULL)
    {
        xx->picture=gtk_image_new_from_pixbuf(pix);
        gtk_fixed_put(GTK_FIXED(xx->fixed),GTK_WIDGET(xx->picture),400,100);
        xx->guard=1;
        gtk_widget_show_all(xx->slide);
        xx->copy=xx->copy->next;
        if(xx->copy==root)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

void make(GtkComboBox *combo, gpointer x)
{   
    char *text=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo));
    gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(combo),GTK_SENSITIVITY_OFF);
    int p=atoi(text);
    slide_data *xx=x;

    if(xx->copy!=NULL) 
    {
        GError *error=NULL;
        GdkPixbuf *pix;
        if(xx->guard!=0) gtk_widget_destroy(xx->picture);
        char *path=malloc(sizeof(char)*128);
        if(xx->path==NULL)
        {

            strcpy(path,"photos/");
            strcat(path,xx->copy->T);
            pix=gdk_pixbuf_new_from_file_at_scale(path,1200,800,0,&error);
            free(path);
        }
        else 
        {
            strcpy(path,xx->path);
            strcat(path,xx->copy->T);
            pix=gdk_pixbuf_new_from_file_at_scale(path,1200,800,0,&error);
        }
        if(error==NULL)
        {   
            xx->picture=gtk_image_new_from_pixbuf(pix);
            gtk_fixed_put(GTK_FIXED(xx->fixed),GTK_WIDGET(xx->picture),400,100);
            xx->guard=1;
            gtk_widget_show_all(xx->slide);
            xx->copy=xx->copy->next;
        }
        g_timeout_add(p*1000,changer,xx);
    }
}

void destroy (GtkWidget *window, gpointer x)
{
    (void)window;
    slide_data *xx=x;
    gtk_widget_destroy(xx->slide);
    xx->slide=NULL;
}

void show(GtkButton *b, char *path)
{
    (void)b;
    char *seconds[]={"Choose delay","1","2","3","4","5","6","7","8","9","10"};
    slide_data *xx=malloc(sizeof(slide_data));
    Names *copy=root;
    int w, h;
    getScreenSize(&w, &h);
    GtkWidget *slide=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *combo=gtk_combo_box_text_new();
    GtkWidget *fixed=gtk_fixed_new();
    for(long unsigned int i=0;i<G_N_ELEMENTS(seconds);i++)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),seconds[i]);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo),0);
    gtk_window_maximize (GTK_WINDOW(slide));
    gtk_widget_set_size_request(combo,200,40);
    gtk_container_add (GTK_CONTAINER (slide), GTK_WIDGET(fixed));
    gtk_fixed_put(GTK_FIXED(fixed),GTK_WIDGET(combo),w/64,h/2.5);
    gtk_window_set_position(GTK_WINDOW(slide), GTK_WIN_POS_CENTER);
    xx->copy=copy;
    xx->slide=slide;
    xx->fixed=fixed;
    xx->guard=false;
    xx->w=w;
    xx->h=h;
    xx->path=path;
    g_signal_connect(slide,"destroy", G_CALLBACK(destroy), xx);
    g_signal_connect(G_OBJECT(combo),"changed",G_CALLBACK(make),xx);
    gtk_window_set_title(GTK_WINDOW(slide), "Slide Show");
    gtk_widget_show_all(slide);
}