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

.PHONY: all exe lib force debug forcedebug clean

LIB = build/libcutie.so
EXE = build/rockpaperscissors

all: $(LIB) $(EXE)

lib: $(LIB)

exe: $(EXE)

$(LIB):
	make -C libsrc

build/%:
	make -C exesrc

clean:
	make -C libsrc clean
	make -C exesrc clean

force:
	make -C libsrc force
	make -C exesrc force

debug:
	make -C libsrc debug
	make -C exesrc debug

forcedebug:
	make -C libsrc forcedebug
	make -C exesrc forcedebug

