includedir = headers/
srcdir = sources/
bindir = binaries/
objdir = objects/

QMAKE_CXX = gcc
QMAKE_CXXFLAGS += -I$${includedir}
QMAKE_CXXFLAGS += -x c -Wall -Wextra -pedantic

SOURCES = $${srcdir}graph.c\
          $${srcdir}main.c

HEADERS = $${includedir}graph.h 


TARGET = $${bindir}grApph

OBJECTS_DIR = $${objdir}