rtos_path = $(PROJECT_ROOT)/rtos/FreeRTOS/Source
_src_files := list.c queue.c tasks.c timers.c portable/GCC/ARM_CM4F/port.c portable/MemMang/heap_4.c
_include_path := include portable/GCC/ARM_CM4F

CPPFLAGS += $(addprefix -I$(rtos_path)/, $(_include_path))
SOURCE_FILES_LIST += $(addprefix $(rtos_path)/, $(_src_files))

rtos_extra_path = $(PROJECT_ROOT)/rtos/FreeRTOS-Plus/Source
_extra_src_files := FreeRTOS-Plus-CLI/FreeRTOS_CLI.c
_extra_include_path := FreeRTOS-Plus-CLI

CPPFLAGS += $(addprefix -I$(rtos_extra_path)/, $(_extra_include_path))
SOURCE_FILES_LIST += $(addprefix $(rtos_extra_path)/, $(_extra_src_files))