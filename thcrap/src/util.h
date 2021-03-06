/**
  * Touhou Community Reliant Automatic Patcher
  * Main DLL
  *
  * ----
  *
  * Random utility functions.
  */

#pragma once

/// Pointers
/// --------
size_t dword_align(const size_t val);
BYTE* ptr_dword_align(const BYTE *in);
// Advances [src] by [num] and returns [num].
size_t ptr_advance(const unsigned char **src, size_t num);
// Copies [num] bytes from [src] to [dst] and advances [src].
size_t memcpy_advance_src(unsigned char *dst, const unsigned char **src, size_t num);
/// --------

/// Strings
/// -------
// Replaces every occurence of the ASCII character [from] in [str] with [to].
void str_ascii_replace(char *str, const char from, const char to);

// Changes directory slashes in [str] to '/'.
void str_slash_normalize(char *str);

/**
  * Usually, the normal version with Unix-style forward slashes should be used, but there
  * are some cases which require the Windows one:
  *
  * - PathRemoveFileSpec is the only shlwapi function not to work with forward
  *   slashes, effectively chopping a path down to just the drive specifier
  *   (PathRemoveFileSpecU works as expected)
  * - In what is probably the weirdest bug I've ever encountered, th07
  *   _REQUIRES_ its launch path to have '\' instead of '/' - otherwise it...
  *   disables vsync.
  *   Yes, out of all sensible bugs there could have been, it had to be _this_.
  *   Amazing.
  */
void str_slash_normalize_win(char *str);

// Counts the number of digits in [number]
unsigned int str_num_digits(int number);

// Returns the base of the number in [str].
int str_num_base(const char *str);

// Prints the hexadecimal [date] (0xYYYYMMDD) as YYYY-MM-DD to [format]
void str_hexdate_format(char format[11], DWORD date);
/// -------
