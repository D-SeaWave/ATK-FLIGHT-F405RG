bsp_path := $(PROJECT_ROOT)/board/bsp/$(BOARD)

_core_src_files   := sys.c stdio-retarget.c default_interrupt_handler.c
_periph_src_files := usart-uart.c timers.c pinmux.c spi.c gpio.c iic.c
_driver_src_files := mpu6000.c
_include_path     := .

CPPFLAGS += $(addprefix -I$(bsp_path)/, $(_include_path))
SOURCE_FILES_LIST += $(addprefix $(bsp_path)/core/, $(_core_src_files))
SOURCE_FILES_LIST += $(addprefix $(bsp_path)/driver/, $(_driver_src_files))
SOURCE_FILES_LIST += $(addprefix $(bsp_path)/periph/, $(_periph_src_files))
