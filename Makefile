C_SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard headers/*.h)

OBJ = ${C_SOURCES:.c=.o}

all: build run

boot_sect.bin:bootloader/main.asm bootloader/gdt.asm bootloader/print_string_pm.asm bootloader/printf.asm bootloader/switch_to_pm.asm bootloader/readDisk.asm 
	nasm -i./bootloader/ -f bin bootloader/main.asm -o $@

clean:
	rm -f *.bin **/*.o

clean_src: 
	rm -f src/*.o

run: image 
	qemu-system-x86_64 $< 

%.o: src/%.c ${HEADERS}
	gcc -m32 -I../headers/ -ffreestanding  -c $< -o build/$@

%.o: bootloader/%.asm
	nasm $<  -felf32 -o build/$@

kernel.bin: ${OBJ} build/kernel_entry.o
	ld -melf_i386 -o $@ -T link.ld $^ --oformat binary 

image: boot_sect.bin kernel.bin
	cat $^ > image

build: clean boot_sect.bin kernel.o kernel_entry.o kernel.bin image
