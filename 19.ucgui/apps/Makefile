
include $(TOPDIR)/config.mk

OBJS	:= lcd_s70.o main.o printf.o
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



