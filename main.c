//Kacper Gawdziński #315121
//Exif Database
//Projekt końcoworoczny z WDPC
#include "header.h"

Names *root=NULL;
GtkWidget *window;
ExifData *d;
int main(int argc, char *argv[])
{
    char *standard_tags[]={"Choose tag","Camera","Date/Time","Focal Length","Shutter Speed","Aperture","Flash",
    "Brightness","White Balance","ISO","Exposure Time","Comment","Rating"};
    gtk_init(&argc, &argv);
    if(argc>2) 
    {
        printf("You put too many arguments!\n"); 
        return 0;
    }

    GtkBuilder *builder=gtk_builder_new_from_file ("window.glade");
    GtkWidget *fixed=GTK_WIDGET(gtk_builder_get_object(builder,"fixed"));
    GtkWidget *button1=GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
    GtkWidget *button2=GTK_WIDGET(gtk_builder_get_object(builder,"button2"));
    GtkWidget *forward_icon=GTK_WIDGET(gtk_builder_get_object(builder,"forward_icon"));
    GtkWidget *rewind_icon=GTK_WIDGET(gtk_builder_get_object(builder,"rewind_icon"));
    GtkWidget *stack1=GTK_WIDGET(gtk_builder_get_object(builder,"stack1"));
    GtkWidget *fixed_page_1=GTK_WIDGET(gtk_builder_get_object(builder,"fixed_page_1"));
    GtkWidget *fixed_page_2=GTK_WIDGET(gtk_builder_get_object(builder,"fixed_page_2"));
    GtkWidget *fixed_page_3=GTK_WIDGET(gtk_builder_get_object(builder,"fixed_page_3"));
    GtkWidget *fixed_page_4=GTK_WIDGET(gtk_builder_get_object(builder,"fixed_page_4"));
    GtkWidget *sw1=GTK_WIDGET(gtk_builder_get_object(builder,"sw1"));
    GtkWidget *label1=GTK_WIDGET(gtk_builder_get_object(builder,"label1"));
    GtkWidget *camera_model=GTK_WIDGET(gtk_builder_get_object(builder,"camera_model"));
    GtkWidget *date_time=GTK_WIDGET(gtk_builder_get_object(builder,"date_time"));
    GtkWidget *focal_length=GTK_WIDGET(gtk_builder_get_object(builder,"focal_length"));
    GtkWidget *shutter_speed=GTK_WIDGET(gtk_builder_get_object(builder,"shutter_speed"));
    GtkWidget *aperture=GTK_WIDGET(gtk_builder_get_object(builder,"aperture"));
    GtkWidget *flash=GTK_WIDGET(gtk_builder_get_object(builder,"flash"));
    GtkWidget *brightness=GTK_WIDGET(gtk_builder_get_object(builder,"brightness"));
    GtkWidget *exposure_time=GTK_WIDGET(gtk_builder_get_object(builder,"exposure_time"));
    GtkWidget *white_balance=GTK_WIDGET(gtk_builder_get_object(builder,"white_balance"));
    GtkWidget *ISO=GTK_WIDGET(gtk_builder_get_object(builder,"ISO"));
    GtkWidget *fixed2=GTK_WIDGET(gtk_builder_get_object(builder,"fixed2"));
    GtkWidget *image_name=GTK_WIDGET(gtk_builder_get_object(builder,"image_name"));
    GtkWidget *resolution=GTK_WIDGET(gtk_builder_get_object(builder,"resolution"));
    GtkWidget *add_image=GTK_WIDGET(gtk_builder_get_object(builder,"add_image"));
    GtkWidget *remove_image=GTK_WIDGET(gtk_builder_get_object(builder,"remove_image"));
    GtkWidget *reset=GTK_WIDGET(gtk_builder_get_object(builder,"reset"));
    GtkWidget *info=GTK_WIDGET(gtk_builder_get_object(builder,"info"));
    GtkWidget *instructions=GTK_WIDGET(gtk_builder_get_object(builder,"instructions"));
    GtkWidget *add_tag=GTK_WIDGET(gtk_builder_get_object(builder,"add_tag"));
    GtkWidget *add_rating=GTK_WIDGET(gtk_builder_get_object(builder,"add_rating"));
    GtkWidget *slide_show=GTK_WIDGET(gtk_builder_get_object(builder,"slide_show"));
    GtkWidget *add[2];
    GtkWidget *List[5];
    GtkWidget *Entry[5];
    GtkWidget *Apply[5];

    (void)instructions,(void)label1,(void)sw1,(void)fixed_page_4,(void)fixed_page_2;
    (void)stack1,(void)rewind_icon,(void)forward_icon,(void)fixed;

    for(int i=0;i<5;i++) 
    { 
        List[i]=gtk_combo_box_text_new();
        Entry[i]=gtk_entry_new();
        Apply[i]=gtk_button_new();
    }

    for(long unsigned int i=0;i<G_N_ELEMENTS(standard_tags);i++)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(List[0]),standard_tags[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(List[1]),standard_tags[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(List[2]),standard_tags[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(List[3]),standard_tags[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(List[4]),standard_tags[i]);
    }

    for(int i=0,j=100;i<5;i++,j=j+100)
    {
        gtk_combo_box_set_active(GTK_COMBO_BOX(List[i]),0);
        gtk_widget_set_size_request(List[i],150,40);
        gtk_fixed_put(GTK_FIXED(fixed_page_1),GTK_WIDGET(Apply[i]),400,j);
        gtk_fixed_put(GTK_FIXED(fixed_page_1),GTK_WIDGET(List[i]),0,j);
        gtk_fixed_put(GTK_FIXED(fixed_page_1),GTK_WIDGET(Entry[i]),180,j);
    }

    add[0]=gtk_entry_new();
    gtk_widget_set_size_request(add[0],400,40);
    gtk_fixed_put(GTK_FIXED(fixed_page_3),GTK_WIDGET(add[0]),31,120);
    gtk_entry_set_placeholder_text (GTK_ENTRY(add[0]),"Place new comment tag...");
    add[1]=gtk_entry_new();
    gtk_widget_set_size_request(add[1],400,40);
    gtk_entry_set_placeholder_text (GTK_ENTRY(add[1]),"Place new rating...");
    gtk_fixed_put(GTK_FIXED(fixed_page_3),GTK_WIDGET(add[1]),31,405);
    GError *error=NULL;
    window=GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    labels label;
    label.camera_model=camera_model;
    label.date_time=date_time;
    label.error=error;
    label.exposure_time=exposure_time;
    label.fixed2=fixed2;
    label.focal_length=focal_length;
    label.image_name=image_name;
    label.ISO=ISO;
    label.shutter_speed=shutter_speed;
    label.resolution=resolution;
    label.white_balance=white_balance;
    label.aperture=aperture;
    label.brightness=brightness;
    label.flash=flash;
    label.info=info;
    label.arg=argv[1];
    for(int i=0;i<5;i++)
    {
        label.T[i]=true;
        g_signal_connect (List[i],"changed",G_CALLBACK (on_changed),&label);
        label.List[i]=List[i];
        label.Entry[i]=Entry[i];
        label.Apply[i]=Apply[i];
    }
    label.T[5]=true;
    label.fixed_page_1=fixed_page_1;
    New_tags cont;
    cont.button[0]=add_tag;
    cont.button[1]=add_rating;
    cont.entry[0]=add[0];
    cont.entry[1]=add[1];
    cont.arg=argv[1];

    build_list(argv[1]);
    g_signal_connect(G_OBJECT(slide_show),"clicked",G_CALLBACK(show),argv[1]);
    g_signal_connect(G_OBJECT(Apply[0]),"clicked",G_CALLBACK(on_l1_clicked),&label);
    g_signal_connect(G_OBJECT(Apply[1]),"clicked",G_CALLBACK(on_l2_clicked),&label);
    g_signal_connect(G_OBJECT(Apply[2]),"clicked",G_CALLBACK(on_l3_clicked),&label);
    g_signal_connect(G_OBJECT(Apply[3]),"clicked",G_CALLBACK(on_l4_clicked),&label);
    g_signal_connect(G_OBJECT(Apply[4]),"clicked",G_CALLBACK(on_l5_clicked),&label);
    g_signal_connect(G_OBJECT(add_tag),"clicked",G_CALLBACK(add_new_comment),&cont);
    g_signal_connect(G_OBJECT(add_rating),"clicked",G_CALLBACK(add_new_rating),&cont);
    g_signal_connect(G_OBJECT(Apply[4]),"clicked",G_CALLBACK(on_l5_clicked),&label);
    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_button1_clicked),&label);
    g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(on_button2_clicked),&label);
    g_signal_connect(G_OBJECT(reset),"clicked",G_CALLBACK(on_reset_clicked),&label);
    g_signal_connect(G_OBJECT(add_image),"clicked",G_CALLBACK(open_dialog),&label);
    g_signal_connect(G_OBJECT(remove_image),"clicked",G_CALLBACK(remove_photo),&label);
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), window);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_builder_connect_signals(builder,NULL);
    gtk_window_set_title(GTK_WINDOW(window), "EXIF Database");
    gtk_widget_show_all(window);
    gtk_main();
}

