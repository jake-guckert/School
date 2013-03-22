//Draw circle
// I'm just throwing out ideas.
// radius
// center
// diameter
// peter said to use a triangle to draw a circle
// so using pathegorum( don't know how to spell this) theorm.
// y*y + x*x = r*r
// so if we start with a center point and go from there
// so I think if we just move the y value

// function that takes the frame we are going to draw the circle on.
AVFrame drawCircle(AVFrame *pict)
{


  uint8_t *buf;
  int height;
  int width;
  height = pict->height; // height of frame
  width = pict->width; // width of frame

  // we could start in the center of the picture
  int center = width/2;

  //we could make a complete center coordinates. maybe a p
  int centerx = width/2;
  int centery = height/2;

  // lets start by adding an entire width of pixels
  for(int col = 0; col < width; col++)
    {

      uint8_t * pixel = pict->data[0] + height/2 + col;
  // do what we did in our encoding. create a pixel and add it to our bytestream
  bytestream_put_byte(&buf, pixel[0]);
      // this seems like it will just go at the end of our picture. How do we get it
      // to go in to the position that we want it to

  //how do we change the set the color of a pixel??????
    }
 
}
