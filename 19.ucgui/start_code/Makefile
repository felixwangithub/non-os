
include $(TOPDIR)/config.mk

SOBJS	:= s3c6410.o
COBJS	:= clock.o sdram.o nand.o timer.o uart.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(SOBJS) $(COBJS)
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

	
