################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ADC.obj: ../ADC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="ADC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

AUDIO.obj: ../AUDIO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="AUDIO.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

BUTTON.obj: ../BUTTON.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="BUTTON.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMD.obj: ../CMD.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="CMD.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DMA.obj: ../DMA.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DMA.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

INTERRUPTS.obj: ../INTERRUPTS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="INTERRUPTS.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

IR.obj: ../IR.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="IR.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LED.obj: ../LED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="LED.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MISC.obj: ../MISC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="MISC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

RELAY.obj: ../RELAY.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="RELAY.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

START.obj: ../START.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="START.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SYSTEM.obj: ../SYSTEM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="SYSTEM.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TIMERS.obj: ../TIMERS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="TIMERS.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TV.obj: ../TV.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="TV.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UART.obj: ../UART.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="UART.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

USER.obj: ../USER.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="USER.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/Library" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


