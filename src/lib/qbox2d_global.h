#ifndef QBOX2D_GLOBAL_H
#define QBOX2D_GLOBAL_H

#include <QtCore/qglobal.h>

//#define QBOX2DSHARED_EXPORT

#if defined(QBOX2D_LIBRARY)
#  define QBOX2DSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QBOX2DSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QBOX2D_GLOBAL_H
