TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    tools.cpp \
    mom.cpp \
    child.cpp \
    mainMom.cpp \
    mainKid.cpp

OTHER_FILES += \
    makefile

HEADERS += \
    tools.hpp \
    mom.hpp \
    child.hpp \
    shared.hpp

