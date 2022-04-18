#ifndef DLL_API_H
#define DLL_API_H
/** vi: tw=128 ts=3 sw=3 et :
@file dll_api.h
@brief This file contains the API for the Run Control Framework, API 2.1
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/api/debugtools/dll_api.h#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#if !defined(NULL)
#define NULL (void*)0
#endif

/**
DLL_API Helper Macros

There will never be a runtime component associated to this header file. It is only
to supply consistent compiler macros that can be used to decorate function signatures
for DLL compilation.
*/

/**
API Function and Symbol Visibility Helpers

Imperical testing of code structured using these helper macros indicates that the
symbol table management of DLL is much better and facilitates faster load times.
The link time flags to enable symbol default visibility for 'hidden' requires that
symbols be explicitly marked for external visibility.

BEST PRACTICE ONLY, OPERATIONAL ONLY WITH SELECTED COMPILERS, IF THE COMPILER IS
NOT SUPPORTED, THE MECHANICS ARE DISABLED. Even when a compiler is not supported,
the sources can still be annotated. No apologies are offered on macro syntax -- we
have to do portable things with the preprocessor pass of compilation.

Per Internet Tribal Knowledge, DLL are compiled within opensource community based
upon compiler command flags that are defined across the whole baseline. The compiler
command flags must be defined, or a DLL is not being produced. Consult online for
autoconf and automake documentation; this will allow the tech area to understand how
this exists as a defacto industry standard based on tribal knowledge.

Technology areas define their mechanism in their deliverable to trigger if the
DLL is being activly built for their area (EXPORT), or if the API header files
are expected to be making use of the API (IMPORT). Notice how below in the code,
that [SONAME] API is defined and utilized in the header. Source files just carry
the regular function signature without all of the attributes or API decorations.

[SONAME]    Technology Area Specific API Collection Name (or DLL/Shared Object Name)
[module]    Technology Area Specific Source Module

   tech_[module].h                     // [module] represents a template entry for tech area substitution
   ------------------------

#include "dll_api.h"                                     // MUST PRECEDE CLIENT DEFINITION OF DLL_API_EXPORT

#if defined(DLL_API_BUILD_[SONAME])                      // REQUIRED TO BE DECLARED IN TECH AREA SOURCE MODULES (SU/VU VISIBLE)
#undef  DLL_API_EXPORT_[SONAME]                          // REDEFINITION FOR THIS SPECIFIC MODULE
#define DLL_API_EXPORT_[SONAME] DLL_API_EXPORT_HELPER    // CONTROL OVER DLL SYMBOL VISIBILITY BY EXPORT
#else
#undef  DLL_API_EXPORT_[SONAME]                          // REDEFINITION FOR THIS SPECIFIC MODULE
#define DLL_API_EXPORT_[SONAME] DLL_API_IMPORT_HELPER    // CONTROL OVER DLL SYMBOL VISIBILITY BY EXPORT
#endif

DLL_API_WARN_UNUSED_RESULT 
DLL_API_EXPORT_[SONAME] int [module]_function_signature(void*, void*, int);

DLL_API_WARN_UNUSED_RESULT DLL_API_WARN_DEPRECATED
DLL_API_EXPORT_[SONAME] int [module]_function_signature_deprecated(void*, void*, int);

DLL_API_EXPORT_[SONAME] extern int variable1;            // Accessible Outside of [SONAME]

DLL_API_LOCAL extern int variable2;                      // Not Accessible Outside of [SONAME]

   tech_[module].c
   ------------------------

#defined DLL_API_BUILD_[SONAME]                          // REQUIRED TO BE DECLARED IN TECH AREA SOURCE MODULES (SU/VU VISIBLE)

#include "api_header1.h"                                 // NOMINAL HEADER FILE DEPENDENCY
#include "api_header2.h"                                 // NOMINAL HEADER FILE DEPENDENCY

#include "tech_[module].h"                               // TECH AREA HEADER FILE DEPENDENCY

// NOTE: THE API FOR THE MODULE IS REFERENCED AS DLL_API_EXPORT_[SONAME] TO AVOID NAMESPACE
// CLASH. RESPECT THE NAMING CONVENTION.

...

// DLL_API Decoration not required in source module; the header file supplies the attributes of compilation
int [module]_function_signature(void*, void*, int)
{
   ...
   return 0;
}

// DLL_API Decoration not required in source module; the header file supplies the attributes of compilation
int [module]_function_signature_deprecated(void*, void*, int)
{
   ...
   return 0;
}

   ...

   [module]_function_signature(NULL, NULL, 1);                                   // generates warnings

   [module]_function_signature_deprecated(NULL, NULL, 1);                        // generates warnings

   if ([module]_function_signature(void_pointer, void_pointer, 2)) {;}           // does not generate warnings

*/

