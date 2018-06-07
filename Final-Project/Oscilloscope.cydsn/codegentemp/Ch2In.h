/*******************************************************************************
* File Name: Ch2In.h  
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

#if !defined(CY_PINS_Ch2In_H) /* Pins Ch2In_H */
#define CY_PINS_Ch2In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ch2In_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ch2In__PORT == 15 && ((Ch2In__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ch2In_Write(uint8 value);
void    Ch2In_SetDriveMode(uint8 mode);
uint8   Ch2In_ReadDataReg(void);
uint8   Ch2In_Read(void);
void    Ch2In_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ch2In_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ch2In_SetDriveMode() function.
     *  @{
     */
        #define Ch2In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ch2In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ch2In_DM_RES_UP          PIN_DM_RES_UP
        #define Ch2In_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ch2In_DM_OD_LO           PIN_DM_OD_LO
        #define Ch2In_DM_OD_HI           PIN_DM_OD_HI
        #define Ch2In_DM_STRONG          PIN_DM_STRONG
        #define Ch2In_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ch2In_MASK               Ch2In__MASK
#define Ch2In_SHIFT              Ch2In__SHIFT
#define Ch2In_WIDTH              1u

/* Interrupt constants */
#if defined(Ch2In__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ch2In_SetInterruptMode() function.
     *  @{
     */
        #define Ch2In_INTR_NONE      (uint16)(0x0000u)
        #define Ch2In_INTR_RISING    (uint16)(0x0001u)
        #define Ch2In_INTR_FALLING   (uint16)(0x0002u)
        #define Ch2In_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ch2In_INTR_MASK      (0x01u) 
#endif /* (Ch2In__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ch2In_PS                     (* (reg8 *) Ch2In__PS)
/* Data Register */
#define Ch2In_DR                     (* (reg8 *) Ch2In__DR)
/* Port Number */
#define Ch2In_PRT_NUM                (* (reg8 *) Ch2In__PRT) 
/* Connect to Analog Globals */                                                  
#define Ch2In_AG                     (* (reg8 *) Ch2In__AG)                       
/* Analog MUX bux enable */
#define Ch2In_AMUX                   (* (reg8 *) Ch2In__AMUX) 
/* Bidirectional Enable */                                                        
#define Ch2In_BIE                    (* (reg8 *) Ch2In__BIE)
/* Bit-mask for Aliased Register Access */
#define Ch2In_BIT_MASK               (* (reg8 *) Ch2In__BIT_MASK)
/* Bypass Enable */
#define Ch2In_BYP                    (* (reg8 *) Ch2In__BYP)
/* Port wide control signals */                                                   
#define Ch2In_CTL                    (* (reg8 *) Ch2In__CTL)
/* Drive Modes */
#define Ch2In_DM0                    (* (reg8 *) Ch2In__DM0) 
#define Ch2In_DM1                    (* (reg8 *) Ch2In__DM1)
#define Ch2In_DM2                    (* (reg8 *) Ch2In__DM2) 
/* Input Buffer Disable Override */
#define Ch2In_INP_DIS                (* (reg8 *) Ch2In__INP_DIS)
/* LCD Common or Segment Drive */
#define Ch2In_LCD_COM_SEG            (* (reg8 *) Ch2In__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ch2In_LCD_EN                 (* (reg8 *) Ch2In__LCD_EN)
/* Slew Rate Control */
#define Ch2In_SLW                    (* (reg8 *) Ch2In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ch2In_PRTDSI__CAPS_SEL       (* (reg8 *) Ch2In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ch2In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ch2In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ch2In_PRTDSI__OE_SEL0        (* (reg8 *) Ch2In__PRTDSI__OE_SEL0) 
#define Ch2In_PRTDSI__OE_SEL1        (* (reg8 *) Ch2In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ch2In_PRTDSI__OUT_SEL0       (* (reg8 *) Ch2In__PRTDSI__OUT_SEL0) 
#define Ch2In_PRTDSI__OUT_SEL1       (* (reg8 *) Ch2In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ch2In_PRTDSI__SYNC_OUT       (* (reg8 *) Ch2In__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ch2In__SIO_CFG)
    #define Ch2In_SIO_HYST_EN        (* (reg8 *) Ch2In__SIO_HYST_EN)
    #define Ch2In_SIO_REG_HIFREQ     (* (reg8 *) Ch2In__SIO_REG_HIFREQ)
    #define Ch2In_SIO_CFG            (* (reg8 *) Ch2In__SIO_CFG)
    #define Ch2In_SIO_DIFF           (* (reg8 *) Ch2In__SIO_DIFF)
#endif /* (Ch2In__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ch2In__INTSTAT)
    #define Ch2In_INTSTAT            (* (reg8 *) Ch2In__INTSTAT)
    #define Ch2In_SNAP               (* (reg8 *) Ch2In__SNAP)
    
	#define Ch2In_0_INTTYPE_REG 		(* (reg8 *) Ch2In__0__INTTYPE)
#endif /* (Ch2In__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ch2In_H */


/* [] END OF FILE */
