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

/*
 * This class defines a bounce program.
 * When a key is pressed, the led start going up and down between key pressed and pannel bottom.
 * When it somes to bottom, the sound or note associated to the channel is played.
 * Simply press again the same key to stop the bouncing.
 * Begin is used to init the class. It's to be used in setup, or in any place you want.
 * You will then be able to access it if needed via a SoundModule pointer.
 */


#ifndef SOUNDBOUNCE_H
#define SOUNDBOUNCE_H

#include <SoundNote.h>
#include <soundmachine.h>
#include <trellismap.h>

#include "SoundModule.h"
#include <Arduino.h>

class Bounce : public SoundModule{
public:

	Bounce();
	
	//Virtuals methods inherited from SoundModule.
	~Bounce();

	void begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes);

	void update();
	void updateTick();
	void updateBeat();

	//Methods of the class

protected:

	int _getKey(byte x, byte y);

	SoundMachine* _synth;
	TrellisMap* _trellis;
	SoundNotes* _notes;

	int _size;
	byte _channels;
	byte _rows;

	byte _tick;

	char *_active, *_direction, *_pos, *_top, *_play;

};

#endif