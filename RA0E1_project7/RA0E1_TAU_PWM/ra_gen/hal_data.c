/* generated HAL source file - do not edit */
#include "hal_data.h"
const tau_pwm_channel_cfg_t g_timer_channel_cfg3 =
{ .channel = 3,
#define OPERATION_TIMER_MODE_ONE_SHOT (0xFFFFFFFF)
#if (OPERATION_TIMER_MODE_ONE_SHOT == OPERATION_TIMER_MODE_PWM)
    /* Actual pulse width: 0.008191875 seconds. */  .duty_cycle_counts = (uint16_t) 0xffff,
#else
  /* Actual duty cycle percent: 33 %. */.duty_cycle_counts = (uint16_t) 0x1b7,
#endif
#undef OPERATION_TIMER_MODE_ONE_SHOT
  .output_level = TAU_PWM_OUTPUT_LEVEL_LOW,
  .output_polarity = TAU_PWM_OUTPUT_POLARITY_ACTIVE_HIGH, .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_TAU0_TMI03)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI03,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
tau_pwm_instance_ctrl_t g_timer0_ctrl;
const tau_pwm_extended_cfg_t g_timer0_extend =
{ .operation_clock = TAU_PWM_OPERATION_CLOCK_CK00,
#define TRIGGER_TAU_PWM_SOURCE_PIN_INPUT (0xFFFFFFFF)
#if (TRIGGER_TAU_PWM_SOURCE_PIN_INPUT == TRIGGER_TAU_PWM_SOURCE_PIN_INPUT)
  .trigger_source = TAU_PWM_SOURCE_PIN_INPUT,
#else
    .trigger_source                  = TAU_PWM_SOURCE_ELC_EVENT,
#endif
#undef TRIGGER_TAU_PWM_SOURCE_PIN_INPUT
  .detect_edge = TAU_PWM_DETECT_EDGE_FALLING,
#define RA_NOT_DEFINED (0xFFFFFFFF)
#if (RA_NOT_DEFINED == 3)
    .p_slave_channel_cfgs[0]       = NULL,
#else

  .p_slave_channel_cfgs[0] = &g_timer_channel_cfg3,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[1] = NULL,
#else
    .p_slave_channel_cfgs[1]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[2] = NULL,
#else
    .p_slave_channel_cfgs[2]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[3] = NULL,
#else
    .p_slave_channel_cfgs[3]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[4] = NULL,
#else
    .p_slave_channel_cfgs[4]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[5] = NULL,
#else
    .p_slave_channel_cfgs[5]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_slave_channel_cfgs[6] = NULL,
#else
    .p_slave_channel_cfgs[6]       = &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
        };
const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PWM,
/* Actual pulse period: 0.000166625 seconds. */.period_counts = (uint32_t) 0x535,
  .source_div = (timer_source_div_t) BSP_CFG_TAU_CK00, .channel = 0, .p_callback = NULL,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &g_timer0_extend,
  .cycle_end_ipl = (2),
#if defined(VECTOR_NUMBER_TAU0_TMI00)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI00,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_tau_pwm };
void g_hal_init(void)
{
    g_common_init ();
}
