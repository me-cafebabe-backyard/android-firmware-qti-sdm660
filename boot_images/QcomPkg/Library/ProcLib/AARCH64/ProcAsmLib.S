//============================================================================
//
//             ProcAsmLib
//
// GENERAL DESCRIPTION
//   Generic processor control routines in assembly
//
// Copyright 2012 - 2013, 2015 by Qualcomm Technologies, Inc.  All Rights Reserved 
//============================================================================

//============================================================================
//
//                       EDIT HISTORY FOR MODULE
//
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when      who     what, where, why
// --------  -----   ----------------------------------------------------------
// 12/09/16   bh      Add function to get stack pointer
// 09/14/15   bh      Add reg read functions
// 11/26/13   vk      Add WriteCNTKCTL
// 10/31/13   vk      Stub for ARMCompiler6
// 03/25/13   nk      Add ETM clock enable 
// 03/13/13   yg      Rename API
// 03/03/13   yg      Add SMP register access functions.
// 05/01/12   yg      Created new file
//============================================================================

.text
.align 3

#include <ProcessorBind.h>

//============================================================================
//                             MODULE EXPORTS
//============================================================================
  ASM_GLOBAL ASM_PFX(ReadPMonCtlReg)
  ASM_GLOBAL ASM_PFX(WritePMonCtlReg)
  ASM_GLOBAL ASM_PFX(ReadUserEnReg)
  ASM_GLOBAL ASM_PFX(WriteUserEnReg)
  ASM_GLOBAL ASM_PFX(ReadCntEnSetReg)
  ASM_GLOBAL ASM_PFX(WriteCntEnSetReg)
  ASM_GLOBAL ASM_PFX(ReadCntEnClrReg)
  ASM_GLOBAL ASM_PFX(WriteCntEnClrReg)
  ASM_GLOBAL ASM_PFX(ReadPerfCntSelReg)
  ASM_GLOBAL ASM_PFX(WritePerfCntSelReg)
  ASM_GLOBAL ASM_PFX(ReadCycleCntReg)
  ASM_GLOBAL ASM_PFX(WriteCycleCntReg)
  ASM_GLOBAL ASM_PFX(ReadEvtSelReg)
  ASM_GLOBAL ASM_PFX(WriteEvtSelReg)
  ASM_GLOBAL ASM_PFX(ReadTPIDRURWReg)
  ASM_GLOBAL ASM_PFX(WriteTPIDRURWReg)
  ASM_GLOBAL ASM_PFX(ReadTPIDRUROReg)
  ASM_GLOBAL ASM_PFX(WriteTPIDRUROReg)
  ASM_GLOBAL ASM_PFX(ReadACTLR)
  ASM_GLOBAL ASM_PFX(WriteACTLR)
  ASM_GLOBAL ASM_PFX(ReadCPMR)
  ASM_GLOBAL ASM_PFX(WriteCPMR)
  ASM_GLOBAL ASM_PFX(WriteETmcr)
  ASM_GLOBAL ASM_PFX(WriteCNTKCTL)
  ASM_GLOBAL ASM_PFX(ReadABit)
  ASM_GLOBAL ASM_PFX(ReadDACRReg)
  ASM_GLOBAL ASM_PFX(GetStackPointer)
         
//============================================================================)
//
//                        MACROS AND FUNCTIONS
//
//============================================================================


//============================================================================
//
//  UINT32 ReadPMonCtlReg (void)//
//
//============================================================================

ASM_PFX(ReadPMonCtlReg):
  ret
  
//============================================================================
//
//  void WritePMonCtlReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WritePMonCtlReg):
  ret

//============================================================================
//
//  UINT32 ReadUserEnReg(void)//
//
//============================================================================
ASM_PFX(ReadUserEnReg):
  ret
  
//============================================================================
//
//  void WriteUserEnReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteUserEnReg):
  ret

//============================================================================
//
//  UINT32 ReadCntEnSetReg(void)//
//
//============================================================================
ASM_PFX(ReadCntEnSetReg):
  ret

//============================================================================
//
//  void WriteCntEnSetReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteCntEnSetReg):
  ret

//============================================================================
//
//  UINT32 ReadCntEnClrReg(void)//
//
//============================================================================
ASM_PFX(ReadCntEnClrReg):
  ret

//============================================================================
//
//  void WriteCntEnClrReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteCntEnClrReg):
  ret

//============================================================================
//
//  UINT32 ReadPerfCntSelReg(void)//
//
//============================================================================
ASM_PFX(ReadPerfCntSelReg):
  ret

//============================================================================
//
//  void WritePerfCntSelReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WritePerfCntSelReg):
  ret

//============================================================================
//
//  UINT32 ReadCycleCntReg(void)//
//
//============================================================================
ASM_PFX(ReadCycleCntReg):
  ret

//============================================================================
//
//  void WriteCycleCntReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteCycleCntReg):
  ret

//============================================================================
//
//  UINT32 ReadEvtSelReg(void)//
//
//============================================================================
ASM_PFX(ReadEvtSelReg):
  ret

//============================================================================
//
//  void WriteEvtSelReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteEvtSelReg):
  ret

//============================================================================
//
//  UINT32 ReadTPIDRURWReg(void)//
//
//============================================================================
ASM_PFX(ReadTPIDRURWReg):
  ret

//============================================================================
//
//  void WriteTPIDRURWReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteTPIDRURWReg):
  ret

//============================================================================
//
//  UINT32 ReadTPIDRUROReg(void)//
//
//============================================================================
ASM_PFX(ReadTPIDRUROReg):
  ret

//============================================================================
//
//  void WriteTPIDRUROReg(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteTPIDRUROReg):
  ret

//============================================================================
//
//  UINT32 ReadACTLR(VOID)//
//
//============================================================================
ASM_PFX(ReadACTLR):
  ret

//============================================================================
//
//  VOID WriteACTLR(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteACTLR):
  ret

//===========================================================================
//
//  UINT32 ReadCPMR(VOID)//
//
//============================================================================
ASM_PFX(ReadCPMR):
   ret

//============================================================================
//
//  VOID WriteCPMR(UINT32 Val)
//
//============================================================================
ASM_PFX(WriteCPMR):
   ret

//============================================================================
//
//  VOID WriteETmcr(UINT32 Val)//
//
//============================================================================
ASM_PFX(WriteETmcr):
   ret

ASM_PFX(WriteCNTKCTL):
   //Write CNTKCTL Register
   //MCR p15, 0, R0, c14, c1, 0 
   MSR CNTKCTL_EL1, x0
   ret

ASM_PFX(ReadABit):
  MRS x0, DAIF
  MOV x1, #1
  AND x0, x1, x0, LSR #8
  ret
   
ASM_PFX(ReadDACRReg):
  //MRC p15, 0, R0, c3, c0, 0
  ret

ASM_PFX(GetStackPointer):
  mov x0, sp
  ret

//============================================================================
