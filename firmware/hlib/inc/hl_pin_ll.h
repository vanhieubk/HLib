#ifndef __HL_PIN_LL
#define __HL_PIN_LL

namespace HLib{

/**
 @brief Available mode of PINs in an MBoard
 @attention Platforms which use STM32F10x MCU such as STM32F100_STARTER, MBoard1
 are only support GPIO and PERIPHERAL modes. The others are reserved for the future
*/
typedef enum{
  GPIO, 		  /**< Pin is connected with the general purpose input/output, used for getting 0/1 input or controlling 0/1 output */
	PERIPHERAL,   /**< Pin is connected with an unspecified peripheral*/
  ADC1_CH_0, 	/**< Pin is connected with channel 0 of ADC0*/ 
  ADC1_CH_1, 	/**< Pin is connected with channel 1 of ADC0*/
  ADC1_CH_2, 	/**< Pin is connected with channel 2 of ADC0*/
  ADC1_CH_3, 	/**< Pin is connected with channel 3 of ADC0*/
  TIM2_CH_1, 	/**< Pin is connected with channel 1 of TIM2*/
  TIM2_CH_2, 	/**< Pin is connected with channel 2 of TIM2*/
  TIM2_CH_3, 	/**< Pin is connected with channel 3 of TIM2*/
  TIM2_CH_4, 	/**< Pin is connected with channel 4 of TIM2*/
  UART2_TXD, 	/**< Pin is connected with TxD of UART2*/
  UART2_RXD, 	/**< Pin is connected with RxD of UART2*/
  SPI1_NSS, 	/**< Pin is connected with NSS of SPI1*/
  SPI1_MISO, 	/**< Pin is connected with MISO of SPI1*/
  SPI1_MOSI, 	/**< Pin is connected with MOSI of SPI1*/
  SPI1_SCK, 	/**< Pin is connected with SCK of SPI1*/
  DAC1_OUT_1, /**< Pin is connected with channel 1 of DAC1*/
  DAC1_OUT_2, /**< Pin is connected with channel 2 of DAC1*/
  I2C1_SCL, 	/**< Pin is connected with SCL of I2C1*/
  I2C1_SDA 		/**< Pin is connected with SDA of I2C1*/
} pin_mode_t;


/**
 @brief Electrical type of PINs in an MBoard
*/
typedef enum {
  IN_ANALOG, 	   /**< An analog input, used for ADC mode */
  IN_FLOATING,   /**< An floating input */
  IN_PULL_UP, 	 /**< An input with pull-up resistor */
  IN_PULL_DOWN,  /**< An input with pull-down resistor */
  OUT_ANALOG,    /**< An analog output, used for DAC mode */
  OUT_PUSH_PULL, /**< An push-pull output */
  OUT_OPEN_DRAIN /**< An open drain output */
} pin_type_t;
} /*namespace HLib */


namespace HLib_LL {

/**
 @brief Low-level PINs class.
 @attention This class is used internal in HLib. Normal users shouldn't touch this
*/
class pin_ll_c {
private:
  HLib::clk_periph_t  clk;  /**< Clock source of GPIO */
  GPIO_TypeDef* port; /**< Port of a I/O pin */
  uint8_t       pin;  /**< Pin number of a I/O pin */
public:
  pin_ll_c(HLib::clk_periph_t clk, GPIO_TypeDef* port, uint8_t pin);  
  HLib::err_t SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type);
  void Release();
  void OutOne();
  void OutZero();
  void OutVal(bool val);
  bool GetInput();
};

} /* namespace HLib__LL */

#endif /* __HL_PIN_LL */
