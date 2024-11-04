#include "hal_data.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */

    while(1)
    {
        /* Set P013、P014 to High */
//        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_13, BSP_IO_LEVEL_HIGH);
//        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_14, BSP_IO_LEVEL_LOW);
//        R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
//
//        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_13, BSP_IO_LEVEL_LOW);
//        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_14, BSP_IO_LEVEL_HIGH);
//        R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);

        /*向端口BSP_IO_PORT_00的第13位写入1，清除第14位
         * BSP_IO_PORT_00 是指定的端口。
         * 0x2000 是要写入的值，其中位13设置为1（0x2000 在二进制表示中为 0010 0000 0000 0000）。
         * 0x6000 是掩码，表示要更新的位是第13位和第14位（0x6000 在二进制表示中为 0110 0000 0000 0000）。此操作将位13设置为1，并清除位14。
         */
        R_IOPORT_PortWrite(&g_ioport_ctrl, BSP_IO_PORT_00, 0x2000, 0x6000);
        R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);
        /*向端口BSP_IO_PORT_00的第14位写入1，清除第13位
         * BSP_IO_PORT_00 是指定的端口。
         * 0x4000 是要写入的值，其中位14设置为1（0x4000 在二进制表示中为 0100 0000 0000 0000）。
         * 0x6000 是掩码，表示要更新的位是第13位和第14位（0x6000 在二进制表示中为 0110 0000 0000 0000）。此操作将位13设置为1，并清除位14。
         */
        R_IOPORT_PortWrite(&g_ioport_ctrl, BSP_IO_PORT_00, 0x4000, 0x6000);
        R_BSP_SoftwareDelay (100, BSP_DELAY_UNITS_MILLISECONDS);

    }






#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, &IOPORT_CFG_NAME);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
