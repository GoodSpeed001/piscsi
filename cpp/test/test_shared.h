//---------------------------------------------------------------------------
//
// SCSI Target Emulator RaSCSI Reloaded
// for Raspberry Pi
//
// Copyright (C) 2022 Uwe Seimet
//
//---------------------------------------------------------------------------

#pragma once

#include "shared/scsi.h"
#include "generated/rascsi_interface.pb.h"
#include <string>
#include <memory>
#include <filesystem>

using namespace std;
using namespace filesystem;
using namespace rascsi_interface;

class PrimaryDevice;
class MockAbstractController;

extern const path test_data_temp_path;

shared_ptr<PrimaryDevice> CreateDevice(PbDeviceType, MockAbstractController&, const string& = "");

void TestInquiry(PbDeviceType, scsi_defs::device_type, scsi_defs::scsi_level, const string&,
		int, bool, const string& = "");

pair<int, path> OpenTempFile();
path CreateTempFile(int);


// create a file with the specified data
void CreateTempFileWithData(string filename, vector<uint8_t> &data);

void DeleteTempFile(string filename);
// Call this at the end of every test case to make sure things are cleaned up
void CleanupAllTempFiles();

int GetInt16(const vector<byte>&, int);
uint32_t GetInt32(const vector<byte>&, int);
