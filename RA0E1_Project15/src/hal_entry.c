#include "hal_data.h"
#include <stdio.h>
#include "lps28dfw_reg.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER


fsp_err_t err = FSP_SUCCESS;
volatile bool uart_send_complete_flag = false;
void user_uart_callback (uart_callback_args_t * p_args)
{
    if(p_args->event == UART_EVENT_TX_COMPLETE)
    {
        uart_send_complete_flag = true;
    }
}


#ifdef __GNUC__                                 //串口重定向
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif


PUTCHAR_PROTOTYPE
{
        err = R_UARTA_Write(&g_uart0_ctrl, (uint8_t *)&ch, 1);
        if(FSP_SUCCESS != err) __BKPT();
        while(uart_send_complete_flag == false){}
        uart_send_complete_flag = false;
        return ch;
}

int _write(int fd,char *pBuffer,int size)
{
    for(int i=0;i<size;i++)
    {
        __io_putchar(*pBuffer++);
    }
    return size;
}

/* Callback function */
i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;
uint32_t  timeout_ms = 100000;
void iica_master_callback(i2c_master_callback_args_t *p_args)
{
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}


#define SENSOR_BUS g_iica_master0_ctrl

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME         10 //ms

/* Private variables ---------------------------------------------------------*/
static uint8_t tx_buffer[1000];
static lps28dfw_data_t data;

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void tx_com( uint8_t *tx_buffer, uint16_t len );
static void platform_delay(uint32_t ms);
static void platform_init(void);


/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */



    /* Open the transfer instance with initial configuration. */
    err = R_UARTA_Open(&g_uart0_ctrl, &g_uart0_cfg);
    assert(FSP_SUCCESS == err);

    printf("hello!\n");

    /* Initialize the I2C module */
    err = R_IICA_MASTER_Open(&g_iica_master0_ctrl, &g_iica_master0_cfg);
    /* Handle any errors. This function should be defined by the user. */
    assert(FSP_SUCCESS == err);

    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_12, BSP_IO_LEVEL_LOW);


    lps28dfw_pin_int_route_t int_route;
    lps28dfw_all_sources_t all_sources;
    lps28dfw_bus_mode_t bus_mode;
    lps28dfw_stat_t status;
    stmdev_ctx_t dev_ctx;
    lps28dfw_id_t id;
    lps28dfw_md_t md;

    /* Initialize mems driver interface */
    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.mdelay = platform_delay;
    dev_ctx.handle = &SENSOR_BUS;

    /* Initialize platform specific hardware */
//    platform_init();

    /* Wait sensor boot time */
    platform_delay(BOOT_TIME);

    /* Check device ID */
    lps28dfw_id_get(&dev_ctx, &id);
    printf("LPS28DFW_ID=0x%x,id.whoami=0x%x\n",LPS28DFW_ID,id.whoami);
    if (id.whoami != LPS28DFW_ID)
      while(1);

    /* Restore default configuration */
    lps28dfw_init_set(&dev_ctx, LPS28DFW_RESET);
    do {
      lps28dfw_status_get(&dev_ctx, &status);
    } while (status.sw_reset);

    /* Set bdu and if_inc recommended for driver usage */
    lps28dfw_init_set(&dev_ctx, LPS28DFW_DRV_RDY);

    /* Select bus interface */
    bus_mode.filter = LPS28DFW_AUTO;
    bus_mode.interface = LPS28DFW_SEL_BY_HW;
    lps28dfw_bus_mode_set(&dev_ctx, &bus_mode);

    /* Set Output Data Rate */
    md.odr = LPS28DFW_4Hz;
    md.avg = LPS28DFW_16_AVG;
    md.lpf = LPS28DFW_LPF_ODR_DIV_4;
    md.fs = LPS28DFW_1260hPa;
    lps28dfw_mode_set(&dev_ctx, &md);

    /* Configure inerrupt pins */
    lps28dfw_pin_int_route_get(&dev_ctx, &int_route);
    int_route.drdy_pres   = PROPERTY_DISABLE;
    lps28dfw_pin_int_route_set(&dev_ctx, &int_route);

    /* Read samples in polling mode (no int) */
    while(1)
    {

      /* Read output only if new values are available */
      lps28dfw_all_sources_get(&dev_ctx, &all_sources);
      if ( all_sources.drdy_pres | all_sources.drdy_temp ) {
        lps28dfw_data_get(&dev_ctx, &md, &data);

        printf("pressure [hPa]:%6.2f temperature [degC]:%6.2f\r\n",
                data.pressure.hpa, data.heat.deg_c);

      }

    }




#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}








/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,uint16_t len)
{
    // 创建一个足够大的缓冲区来包含寄存器地址和数据
    uint8_t data[len + 1];
    data[0] = reg; // 将寄存器地址放在数据的开始
    memcpy(&data[1], bufp, len); // 复制数据到缓冲区

    err = R_IICA_MASTER_Write(&g_iica_master0_ctrl, data, len+1, true);
    assert(FSP_SUCCESS == err);
    /* Since there is nothing else to do, block until Callback triggers*/
    //while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms)
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms>0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
        }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
    }
    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms           = 100000;
    return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,uint16_t len)
{
    err = R_IICA_MASTER_Write(&g_iica_master0_ctrl, &reg, 1, true);
    assert(FSP_SUCCESS == err);
    /* Since there is nothing else to do, block until Callback triggers*/
    //while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms)
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms>0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
        }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
        }
    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms           = 100000;

    /* Read data from I2C slave */
    err = R_IICA_MASTER_Read(&g_iica_master0_ctrl, bufp, len, false);
    assert(FSP_SUCCESS == err);
    while ((I2C_MASTER_EVENT_RX_COMPLETE != i2c_event) && timeout_ms)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
        timeout_ms--;
    }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
    }

    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms           = 100000;
  return 0;
}



/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */
static void platform_delay(uint32_t ms)
{
    R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
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
        R_IOPORT_Open (&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);

#if BSP_CFG_SDRAM_ENABLED

        /* Setup SDRAM and initialize it. Must configure pins first. */
        R_BSP_SdramInit(true);
#endif
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
