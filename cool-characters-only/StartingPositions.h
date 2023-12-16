/**************************************************************************************
 *   StartingPositions.h  --  This file is part of Cool Characters Only.              *
 *                                                                                    *
 *   Copyright (C) 2023 Queen Suzie                                                   *
 *                                                                                    *
 *   Cool Characters Only is free software: you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published                *
 *   by the Free Software Foundation, either version 3 of the License,                *
 *   or (at your option) any later version.                                           *
 *                                                                                    *
 *   Cool Characters Only is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty                      *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                          *
 *   See the GNU General Public License for more details.                             *
 *                                                                                    *
 *   You should have received a copy of the GNU General Public License                *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.              *
 *                                                                                    *
 *************************************************************************************/

#pragma once

class StartingPositions {
	public:
		void init();
};

signed int sub_458970();
void LoadStartPosition_r();
int LoadStartPosition_h(int, NJS_VECTOR*, Rotation*);
void sub_46DC70(int, NJS_VECTOR*, char);
void Load2PIntroPos_h(int);
void Load2PIntroPos_r();
void sub_43DF30_h(int);
void sub_43DF30();
signed int sub_46DBD0(int);
signed int LoadEndPosition_h(int);
void LoadTitleCardTextures();
void loc_472A7D();