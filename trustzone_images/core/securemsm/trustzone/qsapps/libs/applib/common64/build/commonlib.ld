PHDRS {
  RO PT_LOAD;
  GOT PT_LOAD;
  REL_H PT_LOAD;
  REL_H_DYN PT_DYNAMIC;
  REL_D PT_LOAD;
}

SECTIONS {
  .text : {
    KEEP(*\cmnlib_entry.o (CMNLIBENTRYCODE))
    * (.text .text.*)
    KEEP(*(tzapp_syscall_asm))
  } : RO

  .rodata : {
    * (.rodata)
    * (EXCLUDE_FILE(*cmnlib_main.o) .rodata.*)
  } : RO

  .sentinel : {
    * (.rodata.sentinel)
    ASSERT(SIZEOF(.sentinel) != 0, "No sentinel section defined.");
  } : RO

  .metadata_check : {
    *cmnlib_main.o (.rodata.*)
    ASSERT(SIZEOF(.metadata_check) == 0, "New metadata not accounted for here");
  } : RO

  .got : ALIGN(4096) { *(.got.plt) *(.igot.plt) *(.got) *(.igot) } : GOT

   /* Even though this section is zero-length the linker will force it
      to the RO segment if it is placed above .got without forcing it
      to a specific segment.  This makes the RO segment writeable, so
      we will place it after the GOT segment and force it to the GOT
      segment. */
  .data : {
    KEEP(* (.data .bss COMMON))
    ASSERT(SIZEOF(.data) == 0, "Commonlib may not have RW data");
  } : GOT

  .rel.text : {
    *(.rel.text)
  } : GOT
  .rel.rodata : {
    *(.rel.rodata)
  } : GOT
  .data.rel.ro.local : {
    *(.data.rel.ro.local)
  } : GOT
  .data.rel.ro : {
    *(.data.rel.ro)
  } : GOT
  .rel.data : {
    *(.rel.data)
  } : GOT
  .rel.plt : {
    *(.rel.plt)
  } : GOT
  .data.rel : {
    *(.data.rel)
  } : GOT
  .data.rel.local : {
    *(.data.rel.local)
  } : GOT

  .dynamic : ALIGN(4096) { *(.dynamic) }: REL_H : REL_H_DYN

  .rela.dyn : ALIGN(4096) {*(.rela.dyn)} : REL_D

  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.hash) *(.dynsym) *(.dynstr) *(.ARM.exidx*) *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) *(.init) *(.fini) }
}
