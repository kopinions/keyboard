#pragma once
#ifndef KBD_GPIO_H
#define KBD_GPIO_H
#include <esp_err.h>

#ifndef BIT0

#define BIT0 0x00000001  /**< preprocessor alias for 32-bit value with bit 0 set, used to specify this single bit */
#define BIT1 0x00000002  /**< preprocessor alias for 32-bit value with bit 1 set, used to specify this single bit */
#define BIT2 0x00000004  /**< preprocessor alias for 32-bit value with bit 2 set, used to specify this single bit */
#define BIT3 0x00000008  /**< preprocessor alias for 32-bit value with bit 3 set, used to specify this single bit */
#define BIT4 0x00000010  /**< preprocessor alias for 32-bit value with bit 4 set, used to specify this single bit */
#define BIT5 0x00000020  /**< preprocessor alias for 32-bit value with bit 5 set, used to specify this single bit */
#define BIT6 0x00000040  /**< preprocessor alias for 32-bit value with bit 6 set, used to specify this single bit */
#define BIT7 0x00000080  /**< preprocessor alias for 32-bit value with bit 7 set, used to specify this single bit */
#define BIT8 0x00000100  /**< preprocessor alias for 32-bit value with bit 8 set, used to specify this single bit */
#define BIT9 0x00000200  /**< preprocessor alias for 32-bit value with bit 9 set, used to specify this single bit */
#define BIT10 0x00000400 /**< preprocessor alias for 32-bit value with bit 10 set, used to specify this single bit */
#define BIT11 0x00000800 /**< preprocessor alias for 32-bit value with bit 11 set, used to specify this single bit */
#define BIT12 0x00001000 /**< preprocessor alias for 32-bit value with bit 12 set, used to specify this single bit */
#define BIT13 0x00002000 /**< preprocessor alias for 32-bit value with bit 13 set, used to specify this single bit */
#define BIT14 0x00004000 /**< preprocessor alias for 32-bit value with bit 14 set, used to specify this single bit */
#define BIT15 0x00008000 /**< preprocessor alias for 32-bit value with bit 15 set, used to specify this single bit */
#define BIT16 0x00010000 /**< preprocessor alias for 32-bit value with bit 16 set, used to specify this single bit */
#define BIT17 0x00020000 /**< preprocessor alias for 32-bit value with bit 17 set, used to specify this single bit */
#define BIT18 0x00040000 /**< preprocessor alias for 32-bit value with bit 18 set, used to specify this single bit */
#define BIT19 0x00080000 /**< preprocessor alias for 32-bit value with bit 19 set, used to specify this single bit */
#define BIT20 0x00100000 /**< preprocessor alias for 32-bit value with bit 20 set, used to specify this single bit */
#define BIT21 0x00200000 /**< preprocessor alias for 32-bit value with bit 21 set, used to specify this single bit */
#define BIT22 0x00400000 /**< preprocessor alias for 32-bit value with bit 22 set, used to specify this single bit */
#define BIT23 0x00800000 /**< preprocessor alias for 32-bit value with bit 23 set, used to specify this single bit */
#define BIT24 0x01000000 /**< preprocessor alias for 32-bit value with bit 24 set, used to specify this single bit */
#define BIT25 0x02000000 /**< preprocessor alias for 32-bit value with bit 25 set, used to specify this single bit */
#define BIT26 0x04000000 /**< preprocessor alias for 32-bit value with bit 26 set, used to specify this single bit */
#define BIT27 0x08000000 /**< preprocessor alias for 32-bit value with bit 27 set, used to specify this single bit */
#define BIT28 0x10000000 /**< preprocessor alias for 32-bit value with bit 28 set, used to specify this single bit */
#define BIT29 0x20000000 /**< preprocessor alias for 32-bit value with bit 29 set, used to specify this single bit */
#define BIT30 0x40000000 /**< preprocessor alias for 32-bit value with bit 30 set, used to specify this single bit */
#define BIT31 0x80000000 /**< preprocessor alias for 32-bit value with bit 31 set, used to specify this single bit */

#endif /* BIT0 et al */

typedef enum {
  GPIO_DRIVE_CAP_0 = 0,       /*!< Pad drive capability: weak          */
  GPIO_DRIVE_CAP_1 = 1,       /*!< Pad drive capability: stronger      */
  GPIO_DRIVE_CAP_2 = 2,       /*!< Pad drive capability: medium */
  GPIO_DRIVE_CAP_DEFAULT = 2, /*!< Pad drive capability: medium */
  GPIO_DRIVE_CAP_3 = 3,       /*!< Pad drive capability: strongest     */
  GPIO_DRIVE_CAP_MAX,
} gpio_drive_cap_t;

#define GPIO_MODE_DEF_DISABLE (0)
#define GPIO_MODE_DEF_INPUT (BIT0)
#define GPIO_MODE_DEF_OUTPUT (BIT1)
#define GPIO_MODE_DEF_OD (BIT2)

