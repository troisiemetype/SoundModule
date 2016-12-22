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
 * This class defines a simple step sequancer.
 * Each row represents a channel with a sound or note attached to it.
 * A vertical bar moves left to right, each column being a step.
 * When the step bar moves, it triggers every channel that is set for this step.
 * Begin is used to init the class. It's to be used in setup, or in any place you want.
 * You will then be able to access it if needed via a SoundModule pointer.
 */


#ifndef SOUNDSTEP_H
#define SOUNDSTEP_H

#include <SoundNote.h>
#include <soundmachine.h>
#include <trellismap.h>

#include "SoundModule.h"
#include <Arduino.h>

class Step : public SoundModule{
public:

	Step();
	
	//Virtuals methods inherited from SoundModule.
	~Step();

	void begin(SoundMachine* synth, TrellisMap* trellis, SoundNotes* notes);

	void update();
	void updateTick();
	void updateBeat();

	void menuSteps();

	//Methods of the class

protected:

	void _setVert(byte col);
	void _setBar(byte col);
	int _getKey(byte x, byte y);


	SoundMachine* _synth;
	TrellisMap* _trellis;
	SoundNotes* _notes;

	int _size;
	byte _channels;
	byte _cols;
	byte _rows;

	byte _currentChannel;

	byte _currentStep;
	byte _steps;

};
#endif