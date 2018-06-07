/*******************************************************************************
* File Name: Ch1In.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ch1In_H) /* Pins Ch1In_H */
#define CY_PINS_Ch1In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ch1In_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ch1In__PORT == 15 && ((Ch1In__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ch1In_Write(uint8 value);
void    Ch1In_SetDriveMode(uint8 mode);
uint8   Ch1In_ReadDataReg(void);
uint8   Ch1In_Read(void);
void    Ch1In_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ch1In_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ch1In_SetDriveMode() function.
     *  @{
     */
        #define Ch1In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ch1In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ch1In_DM_RES_UP          PIN_DM_RES_UP
        #define Ch1In_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ch1In_DM_OD_LO           PIN_DM_OD_LO
        #define Ch1In_DM_OD_HI           PIN_DM_OD_HI
        #define Ch1In_DM_STRONG          PIN_DM_STRONG
        #define Ch1In_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ch1In_MASK               Ch1In__MASK
#define Ch1In_SHIFT              Ch1In__SHIFT
#define Ch1In_WIDTH              1u

/* Interrupt constants */
#if defined(Ch1In__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ch1In_SetInterruptMode() function.
     *  @{
     */
        #define Ch1In_INTR_NONE      (uint16)(0x0000u)
        #define Ch1In_INTR_RISING    (uint16)(0x0001u)
        #define Ch1In_INTR_FALLING   (uint16)(0x0002u)
        #define Ch1In_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ch1In_INTR_MASK      (0x01u) 
#endif /* (Ch1In__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ch1In_PS                     (* (reg8 *) Ch1In__PS)
/* Data Register */
#define Ch1In_DR                     (* (reg8 *) Ch1In__DR)
/* Port Number */
#define Ch1In_PRT_NUM                (* (reg8 *) Ch1In__PRT) 
/* Connect to Analog Globals */                                                  
#define Ch1In_AG                     (* (reg8 *) Ch1In__AG)                       
/* Analog MUX bux enable */
#define Ch1In_AMUX                   (* (reg8 *) Ch1In__AMUX) 
/* Bidirectional Enable */                                                        
#define Ch1In_BIE                    (* (reg8 *) Ch1In__BIE)
/* Bit-mask for Aliased Register Access */
#define Ch1In_BIT_MASK               (* (reg8 *) Ch1In__BIT_MASK)
/* Bypass Enable */
#define Ch1In_BYP                    (* (reg8 *) Ch1In__BYP)
/* Port wide control signals */                                                   
#define Ch1In_CTL                    (* (reg8 *) Ch1In__CTL)
/* Drive Modes */
#define Ch1In_DM0                    (* (reg8 *) Ch1In__DM0) 
#define Ch1In_DM1                    (* (reg8 *) Ch1In__DM1)
#define Ch1In_DM2                    (* (reg8 *) Ch1In__DM2) 
/* Input Buffer Disable Override */
#define Ch1In_INP_DIS                (* (reg8 *) Ch1In__INP_DIS)
/* LCD Common or Segment Drive */
#define Ch1In_LCD_COM_SEG            (* (reg8 *) Ch1In__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ch1In_LCD_EN                 (* (reg8 *) Ch1In__LCD_EN)
/* Slew Rate Control */
#define Ch1In_SLW                    (* (reg8 *) Ch1In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ch1In_PRTDSI__CAPS_SEL       (* (reg8 *) Ch1In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ch1In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ch1In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ch1In_PRTDSI__OE_SEL0        (* (reg8 *) Ch1In__PRTDSI__OE_SEL0) 
#define Ch1In_PRTDSI__OE_SEL1        (* (reg8 *) Ch1In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ch1In_PRTDSI__OUT_SEL0       (* (reg8 *) Ch1In__PRTDSI__OUT_SEL0) 
#define Ch1In_PRTDSI__OUT_SEL1       (* (reg8 *) Ch1In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ch1In_PRTDSI__SYNC_OUT       (* (reg8 *) Ch1In__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ch1In__SIO_CFG)
    #define Ch1In_SIO_HYST_EN        (* (reg8 *) Ch1In__SIO_HYST_EN)
    #define Ch1In_SIO_REG_HIFREQ     (* (reg8 *) Ch1In__SIO_REG_HIFREQ)
    #define Ch1In_SIO_CFG            (* (reg8 *) Ch1In__SIO_CFG)
    #define Ch1In_SIO_DIFF           (* (reg8 *) Ch1In__SIO_DIFF)
#endif /* (Ch1In__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ch1In__INTSTAT)
    #define Ch1In_INTSTAT            (* (reg8 *) Ch1In__INTSTAT)
    #define Ch1In_SNAP               (* (reg8 *) Ch1In__SNAP)
    
	#define Ch1In_0_INTTYPE_REG 		(* (reg8 *) Ch1In__0__INTTYPE)
#endif /* (Ch1In__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ch1In_H */


/* [] END OF FILE */
