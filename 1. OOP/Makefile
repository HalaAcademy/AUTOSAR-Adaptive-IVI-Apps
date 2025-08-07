# Makefile build cho AUTOSAR-Classic-ECU-Development/1. DIO Driver
# Output (.o, .elf, .bin) sẽ nằm trong thư mục Tools/

# Tên thư mục chứa file build
BUILDDIR = Tools
# Tên file đầu ra (không có phần mở rộng)
TARGET   = $(BUILDDIR)/blinkled

# Toolchain
CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy

# Include path và define macro
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall -ffreestanding -nostdlib \
         -ICMSIS \
         -IMCAL/Dio \
         -IMCAL/Port \
         -ISPL/inc \
         -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER

# Linker script
LDSCRIPT = Linker/stm32f103.ld
LDFLAGS  = -T$(LDSCRIPT) -nostdlib -Wl,--gc-sections

# Source files
SRCS_C = main.c \
         MCAL/Dio/Dio.c \
         MCAL/Port/Port.c \
         $(wildcard SPL/src/*.c)
SRCS_S = Startup/startup_stm32f103.s

# Object files trong Tools/
OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS_C)) \
       $(patsubst %.s,$(BUILDDIR)/%.o,$(SRCS_S))

# Tạo thư mục build nếu chưa có
$(shell mkdir -p $(BUILDDIR))

# Mục tiêu mặc định
all: $(TARGET).bin

# Biên dịch C -> .o
$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Biên dịch ASM -> .o
$(BUILDDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link ELF
$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

# Tạo BIN từ ELF
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Flash qua OpenOCD/ST-Link (bỏ qua lỗi exit code)
flash: $(TARGET).bin
	-openocd \
	  -f interface/stlink.cfg \
	  -f target/stm32f1x.cfg \
	  -c "transport select hla_swd" \
	  -c "set CPUTAPID 0x2ba01477" \
	  -c "init" \
	  -c "reset halt" \
	  -c "flash write_image erase $(TARGET).bin 0x08000000 verify" \
	  -c "reset run" \
	  -c "exit" || true

# Xóa build artifacts
clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET).elf $(TARGET).bin

.PHONY: all clean flash
