/*
 * Copyright (C) 2017 Tim Cadogan-Cowper.
 *
 * This file is part of Fabularium.
 *
 * Fabularium is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fabularium; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/* Fabularium-specific Tads OS functions.
 *
 * Uses QTads and FrobTADS as a guide.
 *
 * This file *must not* contain C++ code, since it gets included from
 * the portable Tads C code.
 */
#ifndef OSFAB_H
#define OSFAB_H

/* Standard C headers should never be included from inside an extern "C" block.
 * However, we are included from tads2/os.h from inside such a block ourselves,
 * so everything we include will be extern "C" too.  We need to reverse this or
 * some compilers will bark (Sun C++ 5.9 on Linux, for example.) */
#ifdef __cplusplus
extern "C++" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#ifdef __cplusplus
}
#endif

/* The base code needs access to the C99 exact-width types (int32_t and
 * friends.)  Those are provided by <stdint.h>, so we simply include that
 * if it's available. */
#include <stdint.h>

/* Used by the base code to inhibit "unused parameter" compiler warnings. */
#define VARUSED(var) (void)var

/* We don't support the Atari 2600. */
#include "osbigmem.h"

/* Our Tads OEM identifier. */
#define TADS_OEM_NAME "Tim Cadogan-Cowper"
#define NO_T2_COPYRIGHT_NOTICE

/* We assume that the C-compiler is mostly ANSI compatible. */
#define OSANSI

/* Orpheus is a multimedia interpreter, not text only */
#define USE_HTML

/* Provide some non-standard functions (memicmp(), etc). */
int memicmp(const char *s1, const char *s2, size_t len);
#define stricmp strcasecmp
#define strnicmp strncasecmp

/* Special function qualifier needed for certain types of callback functions.
 * This is for old 16-bit systems; we don't need it and define it to nothing.
 */
#define OS_LOADDS

/* Unices don't suffer the near/far pointers brain damage (thank God) so we
 * make this a do-nothing macro. */
#define osfar_t

/* This is used to explicitly discard computed values (some compilers would
 * otherwise give a warning like "computed value not used" in some cases).
 * Casting to void should work on every ANSI-Compiler. */
#define DISCARD (void)

/* Copies a struct into another.  ANSI C allows the assignment operator to be
 * used with structs. */
#define OSCPYSTRUCT(x,y) ((x)=(y))

/* Link error messages into the application. */
#define ERR_LINK_MESSAGES

/* System identifier and system descriptive name. */
#define OS_SYSTEM_NAME "Fabularium"
#define OS_SYSTEM_LDESC "Fabularium (Android)"

/* Program Exit Codes. */
#define OSEXSUCC 0 /* Successful completion. */
#define OSEXFAIL 1 /* Failure. */

/* Here we configure the osgen layer; refer to tads2/osgen3.c for more
 * information about the meaning of these macros. */
#define USE_DOSEXT
#define USE_NULLSTYPE
#define USE_NULL_SET_TITLE

/* STD_OSCLS is undocumented; it enables a standard oscls()
 * implementation. */
#define STD_OSCLS

/* Undocumented; enables a standard implementation of the highlighting &
 * colors routines.  It also enables the osgen3 banner API
 * implementation. */
#define STD_OS_HILITE

/* Theoretical maximum osmalloc() size.  Unix systems have at least a 32-bit
 * memory space.  Even on 64-bit systems, 2^32 is a good value, so we don't
 * bother trying to find out an exact value. */
#define OSMALMAX 0xffffffffL

/* Maximum length of a filename. */
#define OSFNMAX 255

#ifndef OSPATHALT
/* Other path separator characters. */
#define OSPATHALT ""
#endif

#ifndef OSPATHURL
/* Path separator characters for URL conversions. */
#define OSPATHURL "/"
#endif

#ifndef OSPATHCHAR
/* Normal path separator character. */
#define OSPATHCHAR '/'
#endif

/* Directory separator for PATH-style environment variables. */
#define OSPATHSEP ':'

/* String giving the special path representing the current
 * working directory. */
#define OSPATHPWD "."

#ifndef OS_NEWLINE_SEQ
/* ASCII string giving the local newline sequence to write on output. */
#define OS_NEWLINE_SEQ  "\n"
#endif

/* Directory separator for PATH-style environment variables. */
#define OSPATHSEP ':'

/* File handle structure for osfxxx functions. */
typedef FILE osfildef;

/* Directory handle for searches via os_open_dir() et al. */
typedef DIR* osdirhdl_t;

/* file type/mode bits */
#define OSFMODE_FILE    S_IFREG
#define OSFMODE_DIR     S_IFDIR
#define OSFMODE_CHAR    S_IFCHR
#define OSFMODE_BLK     S_IFBLK
#define OSFMODE_PIPE    S_IFIFO
#define OSFMODE_LINK    S_IFLNK
#define OSFMODE_SOCKET  0

/* File attribute bits. */
#define OSFATTR_HIDDEN  0x0001
#define OSFATTR_SYSTEM  0x0002
#define OSFATTR_READ    0x0004
#define OSFATTR_WRITE   0x0008

