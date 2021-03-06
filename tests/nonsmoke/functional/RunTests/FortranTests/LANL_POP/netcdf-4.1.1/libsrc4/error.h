/* 

This file is part of netcdf-4, a netCDF-like interface for HDF5, or a
HDF5 backend for netCDF, depending on your point of view.

This file contains macros and prototyes relating to logging errors.

Copyright 1993, University Corporation for Atmospheric Research. See
COPYRIGHT file for copying and redistribution conditions.

*/

#ifndef _NCERROR_
#define _NCERROR_

#include <nc4internal.h>
#include <stdlib.h>
#include <assert.h>
#include "netcdf.h"

#define nc_calloc calloc
#define nc_malloc malloc
#define nc_free free

#ifdef LOGGING

/* To log something... */
void nc_log(int severity, const char *fmt, ...);
#define LOG(e) nc_log e

/* To log based on error code, and set retval. */
#define BAIL2(e) do { \
retval = e; \
LOG((0, "file %s, line %d.\n%s", __FILE__, __LINE__, nc_strerror(e))); \
H5Eprint(NULL); \
} while (0) 

/* To log an error message, set retval, and jump to exit. */
#define BAIL(e) do { \
BAIL2(e); \
goto exit; \
} while (0) 

/* To set retval and jump to exit, without logging error message. */
#define BAIL_QUIET(e) do { \
retval = e; \
goto exit; \
} while (0) 

#else

/* These definitions will be used unless LOGGING is defined. */
#define LOG(e)
#define BAIL(e) do { \
retval = e; \
goto exit; \
} while (0)
#define BAIL_QUIET BAIL
#define BAIL2(e) do { \
goto exit; \
} while (0)
#define nc_set_log_level(e)
#endif

#endif /* _NCERROR_ */


