/**************************************************************************************
 *   main.h  --  This file is part of Cool Characters Only.                           *
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

extern HelperFunctions HelperFunctionsGlobal;
extern const char* CCM_VERSION;
extern std::string DEBUG_MESSAGE;
extern int DEBUG_MESSAGE_TIMER;
extern int DEFAULT_MESSAGE_TIME;
extern float SCALE_MULTIPLIER;
extern int DEBUG_FONT_SCALE;
extern int DEBUG_FONT_COLOR;

static void ExitHandler();
static void SetDebugInfo();
static LRESULT __stdcall WndProcFallen(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);