//
// Oscilloscope Program
// Jacob Ellzey
// CMPE121
//
//

#include "scope.h"

#define BUFFER_SIZE 11100	


int main(int argc, char *argv[]) {

	
	libusb_device_handle *dev; // Pointer to data structure representing USB device
	usbConnect(&dev);

	uint8_t mode = 0;	//Default option values
	uint8_t psoc_enable = 1;
	uint8_t slope = 0;	
	uint8_t chan = 1;		
	int xscale = 1000;		
	int yscale = 1000;
	int trigger_level = 2500;
	
	
	int c = 0;
	while((c = getopt(argc, argv, "m:t:s:c:x:y:e:")) != -1){ //Parse input and update option values
	getOpts(c, &mode, &trigger_level, &slope, &chan,
			&xscale, &yscale,  &psoc_enable);
	}
	
	int garbage; //To store unwanted usb values
	// Transfer byte to enable or disable psoc
	libusb_bulk_transfer(dev, // Handle for the USB device
  			             0x04, // Address of the Endpoint in USB device
                         // MS bit nust be 1 for IN transfers
                         &psoc_enable, 
                         1, // send 1 byte
                	     &garbage, // Number of bytes actually received
        	             0 // Timeout in milliseconds (0 to disable timeout)
	                     );

	int width, height; // Width and height of screen in pixels
	int margin = 10; // Margin spacing around screen
	int xdivisions = 10; // Number of x-axis divisions
	int ydivisions = 8; // Number of y-axis divisions
	char str[100];
	
	VGfloat textcolor[4] = {0, 200, 200, 0.5}; // Color for displaying text
	VGfloat wave1color[4] = {240, 0, 0, 0.5}; // Color for displaying Channel 1 data
	VGfloat wave2color[4] = {200, 200, 0, 0.5}; // Color for displaying Channel 2 data

	uint8_t ch1Data[BUFFER_SIZE]; // Data from psoc
	uint8_t ch2Data[BUFFER_SIZE]; 
	
	uint8_t *newCh1; //buffers used in trigger function
	uint8_t *newCh2;

	data_point channel1_points[BUFFER_SIZE];
	data_point channel2_points[BUFFER_SIZE];
	
	
	uint8_t potVal[2]; //array for pot values
		potVal[0] = 0;
		potVal[1] = 0;
		
	

	init(&width, &height); // Initialize display and get width and height
	Start(width, height);

	int xstart = margin;
	int xlimit = width - 2*margin;
	int ystart = margin;
	int ylimit = height - 2*margin;

	int pixels_per_volt = (ylimit-ystart)*4/(ydivisions*yscale/250);

	while(1){//USB Bulk Transfer In from PSOC 
		libusb_bulk_transfer(dev, // Handle for the USB device
				(0x01 | 0x80), // Address of the Endpoint in USB device
				// MS bit nust be 1 for IN transfers
				ch1Data, // address of receive data buffer
				BUFFER_SIZE, // Size of data buffer
				&garbage, // Number of bytes actually received
				0 // Timeout in milliseconds (0 to disable timeout)
				);
		libusb_bulk_transfer(dev, // Handle for the USB device
				(0x02 | 0x80), // Address of the Endpoint in USB device
				// MS bit nust be 1 for IN transfers
				ch2Data, // address of receive data buffer
				BUFFER_SIZE, // Size of data buffer
				&garbage, // Number of bytes actually received
				0 // Timeout in milliseconds (0 to disable timeout)
				);
		libusb_bulk_transfer(dev, // Handle for the USB device
				(0x03 | 0x80), // Address of the Endpoint in USB device
				// MS bit nust be 1 for IN transfers
				potVal, // address of receive data buffer
				2, // Size of data buffer
				&garbage, // Number of bytes actually received
				100 // Timeout in milliseconds (0 to disable timeout)
				);

		
		drawBackground(width, height, xdivisions, ydivisions, margin);

		printScaleSettings(xscale, yscale, width-300, height-50, textcolor);

		if(mode == 0){		//will find trigger index and shift both data sets accordingly
			getTrigger(&newCh1, &newCh2, ch1Data, ch2Data, chan, trigger_level, slope);
			processSamples(newCh1, xscale*xdivisions/25, margin, width-margin, pixels_per_volt, channel1_points);    		
			processSamples(newCh2, xscale*xdivisions/25, margin, width-margin, pixels_per_volt, channel2_points);	
		}
		else{
			processSamples(ch1Data + 64, xscale*xdivisions/25, margin, width-margin, pixels_per_volt, channel1_points);   
			processSamples(ch2Data + 64, xscale*xdivisions/25, margin, width-margin, pixels_per_volt, channel2_points);
		}

		// Display 2 waves
		plotWave(channel1_points, xscale*xdivisions/25, potVal[0]*height/255, wave1color);	
		plotWave(channel2_points, xscale*xdivisions/25, potVal[1]*height/255, wave2color);
		End(); 

		WindowClear();
		
	}

}


