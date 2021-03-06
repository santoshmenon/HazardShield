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

#include "Scanner.h"

BOOLEAN HsInit()
{
	if (cl_init(CL_INIT_DEFAULT) != CL_SUCCESS)
		return FALSE;

	return NT_SUCCESS(PhInitializePhLib());
}

BOOLEAN HsCreateScanner(
	_Out_ PHS_SCANNER* Scanner)
{
	PHS_SCANNER scanner = PhAllocate(sizeof(HS_SCANNER));

	scanner->ClamAvEngine = cl_engine_new();

	if (scanner->ClamAvEngine)
	{
		scanner->Signatures = 0;
		*Scanner = scanner;

		return TRUE;
	}

	PhFree(scanner);

	return FALSE;
}

VOID HsDeleteScanner(
	_In_ PHS_SCANNER Scanner)
{
	cl_engine_free(Scanner->ClamAvEngine);
	PhFree(Scanner);
}

cl_error_t HsLoadClamAvDatabase(
	_In_ PHS_SCANNER Scanner,
	_In_ PSTR Path,
	_In_ ULONG DatabaseOptions)
{
	return cl_load(
		Path,
		Scanner->ClamAvEngine,
		&Scanner->Signatures,
		DatabaseOptions);
}

cl_error_t HsCompileClamAvDatabase(
	_In_ PHS_SCANNER Scanner)
{
	return cl_engine_compile(Scanner->ClamAvEngine);
}

cl_error_t HsScanBuffer(
	_In_ PHS_SCANNER Scanner,
	_In_ PVOID Buffer,
	_In_ SIZE_T Length,
	_In_ ULONG ScanOptions,
	_Out_ PPH_BYTES* VirusName)
{
	cl_error_t result;
	struct cl_fmap* map;
	char* virusName;

	map = cl_fmap_open_memory(Buffer, Length);

	if (map)
	{
		result = cl_scanmap_callback(
			map,
			&virusName,
			NULL,
			Scanner->ClamAvEngine,
			ScanOptions,
			NULL);

		cl_fmap_close(map);

		if (result == CL_VIRUS)
			*VirusName = PhCreateBytes(virusName);
	}
	else
		result = CL_EMAP;

	return result;
}