//============================================================================
//
//             ProcAsmLib
//
// GENERAL DESCRIPTION
//   Generic processor control routines in assembly
//
// Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved 
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
// 11/29/16   aus     Added support for 32 bit LLVM compilation
//
//============================================================================

.text
.align 2

//============================================================================
//                             MODULE EXPORTS
//============================================================================
   GCC_ASM_EXPORT(ReadPMonCtlReg)
   GCC_ASM_EXPORT(WritePMonCtlReg)
   GCC_ASM_EXPORT(ReadUserEnReg)
   GCC_ASM_EXPORT(WriteUserEnReg)
   GCC_ASM_EXPORT(ReadCntEnSetReg)
   GCC_ASM_EXPORT(WriteCntEnSetReg)
   GCC_ASM_EXPORT(ReadCntEnClrReg)
   GCC_ASM_EXPORT(WriteCntEnClrReg)
   GCC_ASM_EXPORT(ReadPerfCntSelReg)
   GCC_ASM_EXPORT(WritePerfCntSelReg)
   GCC_ASM_EXPORT(ReadCycleCntReg)
   GCC_ASM_EXPORT(WriteCycleCntReg)
   GCC_ASM_EXPORT(ReadEvtSelReg)
   GCC_ASM_EXPORT(WriteEvtSelReg)

   GCC_ASM_EXPORT(ReadTPIDRURWReg)
   GCC_ASM_EXPORT(WriteTPIDRURWReg)
   GCC_ASM_EXPORT(ReadTPIDRUROReg)
   GCC_ASM_EXPORT(WriteTPIDRUROReg)

   GCC_ASM_EXPORT(ReadACTLR)
   GCC_ASM_EXPORT(WriteACTLR)
      
   GCC_ASM_EXPORT(ReadCPMR)
   GCC_ASM_EXPORT(WriteCPMR)
   GCC_ASM_EXPORT(WriteETMCR)
   GCC_ASM_EXPORT(WriteCNTKCTL)
   GCC_ASM_EXPORT(ReadABit)
   GCC_ASM_EXPORT(ReadDACRReg)
      
//============================================================================
//
//                        MACROS AND FUNCTIONS
//
//============================================================================

//============================================================================
//
//  UINT32 ReadPMonCtlReg (void)//
//
//============================================================================
ReadPMonCtlReg:
  MRC p15, 0, R0, c9, c12, 0 // Read PMNC Register
  BX  LR
  
//============================================================================
//
//  void WritePMonCtlReg(UINT32 Val)//
//
//============================================================================
WritePMonCtlReg:
  MCR p15, 0, R0, c9, c12, 0 // Write PMNC Register
  BX LR

//============================================================================
//
//  UINT32 ReadUserEnReg(void)//
//
//============================================================================
ReadUserEnReg:
  MRC p15, 0, R0, c9, c14, 0 // Read USEREN Register
  BX  LR
  
//============================================================================
//
//  void WriteUserEnReg(UINT32 Val)//
//
//============================================================================
WriteUserEnReg:
  MCR p15, 0, R0, c9, c14, 0 // Write USEREN Register
  BX LR

//============================================================================
//
//  UINT32 ReadCntEnSetReg(void)//
//
//============================================================================
ReadCntEnSetReg:
  MRC p15, 0, R0, c9, c12, 1 // Read CNTENS Register
  BX LR

//============================================================================
//
//  void WriteCntEnSetReg(UINT32 Val)//
//
//============================================================================
WriteCntEnSetReg:
  MCR p15, 0, R0, c9, c12, 1 // Write CNTENS Register
  BX LR

//============================================================================
//
//  UINT32 ReadCntEnClrReg(void)//
//
//============================================================================
ReadCntEnClrReg:
  MRC p15, 0, R0, c9, c12, 2 // Read CNTENC Register
  BX LR

//============================================================================
//
//  void WriteCntEnClrReg(UINT32 Val)//
//
//============================================================================
WriteCntEnClrReg:
  MCR p15, 0, R0, c9, c12, 2 // Write CNTENC Register
  BX LR

