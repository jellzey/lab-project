/*******************************************************************************
* File Name: Wave.h  
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

#if !defined(CY_PINS_Wave_H) /* Pins Wave_H */
#define CY_PINS_Wave_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Wave_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Wave__PORT == 15 && ((Wave__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Wave_Write(uint8 value);
void    Wave_SetDriveMode(uint8 mode);
uint8   Wave_ReadDataReg(void);
uint8   Wave_Read(void);
void    Wave_SetInterruptMode(uint16 position, uint16 mode);
uint8   Wave_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Wave_SetDriveMode() function.
     *  @{
     */
        #define Wave_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Wave_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Wave_DM_RES_UP          PIN_DM_RES_UP
        #define Wave_DM_RES_DWN         PIN_DM_RES_DWN
        #define Wave_DM_OD_LO           PIN_DM_OD_LO
        #define Wave_DM_OD_HI           PIN_DM_OD_HI
        #define Wave_DM_STRONG          PIN_DM_STRONG
        #define Wave_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Wave_MASK               Wave__MASK
#define Wave_SHIFT              Wave__SHIFT
#define Wave_WIDTH              1u

/* Interrupt constants */
#if defined(Wave__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Wave_SetInterruptMode() function.
     *  @{
     */
        #define Wave_INTR_NONE      (uint16)(0x0000u)
        #define Wave_INTR_RISING    (uint16)(0x0001u)
        #define Wave_INTR_FALLING   (uint16)(0x0002u)
        #define Wave_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Wave_INTR_MASK      (0x01u) 
#endif /* (Wave__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Wave_PS                     (* (reg8 *) Wave__PS)
/* Data Register */
#define Wave_DR                     (* (reg8 *) Wave__DR)
/* Port Number */
#define Wave_PRT_NUM                (* (reg8 *) Wave__PRT) 
/* Connect to Analog Globals */                                                  
#define Wave_AG                     (* (reg8 *) Wave__AG)                       
/* Analog MUX bux enable */
#define Wave_AMUX                   (* (reg8 *) Wave__AMUX) 
/* Bidirectional Enable */                                                        
#define Wave_BIE                    (* (reg8 *) Wave__BIE)
/* Bit-mask for Aliased Register Access */
#define Wave_BIT_MASK               (* (reg8 *) Wave__BIT_MASK)
/* Bypass Enable */
#define Wave_BYP                    (* (reg8 *) Wave__BYP)
/* Port wide control signals */                                                   
#define Wave_CTL                    (* (reg8 *) Wave__CTL)
/* Drive Modes */
#define Wave_DM0                    (* (reg8 *) Wave__DM0) 
#define Wave_DM1                    (* (reg8 *) Wave__DM1)
#define Wave_DM2                    (* (reg8 *) Wave__DM2) 
/* Input Buffer Disable Override */
#define Wave_INP_DIS                (* (reg8 *) Wave__INP_DIS)
/* LCD Common or Segment Drive */
#define Wave_LCD_COM_SEG            (* (reg8 *) Wave__LCD_COM_SEG)
/* Enable Segment LCD */
#define Wave_LCD_EN                 (* (reg8 *) Wave__LCD_EN)
/* Slew Rate Control */
#define Wave_SLW                    (* (reg8 *) Wave__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Wave_PRTDSI__CAPS_SEL       (* (reg8 *) Wave__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Wave_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Wave__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Wave_PRTDSI__OE_SEL0        (* (reg8 *) Wave__PRTDSI__OE_SEL0) 
#define Wave_PRTDSI__OE_SEL1        (* (reg8 *) Wave__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Wave_PRTDSI__OUT_SEL0       (* (reg8 *) Wave__PRTDSI__OUT_SEL0) 
#define Wave_PRTDSI__OUT_SEL1       (* (reg8 *) Wave__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Wave_PRTDSI__SYNC_OUT       (* (reg8 *) Wave__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Wave__SIO_CFG)
    #define Wave_SIO_HYST_EN        (* (reg8 *) Wave__SIO_HYST_EN)
    #define Wave_SIO_REG_HIFREQ     (* (reg8 *) Wave__SIO_REG_HIFREQ)
    #define Wave_SIO_CFG            (* (reg8 *) Wave__SIO_CFG)
    #define Wave_SIO_DIFF           (* (reg8 *) Wave__SIO_DIFF)
#endif /* (Wave__SIO_CFG) */

/* Interrupt Registers */
#if defined(Wave__INTSTAT)
    #define Wave_INTSTAT            (* (reg8 *) Wave__INTSTAT)
    #define Wave_SNAP               (* (reg8 *) Wave__SNAP)
    
	#define Wave_0_INTTYPE_REG 		(* (reg8 *) Wave__0__INTTYPE)
#endif /* (Wave__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Wave_H */


/* [] END OF FILE */
