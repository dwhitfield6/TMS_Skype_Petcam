################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.obj: ../controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 --fp_mode=relaxed --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib/host" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/utils" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/driverlib" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib/device" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/inc" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/include" --include_path="C:/Users/dwhitfield/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_headers/include" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


