// Filename: selectThreadImpl.h
// Created by:  drose (09Aug02)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#ifndef SELECTTHREADIMPL_H
#define SELECTTHREADIMPL_H

#include "dtoolbase.h"

////////////////////////////////////////////////////////////////////
// This file decides which of the core implementations of the various
// threading and locking implementations we should use, based on
// platform and/or available libraries.
//
// This file, along with mutexImpl.h and the various Mutex
// implementation classes, are defined in dtool so that some form of
// critical-section protection will be available to view low-level
// classes like TypeRegistry.  Most of the rest of the threading and
// synchronization classes are defined in panda/src/express.
////////////////////////////////////////////////////////////////////

// This keyword should be used to mark any variable which is possibly
// volatile because multiple threads might contend on it, unprotected
// by a mutex.  It will be defined out in the non-threaded case.
// Other uses for volatile (dma buffers, for instance) should use the
// regular volatile keyword.
#define TVOLATILE volatile

#if !defined(HAVE_THREADS)

// With threading disabled, use the do-nothing implementation.
#define THREAD_DUMMY_IMPL 1

// And the TVOLATILE keyword means nothing in the absence of threads.
#undef TVOLATILE
#define TVOLATILE

#elif defined(SIMPLE_THREADS)
// Use the simulated threading library.
#define THREAD_SIMPLE_IMPL 1
#undef TVOLATILE
#define TVOLATILE

#elif defined(WIN32_VC)

// In Windows, use the native threading library.
#define THREAD_WIN32_IMPL 1

#elif defined(HAVE_POSIX_THREADS)

// Posix threads are nice.
#define THREAD_POSIX_IMPL 1

#else

// This is a configuration error.  For some reason, HAVE_THREADS is
// defined but we don't have any way to implement it.
#error No thread implementation defined for platform.

#endif

// Let's also factor out some of the other configuration variables.
#if defined(DO_PIPELINING) && defined(HAVE_THREADS)
#define THREADED_PIPELINE 1
#else
#undef THREADED_PIPELINE
#endif

#endif
