CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = \
  -mcpu=cortex-m3 \
  -mthumb \
  -O0 \
  -g \
  -Wall \
  -Wextra \
  -ffreestanding \
  -nostdlib

INCLUDES = \
  -I. \
  -I$(FREERTOS)/include \
  -I$(FREERTOS)/portable/GCC/ARM_CM3

FREERTOS = ../FreeRTOS-Kernel

KERNEL_SRC = \
  $(FREERTOS)/tasks.c \
  $(FREERTOS)/queue.c \
  $(FREERTOS)/list.c \
  $(FREERTOS)/timers.c \
  $(FREERTOS)/event_groups.c

PORT_SRC = \
  $(FREERTOS)/portable/GCC/ARM_CM3/port.c

MEM_SRC = \
  heap_4.c

APP_SRC = \
  main.c \
  uart.c

OBJS = \
  startup.o \
  $(KERNEL_SRC:.c=.o) \
  $(PORT_SRC:.c=.o) \
  $(MEM_SRC:.c=.o) \
  $(APP_SRC:.c=.o)

TARGET = freertos_demo.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) \
	  -mcpu=cortex-m3 \
	  -mthumb \
	  -nostdlib \
	  -Wl,-T,linker_lm3s.ld \
	  -Wl,--gc-sections \
	  $(OBJS) \
	  -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

startup.o: startup.s
	$(CC) \
	  -mcpu=cortex-m3 \
	  -mthumb \
	  -c startup.s \
	  -o startup.o

clean:
	rm -f \
	  *.o \
	  *.elf \
	  *.bin \
	  $(FREERTOS)/**/*.o \
	  $(FREERTOS)/**/**/*.o

run: all
	qemu-system-arm \
	  -M lm3s6965evb \
	  -monitor none \
	  -serial tcp:127.0.0.1:4444,server,nowait \
	  -nographic \
	  -kernel $(TARGET)

debug: all
	qemu-system-arm \
	  -M lm3s6965evb \
	  -monitor none \
	  -serial tcp:127.0.0.1:4444,server,nowait \
	  -nographic \
	  -S \
	  -gdb tcp::3333 \
	  -kernel $(TARGET)

gdb:
	gdb-multiarch $(TARGET) \
	  -ex "target remote :3333"
