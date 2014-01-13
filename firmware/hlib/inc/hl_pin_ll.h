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
	PERIPHERAL, /**< Pin is connected with an unspecified peripheral*/
} pin_mode_t;


/**
 @brief Electrical type of PINs in an MBoard
*/
typedef enum {
  IN_ANALOG, 	   /**< An analog input, used for ADC PERIPHERAL only */
  IN_FLOATING,   /**< An floating input */
  IN_PULL_UP, 	 /**< An input with pull-up resistor */
  IN_PULL_DOWN,  /**< An input with pull-down resistor */
  OUT_ANALOG,    /**< An analog output, used for DAC PERIPHERAL only */
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
