################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./ADC.obj" \
"./AUDIO.obj" \
"./BLUETOOTH.obj" \
"./BUTTON.obj" \
"./CMD.obj" \
"./DMA.obj" \
"./INTERRUPTS.obj" \
"./IR.obj" \
"./LED.obj" \
"./MISC.obj" \
"./PWM.obj" \
"./RELAY.obj" \
"./START.obj" \
"./SYSTEM.obj" \
"./TIMERS.obj" \
"./TOGGLE.obj" \
"./TV.obj" \
"./UART.obj" \
"./USER.obj" \
"./main.obj" \
"./Library/F28377S.obj" \
"../Linker/2837xS_Generic_FLASH_lnk.cmd" \
"../Linker/F2837xS_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Linker/subdir_vars.mk
-include Library/subdir_vars.mk
-include subdir_rules.mk
-include Linker/subdir_rules.mk
-include Library/subdir_rules.mk
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
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
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
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
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
TMS_Skype_Petcam.out \

EXE_OUTPUTS__QUOTED += \
"TMS_Skype_Petcam.out" \

BIN_OUTPUTS += \
TMS_Skype_Petcam.txt \

BIN_OUTPUTS__QUOTED += \
"TMS_Skype_Petcam.txt" \


# All Target
all: TMS_Skype_Petcam.out secondary-outputs

# Tool invocations
TMS_Skype_Petcam.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 -Ooff --fp_mode=relaxed --advice:performance=all -g --define=CPU1 --define=_FLASH --diag_warning=225 --diag_wrap=off --display_error_number -z -m"TMS_Skype_Petcam.map" --stack_size=0x0400 --warn_sections -i"C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Linker" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="TMS_Skype_Petcam_linkInfo.xml" --rom_model -o "TMS_Skype_Petcam.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

TMS_Skype_Petcam.txt: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/hex2000" --ti_txt --load_image -o "TMS_Skype_Petcam.txt" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "ADC.pp" "AUDIO.pp" "BLUETOOTH.pp" "BUTTON.pp" "CMD.pp" "DMA.pp" "INTERRUPTS.pp" "IR.pp" "LED.pp" "MISC.pp" "PWM.pp" "RELAY.pp" "SYSTEM.pp" "TIMERS.pp" "TOGGLE.pp" "TV.pp" "UART.pp" "USER.pp" "main.pp" "Library\F28377S.pp" 
	-$(RM) "ADC.obj" "AUDIO.obj" "BLUETOOTH.obj" "BUTTON.obj" "CMD.obj" "DMA.obj" "INTERRUPTS.obj" "IR.obj" "LED.obj" "MISC.obj" "PWM.obj" "RELAY.obj" "START.obj" "SYSTEM.obj" "TIMERS.obj" "TOGGLE.obj" "TV.obj" "UART.obj" "USER.obj" "main.obj" "Library\F28377S.obj" 
	-$(RM) "START.pp" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

