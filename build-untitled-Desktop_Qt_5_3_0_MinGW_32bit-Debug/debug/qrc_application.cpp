/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.3.0
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qglobal.h>

static const unsigned char qt_resource_data[] = {
  // H:/sfiles/homework/untitled/data_in
  0x0,0x0,0x0,0x46,
  0x31,
  0x20,0x32,0x20,0x33,0x20,0x34,0x20,0x35,0x20,0x31,0x20,0x36,0x20,0x36,0xa,0x32,
  0x20,0x31,0x20,0x33,0x20,0x34,0x20,0x32,0x20,0x33,0x20,0x31,0x20,0x32,0x20,0xa,
  0x34,0x20,0x33,0x20,0x32,0x20,0x33,0x20,0x32,0x20,0x34,0x20,0x31,0x20,0x34,0xa,
  0x31,0x32,0x20,0x32,0x20,0x32,0x33,0x20,0x32,0x20,0x32,0x33,0x20,0x32,0x31,0x20,
  0x32,0x33,0x20,0x32,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // data_in
  0x0,0x7,
  0xa,0x8a,0x75,0x3e,
  0x0,0x64,
  0x0,0x61,0x0,0x74,0x0,0x61,0x0,0x5f,0x0,0x69,0x0,0x6e,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/data_in
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

QT_BEGIN_NAMESPACE

extern Q_CORE_EXPORT bool qRegisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

extern Q_CORE_EXPORT bool qUnregisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

QT_END_NAMESPACE


int QT_MANGLE_NAMESPACE(qInitResources_application)()
{
    QT_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_application))

int QT_MANGLE_NAMESPACE(qCleanupResources_application)()
{
    QT_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_DESTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qCleanupResources_application))