#if defined(__ARMCC_VERSION) && defined(__APCS_FPIC)
#define DLL_API_EXPORT_HELPER       __attribute__((visibility("protected")))  /**< ELF */
#define DLL_API_IMPORT_HELPER       __attribute__((visibility("default")))    /**< ELF */
#define DLL_API_LOCAL               __attribute__((visibility("hidden")))     /**< ELF */
#elif defined(__clang__) && defined(__PIC__)
#define DLL_API_EXPORT_HELPER       __attribute__((visibility("protected")))  /**< ELF */
#define DLL_API_IMPORT_HELPER       __attribute__((visibility("default")))    /**< ELF */
#define DLL_API_LOCAL               __attribute__((visibility("hidden")))     /**< ELF */
#elif defined(__GNUC__) && defined(__PIC__)
#define DLL_API_EXPORT_HELPER       __attribute__((visibility("protected")))  /**< ELF */
#define DLL_API_IMPORT_HELPER       __attribute__((visibility("default")))    /**< ELF */
#define DLL_API_LOCAL               __attribute__((visibility("hidden")))     /**< ELF */
#elif defined(_WIN32) && defined(__PIC__)
#define DLL_API_EXPORT_HELPER       __declspec(dllexport)                     /**< PE/COFF */
#define DLL_API_IMPORT_HELPER       __declspec(dllimport)                     /**< PE/COFF */
#define DLL_API_LOCAL               /*NULL*/
#elif defined(__CYGWIN__) && defined(__PIC__)
#define DLL_API_EXPORT_HELPER       __declspec(dllexport)                     /**< PE/COFF */
#define DLL_API_IMPORT_HELPER       __declspec(dllimport)                     /**< PE/COFF */
#define DLL_API_LOCAL               /*NULL*/
#else
#define DLL_API_EXPORT_HELPER       /*NULL*/
#define DLL_API_IMPORT_HELPER       /*NULL*/
#define DLL_API_LOCAL               /*NULL*/
#endif

#if !defined(DLL_API_EXPORT)
#define DLL_API_EXPORT              DLL_API_IMPORT_HELPER                     /**< Generic Use for DLL_API_EXPORT_[SONAME], Not Recommended */
#endif

/**
API, Function and Symbol Signature Decoration

Function and Symbol Attributes that describe how an API should be treated by the
compiler. Primarily, these attributes are used to generate warnings when clients
misuse an API. It is possible to declare attributes as supplied by the compiler.
When a specific compiler warning is not available (eg, ARMCC), the Decorations
are disabled.

*/

