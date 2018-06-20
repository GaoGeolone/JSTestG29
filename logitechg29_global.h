#ifndef LOGITECHG29_GLOBAL_H
#define LOGITECHG29_GLOBAL_H

#include <QtCore/qglobal.h>
#include "hidapi.h"
#include "SocketMatTransmissionClient.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv/cv.h>
#include <QTextCodec>
#include <QtNetwork>//use the socket
#include <QImageReader>


#if defined(LOGITECHG29_LIBRARY)
#  define LOGITECHG29SHARED_EXPORT Q_DECL_EXPORT
#else
#  define LOGITECHG29SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGITECHG29_GLOBAL_H
