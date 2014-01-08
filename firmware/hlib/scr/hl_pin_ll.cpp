#include "hlib.h"
//#include "hl_pin_ll.h"



namespace HLib_LL{

pin_ll_c::pin_ll_c(HLib::clk_periph_t clk, GPIO_Typedef* port, uint16_t pin){
  this->clk  = clk;
  this->port = port;
  this->pin   = pin;
} 


HLib::err_t pin_ll_c::SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type){
  GPIO_InitTypeDef  GPIO_InitStruct;
  
	if (HLib::GPIO == mode){
		switch (type){
			case HLib::IN_FLOATING:    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
			case HLib::IN_PULL_UP:     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; break;
			case HLib::IN_PULL_DOWN:   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; break;
			case HLib::OUT_PUSH_PULL:  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; break;
			case HLib::OUT_OPEN_DRAIN: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
			default: return HLib::HL_INVALID;
		}
	}
	else if (HLib::PERIPHERAL ==mode){
		switch (type){
			case HLib::IN_ANALOG:
			case HLib::OUT_ANALOG:     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; break;
			case HLib::IN_FLOATING:    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
			case HLib::IN_PULL_UP:     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; break;
			case HLib::IN_PULL_DOWN:   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; break;
			case HLib::OUT_PUSH_PULL:  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; break;
			case HLib::OUT_OPEN_DRAIN: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
			default: return HLib::HL_INVALID;
		}	
	}
	else{
		return HLib::HL_INVALID;
	}
	GPIO_InitStruct.GPIO_Pin   = HL_BitMask(pin);
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	HLib::CLK_Ctrl(clk, true);
	GPIO_Init(port, &GPIO_InitStruct);
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
