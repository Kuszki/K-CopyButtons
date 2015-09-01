#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T17:43:10
#
#-------------------------------------------------

QT		+= core gui widgets

TARGET	= K-CopyButtons
TEMPLATE	= app

CONFIG	+=	c++11

SOURCES	+=	main.cpp \
			mainwindow.cpp \
			buttonwidget.cpp \
			dialogoptions.cpp \
			dialoginfo.cpp

HEADERS	+=	buttonwidget.hpp \
			mainwindow.hpp \
			dialogoptions.hpp \
			dialoginfo.hpp

FORMS	+=	mainwindow.ui \
			buttonwidget.ui \
			dialogoptions.ui \
			dialoginfo.ui

TRANSLATIONS	+=	kcopybuttons_pl.ts

QMAKE_CXXFLAGS	+=	-s -fomit-frame-pointer -march=native
