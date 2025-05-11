# gpioTest/Makefile
CFILES = kernel.c gpio.c
OFILES = $(CFILES:.c=.o)

INCLUDES = -I../include
GCCFLAGS = -g -march=rv32i -mabi=ilp32 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -O0 $(INCLUDES)
CC = riscv-gaisler-elf-gcc
AS = riscv-gaisler-elf-as
LD = riscv-gaisler-elf-ld

all: kernel.elf

start.o:
	$(AS) -march=rv32i -mabi=ilp32 -c ../common/start.s -o start.o

%.o: %.c
	$(CC) $(GCCFLAGS) -c $< -o $@

kernel.elf: start.o $(OFILES)
	$(LD) -g -nostdlib start.o $(OFILES) -T ../common/linker.ld -o $@

clean:
	rm -f *.o kernel.elf
