#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/wrtsspi.o ${OBJECTDIR}/_ext/1472/setcsspi.o ${OBJECTDIR}/_ext/1472/rdsspi.o ${OBJECTDIR}/_ext/1472/clrcsspi.o ${OBJECTDIR}/_ext/1472/opensspi.o ${OBJECTDIR}/_ext/1472/writuart.o ${OBJECTDIR}/_ext/1472/uartdata.o ${OBJECTDIR}/_ext/1472/sw_serial_delays.o ${OBJECTDIR}/_ext/1472/readuart.o ${OBJECTDIR}/_ext/1472/openuart.o ${OBJECTDIR}/_ext/1472/putsuart.o ${OBJECTDIR}/_ext/1472/getsuart.o ${OBJECTDIR}/_ext/1472/d4tcyx.o ${OBJECTDIR}/_ext/1472/delay.o ${OBJECTDIR}/_ext/1472/funcoes.o ${OBJECTDIR}/_ext/1472/interrupt.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/serial.o ${OBJECTDIR}/_ext/1472/led.o ${OBJECTDIR}/_ext/1472/SerialPC.o ${OBJECTDIR}/_ext/1472/status.o ${OBJECTDIR}/_ext/1472/cpu.o ${OBJECTDIR}/_ext/1472/device.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/serialNumber.o ${OBJECTDIR}/_ext/1472/crc32.o ${OBJECTDIR}/_ext/1472/FlashEprom.o ${OBJECTDIR}/_ext/1472/e2prom.o ${OBJECTDIR}/_ext/1472/e2prom_loc.o ${OBJECTDIR}/_ext/1472/AT45DBxx.o ${OBJECTDIR}/_ext/1472/modemGSM.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/bootloader.o ${OBJECTDIR}/_ext/1472/c018i.o ${OBJECTDIR}/_ext/1472/prgmem_access.o ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o ${OBJECTDIR}/_ext/1472/version.o ${OBJECTDIR}/_ext/1472/hw_spi.o ${OBJECTDIR}/_ext/1472/timer0.o ${OBJECTDIR}/_ext/1472/simcardcontrol.o ${OBJECTDIR}/_ext/1472/d1tcyx.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/wrtsspi.o.d ${OBJECTDIR}/_ext/1472/setcsspi.o.d ${OBJECTDIR}/_ext/1472/rdsspi.o.d ${OBJECTDIR}/_ext/1472/clrcsspi.o.d ${OBJECTDIR}/_ext/1472/opensspi.o.d ${OBJECTDIR}/_ext/1472/writuart.o.d ${OBJECTDIR}/_ext/1472/uartdata.o.d ${OBJECTDIR}/_ext/1472/sw_serial_delays.o.d ${OBJECTDIR}/_ext/1472/readuart.o.d ${OBJECTDIR}/_ext/1472/openuart.o.d ${OBJECTDIR}/_ext/1472/putsuart.o.d ${OBJECTDIR}/_ext/1472/getsuart.o.d ${OBJECTDIR}/_ext/1472/d4tcyx.o.d ${OBJECTDIR}/_ext/1472/delay.o.d ${OBJECTDIR}/_ext/1472/funcoes.o.d ${OBJECTDIR}/_ext/1472/interrupt.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/serial.o.d ${OBJECTDIR}/_ext/1472/led.o.d ${OBJECTDIR}/_ext/1472/SerialPC.o.d ${OBJECTDIR}/_ext/1472/status.o.d ${OBJECTDIR}/_ext/1472/cpu.o.d ${OBJECTDIR}/_ext/1472/device.o.d ${OBJECTDIR}/_ext/1472/log.o.d ${OBJECTDIR}/_ext/1472/serialNumber.o.d ${OBJECTDIR}/_ext/1472/crc32.o.d ${OBJECTDIR}/_ext/1472/FlashEprom.o.d ${OBJECTDIR}/_ext/1472/e2prom.o.d ${OBJECTDIR}/_ext/1472/e2prom_loc.o.d ${OBJECTDIR}/_ext/1472/AT45DBxx.o.d ${OBJECTDIR}/_ext/1472/modemGSM.o.d ${OBJECTDIR}/_ext/1472/timer.o.d ${OBJECTDIR}/_ext/1472/bootloader.o.d ${OBJECTDIR}/_ext/1472/c018i.o.d ${OBJECTDIR}/_ext/1472/prgmem_access.o.d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o.d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o.d ${OBJECTDIR}/_ext/1472/version.o.d ${OBJECTDIR}/_ext/1472/hw_spi.o.d ${OBJECTDIR}/_ext/1472/timer0.o.d ${OBJECTDIR}/_ext/1472/simcardcontrol.o.d ${OBJECTDIR}/_ext/1472/d1tcyx.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/wrtsspi.o ${OBJECTDIR}/_ext/1472/setcsspi.o ${OBJECTDIR}/_ext/1472/rdsspi.o ${OBJECTDIR}/_ext/1472/clrcsspi.o ${OBJECTDIR}/_ext/1472/opensspi.o ${OBJECTDIR}/_ext/1472/writuart.o ${OBJECTDIR}/_ext/1472/uartdata.o ${OBJECTDIR}/_ext/1472/sw_serial_delays.o ${OBJECTDIR}/_ext/1472/readuart.o ${OBJECTDIR}/_ext/1472/openuart.o ${OBJECTDIR}/_ext/1472/putsuart.o ${OBJECTDIR}/_ext/1472/getsuart.o ${OBJECTDIR}/_ext/1472/d4tcyx.o ${OBJECTDIR}/_ext/1472/delay.o ${OBJECTDIR}/_ext/1472/funcoes.o ${OBJECTDIR}/_ext/1472/interrupt.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/serial.o ${OBJECTDIR}/_ext/1472/led.o ${OBJECTDIR}/_ext/1472/SerialPC.o ${OBJECTDIR}/_ext/1472/status.o ${OBJECTDIR}/_ext/1472/cpu.o ${OBJECTDIR}/_ext/1472/device.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/serialNumber.o ${OBJECTDIR}/_ext/1472/crc32.o ${OBJECTDIR}/_ext/1472/FlashEprom.o ${OBJECTDIR}/_ext/1472/e2prom.o ${OBJECTDIR}/_ext/1472/e2prom_loc.o ${OBJECTDIR}/_ext/1472/AT45DBxx.o ${OBJECTDIR}/_ext/1472/modemGSM.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/bootloader.o ${OBJECTDIR}/_ext/1472/c018i.o ${OBJECTDIR}/_ext/1472/prgmem_access.o ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o ${OBJECTDIR}/_ext/1472/version.o ${OBJECTDIR}/_ext/1472/hw_spi.o ${OBJECTDIR}/_ext/1472/timer0.o ${OBJECTDIR}/_ext/1472/simcardcontrol.o ${OBJECTDIR}/_ext/1472/d1tcyx.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F27J13
MP_PROCESSOR_OPTION_LD=18f27j13
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/writuart.o: ../writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/writuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/writuart.lst\" -e\"${OBJECTDIR}/_ext/1472/writuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/writuart.o\" ../writuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/writuart.o 
	
