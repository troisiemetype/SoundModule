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

#include "Step.h"


Step::Step(){
	_synth = NULL;
	_trellis = NULL;
	_notes = NULL;
}

Step::~Step(){

}

void Step::begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes){

	_synth = synth;
	_trellis = trellis;
	_notes = notes;

	_channels = notes->getNotes();
	_rows = _trellis->getSizeY();
	_cols = _trellis->getSizeX();
	_size = _trellis->getSize();

	_steps = 8;

	_currentStep = 0;

	_currentChannel = 0;

}

void Step::update(){
	if(!_trellis->readSwitches()){
		return;
	}

	//First get the button pressed for menu
	if(_trellis->justTPressed(TRELLIS_L) && _trellis->justTPressed(TRELLIS_R)){
		menuSteps();
		return;
	}

	if(_trellis->justTPressed(TRELLIS_L)){
		_trellis->setOffsetX(-4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_U)){
		_trellis->setOffsetY(-4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_D)){
		_trellis->setOffsetY(4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_R)){
		_trellis->setOffsetX(4);
		return;
	}

	//Now look if there is a note pressed
	byte limit = _cols * 3;
	for (byte i = 0; i < limit; i++){
		//index is to get the absolute position in the map, given offsets
		byte index = i + _trellis->getOffsetX() + (_trellis->getOffsetY() * _cols);

		if(_trellis->justPressed(index)){
			byte row = index/_cols;
			byte col = index%_cols;

			SoundNote *note = _notes->getNote(row);
			note->toggleStep(col);

			if(note->getStep(col)){
				_trellis->setLED(index);
			} else {
				_trellis->clrLED(index);
			}
		}
	}

	_trellis->writeDisplay();

}

void Step::updateTick(){

}

void Step::updateBeat(){

	SoundNote *note;

	_trellis->clear();

	_setBar(_currentStep);

	//light all the led that have to.
	byte limit = _cols * 3;
	for (byte i = 0; i < limit; i++){
		byte index = i + _trellis->getOffsetX() + (_trellis->getOffsetY() * _cols);
		byte row = index/_cols;
		byte col = index%_cols;

		note = _notes->getNote(row);

		if(note->getStep(col)){
			_trellis->setLED(index);
		}

	}

	_trellis->writeDisplay();

	for (byte i = 0; i < 12; i++){
		SoundNote *note = _notes->getNote(i);
		if(note->getStep(_currentStep)){
			_synth->play(note->getWave(),
						note->getPitch(),
						note->getEnv(),
						note->getVelocity());
		}
	}

	_currentStep++;

	if(_currentStep >= _steps) _currentStep = 0;

}

void Step::menuSteps(){
	bool quit = false;
	while(!_trellis->readSwitches());
	while(!quit){
		_trellis->clear();

		_trellis->readSwitches();

		for (byte i = 0; i < 12; i++){
			if(i < _steps){
				_trellis->setTLED(i);
			}
			if(_trellis->justTPressed(i)) _steps = i + 1;
		}

		_trellis->writeDisplay();

		if(_trellis->justTPressed(TRELLIS_L) && _trellis->justTPressed(TRELLIS_R)){
			quit = true;
		}
	}
	while(!_trellis->readSwitches());
}

void Step::_setVert(byte col){
	for(byte i = 0; i < _rows; i++){
		_trellis->setLED(_getKey(col, i));
	}
}

void Step::_setBar(byte col){
	for(byte i = 0; i < 3; i++){
		_trellis->setLED(_getKey(col, i + _trellis->getOffsetY()));
	}
}

int Step::_getKey(byte x, byte y){
	return x + y * _cols;
}
