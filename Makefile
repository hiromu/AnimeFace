LIBS= -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc
OBJS = anime.o

all: Animeface

Animeface: $(OBJS)
	cc -o Animeface $(OBJS) $(LDFLAGS) $(LIBS)

anime.o: anime.c $(HEADDERS)
	cc -c $(CFLAG) anime.c

clean:
	rm -f *.o
	rm -f Animeface

allclean:
	rm -f *.o
	rm -f Animeface
	rm -f Makefile
