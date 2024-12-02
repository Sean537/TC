# Project: TC
# Makefile created by Sean537 in 537 Studio

CPP      = g++
CC       = gcc
CXXFLAGS = -std=c++11
CFLAGS   = -std=c++11
OBJ      = tc.o
LINKOBJ  = tc.o
BIN      = tc.so tc.dll
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)
	@echo Clean successful.

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)
	@echo Link objects to Dynamic-Link Library.

tc.o: tc.cpp
	$(CPP) -c tc.cpp -fPIC -shared -o tc.o $(CXXFLAGS)
	@echo Build tc.