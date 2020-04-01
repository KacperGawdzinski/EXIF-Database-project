#include "libexif/exif-data.h"
#include "libexif/exif-entry.h"
#include "libexif/exif-loader.h"
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>  
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <X11/Xlib.h>

typedef struct names{
    char *T;
    struct names *next;
    struct names *prev;
}Names;

typedef struct ol
{
    Names *copy;
    GtkWidget *slide;
    GtkWidget *picture;
    GtkWidget *fixed;
    bool guard;
    int h;
    int w;
    char *path;
}slide_data;

typedef struct labs
{
    GtkWidget *camera_model;
    GtkWidget *date_time;
    GtkWidget *focal_length;
    GtkWidget *shutter_speed;
    GtkWidget *aperture;
    GtkWidget *flash;
    GtkWidget *brightness;
    GtkWidget *exposure_time;
    GtkWidget *white_balance;
    GtkWidget *ISO;
    GtkWidget *photo;
    GtkWidget *fixed2;
    GtkWidget *image_name;
    GtkWidget *resolution;
    GtkWidget *add_image;
    GtkWidget *info;
    GtkWidget *List[5];
    GtkWidget *Entry[5];
    GtkWidget *Apply[5];
    GtkWidget *fixed_page_1;
    GdkPixbuf *pixbuf;
    GError *error;
    char *arg;
    bool T[6];
}labels;

typedef struct tagz
{
    GtkWidget *button[2];
    GtkWidget *entry[2];
    char *arg;
}New_tags;


Names *new(Names *actual);
char *extract_tag(ExifData *ed, ExifIfd eid, ExifTag tag, char *s);
long int get_file_size(FILE *file) ;
char *check(ExifData *d, ExifTag tag, char *s);
void change_properties(char *path, labels *label);
void on_button1_clicked(GtkButton *b, gpointer x);
void on_button2_clicked(GtkButton *b, gpointer x);
void on_changed(GtkComboBox *List, gpointer x);
void show_error();
void show_info();
void show_remove_info();
void remove_photo(GtkButton *b, gpointer x);
void open_dialog(GtkWidget *b, gpointer x);
void build_list();
char *strdup(const char* p);
void add_new_comment(GtkButton *b, gpointer x);
void image_filter(GtkComboBox *List, bool writing, const char *text, char *path);
void apply_buttons(GtkButton *b, gpointer x, int k);
void on_l1_clicked(GtkButton *b, gpointer x);
void on_l2_clicked(GtkButton *b, gpointer x);
void on_l3_clicked(GtkButton *b, gpointer x);
void on_l4_clicked(GtkButton *b, gpointer x);
void on_l5_clicked(GtkButton *b, gpointer x);
void on_reset_clicked(GtkButton *b, gpointer x);
void show();
int changer(void *x);
int getScreenSize(int *w, int *h);
void make(GtkComboBox *combo, gpointer x);
void add_new_rating(GtkButton *b, gpointer x);
void destroy (GtkWidget *window, gpointer x);