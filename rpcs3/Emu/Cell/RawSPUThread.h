#pragma once
#include "SPUThread.h"
#include "Emu/event.h"

enum
{
	MFC_LSA_offs			= 0x3004,
	MFC_EAH_offs			= 0x3008,
	MFC_EAL_offs			= 0x300C,
	MFC_Size_Tag_offs		= 0x3010,
	MFC_Class_CMD_offs		= 0x3014,
	MFC_CMDStatus_offs		= 0x3014,
	MFC_QStatus_offs		= 0x3104,
	Prxy_QueryType_offs		= 0x3204,
	Prxy_QueryMask_offs		= 0x321C,
	Prxy_TagStatus_offs		= 0x322C,
	SPU_Out_MBox_offs		= 0x4004,
	SPU_In_MBox_offs		= 0x400C,
	SPU_MBox_Status_offs	= 0x4014,
	SPU_RunCntl_offs		= 0x401C,
	SPU_Status_offs			= 0x4024,
	SPU_NPC_offs			= 0x4034,
	SPU_RdSigNotify1_offs	= 0x1400C,
	SPU_RdSigNotify2_offs	= 0x1C00C,
};

enum : u64
{
	RAW_SPU_OFFSET		= 0x0000000000100000,
	RAW_SPU_BASE_ADDR   = 0x00000000E0000000,
	RAW_SPU_LS_OFFSET	= 0x0000000000000000,
	RAW_SPU_PROB_OFFSET	= 0x0000000000040000,
};

__forceinline static u32 GetRawSPURegAddrByNum(int num, int offset)
{
	return RAW_SPU_OFFSET * num + RAW_SPU_BASE_ADDR + RAW_SPU_PROB_OFFSET + offset;
}

__forceinline static u32 GetRawSPURegAddrById(int id, int offset)
{
	return GetRawSPURegAddrByNum(Emu.GetCPU().GetThreadNumById(PPC_THREAD_RAW_SPU, id), offset);
}


class RawSPUThread : public SPUThread
{
public:
	RawSPUThread(PPCThreadType type = PPC_THREAD_RAW_SPU);
	~RawSPUThread();

	virtual wxString RegsToString()
	{
		wxString ret = PPCThread::RegsToString();
		for(uint i=0; i<128; ++i) ret += wxString::Format("GPR[%d] = 0x%s\n", i, GPR[i].ToString());
		return ret;
	}

public:
	virtual void InitRegs();

private:
	virtual void Task();
};

SPUThread& GetCurrentSPUThread();