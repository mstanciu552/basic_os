boot_sect.bin:bootloader/main.asm bootloader/gdt.asm bootloader/print_string_pm.asm bootloader/printf.asm bootloader/switch_to_pm.asm bootloader/readDisk.asm 
	nasm -i./bootloader/ -f bin bootloader/main.asm -o $@

clean:
	rm *.bin **/*.o

run: image 
	qemu-system-x86_64 $< 

kernel.o: src/kernel.c
	gcc -ffreestanding -c $< -o build/$@

kernel_entry.o: bootloader/kernel_entry.asm
	nasm $<  -f elf64 -o build/$@

kernel.bin: build/kernel_entry.o build/kernel.o
	ld -o kernel.bin -T link.ld $^ --oformat binary --entry main

image: boot_sect.bin kernel.bin
	cat $^ > image

build: clean boot_sect.bin kernel.o kernel_entry.o kernel.bin image