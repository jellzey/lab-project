/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

/* Defines for DMA_1 */
#define DMA_1_BYTES_PER_BURST 1
#define DMA_1_REQUEST_PER_BURST 1
#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_1_DST_BASE (CYDEV_SRAM_BASE)

/* Defines for DMA_2 */
#define DMA_2_BYTES_PER_BURST 1
#define DMA_2_REQUEST_PER_BURST 1
#define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_2_DST_BASE (CYDEV_SRAM_BASE)

/* USB device number. */
#define USBFS_DEVICE  (0u)

/* Active endpoints of USB device. */
#define IN_EP_CH1    (1u)
#define IN_EP_CH2    (2u)
#define IN_EP_POT    (3u)
#define OUT_EP_ENABLE (4u)

/* Size of SRAM buffer to store endpoint data. */
#define BUFFER_SIZE   (64u)

/* Pot threshold*/
#define DEBOUNCE_VALUE 5

/* Global Variables */
uint8_t piEnable[1]; //To toggle ADC conversion

uint8_t buffer[BUFFER_SIZE]; //USB buffer

uint8_t ch1Ping[BUFFER_SIZE]; //Ping pong buffers for data transfer
uint8_t ch1Pong[BUFFER_SIZE];
uint8_t ch2Ping[BUFFER_SIZE];
uint8_t ch2Pong[BUFFER_SIZE];    

uint8_t potVals[2]; //Array to send pot values to Pi
uint8_t val1 = 0;
uint8_t val2 = 0;
uint8_t val1Old = 0; //For debouncing
uint8_t val2Old = 0;

uint8_t ch1Flag = 1; //Flags to toggle buffers
uint8_t ch2Flag = 1;

/* Function Declarations */   
CY_ISR_PROTO(ch1Transmit);
CY_ISR_PROTO(ch2Transmit);
CY_ISR_PROTO(potSample);
void DMA_setup();
void USB_setup();

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DMA_setup();
    USB_setup();
    Mux_Start();
    Timer_1_Start();
    isr_1_StartEx(ch1Transmit);
    isr_2_StartEx(ch2Transmit);
    isr_pot_StartEx(potSample);
    ADC_CH1_Start();
    ADC_CH2_Start();
    ADC_CH1_StartConvert();
    ADC_CH2_StartConvert();
    ADC_POT_Start();
    ADC_POT_StartConvert();
    
    
    for(uint8_t i = 0; i < BUFFER_SIZE; i++){ //Initialize buffers
        ch1Ping[i] = 0;
        ch1Pong[i] = 0;
        ch2Ping[i] = 0;
        ch2Pong[i] = 0;
    }
    
    
    for(;;)
    {
        /* Check if configuration is changed. */
        if(0u != USBFS_IsConfigurationChanged()){
            /* Re-enable endpoint when device is configured. */
            if(0u != USBFS_GetConfiguration()){
                /* Enable OUT endpoint to receive data from host. */
                USBFS_EnableOutEP(OUT_EP_ENABLE);
            }
        }
        /* Check if data was received. */
        if(USBFS_GetEPState(OUT_EP_ENABLE) != USBFS_OUT_BUFFER_EMPTY){ 
            USBFS_ReadOutEP(OUT_EP_ENABLE, piEnable, 1); //Transfer recieved byte with DMA           
 
        }
        
        if(!piEnable[0]){ //Enable or disable ADC 
            ADC_CH1_StopConvert();
            ADC_CH2_StopConvert();
        }
        else{            
            ADC_CH1_StartConvert();
            ADC_CH2_StartConvert();
        }
   
        
    }
    
}
void DMA_setup(){
    
   /* Variable declarations for DMA_1 and DMA_2 */
    uint8_t DMA_1_Chan;
    uint8_t DMA_1_TD[2];
    uint8_t DMA_2_Chan;
    uint8_t DMA_2_TD[2];
    
    /* DMA Configuration for DMA_1 */
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
    HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
    DMA_1_TD[0] = CyDmaTdAllocate();
    DMA_1_TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_1_TD[0], BUFFER_SIZE, DMA_1_TD[1], DMA_1__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetConfiguration(DMA_1_TD[1], BUFFER_SIZE, DMA_1_TD[0], DMA_1__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_CH1_SAR_WRK0_PTR), LO16((uint32)ch1Ping));
    CyDmaTdSetAddress(DMA_1_TD[1], LO16((uint32)ADC_CH1_SAR_WRK0_PTR), LO16((uint32)ch1Pong));
    CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
    CyDmaChEnable(DMA_1_Chan, 1);

    /* DMA Configuration for DMA_2 */
    DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
    HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
    DMA_2_TD[0] = CyDmaTdAllocate();
    DMA_2_TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_2_TD[0], BUFFER_SIZE, DMA_2_TD[1], DMA_2__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetConfiguration(DMA_2_TD[1], BUFFER_SIZE, DMA_2_TD[0], DMA_2__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)ADC_CH2_SAR_WRK0_PTR), LO16((uint32)ch2Ping));
    CyDmaTdSetAddress(DMA_2_TD[1], LO16((uint32)ADC_CH2_SAR_WRK0_PTR), LO16((uint32)ch2Pong));
    CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
    CyDmaChEnable(DMA_2_Chan, 1);
}

void USB_setup(){
    
    /* Start USBFS operation with 5V operation. */
    USBFS_Start(USBFS_DEVICE, USBFS_5V_OPERATION);
    
    /* Wait until device is enumerated by host. */
    while(0 == USBFS_GetConfiguration()){}
    
    /* Enable OUT endpoint to receive data from host. */
    USBFS_EnableOutEP(4u); 
}

CY_ISR(ch1Transmit){
    if(USBFS_GetEPState(IN_EP_CH1) == USBFS_IN_BUFFER_EMPTY){ //Check that host read data
        if(ch1Flag){
            USBFS_LoadInEP(IN_EP_CH1, ch1Ping, 64);   
        }
        else
            USBFS_LoadInEP(IN_EP_CH1, ch1Pong, 64);
    }    
    ch1Flag = (ch1Flag+1)%2; //Flip flag value
}

CY_ISR(ch2Transmit){
     if(USBFS_GetEPState(IN_EP_CH2) == USBFS_IN_BUFFER_EMPTY){
        if(ch2Flag){
            USBFS_LoadInEP(IN_EP_CH2, ch2Ping, 64);   
        }
        else
            USBFS_LoadInEP(IN_EP_CH2, ch2Pong, 64);
    }
    ch2Flag = (ch2Flag+1)%2;    
}

CY_ISR(potSample){
    
    Mux_FastSelect(0); //Select first pot to send ADC
    val1 = ADC_POT_Read8(); //Read first pot 
    
    Mux_FastSelect(1); 
    val2 = ADC_POT_Read8();
    
    //Debounce pot readings and send to Pi
    if(((val1 < val1Old-DEBOUNCE_VALUE) || (val1 > val1Old+DEBOUNCE_VALUE)) || 
    ((val2 < val2Old-DEBOUNCE_VALUE) || (val2 > val2Old+DEBOUNCE_VALUE))){
        potVals[0] = val1;
        potVals[1] = val2;
        USBFS_LoadInEP(IN_EP_POT, potVals, 2);
       }
 
    val1Old = val1; //Store values for later debouncing
    val2Old = val2;
}
        

/* [] END OF FILE */
