# Makefile
#
# (header)
# Copyright (c) 2016 Ammon Smith, Auggie Balquin, Bradley Cai
# 
# (program) is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 2.1 of the License, or
# (at your option) any later version.
# 
# (program) is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with barman.  If not, see <http://www.gnu.org/licenses/>.
#

.PHONY: all force debug forcedebug test clean

CC = g++
BUILDDIR = ../build
EXE = ../build/tictactoe

SRCEXT = cpp
OBJEXT = cpp.o
SOURCES = $(shell echo *.$(SRCEXT))
OBJECTS = $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
FLAGS = -std=c++11 -pipe -Wall -Wextra -O3
INC = -I .
LIB = -L ../build -l cutie

all: $(EXE)

$(EXE): $(OBJECTS)
	@mkdir -p '$(BUILDDIR)'
	@echo '[LN] $(shell basename $(EXE))'
	@$(CC) $(FLAGS) $(LIB) $(DEBUG) $^ -o $(EXE)

$(BUILDDIR)/%.$(OBJEXT): %.$(SRCEXT)
	@mkdir -p '$(BUILDDIR)'
	@echo '[CC] $(shell basename $@)'
	@$(CC) $(FLAGS) $(LIB) $(INC) $(DEBUG) -c -o $@ $<

clean:
	@echo '[RM] $(BUILDDIR)'
	@rm -rf '$(BUILDDIR)'

force:
	@echo '[RM] $(BUILDDIR)'
	@rm -rf '$(BUILDDIR)'
	make $(EXE)

debug:
	make $(EXE) DEBUG='-Og -g'

forcedebug: clean debug