/**
INTERNAL Compiler Pragma Helpers
*/
/* #undef   DLL_API_EXCLUDE_PRAGMA_I */ /**< PL Specialization Tuneable */
/* #undef   DLL_API_EXCLUDE_PRAGMA_W */ /**< PL Specialization Tuneable */
#if defined(__GNUC__) || defined(__clang__)
#define DLL_API_GCC_HELPER_PRAGMA(x)         _Pragma( #x )
#if !defined(DLL_API_EXCLUDE_PRAGMA_I)
#define DLL_API_GCC_HELPER_PRAGMA_I(x)       DLL_API_GCC_HELPER_PRAGMA(GCC diagnostic ignored #x)
#else
#define DLL_API_GCC_HELPER_PRAGMA_I(x)       /*NULL*/
#endif
#if !defined(DLL_API_EXCLUDE_PRAGMA_W)
#define DLL_API_GCC_HELPER_PRAGMA_W(x)       DLL_API_GCC_HELPER_PRAGMA(GCC diagnostic warning #x)
#else
#define DLL_API_GCC_HELPER_PRAGMA_W(x)       /*NULL*/
#endif
#define DLL_API_GCC_HELPER_PRAGMA_IW(x)      DLL_API_GCC_HELPER_PRAGMA_I(x) DLL_API_GCC_HELPER_PRAGMA_W(x)
#define DLL_API_GCC_HELPER_WPUSH             DLL_API_GCC_HELPER_PRAGMA(GCC diagnostic push)
#define DLL_API_GCC_HELPER_WPOP              DLL_API_GCC_HELPER_PRAGMA(GCC diagnostic pop)
#endif

/**
Compile Time Instrumentation to Identify and Report of Client API Misuse

#define -> #undef for each of the following to obtain compile time instrumentation
of API misuse by clients. These show areas at compile time where problematic use of
a declared API is potentially occurring.

*/
#define DLL_API_EXCLUDE_WARN_UNUSED_RESULT
#define DLL_API_EXCLUDE_NONNULL
#define DLL_API_EXCLUDE_WARN_DEPRECATED

/**
Compiler to Warn on Unused Result

DLL_API_WARN_UNUSED_RESULT [...]
int function_signature(void*, void*, int);

*/
#define DLL_API_WARN_UNUSED_RESULT_ATTR      __attribute__((warn_unused_result))
#if !defined(DLL_API_EXCLUDE_WARN_UNUSED_RESULT)
#if defined(__GNUC__) || defined(__clang__)
DLL_API_GCC_HELPER_PRAGMA_IW(-Wunused-result)
#define DLL_API_WARN_UNUSED_RESULT           DLL_API_WARN_UNUSED_RESULT_ATTR
#elif defined(__ARMCC_VERSION)
#define DLL_API_WARN_UNUSED_RESULT           /*NULL*/
#else
#define DLL_API_WARN_UNUSED_RESULT           /*NULL*/
#endif
#else
#define DLL_API_WARN_UNUSED_RESULT           /*NULL*/
#endif

/**
Compiler to Warn on Deprecated API Use

DLL_API_WARN_DEPRECATED [...]
int function_signature(void*, void*, int);

*/
#define DLL_API_WARN_DEPRECATED_ATTR         __attribute__((deprecated))
#if !defined(DLL_API_EXCLUDE_WARN_DEPRECATED)
#if defined(__GNUC__) || defined(__clang__)
DLL_API_GCC_HELPER_PRAGMA_IW(-Wdeprecated-declarations)
#define DLL_API_WARN_DEPRECATED              DLL_API_WARN_DEPRECATED_ATTR
#elif defined(__ARMCC_VERSION)
#pragma diag_warning 1361
#define DLL_API_WARN_DEPRECATED              DLL_API_WARN_DEPRECATED_ATTR
#else
#define DLL_API_WARN_DEPRECATED              /*NULL*/
#endif
#else
#define DLL_API_WARN_DEPRECATED              /*NULL*/
#endif

/**
Compiler to Instructed of NonNull Return

DLL_API_RETURNS_NONNULL [...]
void* function_signature(void*, void*, int);

*/
#if !defined(DLL_API_EXCLUDE_RETURNS_NONNULL)
#if defined(__GNUC__) || defined(__clang__)
#define DLL_API_RETURNS_NONNULL              __attribute__((returns_nonnull))
#elif defined(__ARMCC_VERSION)
#define DLL_API_RETURNS_NONNULL              /*NULL*/
#else
#define DLL_API_RETURNS_NONNULL              /*NULL*/
#endif
#else
#define DLL_API_RETURNS_NONNULL              /*NULL*/
#endif

