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
 * This class defines a simple pad.
 * Begin is used to init the class. It's to be used in setup, or in any place you want.
 * You will then be able to access it if needed via a SoundModule pointer.
 */


#ifndef SOUNDPAD_H
#define SOUNDPAD_H

#include "SoundModule.h"
#include <Arduino.h>

class Pad : public SoundModule{
public:

	Pad();
	
	//Virtuals methods inherited from SoundModule.
	~Pad();

	void begin();

	void update();
	void updateTick();
	void updateBeat();

	//Methods of the class

protected:

};

#endif