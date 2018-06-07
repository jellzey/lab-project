#ifndef SCOPE_H_   /* Include guard */
#define SCOPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>
#include <math.h>
#include <termios.h>
#include <wiringPi.h>
#include <libusb.h>
#include <stdbool.h>
#include <getopt.h>

typedef struct{
	VGfloat x, y;
} data_point;

void grid(VGfloat x, VGfloat y, // Coordinates of lower left corner
		int nx, int ny, // Number of x and y divisions
		int w, int h); // screen width and height

void drawBackground(int w, int h, // width and height of screen
		int xdiv, int ydiv,// Number of x and y divisions
		int margin);

void printScaleSettings(int xscale, int yscale, int xposition, int yposition, VGfloat tcolor[4]);

void processSamples(char *data, // sample data
		int nsamples, // Number of samples
		int xstart, // starting x position of wave
		int xfinish, // Ending x position of wave
		float yscale, // y scale in pixels per volt
		data_point *point_array);

void plotWave(data_point *data, // sample data
		int nsamples, // Number of samples
		int yoffset, // y offset from bottom of screen
		VGfloat linecolor[4] // Color for the wave
	     );
	     
void getTrigger(uint8_t **newCh1,	//post shift
		 uint8_t **newCh2,		
		 uint8_t *ch1Data,	//from psoc
		 uint8_t *ch2Data,	
		 int trigOption,	//option info	
		 int trigLevel,		
		 int slopeOption		
		 );
	     
void usbConnect(libusb_device_handle **dev);

int getOpts(int c, uint8_t * mode, int * trigger_level, uint8_t * slope, uint8_t * chan,
			int * xscale, int * yscale, uint8_t *psoc_enable);

#endif // SCOPE_H_
