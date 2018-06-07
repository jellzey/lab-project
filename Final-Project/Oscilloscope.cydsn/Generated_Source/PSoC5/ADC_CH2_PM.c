/*******************************************************************************
* File Name: ADC_CH2_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_CH2.h"


/***************************************
* Local data allocation
***************************************/

static ADC_CH2_BACKUP_STRUCT  ADC_CH2_backup =
{
    ADC_CH2_DISABLED
};


/*******************************************************************************
* Function Name: ADC_CH2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_CH2_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_CH2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_CH2_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_CH2_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_CH2_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_CH2_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_CH2_Sleep(void)
{
    if((ADC_CH2_PWRMGR_SAR_REG  & ADC_CH2_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_CH2_SAR_CSR0_REG & ADC_CH2_SAR_SOF_START_CONV) != 0u)
        {
            ADC_CH2_backup.enableState = ADC_CH2_ENABLED | ADC_CH2_STARTED;
        }
        else
        {
            ADC_CH2_backup.enableState = ADC_CH2_ENABLED;
        }
        ADC_CH2_Stop();
    }
    else
    {
        ADC_CH2_backup.enableState = ADC_CH2_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_CH2_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_CH2_Sleep() was called. If the component was enabled before the
*  ADC_CH2_Sleep() function was called, the
*  ADC_CH2_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_CH2_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_CH2_Wakeup(void)
{
    if(ADC_CH2_backup.enableState != ADC_CH2_DISABLED)
    {
        ADC_CH2_Enable();
        #if(ADC_CH2_DEFAULT_CONV_MODE != ADC_CH2__HARDWARE_TRIGGER)
            if((ADC_CH2_backup.enableState & ADC_CH2_STARTED) != 0u)
            {
                ADC_CH2_StartConvert();
            }
        #endif /* End ADC_CH2_DEFAULT_CONV_MODE != ADC_CH2__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
