/*
*  Copyright (C) 2015 Orbitech
*
*  Authors: xqrzd
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License version 2 as
*  published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*  MA 02110-1301, USA.
*/

#pragma once

#include "Base.h"

typedef struct _HS_STRING {
	SIZE_T Length;
	WCHAR Buffer[1];
} HS_STRING, *PHS_STRING;

__declspec(dllexport) VOID HsInitializeStringType(
	);

__declspec(dllexport) PHS_STRING HsCreateString(
	_In_ PWSTR Buffer
	);

__declspec(dllexport) PHS_STRING HsCreateStringEx(
	_In_opt_ PWCHAR Buffer,
	_In_ SIZE_T Length
	);