#ifndef __TLC5971_C_H
#define __TLC5971_C_H

typedef struct {
  uint8_t blueGs[2];
  uint8_t greenGs[2];
  uint8_t redGs[2];
} gs_t;

typedef struct{
  uint8_t header[4];
  gs_t    out3Gs;
  gs_t    out2Gs;
  gs_t    out1Gs;
  gs_t    out0Gs;
} tlc5971_packet_t;

class tlc5971_c{
  private: 
  HLib::spi_base_c* usedSpi;
  tlc5971_packet_t pkt;
  void SetCmd(uint8_t cmdVal);

  public:
  tlc5971_c(HLib::spi_base_c* spi);
  void SetFc(uint8_t fcVal);
  uint8_t CreateFc(bool outTmg, bool extGck, bool tmGrst, bool dspRpt, bool blank);
  void SetBlueBc(uint8_t bcVal);
  void SetGreenBc(uint8_t bcVal);
  void SetRedBc(uint8_t bcVal);
  void SetGs(uint8_t outIndex, gs_t* outGs);
  void SetGs(uint8_t outIndex, uint8_t red, uint8_t green, uint8_t blue);
  void Send();
};  
  
#endif /* __TLC5971_C_H */
