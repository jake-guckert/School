all: bouncer.out

bouncer.out: bouncer.c
	gcc -o bouncer bouncer.c -I ../ffmpeg/include/ -L ../ffmpeg/lib  `pkg-config --cflags --libs libavutil libavformat libavcodec libswscale`

clean:
	rm -f *.o a.out
	rm -f *.o *.out *.cc~ *.utah bouncer *.mp4
movie: *.utah
	ffmpeg -i frame%d.utah -vcodec mpeg4 out.mp4; ffplay out.mp4

frame: 
	./bouncer plant.jpg

one:
	make clean; make; make frame; ffplay frame0.utah
it:
	make clean; make; make frame; make movie

