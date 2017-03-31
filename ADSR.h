#ifndef ADSR_H
#define ADSR_H

class ADSR {
public:
  typedef enum
  {
  		stateIdle = 0,
  		stateAttack,
  		stateDecay,
  		stateSustain,
  		stateRelease
  } State;

  ADSR();
  ADSR(float attack, float decay, float sustain, float release);
  ~ADSR();
  void setAttack(float _attackTime, float _attackTarget);
  void setAttackTime(float _attackTime);
  void setAttackSlope(float _attackTarget);
  void setDecay(float _decayTime, float _decayTarget);
  void setDecayTime(float _decayTime);
  void setDecaySlope(float _decayTarget);
  void setRelease(float _releaseTime, float _releaseTarget);
  void setReleaseTime(float _releaseTime);
  void setReleaseSlope(float _releaseSlope);
  void setSustainLevel(float _sustainLevel);
  float getAttackTime();
  float getAttackSlope();
  float getDecayTime();
  float getDecaySlope();
  float getReleaseTime();
  float getReleaseSlope();
  float getSustainLevel();
  State getState();

  float process();
  void reset();
  void gate(int state);


private:
  float attackRate, decayRate, releaseRate;
  float attackTime, decayTime, releaseTime;
  float attackCoef, decayCoef, releaseCoef;
  float attackBase, decayBase, releaseBase;
  float attackTarget, decayTarget, releaseTarget;
  float sustainLevel;
  float value;
  State state;
};

#endif
