/*****************************************************************************/
/*
* Routines to manipulate images
*
* MALIS Lab Session
*
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "image.h"

#define ALLOC2D(Variable,Type,n1,n2) {int A2D; Variable=(Type **)malloc(sizeof(Type *)*n1); \
		Variable[0]=(Type *)malloc(sizeof(Type)*n1*n2); \
		for(A2D=1; A2D<n1; A2D++) Variable[A2D]=Variable[A2D-1]+n2; }

/*****************************************************************************/
void image_read(Image *image, char * filename) {
	FILE *in;
	int x, y;

	if(fopen_s(&in,filename,"rb") != 0) {
		printf("* Error opening file %s\n",filename);
		getchar(); exit(1);
	}

	if(fscanf_s(in,"P6 %d %d 255\n",&image->width,&image->height) != 2) {
		printf("* Error invalid file format in %s\n",filename);
		getchar(); exit(2);
	}

	ALLOC2D(image->R,unsigned char,image->height,image->width);
	ALLOC2D(image->G,unsigned char,image->height,image->width);
	ALLOC2D(image->B,unsigned char,image->height,image->width);

	for(y=0; y < image->height; y++)
	for(x=0; x < image->width; x++) {
		fread(&image->R[y][x],sizeof(char),1,in);
		fread(&image->G[y][x],sizeof(char),1,in);
		fread(&image->B[y][x],sizeof(char),1,in); 
	}

	fclose(in);
}

/*****************************************************************************/
void image_write(Image *image, char * filename) {
	FILE *out;
	int x, y;

	if(fopen_s(&out,filename,"wb") != 0) {
		printf("* Error opening file %s\n",filename);
		getchar(); exit(1);
	}

	fprintf(out,"P6 %d %d 255\n",image->width,image->height);

	for(y=0; y < image->height; y++)
	for(x=0; x < image->width; x++) {
		fwrite(&image->R[y][x],sizeof(char),1,out);
		fwrite(&image->G[y][x],sizeof(char),1,out);
		fwrite(&image->B[y][x],sizeof(char),1,out); 
	}

	fclose(out);
}

/*****************************************************************************/
void image_drawline(Image *image, int x_start, int y_start, int x_end, int y_end, unsigned char red, unsigned char green, unsigned char blue) {
	int dx = x_end-x_start;
	int dy = y_end-y_start;
	int steps,k;
	double xInc, yInc, x=x_start, y=y_start;

	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	xInc= dx/ (double)steps;
	yInc= dy/ (double)steps;

	for(k=0; k<steps ; k++) {
		x=(xInc*k)+x_start;
		y=(yInc*k)+y_start;
		image->R[(int)y][(int)x]=red;
		image->G[(int)y][(int)x]=green;
		image->B[(int)y][(int)x]=blue;
	}
}
