/*
 * This Arduino library is for a class that is the base class for sound modules.
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
 * This is an abstract class for sound modeuls. It provides a base structure that all modules rely on.
 * Using this class, the main program can access any sound module with the sames functions,
 * whatever those functions do internally.
 */


#ifndef SOUNDMODULE_H
#define SOUNDMODULE_H

#include <Arduino.h>

class SoundModule{
public:

	virtual ~SoundModule(){};

//	virtual void begin() = 0;

	virtual void update() = 0;
	virtual void updateTick() = 0;
	virtual void updateBeat() = 0;

protected:

};

#endif