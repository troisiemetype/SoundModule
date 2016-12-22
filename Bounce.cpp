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

#include "Bounce.h"

Bounce::Bounce(){
	_synth = NULL;
	_trellis = NULL;
	_notes = NULL;
}

Bounce::~Bounce(){
	delete _active;
	delete _direction;
	delete _pos;
	delete _top;
	delete _play;
}

void Bounce::begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes){

	_tick = 0;
	_synth = synth;
	_trellis = trellis;
	_notes = notes;

	_channels = _trellis->getSizeX();
	_rows = _trellis->getSizeY();
	_size = _trellis->getSize();

	_active = new char[_channels];
	_direction = new char[_channels];
	_pos = new char[_channels];
	_top = new char[_channels];
	_play = new char[_channels];

	memset(_active, 0, _channels);
	memset(_direction, 0, _channels);
	memset(_pos, 0, _channels);
	memset(_top, 0, _channels);
	memset(_play, 0, _channels);


}

//Look af it there is a press on the panel.
void Bounce::update(){
	bool update = _trellis->readSwitches();
	if(!update){
		return;
	}

	//First get the button pressed for offset
	if(_trellis->justTPressed(TRELLIS_U1) && _trellis->justTPressed(TRELLIS_U2)){
		_trellis->setOffsetY(-4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_L1) && _trellis->justTPressed(TRELLIS_L2)){
		_trellis->setOffsetX(-4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_D1) && _trellis->justTPressed(TRELLIS_D2)){
		_trellis->setOffsetY(4);
		return;
	}

	if(_trellis->justTPressed(TRELLIS_R1) && _trellis->justTPressed(TRELLIS_R2)){
		_trellis->setOffsetX(4);
		return;
	}

	//Get the button pressed for note setting
	for (byte i = 0; i < _size; i++){
		if(_trellis->justPressed(i)){

			byte col = i%_channels;
			byte row = i/_channels;

			//If the button was already press for this channel, we have to shut it.
			if(_top[col] == row){
				_active[col] = 0;
				_top[col] = -1;
			//Else the column is initialize with the new value.
			} else {
				_top[col] = row;
				_active[col] = 1;
				_direction[col] = -1;
				_play[col] = 1;
				_pos[col] = _rows;

			}

		}
	}
}

void Bounce::updateTick(){

}

void Bounce::updateBeat(){

	_trellis->clear();

	for(byte i = 0; i < _channels; i++){
		//If the channel is not set, change channel

		if(_active[i] == 0){
			continue;
		}

		//If pos = _rows, the note has to be played, and direction reversed.
		if(_pos[i] >= _rows - 1){
			_play[i] = 1;
			_direction[i] = -1;
			_pos[i] = _rows -1;
		}
		//If pos = top, the direction has to be reversed too.
		if(_pos[i] == _top[i]){
			_direction[i] = 1;
		}

		_trellis->setLED(_getKey(i, _pos[i]));
		_trellis->setLED(_getKey(i, _top[i]));

		_pos[i] += _direction[i];
	}

	_trellis->writeDisplay();

	for(byte i = 0; i < _channels; i++){
		if(_play[i] != 1){
			continue;
		}
		_play[i] = 0;
		SoundNote *note = _notes->getNote(i);

		_synth->play(note->getWave(),
					note->getPitch(),
					note->getEnv(),
					note->getVelocity());

	}


}

int Bounce::_getKey(byte x, byte y){
	return x + y * _channels;
}