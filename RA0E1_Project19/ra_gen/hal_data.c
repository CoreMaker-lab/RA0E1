/* generated HAL source file - do not edit */
#include "hal_data.h"
adc_d_instance_ctrl_t g_adc1_ctrl;

/* ADC conversion time 36.75 us, conversion start time: 4.25us */
const adc_d_extended_cfg_t g_adc1_cfg_extend =
{ .channel_mode = ADC_D_CHANNEL_MODE_SCAN, .operation_voltage = ADC_D_VOLTAGE_MODE_NORMAL_1, .conversion_clockdiv =
          ADC_D_CLOCK_DIV_1,
  .trigger_source = ADC_D_TRIGGER_SOURCE_SOFTWARE, .operation_trigger = ADC_D_TRIGGER_MODE_WAIT, .conversion_operation =
          ADC_D_CONVERSION_MODE_SEQUENTIAL,
  .upper_lower_bound = ADC_D_BOUNDARY_IN_RANGE, .negative_vref = ADC_D_NEGATIVE_VREF_VSS, .positive_vref =
          ADC_D_POSITIVE_VREF_VCC,
  .upper_bound_limit = 255, .lower_bound_limit = 0, };
const adc_cfg_t g_adc1_cfg =
{ .unit = 0, .mode = (adc_mode_t) 0, // Unused
  .resolution = ADC_RESOLUTION_12_BIT,
  .alignment = (adc_alignment_t) 0, // Unused
  .trigger = (adc_trigger_t) 0, // Unused
  .p_callback = adc1_callback,
  .p_context = NULL,
  .p_extend = &g_adc1_cfg_extend,
#if defined(VECTOR_NUMBER_ADC0_SCAN_END)
    .scan_end_irq        = VECTOR_NUMBER_ADC0_SCAN_END,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (2),
  .scan_end_b_irq = FSP_INVALID_VECTOR,
  .scan_end_b_ipl = BSP_IRQ_DISABLED, };

const adc_d_channel_cfg_t g_adc1_channel_cfg =
{ .channel_input = ADC_CHANNEL_4 };
/* Instance structure to use this module. */
const adc_instance_t g_adc1 =
{ .p_ctrl = &g_adc1_ctrl, .p_cfg = &g_adc1_cfg, .p_channel_cfg = &g_adc1_channel_cfg, .p_api = &g_adc_on_adc_d };
adc_d_instance_ctrl_t g_adc0_ctrl;

/* ADC conversion time 36.75 us, conversion start time: 4.25us */
const adc_d_extended_cfg_t g_adc0_cfg_extend =
{ .channel_mode = ADC_D_CHANNEL_MODE_SCAN, .operation_voltage = ADC_D_VOLTAGE_MODE_NORMAL_1, .conversion_clockdiv =
          ADC_D_CLOCK_DIV_1,
  .trigger_source = ADC_D_TRIGGER_SOURCE_SOFTWARE, .operation_trigger = ADC_D_TRIGGER_MODE_WAIT, .conversion_operation =
          ADC_D_CONVERSION_MODE_SEQUENTIAL,
  .upper_lower_bound = ADC_D_BOUNDARY_IN_RANGE, .negative_vref = ADC_D_NEGATIVE_VREF_VSS, .positive_vref =
          ADC_D_POSITIVE_VREF_VCC,
  .upper_bound_limit = 255, .lower_bound_limit = 0, };
const adc_cfg_t g_adc0_cfg =
{ .unit = 0, .mode = (adc_mode_t) 0, // Unused
  .resolution = ADC_RESOLUTION_12_BIT,
  .alignment = (adc_alignment_t) 0, // Unused
  .trigger = (adc_trigger_t) 0, // Unused
  .p_callback = adc_callback,
  .p_context = NULL,
  .p_extend = &g_adc0_cfg_extend,
#if defined(VECTOR_NUMBER_ADC0_SCAN_END)
    .scan_end_irq        = VECTOR_NUMBER_ADC0_SCAN_END,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (2),
  .scan_end_b_irq = FSP_INVALID_VECTOR,
  .scan_end_b_ipl = BSP_IRQ_DISABLED, };

const adc_d_channel_cfg_t g_adc0_channel_cfg =
{ .channel_input = ADC_CHANNEL_0 };
/* Instance structure to use this module. */
const adc_instance_t g_adc0 =
{ .p_ctrl = &g_adc0_ctrl, .p_cfg = &g_adc0_cfg, .p_channel_cfg = &g_adc0_channel_cfg, .p_api = &g_adc_on_adc_d };
uarta_instance_ctrl_t g_uart0_ctrl;

uarta_baud_setting_t g_uart0_baud_setting =
{
#if (BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)

  /* Baud rate calculated with Acutal_Error 0.79%. */
  /* The permissible baud rate error range during reception: -4.63% ~ 5.11% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOSC,
  .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1, .brgca = 35, .delay_time = 1
#elif (BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)

/* Baud rate calculated with Acutal_Error 0.79%. */
/* The permissible baud rate error range during reception: -4.63% ~ 5.11% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_HOCO
, .utanck_clock_b.utanck = UARTA_CLOCK_DIV_4
, .brgca = 35
, .delay_time = 1
 #elif (BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)

/* Baud rate calculated with Acutal_Error 2.12%. */ 
/* The permissible baud rate error range during reception: -4.49% ~ 4.94% */
  .utanck_clock_b.utasel = UARTA_CLOCK_SOURCE_MOCO
, .utanck_clock_b.utanck = UARTA_CLOCK_DIV_1
, .brgca = 17
, .delay_time = 1
 #elif ((BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_FSXP) || (BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO))

/* Baud rate calculated with Acutal_Error 100%. */
/* The permissible baud rate error range during reception: Invalid Range Error */
  .utanck_clock_b.utasel = 0
, .utanck_clock_b.utanck = 0
, .brgca = 0
, .delay_time = 31
 #elif (BSP_CFG_UARTA0_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK)

/* Baud rate calculated with Acutal_Error 100%. */
/* The permissible baud rate error range during reception: Invalid Range Error */
  .utanck_clock_b.utasel = 0
, .utanck_clock_b.utanck = 0
, .brgca = 0
, .delay_time = 31
 #endif
        };

/** UART extended configuration for UART on UARTA HAL driver */
const uarta_extended_cfg_t g_uart0_cfg_extend =
{ .transfer_dir = UARTA_DIR_BIT_LSB_FIRST, .transfer_level = UARTA_ALV_BIT_POSITIVE_LOGIC, .clock_output =
          UARTA_CLOCK_OUTPUT_DISABLED,
  .p_baud_setting = &g_uart0_baud_setting, };

/** UART interface configuration */
const uart_cfg_t g_uart0_cfg =
{ .channel = 0, .data_bits = UART_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
          user_uart_callback,
  .p_context = NULL, .p_extend = &g_uart0_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
  .rxi_ipl = (2),
  .txi_ipl = (2), .eri_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_UARTA0_RXI)
                .rxi_irq             = VECTOR_NUMBER_UARTA0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_UARTA0_TXI)
                .txi_irq             = VECTOR_NUMBER_UARTA0_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_UARTA0_ERRI)
                .eri_irq             = VECTOR_NUMBER_UARTA0_ERRI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
        };

/* Instance structure to use this module. */
const uart_instance_t g_uart0 =
{ .p_ctrl = &g_uart0_ctrl, .p_cfg = &g_uart0_cfg, .p_api = &g_uart_on_uarta };
void g_hal_init(void)
{
    g_common_init ();
}
