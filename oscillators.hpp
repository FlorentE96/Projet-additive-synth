#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#define RES (1024)
#define PHASE_FACTOR  ((float)RES/(float)SAMPLE_RATE) // factor between the phase and the array index
#define DEFAULT_WF (wavetable_sine)
#define DEFAULT_FREQ (440)

class Osc {
public:
    enum note2Freq   //link a frequencie to a note
                     {DO_0=16    ,RE_0=18    ,MI_0=20    ,FA_0=22     ,SOL_0=24   ,LA_0=27   ,SI_0=31,
                      DOd_0=17   ,REd_0=20   ,FAd_0=23   ,SOLd_0=26   ,LAd_0=29   ,
                      DO_1=33    ,RE_1=37    ,MI_1=41    ,FA_1=44     ,SOL_1=49   ,LA_1=55   ,SI_1=62,
                      DOd_1=35   ,REd_1=39   ,FAd_1=46   ,SOLd_1=52   ,LAd_1=58   ,
                      DO_2=65    ,RE_2=73    ,MI_2=82    ,FA_2=87     ,SOL_2=98   ,LA_2=110  ,SI_2=123,
                      DOd_2=69   ,REd_2=78   ,FAd_2=92   ,SOLd_2=104  ,LAd_2=117  ,
                      DO_3=131   ,RE_3=147   ,MI_3=165   ,FA_3=175    ,SOL_3=196  ,LA_3=220  ,SI_3=247,
                      DOd_3=139  ,REd_3=156  ,FAd_3=185  ,SOLd_3=208  ,LAd_3=233  ,
                      DO_4=262   ,RE_4=294   ,MI_4=329   ,FA_4=349    ,SOL_4=392  ,LA_4=440  ,SI_4=494,
                      DOd_4=277  ,REd_4=311  ,FAd_4=370  ,SOLd_4=415  ,LAd_4=466  ,
                      DO_5=523   ,RE_5=587   ,MI_5=659   ,FA_5=698    ,SOL_5=784  ,LA_5=880  ,SI_5=988,
                      DOd_5=554  ,REd_5=622  ,FAd_5=740  ,SOLd_5=831  ,LAd_5=932  ,
                      DO_6=1046  ,RE_6=1175  ,MI_6=1319  ,FA_6=1397   ,SOL_6=1568 ,LA_6=1760 ,SI_6=1976,
                      DOd_6=1109 ,REd_6=1245 ,FAd_6=1480 ,SOLd_6=1661 ,LAd_6=1865 ,
                      DO_7=2094  ,RE_7=2349  ,MI_7=2637  ,FA_7=2793   ,SOL_7=3135 ,LA_7=3520 ,SI_7=3951,
                      DOd_7=2217 ,REd_7=2489 ,FAd_7=2959 ,SOLd_7=3322 ,LAd_7=3729 ,
                      DO_8=4186  ,RE_8=4698  ,
                      DOd_8=4434 ,REd_8=4978 ,};
  Osc();
  Osc(int16_t * _wavetable, uint32_t _frequency);
  ~Osc();
  void setFrequency(uint32_t _frequency);
  int16_t process();
  void reset();
private:
  int16_t linearInterpolation();
  int16_t * wavetable;
  uint32_t phase;
  uint32_t frequency;
  int16_t value;
};

#endif
