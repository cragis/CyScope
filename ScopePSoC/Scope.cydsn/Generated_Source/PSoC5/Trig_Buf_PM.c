/*******************************************************************************
* File Name: Trig_Buf_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Trig_Buf.h"

static Trig_Buf_BACKUP_STRUCT  Trig_Buf_backup;


/*******************************************************************************  
* Function Name: Trig_Buf_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Trig_Buf_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Trig_Buf_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Trig_Buf_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Trig_Buf_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Trig_Buf_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Trig_Buf_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Trig_Buf_PM_ACT_CFG_REG & Trig_Buf_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Trig_Buf_backup.enableState = 1u;
         /* Stops the component */
         Trig_Buf_Stop();
    }
    else
    {
        /* Component is disabled */
        Trig_Buf_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Trig_Buf_SaveConfig();
}


/*******************************************************************************  
* Function Name: Trig_Buf_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Trig_Buf_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Trig_Buf_Wakeup(void) 
{
    /* Restore the user configuration */
    Trig_Buf_RestoreConfig();

    /* Enables the component operation */
    if(Trig_Buf_backup.enableState == 1u)
    {
        Trig_Buf_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
