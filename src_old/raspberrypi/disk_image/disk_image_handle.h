//---------------------------------------------------------------------------
//
//	SCSI Target Emulator RaSCSI (*^..^*)
//	for Raspberry Pi
//
//	Copyright (C) 2022 akuker
//
//  	Base class for interfacing with disk images.
//
//	[ DiskImageHandle ]
//
//---------------------------------------------------------------------------

#pragma once

#include "filepath.h"

class DiskImageHandle
{
public:
	DiskImageHandle(const Filepath &path, int size, uint32_t blocks, off_t imgoff = 0);
	virtual ~DiskImageHandle();

	void SetRawMode(bool raw) { cd_raw = raw; }; // CD-ROM raw mode setting

	// Access
	virtual bool Save() = 0;											   // Save and release all
	virtual bool ReadSector(BYTE *buf, int block) = 0;					   // Sector Read
	virtual bool WriteSector(const BYTE *buf, int block) = 0;			   // Sector Write
	virtual bool GetCache(int index, int &track, DWORD &serial) const = 0; // Get cache information

protected:
	bool cd_raw = false;
	DWORD serial;	   // Last serial number
	Filepath sec_path; // Path

	int sec_size;	 // Sector Size (8=256, 9=512, 10=1024, 11=2048, 12=4096)
	int sec_blocks;	 // Blocks per sector
	off_t imgoffset; // Offset to actual data

	off_t GetTrackOffset(int block);
	off_t GetSectorOffset(int block);
};
