PREFIX  = /usr/local/h8-elf
ARCH    = h8300-elf
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

TOOLDIR  = ../tools/exec
ELF2KIRA = $(TOOLDIR)/elf2kira

# FreeBSD-4.x:/dev/cuaaX, FreeBSD-6.x:/dev/cuadX, FreeBSD(USB):/dev/cuaUx
# Linux:/dev/ttySx, Linux(USB):/dev/ttyUSBx, Windows:comX
H8WRITE_SERDEV = /dev/cu.usbserial

OBJS  = startup.o main.o
OBJS += lib.o serial.o
OBJS += port.o timer.o ad.o

TARGET = kiraos

CFLAGS = -W -Wall -mh -mn -nostdinc -nostdlib -fno-builtin -mrelax
#CFLAGS += -mint32
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKIRAOS

#AFLAGS += -CPu=300HA:24
#CFLAGS += -CPu=300HA:24
LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :		$(TARGET) kira

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

.s.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET)*

serial :
		cu -l $(H8WRITE_SERDEV) -s 9600

kira :
		$(ELF2KIRA)
		cp $(TARGET).kira ../
