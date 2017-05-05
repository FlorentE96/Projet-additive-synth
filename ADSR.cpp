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

ADSR::ADSR(double attack, double decay, double sustain, double release) {
  setAttack(attack, DEFAULT_SLOPE);
  setDecay(decay, DEFAULT_SLOPE);
  setSustainLevel(sustain);
  setRelease(release, DEFAULT_SLOPE);
  reset();
}

ADSR::~ADSR(void) {
  //
}

void ADSR::setAttack(double _attackTime, double _attackTarget) {
  attackTime = _attackTime;
  attackTarget = _attackTarget;
  attackRate = _attackTime * SAMPLE_RATE; // attack rate in samples
  attackCoef = exp(-log((1.0 + _attackTarget) / _attackTarget) / attackRate);
  attackBase = (1.0 + _attackTarget) * (1.0 - attackCoef);
}

void ADSR::setAttackTime(double _attackTime) {
  attackTime = _attackTime;
  attackRate = _attackTime * SAMPLE_RATE; // attack rate in samples
  attackCoef = exp(-log((1.0 + attackTarget) / attackTarget) / attackRate);
  attackBase = (1.0 + attackTarget) * (1.0 - attackCoef);
}

void ADSR::setAttackSlope(double _attackTarget) {
  attackTarget = _attackTarget;
  attackCoef = exp(-log((1.0 + _attackTarget) / _attackTarget) / attackRate);
  attackBase = (1.0 + attackTarget) * (1.0 - attackCoef);
}

void ADSR::setDecay(double _decayTime, double _decayTarget) {
  decayTime = _decayTime;
  decayTarget = _decayTarget;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0 + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - _decayTarget) * (1.0 - decayCoef);
}

void ADSR::setDecayTime(double _decayTime) {
  decayTime = _decayTime;
  decayRate = _decayTime * SAMPLE_RATE; // decay rate in samples
  decayCoef = exp(-log((1.0 + decayTarget) / decayTarget) / decayRate);
  decayBase = (sustainLevel - decayTarget) * (1.0 - decayCoef);
}

void ADSR::setDecaySlope(double _decayTarget) {
  decayTarget = _decayTarget;
  decayCoef = exp(-log((1.0 + _decayTarget) / _decayTarget) / decayRate);
  decayBase = (sustainLevel - _decayTarget) * (1.0 - decayCoef);
}

void ADSR::setRelease(double _releaseTime, double _releaseTarget) {
  releaseTime = _releaseTime;
  releaseTarget = _releaseTarget;
  releaseRate = _releaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0 + _releaseTarget) / _releaseTarget) / releaseRate);
  releaseBase = -_releaseTarget * (1.0 - releaseCoef);
}

void ADSR::setReleaseTime(double _releaseTime) {
  releaseTime = _releaseTime;
  releaseRate = _releaseTime * SAMPLE_RATE; // release rate in samples
  releaseCoef = exp(-log((1.0 + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0 - releaseCoef);
}

void ADSR::setReleaseSlope(double _releaseTarget) {
  releaseTarget = _releaseTarget;
  releaseCoef = exp(-log((1.0 + releaseTarget) / releaseTarget) / releaseRate);
  releaseBase = (-releaseTarget) * (1.0 - releaseCoef);
}

void ADSR::setSustainLevel(double _sustainLevel) {
  if(_sustainLevel > 1.0)
    _sustainLevel = 1.0;
  else if(_sustainLevel < 0.0)
    _sustainLevel = 0.0;
  sustainLevel = _sustainLevel;
}

double ADSR::getAttackTime(void) {
  return attackTime;
}

double ADSR::getAttackSlope(void) {
  return attackTarget;
}

double ADSR::getDecayTime(void) {
  return decayTime;
}

double ADSR::getDecaySlope(void) {
  return decayTarget;
}

double ADSR::getReleaseTime(void) {
  return releaseTime;
}

double ADSR::getReleaseSlope(void) {
  return releaseTarget;
}

double ADSR::getSustainLevel(void) {
  return sustainLevel;
}

State ADSR::getState(void) {
  return state;
}

double ADSR::getValue(void) {
  return value;
}

double ADSR::process(void) {
  switch (state) {
    case stateIdle:
      break;
    case stateAttack:
      value = attackBase + value * attackCoef;
      if(value >= 1.0) {
        value = 1.0;
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
      if(value <= 0.0) {
        value = 0.0;
        state = stateIdle;
      }
      break;
  } // switch
  return value;
}

void ADSR::reset(void) {
  value = 0.0;
  state = stateIdle;
}

void ADSR::gate(int gateState) {
  if(gateState)
    state = stateAttack;
  else
    state = stateRelease;
}
