MODULES += cyclical_list.o
MODULES += exif_tags.o
MODULES += manipulate_images.o
MODULES += slide_show.o
MODULES += custom_functions.o
MODULES += information_dialogs.o
MODULES += show_image_info.o
MODULES += widget_signals.o

MODULES += header.h

FLAGS = -xc -std=c11 -Wall -Wextra -lm -g -Werror
FLAGS += -ggdb `pkg-config --libs --cflags gtk+-3.0 libexif`
FLAGS += -lX11

exifdb: main.o ${MODULES}
	gcc -o $@ $< ${MODULES} ${FLAGS} -rdynamic

%.o: %.c
	gcc -c -o $@ $< ${FLAGS}

clean:
	-rm -f *.o exifdb

loc:
	cloc .