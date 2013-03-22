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
AVFrame drawCircle(AVFrame *p)
{
}

uint8_t *buf;
int height;
int width;
height = p->height; // height of frame
width = p->width; // width of frame

// we could start in the center of the picture
int center = width/2;

//we could make a complete center coordinates. maybe a p
int centerx = width/2;
int centery = height/2;

// lets start by adding say width/3 number of pixels to a line
for(int row = 0; row < 

// do what we did in our encoding. create a pixel and add it to our bytestream
bytestream_put_byte(&buf, pixel[0]);

//how do we change the set the color of a pixel??????
