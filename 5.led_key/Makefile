led_key.bin: start.o main.o
	arm-linux-ld -Ttext 0x50000000 -o led_key.elf $^
	arm-linux-objcopy -O binary led_key.elf led_key.bin
	arm-linux-objdump -D led_key.elf > led_key_elf.dis
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis  -rf