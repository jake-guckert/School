// g++ -I ../include/ -L../lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`


#include <iostream>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{

  #include "libavcodec/avcodec.h"
  #include "libavformat/avformat.h"
#include "libswscale/swscale.h"

}

using namespace std;

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
  FILE *pFile;
  char szFilename[32];
  int  y;
  
  // Open file
  sprintf(szFilename, "frame%d.utah", iFrame);
  pFile=fopen(szFilename, "wb");
  if(pFile==NULL)
    return;
  
  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);
  
  // Write pixel data
  for(y=0; y<height; y++)
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);
  
  // Close file
  fclose(pFile);
}

int main (int argc, const char* argv[])
{
 
  av_register_all();
  avcodec_register_all();
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
  AVPacket uPacket;
  AVDictionary *dict = NULL;
 struct SwsContext      *sws_ctx = NULL;

 
  // pCodecCtx->width and width are 0 why?
  // change output to a utah file
  // call draw circle function.

  //open jpg image file
  if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
    return -1;

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, NULL)<0)
    return -1; // Couldn't find stream information
 
  pCodecCtx = pFormatCtx->streams[0]->codec; // figure out what this does

  // Find the decoder for the file
  pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==NULL) {
    cout << "Codec is not found" << endl;
  }

  // Open codec ???????????????????
  if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
    {
      cout << "Problem open codec" << endl;
      return -1; // Could not open codec
    }
 cout << pCodecCtx->width << endl;
 cout << pCodecCtx->height << endl;
  // Allocate picture frame
  pFrame=avcodec_alloc_frame();

  // Allocate an AVFrame structure
  pFrame=avcodec_alloc_frame();
  if(pFrame==NULL)
    return -1;
 
  // Determine required buffer size and allocate buffer
  // RGB24 becaue ppm is rgb24. 
  numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
			      pCodecCtx->height);

  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));


  sws_ctx =
    sws_getContext
    (
     pCodecCtx->width,
     pCodecCtx->height,
     pCodecCtx->pix_fmt,
     pCodecCtx->width,
     pCodecCtx->height,
     PIX_FMT_RGB24,
     SWS_BILINEAR,
     NULL,
     NULL,
     NULL
     );
  
  // Assign appropriate parts of buffer to image planes
  avpicture_fill((AVPicture *)pFrame, buffer, PIX_FMT_RGB24,
		 pCodecCtx->width, pCodecCtx->height);

  // only looking at one frame. I don't think we need while
  int i=0;
  while(av_read_frame(pFormatCtx, &packet) >=0 ) {
  // Decode packet to a frame
  avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
 
  if(frameFinished){

   sws_scale
        (
            sws_ctx,
            (uint8_t const * const *)pFrame->data,
            pFrame->linesize,
            0,
            pCodecCtx->height,
            pFrameRGB->data,
            pFrameRGB->linesize
        );
        
}

  //set the specs for the new packet, upacket
  uPacket.size = 0;
  uPacket.data = NULL;
  uCodec = avcodec_find_encoder(AV_CODEC_ID_UTAH);
  pCodecCtx->codec = utahCodec;
  avcodec_encode_video2(pCodecCtx, &uPacket, pFrame, 0);

   // Save the frame to disk    
  SaveFrame(pFrame, pCodecCtx->width, 
    pCodecCtx->height, i);
  i++;

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
