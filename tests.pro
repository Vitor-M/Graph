includedir = headers/
srcdir = sources/
bindir = binaries/
objdir = objects/

QMAKE_CXX = gcc
QMAKE_CXXFLAGS += -I$${includedir}
QMAKE_CXXFLAGS += -x c -Wall -Wextra -pedantic

SOURCES = $${srcdir}graph.c\
          $${srcdir}dijkstra.c\
          $${srcdir}test.c

HEADERS = $${includedir}graph.h\
          $${includedir}dijkstra.h\


TARGET = $${bindir}grApph

OBJECTS_DIR = $${objdir}