/* Get a file's stat() type. */
int osfmode( const char* fname, int follow_links, unsigned long* mode,
             unsigned long* attr );

/* The maximum width of a line of text.  We ignore this, but the base code
 * needs it defined.
 *
 * Note: this value must fit in a single byte, so the maximum is 255. */
#define OS_MAXWIDTH 255

/* Disable the Tads swap file; computers have plenty of RAM these days. */
#define OS_DEFAULT_SWAP_ENABLED 0

/* TADS 2 macro/function configuration.  Modern configurations always use the
 * no-macro versions, so these definitions should always be set as shown
 * below. */
#define OS_MCM_NO_MACRO
#define ERR_NO_MACRO

/* Not really needed; just a dummy. */
#define OS_TR_USAGE "usage: tads [options] file"

/* These values are used for the "mode" parameter of osfseek() to
 * indicate where to seek in the file. */
#define OSFSK_SET SEEK_SET /* Set position relative to the start of the file. */
#define OSFSK_CUR SEEK_CUR /* Set position relative to the current file position. */
#define OSFSK_END SEEK_END /* Set position relative to the end of the file. */

/* ============= Functions follow ================ */

/* Allocate a block of memory of the given size in bytes. */
#define osmalloc malloc

/* Free memory previously allocated with osmalloc(). */
#define osfree free

/* Reallocate memory previously allocated with osmalloc() or osrealloc(),
 * changing the block's size to the given number of bytes. */
#define osrealloc realloc

/* Open text file for reading. */
#define osfoprt(fname,typ) (fopen((fname),"r"))

/* Open text file for writing. */
#define osfopwt(fname,typ) (fopen((fname),"w"))

/* Open text file for reading and writing, keeping the file's existing
 * contents if the file already exists or creating a new file if no
 * such file exists. */
osfildef* osfoprwt( const char* fname, os_filetype_t typ );

/* Open text file for reading/writing.  If the file already exists,
 * truncate the existing contents.  Create a new file if it doesn't
 * already exist. */
#define osfoprwtt(fname,typ) (fopen((fname),"w+"))

/* Open binary file for writing. */
#define osfopwb(fname,typ) (fopen((fname),"wb"))

/* Open source file for reading - use the appropriate text or binary
 * mode. */
#define osfoprs osfoprt

/* Open binary file for reading. */
#define osfoprb(fname,typ) (fopen((fname),"rb"))

/* Open binary file for reading/writing.  If the file already exists,
 * keep the existing contents.  Create a new file if it doesn't already
 * exist. */
osfildef* osfoprwb( const char* fname, os_filetype_t typ );

/* Open binary file for reading/writing.  If the file already exists,
 * truncate the existing contents.  Create a new file if it doesn't
 * already exist. */
#define osfoprwtb(fname,typ) (fopen((fname),"w+b"))

/* Get a line of text from a text file. */
#define osfgets fgets

/* Write a line of text to a text file. */
#define osfputs fputs

/* Write bytes to file. */
#define osfwb(fp,buf,bufl) (fwrite((buf),(bufl),1,(fp))!=1)

/* Flush buffered writes to a file. */
#define osfflush fflush

/* Read bytes from file. */
#define osfrb(fp,buf,bufl) (fread((buf),(bufl),1,(fp))!=1)

/* Read bytes from file and return the number of bytes read. */
#define osfrbc(fp,buf,bufl) (fread((buf),1,(bufl),(fp)))

/* Get the current seek location in the file. */
#define osfpos ftell

/* Seek to a location in the file. */
#define osfseek fseek

/* Close a file. */
#define osfcls fclose

/* Delete a file. */
#define osfdel remove

/* Access a file - determine if the file exists.
 *
 * We map this to the access() function.  It should be available in
 * virtually every system out there, as it appears in many standards
 * (SVID, AT&T, POSIX, X/OPEN, BSD 4.3, DOS, MS Windows, maybe more). */
#define osfacc(fname) (access((fname), F_OK))

/* Rename a file. */
#define os_rename_file(from, to) (rename(from, to) == 0)

/* Get a file's stat() type. */
struct os_file_stat_t;
int os_file_stat( const char* fname, int follow_links,
                  struct os_file_stat_t* s );

/* Get a character from a file. */
#define osfgetc fgetc

/* Update progress display.
 *
 * We don't provide any kind of "compilation progress display", so we
 * just define this as an empty macro.
 */
#define os_progress(fname,linenum)

/* Initialize the time zone.
 *
 * We don't need this (I think). */
#define os_tzset()

/* File timestamp type.
 *
 * Needed by the TADS 3 compiler. */
struct os_file_time_t {
    time_t t;
};

/* Allocating sprintf/vsprintf.  NB: These definitions are
 * placeholders.  asprintf() and vasprintf() are GNU/BSD extensions
 * that aren't available on all Unix variants.  Eventually these will
 * need to be replaced with more thorough versions that encompass
 * other Unix variants. */
int asprintf(char **strp, const char *fmt, ...);
int vasprintf(char **strp, const char *fmt, va_list ap);
#define os_asprintf asprintf
#define os_vasprintf vasprintf

#endif /* OSFAB_H */
