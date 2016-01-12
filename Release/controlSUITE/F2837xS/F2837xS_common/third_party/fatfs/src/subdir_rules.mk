################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/ff.obj: ../controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/ff.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/tff.obj: ../controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/tff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src/tff.pp" --obj_directory="controlSUITE/F2837xS/F2837xS_common/third_party/fatfs/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


