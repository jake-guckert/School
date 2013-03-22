// g++ -I ../include/ -L../lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`


#include <iostream>
#include <avcodec.h>
#include <avformat.h>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{

  #include "libavcodec/avcodec.h"
  #include "libavformat/avformat.h"

}

using namespace std;

int main (int argc, const char* argv[])
{
  av_register_all();
  // get file from commandline
  // check if it is a .jpg file
  // if not a .jpg file send error and end

  AVFormatContext *pFormatCtx; //where jpg will be stored
  AVCodecContext *pCodecCtx = NULL;
  AVFrame *pFrame;
  AVCodec *pCodec;
  uint8_t *buffer;
  int numBytes;
  int frameFinished;
  AVPacket packet;
  AVDictionary *dict = NULL;


  //open jpg image file
  if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
    return -1;

  pCodecCtx = pFormatCtx->streams[0]->codec; // figure out what this does
  
  // Retrieve stream information
  //if(av_find_stream_info(pFormatCtx)<0)
  //return -1; // Couldn't find stream information

  // Dump information about file onto standard error
  //dump_format(pFormatCtx, 0, argv[1], 0);

  // Find the decoder for the file
  pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==NULL) {
    cout << "Codec is not found" << endl;
  }

  // Open codec ???????????????????
  if(avcodec_open2(pCodecCtx, pCodec, &dict)<0)
    {
      cout << "Problem open codec" << endl;
      return -1; // Could not open codec
    }

  // Allocate video frame
  pFrame=avcodec_alloc_frame();

  // Allocate an AVFrame structure
  pFrame=avcodec_alloc_frame();
  if(pFrame==NULL)
    return -1;

  // Determine required buffer size and allocate buffer
  // this may need to be RGB8??????????????????????????????
  numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
			      pCodecCtx->height);
  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes
  avpicture_fill((AVPicture *)pFrame, buffer, PIX_FMT_RGB24,
		 pCodecCtx->width, pCodecCtx->height);


  // I'm a bit
  int i=0;
  while(av_read_frame(pFormatCtx, &packet) >=0 ) {
    // Decode video frame
    avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
     
      // Did we get a video frame?
      //if(frameFinished) {
	// Convert the image from its native format to RGB
        //img_convert((AVPicture *)pFrame, PIX_FMT_RGB24, 
	//	    (AVPicture*)pFrame, pCodecCtx->pix_fmt, 
	//	    pCodecCtx->width, pCodecCtx->height);
	
        // Save the frame to disk
        //if(++i<=5)
	  // SaveFrame(pFrame, pCodecCtx->width, 
	  //  pCodecCtx->height, i);
	  //}
    }
    
    // Free the packet that was allocated by av_read_frame
    av_free_packet(&packet);

    // Free the RGB image
    av_free(buffer);
    av_free(pFrame);

    // Close the codec
    avcodec_close(pCodecCtx);

    // Close the video file
    //av_close_input_file(pFormatCtx);


  // output 300 .utah files into the current directory
  return 0;
}