${OBJECTDIR}/_ext/1472/uartdata.o: ../uartdata.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/uartdata.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/uartdata.lst\" -e\"${OBJECTDIR}/_ext/1472/uartdata.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/uartdata.o\" ../uartdata.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/uartdata.o 
	
${OBJECTDIR}/_ext/1472/readuart.o: ../readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/readuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/readuart.lst\" -e\"${OBJECTDIR}/_ext/1472/readuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/readuart.o\" ../readuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/readuart.o 
	
${OBJECTDIR}/_ext/1472/openuart.o: ../openuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/openuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/openuart.lst\" -e\"${OBJECTDIR}/_ext/1472/openuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/openuart.o\" ../openuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/openuart.o 
	
${OBJECTDIR}/_ext/1472/d4tcyx.o: ../d4tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/d4tcyx.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/d4tcyx.lst\" -e\"${OBJECTDIR}/_ext/1472/d4tcyx.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/d4tcyx.o\" ../d4tcyx.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/d4tcyx.o 
	
${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o: ../CPU_disableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.lst\" -e\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o\" ../CPU_disableAll_Int.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o 
	
${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o: ../CPU_EnableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.lst\" -e\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o\" ../CPU_EnableAll_Int.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o 
	
${OBJECTDIR}/_ext/1472/d1tcyx.o: ../d1tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/d1tcyx.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG  -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/d1tcyx.lst\" -e\"${OBJECTDIR}/_ext/1472/d1tcyx.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/d1tcyx.o\" ../d1tcyx.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/d1tcyx.o 
	
else
${OBJECTDIR}/_ext/1472/writuart.o: ../writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/writuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/writuart.lst\" -e\"${OBJECTDIR}/_ext/1472/writuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/writuart.o\" ../writuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/writuart.o 
	
${OBJECTDIR}/_ext/1472/uartdata.o: ../uartdata.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/uartdata.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/uartdata.lst\" -e\"${OBJECTDIR}/_ext/1472/uartdata.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/uartdata.o\" ../uartdata.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/uartdata.o 
	
${OBJECTDIR}/_ext/1472/readuart.o: ../readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/readuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/readuart.lst\" -e\"${OBJECTDIR}/_ext/1472/readuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/readuart.o\" ../readuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/readuart.o 
	
${OBJECTDIR}/_ext/1472/openuart.o: ../openuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/openuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/openuart.lst\" -e\"${OBJECTDIR}/_ext/1472/openuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/openuart.o\" ../openuart.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/openuart.o 
	
${OBJECTDIR}/_ext/1472/d4tcyx.o: ../d4tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/d4tcyx.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/d4tcyx.lst\" -e\"${OBJECTDIR}/_ext/1472/d4tcyx.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/d4tcyx.o\" ../d4tcyx.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/d4tcyx.o 
	
${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o: ../CPU_disableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.lst\" -e\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o\" ../CPU_disableAll_Int.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.o 
	
${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o: ../CPU_EnableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.lst\" -e\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o\" ../CPU_EnableAll_Int.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.o 
	
${OBJECTDIR}/_ext/1472/d1tcyx.o: ../d1tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.o.d 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/_ext/1472/d1tcyx.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/_ext/1472/d1tcyx.lst\" -e\"${OBJECTDIR}/_ext/1472/d1tcyx.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/_ext/1472/d1tcyx.o\" ../d1tcyx.asm 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/d1tcyx.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/wrtsspi.o: ../wrtsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/wrtsspi.o   ../wrtsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/wrtsspi.o 
	
${OBJECTDIR}/_ext/1472/setcsspi.o: ../setcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/setcsspi.o   ../setcsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/setcsspi.o 
	
${OBJECTDIR}/_ext/1472/rdsspi.o: ../rdsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/rdsspi.o   ../rdsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/rdsspi.o 
	
${OBJECTDIR}/_ext/1472/clrcsspi.o: ../clrcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/clrcsspi.o   ../clrcsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/clrcsspi.o 
	
${OBJECTDIR}/_ext/1472/opensspi.o: ../opensspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/opensspi.o   ../opensspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/opensspi.o 
	
${OBJECTDIR}/_ext/1472/sw_serial_delays.o: ../sw_serial_delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/sw_serial_delays.o   ../sw_serial_delays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/sw_serial_delays.o 
	
${OBJECTDIR}/_ext/1472/putsuart.o: ../putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/putsuart.o   ../putsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/putsuart.o 
	
${OBJECTDIR}/_ext/1472/getsuart.o: ../getsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/getsuart.o   ../getsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/getsuart.o 
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/delay.o   ../delay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/delay.o 
	
${OBJECTDIR}/_ext/1472/funcoes.o: ../funcoes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/funcoes.o   ../funcoes.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/funcoes.o 
	
${OBJECTDIR}/_ext/1472/interrupt.o: ../interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/interrupt.o   ../interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/interrupt.o 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	
${OBJECTDIR}/_ext/1472/serial.o: ../serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/serial.o   ../serial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/serial.o 
	
${OBJECTDIR}/_ext/1472/led.o: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/led.o   ../led.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/led.o 
	
${OBJECTDIR}/_ext/1472/SerialPC.o: ../SerialPC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/SerialPC.o   ../SerialPC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/SerialPC.o 
	
${OBJECTDIR}/_ext/1472/status.o: ../status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/status.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/status.o   ../status.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/status.o 
	
${OBJECTDIR}/_ext/1472/cpu.o: ../cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/cpu.o   ../cpu.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/cpu.o 
	
${OBJECTDIR}/_ext/1472/device.o: ../device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/device.o   ../device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/device.o 
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/log.o   ../log.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/log.o 
	
${OBJECTDIR}/_ext/1472/serialNumber.o: ../serialNumber.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/serialNumber.o   ../serialNumber.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/serialNumber.o 
	
${OBJECTDIR}/_ext/1472/crc32.o: ../crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/crc32.o   ../crc32.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/crc32.o 
	
${OBJECTDIR}/_ext/1472/FlashEprom.o: ../FlashEprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/FlashEprom.o   ../FlashEprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/FlashEprom.o 
	
${OBJECTDIR}/_ext/1472/e2prom.o: ../e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/e2prom.o   ../e2prom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/e2prom.o 
	
${OBJECTDIR}/_ext/1472/e2prom_loc.o: ../e2prom_loc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/e2prom_loc.o   ../e2prom_loc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/e2prom_loc.o 
	
${OBJECTDIR}/_ext/1472/AT45DBxx.o: ../AT45DBxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/AT45DBxx.o   ../AT45DBxx.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/AT45DBxx.o 
	
${OBJECTDIR}/_ext/1472/modemGSM.o: ../modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/modemGSM.o   ../modemGSM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/modemGSM.o 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/timer.o   ../timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/timer.o 
	
${OBJECTDIR}/_ext/1472/bootloader.o: ../bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/bootloader.o   ../bootloader.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/bootloader.o 
	
${OBJECTDIR}/_ext/1472/c018i.o: ../c018i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/c018i.o   ../c018i.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/c018i.o 
	
${OBJECTDIR}/_ext/1472/prgmem_access.o: ../prgmem_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/prgmem_access.o   ../prgmem_access.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/prgmem_access.o 
	
${OBJECTDIR}/_ext/1472/version.o: ../version.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/version.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/version.o   ../version.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/version.o 
	
${OBJECTDIR}/_ext/1472/hw_spi.o: ../hw_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/hw_spi.o   ../hw_spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/hw_spi.o 
	
${OBJECTDIR}/_ext/1472/timer0.o: ../timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/timer0.o   ../timer0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/timer0.o 
	
${OBJECTDIR}/_ext/1472/simcardcontrol.o: ../simcardcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/simcardcontrol.o   ../simcardcontrol.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/simcardcontrol.o 
	
else
${OBJECTDIR}/_ext/1472/wrtsspi.o: ../wrtsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/wrtsspi.o   ../wrtsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/wrtsspi.o 
	
${OBJECTDIR}/_ext/1472/setcsspi.o: ../setcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/setcsspi.o   ../setcsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/setcsspi.o 
	
${OBJECTDIR}/_ext/1472/rdsspi.o: ../rdsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/rdsspi.o   ../rdsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/rdsspi.o 
	
${OBJECTDIR}/_ext/1472/clrcsspi.o: ../clrcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/clrcsspi.o   ../clrcsspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/clrcsspi.o 
	
${OBJECTDIR}/_ext/1472/opensspi.o: ../opensspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/opensspi.o   ../opensspi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/opensspi.o 
	
${OBJECTDIR}/_ext/1472/sw_serial_delays.o: ../sw_serial_delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/sw_serial_delays.o   ../sw_serial_delays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/sw_serial_delays.o 
	
${OBJECTDIR}/_ext/1472/putsuart.o: ../putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/putsuart.o   ../putsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/putsuart.o 
	
${OBJECTDIR}/_ext/1472/getsuart.o: ../getsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/getsuart.o   ../getsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/getsuart.o 
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/delay.o   ../delay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/delay.o 
	
${OBJECTDIR}/_ext/1472/funcoes.o: ../funcoes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/funcoes.o   ../funcoes.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/funcoes.o 
	
${OBJECTDIR}/_ext/1472/interrupt.o: ../interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/interrupt.o   ../interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/interrupt.o 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	
${OBJECTDIR}/_ext/1472/serial.o: ../serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/serial.o   ../serial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/serial.o 
	
${OBJECTDIR}/_ext/1472/led.o: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/led.o   ../led.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/led.o 
	
${OBJECTDIR}/_ext/1472/SerialPC.o: ../SerialPC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/SerialPC.o   ../SerialPC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/SerialPC.o 
	
${OBJECTDIR}/_ext/1472/status.o: ../status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/status.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/status.o   ../status.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/status.o 
	
${OBJECTDIR}/_ext/1472/cpu.o: ../cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/cpu.o   ../cpu.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/cpu.o 
	
${OBJECTDIR}/_ext/1472/device.o: ../device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/device.o   ../device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/device.o 
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/log.o   ../log.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/log.o 
	
${OBJECTDIR}/_ext/1472/serialNumber.o: ../serialNumber.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/serialNumber.o   ../serialNumber.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/serialNumber.o 
	
${OBJECTDIR}/_ext/1472/crc32.o: ../crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/crc32.o   ../crc32.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/crc32.o 
	
${OBJECTDIR}/_ext/1472/FlashEprom.o: ../FlashEprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/FlashEprom.o   ../FlashEprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/FlashEprom.o 
	
${OBJECTDIR}/_ext/1472/e2prom.o: ../e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/e2prom.o   ../e2prom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/e2prom.o 
	
${OBJECTDIR}/_ext/1472/e2prom_loc.o: ../e2prom_loc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/e2prom_loc.o   ../e2prom_loc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/e2prom_loc.o 
	
${OBJECTDIR}/_ext/1472/AT45DBxx.o: ../AT45DBxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/AT45DBxx.o   ../AT45DBxx.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/AT45DBxx.o 
	
${OBJECTDIR}/_ext/1472/modemGSM.o: ../modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/modemGSM.o   ../modemGSM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/modemGSM.o 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/timer.o   ../timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/timer.o 
	
${OBJECTDIR}/_ext/1472/bootloader.o: ../bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/bootloader.o   ../bootloader.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/bootloader.o 
	
${OBJECTDIR}/_ext/1472/c018i.o: ../c018i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/c018i.o   ../c018i.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/c018i.o 
	
${OBJECTDIR}/_ext/1472/prgmem_access.o: ../prgmem_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/prgmem_access.o   ../prgmem_access.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/prgmem_access.o 
	
${OBJECTDIR}/_ext/1472/version.o: ../version.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/version.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/version.o   ../version.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/version.o 
	
${OBJECTDIR}/_ext/1472/hw_spi.o: ../hw_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/hw_spi.o   ../hw_spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/hw_spi.o 
	
${OBJECTDIR}/_ext/1472/timer0.o: ../timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/timer0.o   ../timer0.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/timer0.o 
	
${OBJECTDIR}/_ext/1472/simcardcontrol.o: ../simcardcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D_BAUDRATE_AUTOBAUD -I"../C:/mcc18/h" -I".." -Ls -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/simcardcontrol.o   ../simcardcontrol.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/simcardcontrol.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\18f4680.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../C:/mcc18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\18f4680.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../C:/mcc18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
