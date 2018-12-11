#
# Copyright (C)  Dinghong Huang(1048272975@qq.com)
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

OBJS	:= GUI_X.o GUI_X_Touch.o
SRCS	:= $(OBJS:.o=.c)

CURDIR	:= $(shell pwd)
FOLDER	:= $(notdir $(CURDIR))
LIB	:= lib$(FOLDER).a

.PHONY: all clean
all: .depend $(LIB)

$(LIB): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f .depend *.o $(LIB)


#########################################################################

# defines $(obj).depend target
include $(TOPDIR)/rules.mk

sinclude .depend

#########################################################################