/**
Compiler to Instructed of NoReturn

DLL_API_NORETURN [...]
void function_signature(void*, void*, int);

*/
#if !defined(DLL_API_EXCLUDE_NORETURN)
#if defined(__GNUC__) || defined(__clang__)
#define DLL_API_NORETURN                     __attribute__((noreturn))
#elif defined(__ARMCC_VERSION)
#define DLL_API_NORETURN                     __attribute__((noreturn))
#else
#define DLL_API_NORETURN                     /*NULL*/
#endif
#else
#define DLL_API_NORETURN                     /*NULL*/
#endif

/**
Compiler to Instructed of Used

DLL_API_USED [...]
void function_signature(void*, void*, int);

*/
#if !defined(DLL_API_EXCLUDE_USED)
#if defined(__GNUC__) || defined(__clang__)
#define DLL_API_USED                         __attribute__((used))
#elif defined(__ARMCC_VERSION)
#define DLL_API_USED                         __attribute__((used))
#else
#define DLL_API_USED                         /*NULL*/
#endif
#else
#define DLL_API_USED                         /*NULL*/
#endif

/**
Compiler to Instructed of ARM and HARD FLOAT

#if !defined(DLL_API_ABI_ARMHF)
.. soft float ..
#endif

*/
#if !defined(DLL_API_EXCLUDE_ABI_ARMHF)
#if defined(__clang__) && defined(__arm__) && defined(__TARGET_ARCH_7) && !defined(__TARGET_FPU_NONE) && !defined(__TARGET_FPU_SOFTVFP)
#define DLL_API_ABI_ARMHF                    /*NULL*/
#endif
#endif

/**
Compiler to Instructed of HEXAGON and MSGABI

#if !defined(DLL_API_ABI_HEXMSG)
.. older ABI ...
#endif

or

DLL_API_ABI_HEXMSG [...]
void function_signature(void*, void*, int);

*/
#if !defined(DLL_API_EXCLUDE_ABI_HEXMSGABI)
#if defined(__HEXMSGABI_SUPPORTED__)
#define DLL_API_ABI_HEXMSGABI                __attribute__((hexmsgabi))
#else
#define DLL_API_ABI_HEXMSGABI                /*NULL*/
#endif
#endif

/**
Compiler to Static Inline, Availble ISO/ANSI C99

[...]
DLL_API_STATIC_INLINE void function_signature(void*, void*, int)
{
   ...
}

*/
#if defined(__ARMCC_VERSION)
#define DLL_API_STATIC_INLINE                static inline
#elif defined(__clang__)
#define DLL_API_STATIC_INLINE                static inline
#elif defined(__GNUC__)
#define DLL_API_STATIC_INLINE                static inline
#elif defined(_WIN32)
#define DLL_API_STATIC_INLINE                static
#elif defined(__CYGWIN__)
#define DLL_API_STATIC_INLINE                static inline
#else
#define DLL_API_STATIC_INLINE                static
#endif

