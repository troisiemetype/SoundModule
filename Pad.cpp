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

#include "Pad.h"

Pad::Pad(){
	_synth = NULL;
	_trellis = NULL;
	_notes = NULL;
}

Pad::~Pad(){

}

void Pad::begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes){
	_synth = synth;
	_trellis = trellis;
	_notes = notes;

	_numKeys = _trellis->getSize();
	_cols = _trellis->getSizeX();
	_rows = _trellis->getSizeY();
}

void Pad::update(){
	bool update = _trellis->readSwitches();
	if(!update){
		return;
	}

	for(int i = 0; i < _numKeys; i++){
		if(_trellis->justPressed(i)){
			byte row = i/_cols;
			byte col = i%_cols;

			_trellis->setLED(i);

			SoundNote *note = _notes->getNote(col + ((_rows - 1 - row) * _cols));

			_synth->play(note->getWave(),
						note->getPitch(),
						note->getEnv(),
						note->getVelocity());
		}

		if(_trellis->justReleased(i)){
			_trellis->clrLED(i);
		}
	}

	_trellis->writeDisplay();


}

void Pad::updateTick(){

}

void Pad::updateBeat(){

}
