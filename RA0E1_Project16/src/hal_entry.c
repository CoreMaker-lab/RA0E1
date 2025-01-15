#include "hal_data.h"
#include <stdio.h>
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


//RTC变量
/* rtc_time_t is an alias for the C Standard time.h struct 'tm' */
rtc_time_t set_time =
{
    .tm_sec  = 50,      /* 秒，范围从 0 到 59 */
    .tm_min  = 59,      /* 分，范围从 0 到 59 */
    .tm_hour = 23,      /* 小时，范围从 0 到 23*/
    .tm_mday = 14,       /* 一月中的第几天，范围从 0 到 30*/
    .tm_mon  = 1,      /* 月份，范围从 0 到 11*/
    .tm_year = 125,     /* 自 1900 起的年数，2025为125*/
    .tm_wday = 2,       /* 一周中的第几天，范围从 0 到 6*/
//    .tm_yday=0,         /* 一年中的第几天，范围从 0 到 365*/
//    .tm_isdst=0;        /* 夏令时*/
};


//RTC闹钟变量
rtc_alarm_time_t set_alarm_time=
{
     .time_minute=00,
     .time_hour=0,
     .sunday_match=0 , ///< Enable the alarm on Sunday
     .monday_match=0 , ///< Enable the alarm on Monday
     .tuesday_match=0 , ///< Enable the alarm on Tuesday
     .wednesday_match=1 , ///< Enable the alarm on Wednesday
     .thursday_match=0 ,///< Enable the alarm on Thursday
     .friday_match=0 ,///< Enable the alarm on Friday
     .saturday_match=0 ,//

    };

//RTC回调函数
volatile bool rtc_flag = 0;//RTC延时1s标志位
volatile bool rtc_alarm_flag = 0;//RTC闹钟
/* Callback function */
void rtc_callback(rtc_callback_args_t *p_args)
{
    /* TODO: add your own code here */
    if(p_args->event == RTC_EVENT_PERIODIC_IRQ)
        rtc_flag=1;
    else if(p_args->event == RTC_EVENT_ALARM_IRQ)
        rtc_alarm_flag=1;
}


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

    printf("hello\n");


    /**********************RTC开启***************************************/
        /* Initialize the RTC module*/
        err = R_RTC_C_Open(&g_rtc0_ctrl, &g_rtc0_cfg);
        /* Handle any errors. This function should be defined by the user. */
        assert(FSP_SUCCESS == err);

        /* Set the RTC clock source. Can be skipped if "Set Source Clock in Open" property is enabled. */
        R_RTC_C_ClockSourceSet(&g_rtc0_ctrl);

        /* R_RTC_CalendarTimeSet must be called at least once to start the RTC */
        R_RTC_C_CalendarTimeSet(&g_rtc0_ctrl, &set_time);
        /* Set the periodic interrupt rate to 1 second */
        R_RTC_C_PeriodicIrqRateSet(&g_rtc0_ctrl, RTC_PERIODIC_IRQ_SELECT_1_SECOND);

        R_RTC_C_CalendarAlarmSet(&g_rtc0_ctrl, &set_alarm_time);
        uint8_t rtc_second= 0;      //秒
        uint8_t rtc_minute =0;      //分
        uint8_t rtc_hour =0;         //时
        uint8_t rtc_day =0;          //日
        uint8_t rtc_month =0;      //月
        uint16_t rtc_year =0;        //年
        uint8_t rtc_week =0;        //周
        rtc_time_t get_time;


        while(1)
        {
            if(rtc_flag)
            {
                R_RTC_C_CalendarTimeGet(&g_rtc0_ctrl, &get_time);//获取RTC计数时间
                rtc_flag=0;
                rtc_second=get_time.tm_sec;//秒
                rtc_minute=get_time.tm_min;//分
                rtc_hour=get_time.tm_hour;//时
                rtc_day=get_time.tm_mday;//日
                rtc_month=get_time.tm_mon;//月
                rtc_year=get_time.tm_year; //年
                rtc_week=get_time.tm_wday;//周
                printf(" %d y %d m %d d %d h %d m %d s %d w\n",rtc_year+1900,rtc_month,rtc_day,rtc_hour,rtc_minute,rtc_second,rtc_week);

                uint8_t num1,num2,num3,num4;
                 //时间显示
                num1=rtc_hour/10;
                num2=rtc_hour%10;

                num3=rtc_minute/10;
                num4=rtc_minute%10;
            }
            if(rtc_alarm_flag)
            {
                rtc_alarm_flag=0;
                printf("/************************Alarm Clock********************************/\n");
            }

            R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MILLISECONDS);



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