/**
Compiler to Supply DLL API Version Hints

ALLOWING FOR MULTIPLE ENTRY POINTS WITHIN DLL VERSIONING TO SUPPLY A SPECIFIC API, LINK SCRIPT SELECTED
DLL_API_VER_DEFAULT([module]_function_signature, 1.0.0, [module]_function_signature_latest);
DLL_API_VER_SPECIFIC([module]_function_signature, 0.9.0, [module]_function_signature_old);

ALLOWING FOR MULTIPLE ENTRY POINTS WITHIN DLL VERSIONING TO SUPPLY A SPECIFIC API, LINK SCRIPT SELECTED
DLL_API_VER_DEFAULT([module]_function_signature_deprecated, 0.9.0, [module]_function_signature_deprecated_old);
DLL_API_VER_SPECIFIC([module]_function_signature_deprecated, 0.8.0, [module]_function_signature_deprecated_older);
DLL_API_VER_SPECIFIC([module]_function_signature_deprecated, 0.7.0, [module]_function_signature_deprecated_oldest);

This only works with GNU as compatible assemblers that implement the
pseudo-op ".symver" as part of the mechanism to identify entry points
and associate those entry points to various release versions of the
in which they occur. See the GNU ld linker documentation for the command
line option `--version-script' for additional information.

Each individual function is not expected to carry an arbitrary version;
The version reflects DLL, and the union of all functions that are available
with a specific DLL version.

Versioning is comprised of 3 decimal digits that are concatenated together
with a period '.' to represent the DLL version.

x = API name entry
y = NN.NN.NN version of DLL
z = localized existing function implements the API x@y
*/
#if !defined(DLL_API_EXCLUDE_DLL_API_VERSION)
#if defined(__GNUC__) || defined(__clang__)
#define DLL_API_VER_DEFAULT(x,y,z)           __asm__(".symver " #z "," #x "@@" #y )
#define DLL_API_VER_SPECIFIC(x,y,z)          __asm__(".symver " #z "," #x "@" #y )
#define DLL_API_VER_HIDDEN(x,y)              /*NULL*/
#elif defined(__ARMCC_VERSION)
#define DLL_API_VER_DEFAULT(x,y,z)           /*NULL*/
#define DLL_API_VER_SPECIFIC(x,y,z)          /*NULL*/
#define DLL_API_VER_HIDDEN(x,y)              /*NULL*/
#else
#define DLL_API_VER_DEFAULT(x,y,z)           /*NULL*/
#define DLL_API_VER_SPECIFIC(x,y,z)          /*NULL*/
#define DLL_API_VER_HIDDEN(x,y)              /*NULL*/
#endif
#else
#define DLL_API_VER_DEFAULT(x,y,z)           /*NULL*/
#define DLL_API_VER_SPECIFIC(x,y,z)          /*NULL*/
#define DLL_API_VER_HIDDEN(x,y)              /*NULL*/
#endif

/**
DLL_API Constructor/Destructor Sorting Hint "Weight"
*/
#define DLL_API_CTOR 127                     /**< DLL_API CTOR Sorting Hint "Weight", Middle of [0..255]~["Early" .. "Late"] */
#define DLL_API_DTOR 127                     /**< DLL_API DTOR Sorting Hint "Weight", Middle of [0..255]~["Early" .. "Late"] */

#if 0