typedef enum {
  GPIO_MODE_DISABLE = GPIO_MODE_DEF_DISABLE, /*!< GPIO mode : disable input and output             */
  GPIO_MODE_INPUT = GPIO_MODE_DEF_INPUT,     /*!< GPIO mode : input only                           */
  GPIO_MODE_OUTPUT = GPIO_MODE_DEF_OUTPUT,   /*!< GPIO mode : output only mode                     */
  GPIO_MODE_OUTPUT_OD =
      ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), /*!< GPIO mode : output only with open-drain mode     */
  GPIO_MODE_INPUT_OUTPUT_OD = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) |
                               (GPIO_MODE_DEF_OD)), /*!< GPIO mode : output and input with open-drain mode*/
  GPIO_MODE_INPUT_OUTPUT = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)), /*!< GPIO mode : output and input mode */
} gpio_mode_t;

typedef enum {
  GPIO_NUM_NC = -1, /*!< Use to signal not connected to S/W */
  GPIO_NUM_0 = 0,   /*!< GPIO0, input and output */
  GPIO_NUM_1 = 1,   /*!< GPIO1, input and output */
  GPIO_NUM_2 = 2,   /*!< GPIO2, input and output */
  GPIO_NUM_3 = 3,   /*!< GPIO3, input and output */
  GPIO_NUM_4 = 4,   /*!< GPIO4, input and output */
  GPIO_NUM_5 = 5,   /*!< GPIO5, input and output */
  GPIO_NUM_6 = 6,   /*!< GPIO6, input and output */
  GPIO_NUM_7 = 7,   /*!< GPIO7, input and output */
  GPIO_NUM_8 = 8,   /*!< GPIO8, input and output */
  GPIO_NUM_9 = 9,   /*!< GPIO9, input and output */
  GPIO_NUM_10 = 10, /*!< GPIO10, input and output */
  GPIO_NUM_11 = 11, /*!< GPIO11, input and output */
  GPIO_NUM_12 = 12, /*!< GPIO12, input and output */
  GPIO_NUM_13 = 13, /*!< GPIO13, input and output */
  GPIO_NUM_14 = 14, /*!< GPIO14, input and output */
  GPIO_NUM_15 = 15, /*!< GPIO15, input and output */
  GPIO_NUM_16 = 16, /*!< GPIO16, input and output */
  GPIO_NUM_17 = 17, /*!< GPIO17, input and output */
  GPIO_NUM_18 = 18, /*!< GPIO18, input and output */
  GPIO_NUM_19 = 19, /*!< GPIO19, input and output */
  GPIO_NUM_20 = 20, /*!< GPIO20, input and output */
  GPIO_NUM_21 = 21, /*!< GPIO21, input and output */
#if CONFIG_IDF_TARGET_ESP32
  GPIO_NUM_22 = 22, /*!< GPIO22, input and output */
  GPIO_NUM_23 = 23, /*!< GPIO23, input and output */

  GPIO_NUM_25 = 25, /*!< GPIO25, input and output */
#endif
  /* Note: The missing IO is because it is used inside the chip. */
  GPIO_NUM_26 = 26, /*!< GPIO26, input and output */
  GPIO_NUM_27 = 27, /*!< GPIO27, input and output */
  GPIO_NUM_28 = 28, /*!< GPIO28, input and output */
  GPIO_NUM_29 = 29, /*!< GPIO29, input and output */
  GPIO_NUM_30 = 30, /*!< GPIO30, input and output */
  GPIO_NUM_31 = 31, /*!< GPIO31, input and output */
  GPIO_NUM_32 = 32, /*!< GPIO32, input and output */
  GPIO_NUM_33 = 33, /*!< GPIO33, input and output */
  GPIO_NUM_34 = 34, /*!< GPIO34, input mode only(ESP32) / input and output(ESP32-S2) */
  GPIO_NUM_35 = 35, /*!< GPIO35, input mode only(ESP32) / input and output(ESP32-S2) */
  GPIO_NUM_36 = 36, /*!< GPIO36, input mode only(ESP32) / input and output(ESP32-S2) */
  GPIO_NUM_37 = 37, /*!< GPIO37, input mode only(ESP32) / input and output(ESP32-S2) */
  GPIO_NUM_38 = 38, /*!< GPIO38, input mode only(ESP32) / input and output(ESP32-S2) */
  GPIO_NUM_39 = 39, /*!< GPIO39, input mode only(ESP32) / input and output(ESP32-S2) */
#if GPIO_PIN_COUNT > 40
  GPIO_NUM_40 = 40, /*!< GPIO40, input and output */
  GPIO_NUM_41 = 41, /*!< GPIO41, input and output */
  GPIO_NUM_42 = 42, /*!< GPIO42, input and output */
  GPIO_NUM_43 = 43, /*!< GPIO43, input and output */
  GPIO_NUM_44 = 44, /*!< GPIO44, input and output */
  GPIO_NUM_45 = 45, /*!< GPIO45, input and output */
  GPIO_NUM_46 = 46, /*!< GPIO46, input mode only */
#endif
  GPIO_NUM_MAX,
  /** @endcond */
} gpio_num_t;

esp_err_t gpio_set_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t strength) { return ESP_OK; }

int gpio_get_level(gpio_num_t gpio_num) { return 0; }

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level) { return ESP_OK; }

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode) { return ESP_OK; }
#endif  // KBD_GPIO_H
