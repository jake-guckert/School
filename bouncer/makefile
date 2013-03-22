all: a.out

a.out: bouncer.cc
	g++ -I ../ffmpeg/include/ -L ../ffmpeg/lib *.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`

clean:
	rm -f *.o a.out
	rm -f *.o *.out *.cc~ *.ut
movie: 

install: echo 
