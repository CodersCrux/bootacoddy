
BIN = out/bootacoddy.bin
ISO = out/bootacoddy.iso

LINK = link.ld
GRUBCFG = grub.cfg
RAMDISK = ramdisk.bafs

AS = nasm
CC = gcc
CPPC = g++
Ee = e
LD = ld

CFLAGS = -O1 -Isrc -nostdlib -nostdinc -fno-exceptions -fno-builtin -fno-stack-protector -m32 -march=i686 -fno-rtti -fno-use-cxa-atexit
LDFLAGS =-m elf_i386 -z noexecstack
ASFLAGS = -f elf


SRC_ASM = $(shell find ./src/ -type f -name "*.asm")
SRC_C = $(shell find ./src/ -type f -name "*.c")
SRC_CPP = $(shell find ./src/ -type f -name "*.cpp")
OUT_ASM = $(SRC_ASM:.asm=.o)
OUT_C = $(SRC_C:.c=.o)
OUT_CPP = $(SRC_CPP:.cpp=.o)

MAIN_DIR = $(CURDIR)

all: build run

build: clean $(OUT_ASM) $(OUT_C) $(OUT_CPP) link initrd iso

clean:
	@rm -rf ./out/

link:
	@$(LD) -T$(LINK) $(LDFLAGS) -o $(BIN) $(subst ./src/,./out/,$(OUT_ASM)) $(subst ./src/,./out/,$(OUT_C)) $(subst ./src/,./out/,$(OUT_CPP))

initrd:
	@./bafs_gen

iso:
	@mkdir -p ./out/iso/boot/grub/
	@cp $(BIN) ./out/iso/boot/
	@cp $(GRUBCFG) ./out/iso/boot/grub
	@cp $(RAMDISK) ./out/iso/boot/
	@grub-mkrescue -o $(ISO) ./out/iso/ -V bootacoddy

run:
	qemu-system-i386 -nic model=ne2k_pci -serial file:/dev/fd/1 -no-reboot -vga virtio -usb -serial stdio -drive format=raw,media=cdrom,file=$(ISO) -m 2G

etch:
	sudo -S dd bs=4M if=$(ISO) of=/dev/sda status=progress oflag=sync

%.o: %.asm
	@mkdir -p $(subst src/,out/,$(dir $@))
	@$(AS) $(ASFLAGS) -o $(subst src/,out/,$@) $<

%.o: %.c
	@mkdir -p $(subst src/,out/,$(dir $@))
	@$(CC) $(CFLAGS) -o $(subst src/,out/,$@) -c $<

%.o: %.cpp
	@mkdir -p $(subst src/,out/,$(dir $@))
	@$(CPPC) $(CFLAGS) -o $(subst src/,out/,$@) -c $<


	