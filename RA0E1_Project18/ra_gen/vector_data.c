/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [31] = adc_d_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [40] = uarta_txi_isr, /* UARTA0 TXI (Transfer completion interrupt) */
            [41] = uarta_rxi_isr, /* UARTA0 RXI (Reception transfer end) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [31] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP7), /* ADC0 SCAN END (End of A/D scanning operation) */
            [40] = BSP_PRV_VECT_ENUM(EVENT_UARTA0_TXI,FIXED), /* UARTA0 TXI (Transfer completion interrupt) */
            [41] = BSP_PRV_VECT_ENUM(EVENT_UARTA0_RXI,FIXED), /* UARTA0 RXI (Reception transfer end) */
        };
        #endif
        #endif
