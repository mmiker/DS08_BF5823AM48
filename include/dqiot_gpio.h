
#ifndef __DQIOT_GPIO_H__

#define __DQIOT_GPIO_H__

#include "mmi_feature.h"
#include "mcu02_gpio.h"


#define EXT_LDO_PORT 		GPIOH
#define EXT_LDO_PIN			GPIO_PIN_4

#define KEY_LED_1_PORT		GPIOB
#define KEY_LED_1_PIN		GPIO_PIN_5

#define KEY_LED_2_PORT		GPIOB
#define KEY_LED_2_PIN		GPIO_PIN_6

#define KEY_LED_3_PORT		GPIOB
#define KEY_LED_3_PIN		GPIO_PIN_7

#define RGB_LED_R_PORT		GPIOB
#define RGB_LED_R_PIN		GPIO_PIN_0

#define RGB_LED_G_PORT		GPIOB
#define RGB_LED_G_PIN		GPIO_PIN_1

#define RGB_LED_B_PORT		GPIOB
#define RGB_LED_B_PIN		GPIO_PIN_2

#define AUD_BUSY_PORT		GPIOA
#define AUD_BUSY_PIN		GPIO_PIN_1

#define AUD_DATA_PORT		GPIOA
#define AUD_DATA_PIN		GPIO_PIN_0

#define AUD_RST_PORT		GPIOG
#define AUD_RST_PIN			GPIO_PIN_2

#define FP_PWR_PORT			GPIOF
#define FP_PWR_PIN			GPIO_PIN_7

#define FP_INT_PORT			GPIOF
#define FP_INT_PIN			GPIO_PIN_6

#define FP_TX_PORT			GPIOF
#define FP_TX_PIN			GPIO_PIN_4

#define FP_RX_PORT			GPIOF
#define FP_RX_PIN			GPIO_PIN_5

#define MOTOR_PWREN_PORT	GPIOH
#define MOTOR_PWREN_PIN		GPIO_PIN_0

#define MOTOR_A_PORT		GPIOH
#define MOTOR_A_PIN			GPIO_PIN_2

#define MOTOR_B_PORT		GPIOH
#define MOTOR_B_PIN			GPIO_PIN_1

#define VBAT_TEST_PORT		GPIOG
#define VBAT_TEST_PIN		GPIO_PIN_3

#define VBAT_ADC_PORT		GPIOH
#define VBAT_ADC_PIN		GPIO_PIN_6

#define WIFI_SDA_PORT		GPIOC
#define WIFI_SDA_PIN		GPIO_PIN_4

#define WIFI_SCL_PORT		GPIOC
#define WIFI_SCL_PIN		GPIO_PIN_3

#define RESET_PORT			GPIOB
#define RESET_PIN			GPIO_PIN_3

#define SW_PORT				GPIOH
#define SW_PIN				GPIO_PIN_5

#endif
