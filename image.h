/*****************************************************************************/
/*
* Some utility routines
*
* MALIS Lab Session
*
/*****************************************************************************/

#ifndef image_H
#define image_H

typedef struct {
  int width;
  int height;
  
  unsigned char ** R; // stores the red intensity 
  unsigned char ** G; // stores the green intensity
  unsigned char ** B; // stores the blue intensity
} Image;

void image_read(Image *image, char * filename);

void image_write(Image *image, char * filename);

void image_drawline(Image *image, int x_start, int y_start, int x_end, int y_end, unsigned char red, unsigned char green, unsigned char blue);

#endif





