#include "hlib.h"
#include "tlc5971_c.h"

tlc5971_c::tlc5971_c(HLib::spi_base_c* spi){
  usedSpi = spi;
  SetCmd(0x25);
  SetFc(CreateFc(true, false, false, true, true));
  SetBlueBc(0x7F);
  SetGreenBc(0x7F);
  SetRedBc(0x7F);
  SetGs(3, 255, 255, 255);
  SetGs(2, 255, 255, 255);
  SetGs(1, 255, 255, 255);
  SetGs(0, 255, 255, 255);
}


void tlc5971_c::SetCmd(uint8_t cmdVal){
  pkt.header[0] &= 0x03;
  pkt.header[0] |= (cmdVal << 2);  
}

      
uint8_t tlc5971_c::CreateFc(bool outTmg, bool extGck, bool tmGrst, bool dspRpt, bool blank){
  uint8_t retFc = 0;
  if (blank){
    retFc |= 0x01;
  }
  if (dspRpt){
    retFc |= 0x02;
  }
  if (tmGrst){
    retFc |= 0x04;
  }
  if (extGck){
    retFc |= 0x08;
  }
  if (outTmg){
    retFc |= 0x10;
  }
  return retFc;
}


void tlc5971_c::SetFc(uint8_t fcVal){
  uint8_t tmp;
  tmp = fcVal >> 3; //get 2 MSB bits of 5-bit data
  pkt.header[0] &= 0xFC;
  pkt.header[0] |= tmp;
  tmp = (fcVal << 5); //get 3 LSB bits
  pkt.header[1] &= 0x1F;
  pkt.header[1] |= tmp;
}


void tlc5971_c::SetBlueBc(uint8_t bcVal){
  uint8_t tmp;
  tmp = bcVal >> 2; //get 5 MSB bits of 7-bit data
  pkt.header[1] &= 0xE0;
  pkt.header[1] |= tmp;
  tmp = (bcVal << 6); //get 2 LSB bits
  pkt.header[2] &= 0x3F;
  pkt.header[2] |= tmp;
}



void tlc5971_c::SetGreenBc(uint8_t bcVal){
  uint8_t tmp;
  tmp = bcVal >> 1; //get 6 MSB bits of 7-bit data
  pkt.header[2] &= 0xC0;
  pkt.header[2] |= tmp;
  tmp = (bcVal << 7); //get 1 LSB bits
  pkt.header[3] &= 0x7F;
  pkt.header[3] |= tmp;
}


//Input must be in range 0-127 or collapse data happen
void tlc5971_c::SetRedBc(uint8_t bcVal){
  pkt.header[3] &= 0x80;
  pkt.header[3] |= bcVal;
}


void tlc5971_c::SetGs(uint8_t outIndex, gs_t* outGs){
  gs_t* dstGs = NULL;
  switch (outIndex){
    case 3: dstGs = &pkt.out3Gs; break;
    case 2: dstGs = &pkt.out2Gs; break;
    case 1: dstGs = &pkt.out1Gs; break;
    case 0: dstGs = &pkt.out0Gs; break;
  }  
  if (dstGs){
    dstGs->blueGs[0]  = outGs->blueGs[0];
    dstGs->blueGs[1]  = outGs->blueGs[1];
    dstGs->greenGs[0] = outGs->greenGs[0];
    dstGs->greenGs[1] = outGs->greenGs[1];
    dstGs->redGs[0]   = outGs->redGs[0];
    dstGs->redGs[1]   = outGs->redGs[1];
  }
}
void tlc5971_c::SetGs(uint8_t outIndex, uint8_t red, uint8_t green, uint8_t blue){
  gs_t* dstGs = NULL;
  switch (outIndex){
    case 3: dstGs = &pkt.out3Gs; break;
    case 2: dstGs = &pkt.out2Gs; break;
    case 1: dstGs = &pkt.out1Gs; break;
    case 0: dstGs = &pkt.out0Gs; break;
  }  
  if (dstGs){
    dstGs->blueGs[0]  = blue;
    dstGs->blueGs[1]  = 0xFF;
    dstGs->greenGs[0] = green;
    dstGs->greenGs[1] = 0xFF;
    dstGs->redGs[0]   = red;
    dstGs->redGs[1]   = 0xFF;
  }
}


void tlc5971_c::Send(){
  if (usedSpi){
    usedSpi->Send((uint8_t*) &pkt, sizeof(pkt));
  }
}