//============================================================================
//
//  UINT32 ReadPerfCntSelReg(void)//
//
//============================================================================
ReadPerfCntSelReg:
  MRC p15, 0, R0, c9, c12, 5// Read PMNXSEL Register
  BX LR

//============================================================================
//
//  void WritePerfCntSelReg(UINT32 Val)//
//
//============================================================================
WritePerfCntSelReg:
  MCR p15, 0, R0, c9, c12, 5// Write PMNXSEL Register
  BX LR

//============================================================================
//
//  UINT32 ReadCycleCntReg(void)//
//
//============================================================================
ReadCycleCntReg:
  MRC p15, 0, R0, c9, c13, 0 // Read CCNT Register
  BX LR

//============================================================================
//
//  void WriteCycleCntReg(UINT32 Val)//
//
//============================================================================
WriteCycleCntReg:
  MCR p15, 0, R0, c9, c13, 0 // Write CCNT Register
  BX LR

//============================================================================
//
//  UINT32 ReadEvtSelReg(void)//
//
//============================================================================
ReadEvtSelReg:
  MRC p15, 0, R0, c9, c13, 1 // Read EVTSEL Register
  BX LR

//============================================================================
//
//  void WriteEvtSelReg(UINT32 Val)//
//
//============================================================================
WriteEvtSelReg:
  MCR p15, 0, R0, c9, c13, 1 // Write EVTSEL Register
  BX LR

//============================================================================
//
//  UINT32 ReadTPIDRURWReg(void)//
//
//============================================================================
ReadTPIDRURWReg:
  MRC p15, 0, R0, c13, c0, 2 // Read TPIDRURW Register
  BX LR

//============================================================================
//
//  void WriteTPIDRURWReg(UINT32 Val)//
//
//============================================================================
WriteTPIDRURWReg:
  MCR p15, 0, R0, c13, c0, 2 // Write TPIDRURW Register
  BX LR

//============================================================================
//
//  UINT32 ReadTPIDRUROReg(void)//
//
//============================================================================
ReadTPIDRUROReg:
  MRC p15, 0, R0, c13, c0, 3 // Read TPIDRURO Register
  BX LR

//============================================================================
//
//  void WriteTPIDRUROReg(UINT32 Val)//
//
//============================================================================
WriteTPIDRUROReg:
  MCR p15, 0, R0, c13, c0, 3 // Write TPIDRURO Register
  BX LR

//============================================================================
//
//  UINT32 ReadACTLR(VOID)//
//
//============================================================================
ReadACTLR:
  MRC p15, 0, R0, c1, c0, 1 // Read ACTLR Register
  BX LR

//============================================================================
//
//  VOID WriteACTLR(UINT32 Val)//
//
//============================================================================
WriteACTLR:
  MCR p15, 0, R0, c1, c0, 1 // Write ACTLR Register
  BX LR

//===========================================================================
//
//  UINT32 ReadCPMR(VOID)//
//
//============================================================================
ReadCPMR:
   MRC p15, 7, R0, c15, c0, 5 // Read CPMR Register
   BX LR

//============================================================================
//
//  VOID WriteCPMR(UINT32 Val)
//
//============================================================================
WriteCPMR:
   MCR p15, 7, R0, c15, c0, 5 // Write 1 to ETMCLKEN bit
   BX LR

//============================================================================
//
//  VOID WriteETMCR(UINT32 Val)//
//
//============================================================================
WriteETMCR:
   MCR p14, 1, R0, c0, c0, 0 // Write ETMCR Register
   BX LR

//============================================================================
//
//  VOID WriteCNTKCTL(UINT32 Val)//
//
//============================================================================
WriteCNTKCTL:
   MCR p15, 0, R0, c14, c1, 0 // Write CNTKCTL Register
   BX LR

//============================================================================
//
//  UINT32 ReadABit(VOID)//
//
//============================================================================
ReadABit:
   MRS R0, CPSR
   MOV R1, #1
   AND R0, R1, R0, LSR #8
   BX LR

//============================================================================
//
//  UINT32 ReadDACRReg(VOID)//
//
//============================================================================
ReadDACRReg:
   MRC p15, 0, R0, c3, c0, 0
   BX LR

//===========================================================================

