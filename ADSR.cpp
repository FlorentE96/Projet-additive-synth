#include ADSR.h

ADSR::ADSR() {
  setAttack(0.01f, 0.001f);
  setDecay(0.2f, 0.001f);
  setSustainLevel(0.8f);
  setRelease(0.5f, 0.001f);
  reset();
}

ADSR::ADSR(float attack, float decay, float sustain, float release) {
  setAttack(attack, 0.001f);
  setDecay(decay, 0.001f);
  setSustainLevel(sustain);
  setRelease(release, 0.001f);
  reset();
}

ADSR::~ADSR() {
  //
}

void ADSR::setAttack(float _attackTime, float _attackTarget) {
  attacktime = _attackTime;
  attackRate = attackTime * SAMPLE_RATE; // attack rate in samples
  attackCoef = exp(-log((1.0f + _attackTarget) / _attackTarget) / attackRate);
  attackBase = (1.0f + _attackTarget) * (1.0f - attackCoef);
}

void ADSR::setAttackTime(float _attackTime) {
  attackTime = _attackTime;
  attackRate = _attackTime * SAMPLE_RATE; // attack rate in samples
  attackCoef = exp(-log((1.0f + attackTarget) / attackTarget) / attackRate);
  attackBase = (1.0f + attackTarget) * (1.0f - attackCoef);
}

void ADSR::setAttackSlope(float _attackTarget) {
  attackCoef = exp(-log((1.0f + _attackTarget) / _attackTarget) / attackRate);
  attackBase = (1.0f + attackTarget) * (1.0f - attackCoef);
}

void ADSR::setDecay(float _decayTime, float _decayTarget) {
  decayTime = _decayTime;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0f + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - decayTarget) * (1.0f - decayCoef);
}

void ADSR::setDecayTime(float _decayTime) {
  decayTime = _decayTime;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0f + decayTarget) / decayTarget) / decayRate);
  decayBase = (sustainLevel - decayTarget) * (1.0f - decayCoef);
}

void ADSR::setDecaySlope(float _decayTarget) {
  decayCoef = exp(-log((1.0f + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - _decayTarget) * (1.0f - decayCoef);
}

void ADSR::setRelease(float ReleaseTime, float ReleaseTarget) {
  releaseTime = ReleaseTime;
  releaseRate = ReleaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0f + ReleaseTarget) / ReleaseTarget) / releaseRate);
  releaseBase = -ReleaseTarget * (1.0f - releaseCoef);
}

void ADSR::setReleaseTime(float ReleaseTime) {
  releaseTime = ReleaseTime;
  releaseRate = ReleaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0f + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0f - releaseCoef);
}

void ADSR::setReleaseSlope(float ReleaseSlope) {
  releaseCoef = exp(-log((1.0 + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0 - releaseCoef);
}

void ADSR::setSustainLevel(float SustainLevel) {
  if(level > 1.0f)
    level = 1.0f;
  else if(level < 0.0f)
    level = 0.0f;
  sustainLevel = level;
}

float ADSR::getAttackTime() {
  return attackTime;
}

float ADSR::getAttackSlope() {
  return attackTarget;
}

float ADSR::getDecayTime() {
  return decayTime;
}

float ADSR::getDecaySlope() {
  return decayTarget;
}

float ADSR::getReleaseTime() {
  return releaseTime;
}

float ADSR::getReleaseSlope() {
  return releaseTarget;
}

float ADSR::getSustainLevel() {
  return sustainLevel;
}

State ADSR::getState() {
  return state;
}

float ADSR::process() {
  switch (state) {
    case stateIdle:
      break;
    case stateAttack:
      value = attackBase + value * attackCoef;
      if(value >= 1.0f) {
        value = 1.0f;
        state = stateDecay;
      }
      break;
    case state_decay:
      value = decayBase + value * decayCoef;
      if(value <= sustainLevel) {
        value = sustainLevel;
        state = stateSustain;
      }
      break;
    case stateSustain:
      break;
    case stateRelease:
      value = releaseBase + value * releaseCoef;
      if(value <= 0.0f) {
        value = 0.0f;
        state = stateIdle;
      }
      break;
  } // switch
}

void ADSR::reset() {
  value = 0.0f;
  state = stateIdle;
}

void ADSR::gate(int gateState) {
  if(gateState)
    state = stateAttack;
  else
    state = stateRelease;
}
