################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.obj: ../controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib/host" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/utils" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/driverlib" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/usblib/device" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/inc" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_common/include" --include_path="C:/Users/pskkd/Documents/GitHub/TMS_Skype_Petcam/controlSUITE/F2837xS/F2837xS_headers/include" --advice:performance=all -g --define=DISK0_USB_MSC --define=CPU1 --define=_FLASH --define=ccs_c2k --define=DISK1_USB_MSC --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_headers/source/F2837xS_GlobalVariableDefs.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


