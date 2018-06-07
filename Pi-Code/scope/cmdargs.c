#include "scope.h"  /* Include the header */

int getOpts(int c, uint8_t * mode, int * trigger_level, uint8_t * slope, uint8_t * chan,
			int * xscale, int * yscale, uint8_t *psoc_enable){
	
	extern char *optarg;

		switch(c)
		{
			case 'm':
				if(strcmp(optarg, "free") != 0 && strcmp(optarg, "trigger") != 0) {
					printf("Invalid mode input! \n");
					return -1;
				}
				else{
					if(strcmp(optarg, "free") == 0) *mode = 1;	
					else *mode = 0;
					printf("Mode set to %d, 0 for trigger, 1 for free\n", *mode);
				}
				break;

			case 't':
				if(atoi(optarg) > 5000 || atoi(optarg) < 0 || atoi(optarg)%100 != 0){
					printf("Invalid trigger input! \n");
					return -1;
				}
				else{
					*trigger_level = atoi(optarg);
					printf("Trigger level set to %d\n", *trigger_level);
				}
				break;

			case 's':
				if(strcmp(optarg,"pos") != 0 && strcmp(optarg,"neg") != 0){
					printf("Invalid slope input!\n");
					return -1;
				}
				else{
					if(strcmp(optarg, "pos") != 0) *slope = 1;
					else *slope = 0;
					printf("Slope set to %d, 0 for pos, 1 for neg\n", *slope);
				}
				break;

			case 'c':
				if(atoi(optarg) != 1 && atoi(optarg) != 2){
					printf("Invalid Channel input!\n");
					return -1;
				}
				else{
					*chan = atoi(optarg);
					printf("Trigger channel set to %d\n", *chan);
				}
				break;
	
			case 'x':
				*xscale = atoi(optarg);
				if(*xscale != 100 && *xscale != 500 
				&& *xscale != 1000 && *xscale != 2000 && *xscale != 5000 
				&& *xscale != 10000 && *xscale != 50000 && *xscale != 100000){
					printf("Invalid xscale input!\n");
					return -1;
				}
				printf("Xscale set to %d\n", *xscale);
			   	break;

			case 'y':
				*yscale = atoi(optarg);
				if(*yscale != 100 && *yscale != 500 && *yscale != 1000 
				&& *yscale != 2000 && *yscale != 2500){
					printf("Invalid yscale input!\n");
					return -1;
				}
				printf("Yscale set to %d\n", *yscale);
				break;	
			
			case 'e':
				*psoc_enable = atoi(optarg);
				if(*psoc_enable != 1 && *psoc_enable != 0){
					printf("Invalid enable input!\n");
					return -1;
				}

				break;	                      	
			
		}


}

void getTrigger(uint8_t **newCh1,	//post shift
		 uint8_t **newCh2,		
		 uint8_t *ch1Data,	//from psoc
		 uint8_t *ch2Data,	
		 int trigOption,	//option info	
		 int trigLevel,		
		 int slopeOption		
		 ){		

	int ymax = 0;			
	int trig_level = 0;		
	int trig_index = 64;
	
	if(trigOption == 1){ //Ch1 trigger		
		for(int i = 64; i < 10064; i++){		
			if(ch1Data[i] > ymax) ymax = ch1Data[i]; //find ymax
		}
		trig_level = (ymax/4)*(trigLevel/1000); //map trigger level
		for(int i = 64; i < 10064; i++){			
			if(slopeOption == 0){ //slope is positive
				if(ch1Data[i] <= trig_level && ch1Data[i+1] > trig_level){	
					trig_index = i;
					break;
				}
			}
			else{ //slope is negative
				if(ch1Data[i] >= trig_level && ch1Data[i+1] <trig_level){
					trig_index = i;
					break;
				}
			}
		}
	}
	
	else{ //Ch2 trigger
		for(int i = 64; i < 10064; i++){		
			if(ch2Data[i] > ymax) ymax = ch2Data[i];		
		}
		trig_level = (ymax/4)*(trigLevel/1000.0);		
		for(int i = 64; i < 10064; i++){			
			if(slopeOption == 0){			
				if(ch2Data[i] < trig_level && ch2Data[i+1] >= trig_level){	
					trig_index = i;
					break;
				}
			}
			else{ 
				if(ch2Data[i] > trig_level && ch2Data[i+1] <=trig_level){
					trig_index = i;
					break;
				}
			}
		}
	}

	*newCh1 = ch1Data + trig_index; //add index to address
	*newCh2 = ch2Data + trig_index;
}


