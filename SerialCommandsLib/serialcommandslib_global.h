#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SERIALCOMMANDSLIB_LIB)
#  define SERIALCOMMANDSLIB_EXPORT Q_DECL_EXPORT
# else
#  define SERIALCOMMANDSLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define SERIALCOMMANDSLIB_EXPORT
#endif
