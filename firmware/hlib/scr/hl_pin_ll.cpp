#include "hlib.h"


namespace HLib_LL{

pin_ll_c::pin_ll_c(HLib::clk_periph_t clk, GPIO_TypeDef* port, uint8_t pin){
  this->clk   = clk;
  this->port  = port;
  this->pin   = pin;
} 


HLib::err_t pin_ll_c::SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type){
  uint32_t configBits;
  uint32_t reg;

	if (HLib::GPIO == mode){
		switch (type){
			case HLib::IN_FLOATING:    configBits = 0x04; break;
			case HLib::IN_PULL_UP:     configBits = 0x08; break;
			case HLib::IN_PULL_DOWN:   configBits = 0x08; break;
			case HLib::OUT_PUSH_PULL:  configBits = 0x03; break;
			case HLib::OUT_OPEN_DRAIN: configBits = 0x07; break;
			default: return HLib::HL_INVALID;
		}
	}
	else if (HLib::PERIPHERAL ==mode){
		switch (type){
			case HLib::IN_ANALOG:
			case HLib::OUT_ANALOG:     configBits = 0x00; break;
			case HLib::IN_FLOATING:    configBits = 0x04; break;
			case HLib::IN_PULL_UP:     configBits = 0x08; break;
			case HLib::IN_PULL_DOWN:   configBits = 0x08; break;
			case HLib::OUT_PUSH_PULL:  configBits = 0x0B; break;
			case HLib::OUT_OPEN_DRAIN: configBits = 0x0F; break;
			default: return HLib::HL_INVALID;
		}	
	}
	else{
		return HLib::HL_INVALID;
	}
  /* update register */
  if (pin <8){
    configBits  =  (configBits << (pin*4));
    reg         =  port->CRL;
    reg         &= ~(((uint32_t) 0x0F) << (pin*4));
    reg         |= configBits;
    port->CRL   = reg;
  }
  else if (pin <16){
    configBits  =  (configBits << ((pin-8)*4));
    reg         =  port->CRH;
    reg         &= ~(((uint32_t) 0x0F) << ((pin-8)*4));
    reg         |= configBits;
    port->CRH   = reg;
  }
  else{
    return HLib::HL_INVALID;
  }
  /* config pullup/pulldown resistor */
  if (HLib::IN_PULL_UP == type){
    port->BSRR = HL_BitMask(pin);
  }
  else if (HLib::IN_PULL_DOWN == type){
    port->BRR = HL_BitMask(pin);
  }
	return HLib::HL_OK;
}


void pin_ll_c::Release(){
  SetMode(HLib::GPIO, HLib::IN_FLOATING);
}


void pin_ll_c::OutOne(){
  port->BSRR = HL_BitMask(pin);
}


void pin_ll_c::OutZero(){
  port->BRR = HL_BitMask(pin);
}


void pin_ll_c::OutVal(bool val){
  if (val){
    OutOne();
  }
  else{
    OutZero();
  }
}


bool pin_ll_c::GetInput(){
  return (bool) (port->IDR & HL_BitMask(pin));
}

} /* namespace HLib_LL */
