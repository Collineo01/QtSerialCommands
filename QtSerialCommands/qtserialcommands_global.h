#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTSERIALCOMMANDS_LIB)
#  define QTSERIALCOMMANDS_EXPORT Q_DECL_EXPORT
# else
#  define QTSERIALCOMMANDS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTSERIALCOMMANDS_EXPORT
#endif
