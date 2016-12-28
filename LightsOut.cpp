/*
 * This Arduino library implement a simple pad as a sound module
 * Copyright (C) 2016  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LightsOut.h"

LightsOut::LightsOut(){
	_synth = NULL;
	_trellis = NULL;
	_notes = NULL;
}

LightsOut::~LightsOut(){

}

void LightsOut::begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes){
	_synth = synth;
	_trellis = trellis;
	_notes = notes;

	_numKeys = _trellis->getSize();
	_cols = _trellis->getSizeX();
	_rows = _trellis->getSizeY();
	_limitRow = _rows - 1;
	_limitCol = _cols - 1;

	randomSeed(millis());

	bool state = false;

	for(byte j = 0; j < 3; j++){
		for(int i = 0; i < _numKeys; i++){
			state = random(2);
			if(state){
				_trellis->setLED(i);
			} else {
				_trellis->clrLED(i);
			}
			_trellis->writeDisplay();
			delay(10);
		}
	}

}

void LightsOut::update(){
	bool update = _trellis->readSwitches();
	if(!update){
		return;
	}

	for(int i = 0; i < _numKeys; i++){
		if(_trellis->justPressed(i)){
			byte row = i/_cols;
			byte col = i%_cols;

			_toggleLed(i);

			if(row != 0){
				_toggleLed(i - _cols);
			}
			if(row != _limitRow){
				_toggleLed(i + _cols);
			}

			if(col != 0){
				_toggleLed(i - 1);
			}
			if(col != _limitCol){
				_toggleLed(i + 1);
			}
		}
	}

	_trellis->writeDisplay();

	bool clear = true;

	for(int i = 0; i < _numKeys; i++){
		if(_trellis->isLED(i)){
			clear = false;
		}
	}

	if(clear){
		_winner();
		begin(_synth, _trellis, _notes);
	}

}

void LightsOut::updateTick(){

}

void LightsOut::updateBeat(){

}

void LightsOut::_toggleLed(int i){
	if(_trellis->isLED(i)){
		_trellis->clrLED(i);
	} else {
		_trellis->setLED(i);
	}
}

void LightsOut::_winner(){
	for( byte j = 0; j < 3; j++){
		_trellis->clear();
		for(int i = 0; i < _numKeys; i++){
			_trellis->setLED(i);
		}
		_trellis->writeDisplay();
		delay(250);
		_trellis->clear();
		_trellis->writeDisplay();
		delay(250);
	}
}
