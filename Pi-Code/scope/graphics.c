#include "scope.h"  /* Include the header */



// Draw grid lines
void grid(VGfloat x, VGfloat y, // Coordinates of lower left corner
		int nx, int ny, // Number of x and y divisions
		int w, int h) // screen width and height

{
	VGfloat ix, iy;
	Stroke(128, 128, 128, 0.5); // Set color
	StrokeWidth(2); // Set width of lines
	for (ix = x; ix <= x + w; ix += w/nx) {
		Line(ix, y, ix, y + h);
	}

	for (iy = y; iy <= y + h; iy += h/ny) {
		Line(x, iy, x + w, iy);
	}
}


// Draw the background for the oscilloscope screen
void drawBackground(int w, int h, // width and height of screen
		int xdiv, int ydiv,// Number of x and y divisions
		int margin){ // Margin around the image
	VGfloat x1 = margin;
	VGfloat y1 = margin;
	VGfloat x2 = w - 2*margin;
	VGfloat y2 = h - 2*margin;

	Background(128, 128, 128);

	Stroke(204, 204, 204, 1);
	StrokeWidth(1);

	Fill(44, 77, 120, 1);
	Rect(10, 10, w-20, h-20); // Draw framing rectangle

	grid(x1, y1, xdiv, ydiv, x2, y2); // Draw grid lines
}


// Display x and y scale settings
void printScaleSettings(int xscale, int yscale, int xposition, int yposition, VGfloat tcolor[4]) {
	char str[100];

	setfill(tcolor);
	if (xscale >= 1000)
		sprintf(str, "X scale = %0d ms/div", xscale/1000);
	else
		sprintf(str, "X scale = %0d us/div", xscale);
	Text(xposition, yposition, str, SansTypeface, 18);

	sprintf(str, "Y scale = %3.2f V/div", yscale * 0.001);
	Text(xposition, yposition-50, str, SansTypeface, 18);
}


// Convert waveform samples into screen coordinates
void processSamples(char *data, // sample data
		int nsamples, // Number of samples
		int xstart, // starting x position of wave
		int xfinish, // Ending x position of wave
		float yscale, // y scale in pixels per volt
		data_point *point_array){
	//xfinish += 5;
	VGfloat x1, y1;
	data_point p;

	for (int i=0; i< nsamples; i++){
	    x1 = xstart + (xfinish-xstart)*i/nsamples;
	    y1 = data[i] * 5 * yscale/256;
	    p.x = x1;
	    p.y = y1;
	    point_array[i] = p;
	    }
}

// Plot waveform
void plotWave(data_point *data, // sample data
		int nsamples, // Number of samples
		int yoffset, // y offset from bottom of screen
		VGfloat linecolor[4] // Color for the wave
	     ){
	
	data_point p;
	VGfloat x1, y1, x2, y2;

	Stroke(linecolor[0], linecolor[1], linecolor[2], linecolor[3]);
	StrokeWidth(4);

	p = data[0];
	x1 = p.x;
	y1 = p.y + yoffset;

	for (int i=1; i< nsamples; i++){
		p = data[i];
		x2 = p.x;
		y2 = p.y + yoffset;
		Line(x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
}