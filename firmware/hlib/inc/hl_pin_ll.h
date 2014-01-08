#ifndef __HL_PIN_LL
#define __HL_PIN_LL

namespace HLIb_LL {

/**
 @brief Low-level PINs class.
 @attention This class is used internal in HLib. Normal users shouldn't touch this
*/
class pin_ll_c {
private:
  HLib::clk_periph_t  clk;  /**< Clock source of GPIO */
  GPIO_TypeDef* port; /**< Port of a I/O pin */
  uint16_t      pin;  /**< Pin number of a I/O pin */
public:
  pin_ll_c(HLib::clk_periph_t clk, GPIO_Typedef* port, uint16_t pin);  
  HLib::err_t SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type);
  void Release();
  void OutOne();
  void OutZero();
  void OutVal(bool val);
  bool GetInput();
};

} /* namespace HLib__LL */

#endif /* __HL_PIN_LL */
