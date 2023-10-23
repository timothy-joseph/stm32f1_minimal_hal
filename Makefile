CFLAGS  ?= -Os -mcpu=cortex-m3
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = main.c 

ifeq ($(OS),Windows_NT)
  RM = cmd /C del /Q /F
else
  RM = rm -f
endif

build: firmware.bin

firmware.elf: $(SOURCES)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: firmware.bin
	st-flash --reset write $< 0x8000000

clean:
	$(RM) firmware.*
