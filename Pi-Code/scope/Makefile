binaries = oscope 

all: main.c graphics.c cmdargs.c usbcomm.c
	gcc -I /opt/vc/include -I /usr/include -lshapes -lm -o oscope main.c graphics.c cmdargs.c usbcomm.c -std=c99 -I/usr/include/libusb-1.0/ -lusb-1.0

clean: 
	rm -f $(binaries) *.o