/**
MANUAL PROCEDURE LINK TABLE (PLT) Management Helpers

These Macros "SIMULATE" various techniques available in modern linkers in a
very primitive manner. It is far better to use built in linker features when
building a DLL. It is not required that a DLL be loaded from magnetic media
(hard disk), a DLL can be potentially be placed into any type of media.
Characteristic of a DLL is that the code is read-only and position relative,
allowing for the code to be loaded at any virtual memory address. Data may
optionally be supplied as position relative, but not all DLL have this
characteristic.

Possible Compiler Command Line Switches to Avoid Simulated PLT:

GCC: -fpic -fvisibility=default
ARMCC: --apcs=/fpic --no_hide_all or (--base_platform --dll --pltgot=direct/indirect --pltgot_opts=crosslr)

   tech_[module_subm].h
   ------------------------

#include "dll_api.h"

DLL_API_WARN_UNUSED_RESULT DLL_API_NONNULL((1, 2))
#if !defined(DLL_API_PLT_MANUAL)
DLL_API_LOCAL int api_fn1(void);                         // local runtime entry (notice NO '_' underscore prefix)
#else
DLL_API_LOCAL int _api_fn1(void);                        // local runtime entry (notice '_' underscore prefix)
#endif

DLL_API_WARN_UNUSED_RESULT DLL_API_NONNULL((1, 2))
#if !defined(DLL_API_PLT_MANUAL)
DLL_API_LOCAL void api_fn2(void);                        // local runtime entry (notice NO '_' underscore prefix)
#else
DLL_API_LOCAL void _api_fn2(void);                       // local runtime entry (notice '_' underscore prefix)
#endif

DLL_API_PLT_EXTERN_B([module_subm])                      // type declare begin
DLL_API_PLT_EXTERN_FNC(_api_fn1, int, void)              // function signature, name, return_type, ... (function signature args)
DLL_API_PLT_EXTERN_FNC(_api_fn2, void, void)             // function signature, name, return_type, ... (function signature args)
DLL_API_PLT_EXTERN_E([module_subm])                      // type declare end

#if !defined(DLL_API_PLT_MANUAL)
// NULL                                                  // no name transforms of API
#else
#define api_fn1 DLL_API_PLT_DEREF([module_subm], _api_fn1) // name transform for client API
#define api_fn2 DLL_API_PLT_DEREF([module_subm], _api_fn2) // name transform for client API
#endif

   tech_[module_subm].c
   ------------------------

#defined DLL_API_BUILD_[SONAME]           // REQUIRED TO BE DECLARED IN TECH AREA SOURCE MODULES (SU/VU VISIBLE)

#include "tech_[module_subm].h"

DLL_API_PLT_DEFINE_B([module_subm])
DLL_API_PLT_DEFINE_FNC(_api_fn1)
DLL_API_PLT_DEFINE_FNC(_api_fn2)
DLL_API_PLT_DEFINE_E([module_subm])

DLL_API_PLT_INIT([module_subm])                          // initialize complete simulated plt

DLL_API_PLT_INIT_FNC([module_subm], _api_fn1)            // initialize individual member of simulated plt

DLL_API_PLT_INIT_FNC2([module_subm], _api_fn2, NULL)     // initialize individual member of simulated plt

   tech_client.c
   ------------------------

#include "tech_[module].h"

// CFLAGS -DDLL_API_PLT_MANUAL selects direct or indirect call at compile time, must be consistent and
// applied to all source modules being compiled as part of the link unit (ELF) being created.

int ret = api_fn1();                      // client use example, macro api_fn1 selects direct or indirect call

api_fn2();                                // client use example, macro api_fn2 selects direct or indirect call

IMPORTANT: SECTION NAME OF PLT IN RW REGION IS PREFIX WITH .bss.plt_rw_* SECTION NAME OF PLT IN RO REGION
IS PREFIX WITH .rodata.plt_ro_*. THESE SECTION NAMES MUST BE COLLECTED INTO THE APPROPRIATE LOAD SEGMENTS AT
LINK TIME BY USE OF A SCATTERLINK FILE BY THE IMAGE OWNER. THE TECH AREA WILL NOT BE SUPPLYING INFORMATION
SPECIFIC TO ADDRESSING OR MEMORY LAYOUT.

*/
#if !defined(DLL_API_PLT_MANUAL)
#define DLL_API_FNC_DEFINE(x,y,...)          y __##x (__VA_ARGS__)
#define DLL_API_FNC_EXTERN(x,y,...)          y __##x (__VA_ARGS__);
#define DLL_API_PLT_EXTERN_B(x)
#define DLL_API_PLT_EXTERN_VAR(x,y)
#define DLL_API_PLT_EXTERN_FNC(x,y,...)
#define DLL_API_PLT_EXTERN_E(x)
#define DLL_API_PLT_DEFINE_B(x)
#define DLL_API_PLT_DEFINE_VAR(x)
#define DLL_API_PLT_DEFINE_FNC(x)
#define DLL_API_PLT_DEFINE_E(x)
#define DLL_API_PLT_DEREF(x,y)
#define DLL_API_PLT_INIT(x)
#define DLL_API_PLT_INIT_VAR(x,y)
#define DLL_API_PLT_INIT_VAR2(x,y,z)
#define DLL_API_PLT_INIT_FNC(x,y)
#define DLL_API_PLT_INIT_FNC2(x,y,z)
#define DLL_API_PLT_TERM(x)
#define DLL_API_PLT_TERM_VAR(x,y)
#define DLL_API_PLT_TERM_FNC(x,y)
#else
#define DLL_API_FNC_DEFINE(x,y,...)          y __##x (__VA_ARGS__)
#define DLL_API_FNC_EXTERN(x,y,...)          y __##x (__VA_ARGS__);
#define DLL_API_PLT_EXTERN_B(x)              typedef struct {
#define DLL_API_PLT_EXTERN_VAR(x,y)          y (*_##x);
#define DLL_API_PLT_EXTERN_FNC(x,y,...)      y (*_##x) (__VA_ARGS__);
#define DLL_API_PLT_EXTERN_E(x)              } x##_plt_t; extern x##_plt_t x##_plt_rw; extern x##_plt_t const x##_plt_ro;
#define DLL_API_PLT_DEFINE_B(x)              x##_plt_t const x##_plt_ro __attribute__((section(".bss.plt_rw_" #x))) = {
#define DLL_API_PLT_DEFINE_VAR(x)            ._##x = &__##x,
#define DLL_API_PLT_DEFINE_FNC(x)            ._##x = __##x,
#define DLL_API_PLT_DEFINE_E(x)              }; x##_plt_t x##_plt_rw  __attribute__((section(".rodata.plt_ro_" #x))) = { 0 };
#define DLL_API_PLT_DEREF(x,y)               (*x##_plt_rw._##y)
#define DLL_API_PLT_INIT(x)                  void x##_plt_init(void) __attribute__((used, constructor(DLL_API_CTOR))); void x##_plt_init(void) { x##_plt_rw = x##_plt_ro; }
#define DLL_API_PLT_INIT_VAR(x,y)            void x##y##_plt_init(void) __attribute__((used, constructor(DLL_API_CTOR+1))); void x##y##_plt_init(void) { x##_plt_rw._##y = x##_plt_ro._##y; }
#define DLL_API_PLT_INIT_VAR2(x,y,z)         void x##y##_plt_init(void) __attribute__((used, constructor(DLL_API_CTOR+1))); void x##y##_plt_init(void) { x##_plt_rw._##y = z; }
#define DLL_API_PLT_INIT_FNC(x,y)            void x##y##_plt_init(void) __attribute__((used, constructor(DLL_API_CTOR+1))); void x##y##_plt_init(void) { x##_plt_rw._##y = x##_plt_ro._##y; }
#define DLL_API_PLT_INIT_FNC2(x,y,z)         void x##y##_plt_init(void) __attribute__((used, constructor(DLL_API_CTOR+1))); void x##y##_plt_init(void) { x##_plt_rw._##y = z; }
#define DLL_API_PLT_TERM(x)                  void x##_plt_term(void) __attribute__((used, destructor(DLL_API_DTOR))); void x##_plt_term(void) { x##_plt_rw = {0}; }
#define DLL_API_PLT_TERM_VAR(x,y)            void x##y##_plt_term(void) __attribute__((used, destructor(DLL_API_DTOR-1))); void x##y##_plt_term(void) { x##_plt_rw._##y = 0; }
#define DLL_API_PLT_TERM_FNC(x,y)            void x##y##_plt_term(void) __attribute__((used, destructor(DLL_API_DTOR-1))); void x##y##_plt_term(void) { x##_plt_rw._##y = NULL; }
#endif

#endif

/**
MANUAL GLOBAL OFFSET TABLE (GOT) Management Helpers
*/
#define DLL_API_GOT_SECT(x)                  extern x##_got_t __attribute__((section(".data.got_" #x)))

#endif
