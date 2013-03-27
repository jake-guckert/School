
#includ <math.h>
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

// Using a triangle to build a circle
// We have the radius below that we have set. With the y value I think we could just 
// choose some arbitrary height to go with so we can calcualte our x value. Using 
// pathegorem theorm. It would be sqrt(radius^2 + y^2).

// We can either draw the circle line by line or draw around the circle and fill it
// in. I think going line by line would be our best option. So this would mean that
// we need a left and a right and a row. What row were drawing the line on and from
// what point to what point.

// function that takes the frame we are going to draw the circle on.
// each ball is going to start at a different position on the frame. We need to get a
// starting point for the ball each time we create a new frame.
AVFrame drawCircle(AVFrame *pict) //int start)// I think it'd be best to start at the
                                             // top of the circle. So start will be
                                            // what row we are going to start on.
{


  uint8_t *buf;
  int height;
  int width;
  height = pict->height; // height of frame
  width = pict->width; // width of frame
  int radius = .3*width; // how large we want the ball. 30% of the width

  int center = width/2;

  // start on row 10. This is for drawing one line of the ball.
  for(int row = 10; row < height; row++)
    {
      // our y value will alway be what row we are.
      int y = row;
      // our x value will be used to determine from left to right what pixels do we 
      // need to draw on. using pathegorems
      int x = sqrt(radius*radius - y*y);
      // to determine the left starting position on the row
      int leftStart = center - x;
      // to determine the right ending position on the row
      int rightEnd = center + x;

      //for loop to draw a line of pixels from leftStart to rightEnd
      for(leftStart; leftStart < rightEnd; leftStart++)
	{
	  // we need to figure out how to change the color of a pixel!!!!!!!
	
      //I don't know if this is right. It seems. before we were changing the row each time but this time were just gonna change one entire line. That line will be at heigheight/2 * pict->line
      uint8_t * pixel = pict->data[0] + (row * pict->linesize[0]) + leftStart;

      // do what we did in our encoding. create a pixel and add it to our bytestream
      bytestream_put_byte(&buf, pixel[0]);
      // this seems like it will just go at the end of our picture. How do we get it
      // to go in to the position that we want it to
	}

  //how do we change the set the color of a pixel??????
    }
 
}

// Fill in circle function?????
