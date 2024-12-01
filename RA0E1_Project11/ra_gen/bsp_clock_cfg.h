/* generated configuration header file - do not edit */
#ifndef BSP_CLOCK_CFG_H_
#define BSP_CLOCK_CFG_H_
#define BSP_CFG_CLOCKS_SECURE (0)
#define BSP_CFG_CLOCKS_OVERRIDE (0)
#define BSP_CFG_XTAL_HZ (8000000) /* X1 8000000Hz */
#define BSP_CFG_XTAL_DIV (BSP_CLOCKS_SYS_CLOCK_DIV_1) /* X1 Div /1 */
#define BSP_CFG_HOCO_FREQUENCY (2) /* HOCO 32MHz */
#define BSP_CFG_HOCO_DIV (BSP_CLOCKS_SYS_CLOCK_DIV_1) /* HOCO Div /1 */
#define BSP_CFG_MOCO_DIV (BSP_CLOCKS_SYS_CLOCK_DIV_1) /* MOCO Div /1 */
#define BSP_CFG_CLOCK_SOURCE (3) /* ICLK Src: X1 */
#define BSP_CFG_TAU_CK00 (TIMER_SOURCE_DIV_1) /* TAU CK00 Div /1 */
#define BSP_CFG_TAU_CK01 (TIMER_SOURCE_DIV_1) /* TAU CK01 Div /1 */
#define BSP_CFG_TAU_CK02 (TIMER_SOURCE_DIV_2) /* TAU CK02 Div /2 */
#define BSP_CFG_TAU_CK03 (TIMER_SOURCE_DIV_256) /* TAU CK03 Div /256 */
#define BSP_CFG_SAU_CK00_DIV (BSP_CLOCKS_SAU_CLOCK_DIV_2) /* SAU CK00 Div /2 */
#define BSP_CFG_SAU_CK01_DIV (BSP_CLOCKS_SAU_CLOCK_DIV_1) /* SAU CK01 Div /1 */
#define BSP_CFG_SAU_CK10_DIV (BSP_CLOCKS_SAU_CLOCK_DIV_2) /* SAU CK10 Div /2 */
#define BSP_CFG_SAU_CK11_DIV (BSP_CLOCKS_SAU_CLOCK_DIV_1) /* SAU CK11 Div /1 */
#define BSP_CFG_CLKOUT_SOURCE (BSP_CLOCKS_CLOCK_DISABLED) /* CLKOUT Disabled */
#define BSP_CFG_CLKOUT_DIV (0x0U) /* CLKOUT Div /1 */
#define BSP_CFG_UARTA0_CLOCK_SOURCE (BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC) /* UARTA0 Src: X1 */
#define BSP_CFG_FSXP_SOURCE (BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK) /* FSXP Src: SUBCLK */
#define BSP_CFG_TML_FITL0_SOURCE (BSP_CLOCKS_CLOCK_DISABLED) /* TML FITL0 Src: ELC event/No BSP Source Clock */
#define BSP_CFG_TML_FITL1_SOURCE (BSP_CLOCKS_CLOCK_DISABLED) /* TML FITL1 Src: ELC event/No BSP Source Clock */
#define BSP_CFG_TML_FITL2_SOURCE (BSP_CLOCKS_CLOCK_DISABLED) /* TML FITL2 Disabled/No BSP Source Clock */
#endif /* BSP_CLOCK_CFG_H_ */
