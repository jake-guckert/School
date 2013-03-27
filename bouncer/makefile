all: a.out

a.out: bouncer.c
	gcc bouncer.c -I ../ffmpeg/include/ -L ../ffmpeg/lib  `pkg-config --cflags --libs libavutil libavformat libavcodec libswscale`

clean:
	rm -f *.o a.out
	rm -f *.o *.out *.cc~ *.utah *.ppm
movie: *.utah
	ffmpeg -f image2 -r 30 -pattern_type glob -i '*.utah' out.mp4; ffplay out.mp4
