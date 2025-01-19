/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (3)
#endif
/* ISR prototypes */
void rtc_c_alarm_prd_or_alm_isr(void);
void uarta_txi_isr(void);
void uarta_rxi_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_RTC_ALARM_OR_PERIOD ((IRQn_Type) 32) /* RTC ALARM OR PERIOD (Alarm or Periodic interrupt) */
#define RTC_ALARM_OR_PERIOD_IRQn          ((IRQn_Type) 32) /* RTC ALARM OR PERIOD (Alarm or Periodic interrupt) */
#define VECTOR_NUMBER_UARTA0_TXI ((IRQn_Type) 40) /* UARTA0 TXI (Transfer completion interrupt) */
#define UARTA0_TXI_IRQn          ((IRQn_Type) 40) /* UARTA0 TXI (Transfer completion interrupt) */
#define VECTOR_NUMBER_UARTA0_RXI ((IRQn_Type) 41) /* UARTA0 RXI (Reception transfer end) */
#define UARTA0_RXI_IRQn          ((IRQn_Type) 41) /* UARTA0 RXI (Reception transfer end) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
