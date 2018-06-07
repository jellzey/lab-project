/*******************************************************************************
* File Name: Pot2.h  
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

#if !defined(CY_PINS_Pot2_H) /* Pins Pot2_H */
#define CY_PINS_Pot2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pot2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pot2__PORT == 15 && ((Pot2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pot2_Write(uint8 value);
void    Pot2_SetDriveMode(uint8 mode);
uint8   Pot2_ReadDataReg(void);
uint8   Pot2_Read(void);
void    Pot2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pot2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pot2_SetDriveMode() function.
     *  @{
     */
        #define Pot2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pot2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pot2_DM_RES_UP          PIN_DM_RES_UP
        #define Pot2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pot2_DM_OD_LO           PIN_DM_OD_LO
        #define Pot2_DM_OD_HI           PIN_DM_OD_HI
        #define Pot2_DM_STRONG          PIN_DM_STRONG
        #define Pot2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pot2_MASK               Pot2__MASK
#define Pot2_SHIFT              Pot2__SHIFT
#define Pot2_WIDTH              1u

/* Interrupt constants */
#if defined(Pot2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pot2_SetInterruptMode() function.
     *  @{
     */
        #define Pot2_INTR_NONE      (uint16)(0x0000u)
        #define Pot2_INTR_RISING    (uint16)(0x0001u)
        #define Pot2_INTR_FALLING   (uint16)(0x0002u)
        #define Pot2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pot2_INTR_MASK      (0x01u) 
#endif /* (Pot2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pot2_PS                     (* (reg8 *) Pot2__PS)
/* Data Register */
#define Pot2_DR                     (* (reg8 *) Pot2__DR)
/* Port Number */
#define Pot2_PRT_NUM                (* (reg8 *) Pot2__PRT) 
/* Connect to Analog Globals */                                                  
#define Pot2_AG                     (* (reg8 *) Pot2__AG)                       
/* Analog MUX bux enable */
#define Pot2_AMUX                   (* (reg8 *) Pot2__AMUX) 
/* Bidirectional Enable */                                                        
#define Pot2_BIE                    (* (reg8 *) Pot2__BIE)
/* Bit-mask for Aliased Register Access */
#define Pot2_BIT_MASK               (* (reg8 *) Pot2__BIT_MASK)
/* Bypass Enable */
#define Pot2_BYP                    (* (reg8 *) Pot2__BYP)
/* Port wide control signals */                                                   
#define Pot2_CTL                    (* (reg8 *) Pot2__CTL)
/* Drive Modes */
#define Pot2_DM0                    (* (reg8 *) Pot2__DM0) 
#define Pot2_DM1                    (* (reg8 *) Pot2__DM1)
#define Pot2_DM2                    (* (reg8 *) Pot2__DM2) 
/* Input Buffer Disable Override */
#define Pot2_INP_DIS                (* (reg8 *) Pot2__INP_DIS)
/* LCD Common or Segment Drive */
#define Pot2_LCD_COM_SEG            (* (reg8 *) Pot2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pot2_LCD_EN                 (* (reg8 *) Pot2__LCD_EN)
/* Slew Rate Control */
#define Pot2_SLW                    (* (reg8 *) Pot2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pot2_PRTDSI__CAPS_SEL       (* (reg8 *) Pot2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pot2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pot2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pot2_PRTDSI__OE_SEL0        (* (reg8 *) Pot2__PRTDSI__OE_SEL0) 
#define Pot2_PRTDSI__OE_SEL1        (* (reg8 *) Pot2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pot2_PRTDSI__OUT_SEL0       (* (reg8 *) Pot2__PRTDSI__OUT_SEL0) 
#define Pot2_PRTDSI__OUT_SEL1       (* (reg8 *) Pot2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pot2_PRTDSI__SYNC_OUT       (* (reg8 *) Pot2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pot2__SIO_CFG)
    #define Pot2_SIO_HYST_EN        (* (reg8 *) Pot2__SIO_HYST_EN)
    #define Pot2_SIO_REG_HIFREQ     (* (reg8 *) Pot2__SIO_REG_HIFREQ)
    #define Pot2_SIO_CFG            (* (reg8 *) Pot2__SIO_CFG)
    #define Pot2_SIO_DIFF           (* (reg8 *) Pot2__SIO_DIFF)
#endif /* (Pot2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pot2__INTSTAT)
    #define Pot2_INTSTAT            (* (reg8 *) Pot2__INTSTAT)
    #define Pot2_SNAP               (* (reg8 *) Pot2__SNAP)
    
	#define Pot2_0_INTTYPE_REG 		(* (reg8 *) Pot2__0__INTTYPE)
#endif /* (Pot2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pot2_H */


/* [] END OF FILE */
