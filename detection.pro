TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_core
LIBS += -L/usr/local/lib -lopencv_calib3d
LIBS += -L/usr/local/lib -lopencv_features2d
LIBS += -L/usr/local/lib -lopencv_flann
LIBS += -L/usr/local/lib -lopencv_highgui
LIBS += -L/usr/local/lib -lopencv_imgproc
LIBS += -L/usr/local/lib -lopencv_ml
LIBS += -L/usr/local/lib -lopencv_photo
LIBS += -L/usr/local/lib -lopencv_videostab
LIBS += -L/usr/local/lib -lopencv_videoio
LIBS += -L/usr/local/lib -lopencv_video
LIBS += -L/usr/local/lib -lopencv_superres
LIBS += -L/usr/local/lib -lopencv_shape
LIBS += -L/usr/local/lib -lopencv_stitching
LIBS += -L/usr/local/lib -lopencv_imgcodecs
LIBS += -L/usr/local/lib -lopencv_objdetect

unix:!macx: LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/ -lpthread

INCLUDEPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu
DEPENDPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/libpthread.a
