#ifndef QMOSICPROCESS_GLOBAL_H
#define QMOSICPROCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QMOSICPROCESS_LIB
# define QMOSICPROCESS_EXPORT Q_DECL_EXPORT
#else
# define QMOSICPROCESS_EXPORT Q_DECL_IMPORT
#endif

#endif // QMOSICPROCESS_GLOBAL_H
