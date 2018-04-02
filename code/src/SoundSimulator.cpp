#include "../header/SoundSimulator.h"

SoundSimulator::SoundSimulator(){
  massSpringIsCalculated = false;
  deformationModelingIsCalculated = false;
}

SoundSimulator::SoundSimulator(Instrument instrument, bool calculateNow) : SoundSimulator(){
  this->setInstrument(instrument);
  if(calculateNow){
    this->calculateMassSpringSystem();
    this->calcuateDoformationModeling();
  }
}

void SoundSimulator::setInstrument(Instrument instrument){
  this->instrument = instrument;
}


void SoundSimulator::calculateMassSpringSystem(){

}
void SoundSimulator::calcuateDoformationModeling(){

}
