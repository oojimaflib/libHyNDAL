CC=g++
PREFIX=/usr/local
LIBNAME=../libHyNDAL_ISIS.so
CXXFLAGS=-g -pthread -fPIC -DTESTING -Wall -I../../boost/include
LDFLAGS=-g -pthread -fPIC -DTESTING -Wall -L../../boost/lib -L..
LIBS=-lHyNDAL

SOURCES=ISISDataTable.cpp			\
	ISISNetwork.cpp				\
	ISISStructure.cpp			\
	ISISStructures.cpp			\
	../util/string_list.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) $(LIBS) -o $(LIBNAME)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(LIBNAME)

install: $(LIBNAME)
	install -m 0755 $(LIBNAME) $(PREFIX)/lib

.PHONY: install
