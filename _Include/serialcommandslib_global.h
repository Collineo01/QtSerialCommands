#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SERIALCOMMANDSLIB_LIB)
#  define Q_DECL_EXPORT
# else
#  define Q_DECL_IMPORT
# endif
#else
# define
#endif
