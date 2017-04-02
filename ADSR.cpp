#include <cmath>
#include <iostream>
#include <fstream>
#include "global.hpp"
#include "ADSR.hpp"
using namespace std;

ADSR::ADSR() {
  setSustainLevel(DEFAULT_SUSTAIN);
  setAttack(DEFAULT_ATTACK, DEFAULT_SLOPE);
  setDecay(DEFAULT_DECAY, DEFAULT_SLOPE);
  setRelease(DEFAULT_RELEASE, DEFAULT_SLOPE);
  reset();
}

ADSR::ADSR(float attack, float decay, float sustain, float release) {
  setAttack(attack, DEFAULT_SLOPE);
  setDecay(decay, DEFAULT_SLOPE);
  setSustainLevel(sustain);
  setRelease(release, DEFAULT_SLOPE);
  reset();
}

ADSR::~ADSR(void) {
  //
}

void ADSR::setAttack(float _attackTime, float _attackTarget) {
  attackTime = _attackTime;
  attackTarget = _attackTarget;
  attackRate = _attackTime * SAMPLE_RATE; // attack rate in samples
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
  attackTarget = _attackTarget;
  attackCoef = exp(-log((1.0f + _attackTarget) / _attackTarget) / attackRate);
  attackBase = (1.0f + attackTarget) * (1.0f - attackCoef);
}

void ADSR::setDecay(float _decayTime, float _decayTarget) {
  decayTime = _decayTime;
  decayTarget = _decayTarget;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0f + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - _decayTarget) * (1.0f - decayCoef);
}

void ADSR::setDecayTime(float _decayTime) {
  decayTime = _decayTime;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0f + decayTarget) / decayTarget) / decayRate);
  decayBase = (sustainLevel - decayTarget) * (1.0f - decayCoef);
}

void ADSR::setDecaySlope(float _decayTarget) {
  decayTarget = _decayTarget;
  decayCoef = exp(-log((1.0f + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - _decayTarget) * (1.0f - decayCoef);
}

void ADSR::setRelease(float _releaseTime, float _releaseTarget) {
  releaseTime = _releaseTime;
  releaseTarget = _releaseTarget;
  releaseRate = _releaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0f + _releaseTarget) / _releaseTarget) / releaseRate);
  releaseBase = -_releaseTarget * (1.0f - releaseCoef);
}

void ADSR::setReleaseTime(float _releaseTime) {
  releaseTime = _releaseTime;
  releaseRate = _releaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0f + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0f - releaseCoef);
}

void ADSR::setReleaseSlope(float _releaseTarget) {
  releaseTarget = _releaseTarget;
  releaseCoef = exp(-log((1.0 + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0 - releaseCoef);
}

void ADSR::setSustainLevel(float _sustainLevel) {
  if(_sustainLevel > 1.0f)
    _sustainLevel = 1.0f;
  else if(_sustainLevel < 0.0f)
    _sustainLevel = 0.0f;
  sustainLevel = _sustainLevel;
}

float ADSR::getAttackTime(void) {
  return attackTime;
}

float ADSR::getAttackSlope(void) {
  return attackTarget;
}

float ADSR::getDecayTime(void) {
  return decayTime;
}

float ADSR::getDecaySlope(void) {
  return decayTarget;
}

float ADSR::getReleaseTime(void) {
  return releaseTime;
}

float ADSR::getReleaseSlope(void) {
  return releaseTarget;
}

float ADSR::getSustainLevel(void) {
  return sustainLevel;
}

State ADSR::getState(void) {
  return state;
}

float ADSR::getValue(void) {
  return value;
}

float ADSR::process(void) {
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
    case stateDecay:
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
  return value;
}

void ADSR::reset(void) {
  value = 0.0f;
  state = stateIdle;
}

void ADSR::gate(int gateState) {
  if(gateState)
    state = stateAttack;
  else
    state = stateRelease;
}
