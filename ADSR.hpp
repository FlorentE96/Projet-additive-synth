#ifndef ADSR_H
#define ADSR_H

#define DEFAULT_SUSTAIN (0.8)
#define DEFAULT_SLOPE   (0.01)
#define DEFAULT_ATTACK  (0.01)
#define DEFAULT_DECAY   (0.2)
#define DEFAULT_RELEASE (0.5)


typedef enum
{
    stateIdle = 0,
    stateAttack,
    stateDecay,
    stateSustain,
    stateRelease
} State;

class ADSR
{
public:
  ADSR();
  ADSR(double attack, double decay, double sustain, double release);
  ~ADSR();
  void setAttack(double _attackTime, double _attackTarget);
  void setAttackTime(double _attackTime);
  void setAttackSlope(double _attackTarget);
  void setDecay(double _decayTime, double _decayTarget);
  void setDecayTime(double _decayTime);
  void setDecaySlope(double _decayTarget);
  void setRelease(double _releaseTime, double _releaseTarget);
  void setReleaseTime(double _releaseTime);
  void setReleaseSlope(double _releaseSlope);
  void setSustainLevel(double _sustainLevel);
  double getAttackTime(void);
  double getAttackSlope(void);
  double getDecayTime(void);
  double getDecaySlope(void);
  double getReleaseTime(void);
  double getReleaseSlope(void);
  double getSustainLevel(void);
  State getState(void);
  double getValue(void);

  double process(void);
  void reset(void);
  void gate(int state);


private:
  double attackRate, decayRate, releaseRate;
  double attackTime, decayTime, releaseTime;
  double attackCoef, decayCoef, releaseCoef;
  double attackBase, decayBase, releaseBase;
  double attackTarget, decayTarget, releaseTarget;
  double sustainLevel;
  double value;
  State state;
};

#endif
