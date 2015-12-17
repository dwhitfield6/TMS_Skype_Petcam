################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/stdafx.obj: ../controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/stdafx.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/stdafx.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/tiusbdll.obj: ../controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/tiusbdll.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll/tiusbdll.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_common/tools/tiusbdll" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


