################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/arm_5.1.6

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./network_if.obj" \
"./startup_ccs.obj" \
"./uart_if.obj" \
"./udma_if.obj" \
"./wdt_if.obj" \
"./source/system/hibernate.obj" \
"./source/system/system.obj" \
"./source/pin_mux_config.obj" \
"./source/hardware/watchdog/watchdog.obj" \
"./source/hardware/uart/uartA0.obj" \
"../cc3200v1p32.cmd" \
-l"libc.a" \
-l"driverlib.a" \
-l"simplelink.a" \
-l"free_rtos.a" \
-l"libEmail.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/system/subdir_vars.mk
-include source/subdir_vars.mk
-include source/hardware/watchdog/subdir_vars.mk
-include source/hardware/uart/subdir_vars.mk
-include subdir_rules.mk
-include source/system/subdir_rules.mk
-include source/subdir_rules.mk
-include source/hardware/watchdog/subdir_rules.mk
-include source/hardware/uart/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
iot_postbox.out \

EXE_OUTPUTS__QUOTED += \
"iot_postbox.out" \

BIN_OUTPUTS += \
iot_postbox.hex \

BIN_OUTPUTS__QUOTED += \
"iot_postbox.hex" \


# All Target
all: iot_postbox.out

# Tool invocations
iot_postbox.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -g --define=ccs --define=cc3200 --define=USE_FREERTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off -z -m"iot_postbox.map" --heap_size=0x8000 --stack_size=0x800 -i"c:/ti/ccsv6/tools/compiler/arm_5.1.6/lib" -i"C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib/ccs/Release" -i"C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/ccs/OS" -i"C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib/ccs/free_rtos" -i"c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" -i"C:/ti/CC3200SDK_1.0.0/cc3200-sdk/netapps/smtp/client/ccs/Release" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="iot_postbox_linkInfo.xml" --rom_model -o "iot_postbox.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

iot_postbox.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armhex"  -o "iot_postbox.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "network_if.pp" "startup_ccs.pp" "uart_if.pp" "udma_if.pp" "wdt_if.pp" "source\system\hibernate.pp" "source\system\system.pp" "source\pin_mux_config.pp" "source\hardware\watchdog\watchdog.pp" "source\hardware\uart\uartA0.pp" 
	-$(RM) "main.obj" "network_if.obj" "startup_ccs.obj" "uart_if.obj" "udma_if.obj" "wdt_if.obj" "source\system\hibernate.obj" "source\system\system.obj" "source\pin_mux_config.obj" "source\hardware\watchdog\watchdog.obj" "source\hardware\uart\uartA0.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"c:/ti/ccsv6/utils/tiobj2bin/tiobj2bin" "iot_postbox.out" "iot_postbox.bin" "c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armofd" "c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armhex" "c:/ti/ccsv6/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

