#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../wrtsspi.c ../setcsspi.c ../rdsspi.c ../clrcsspi.c ../opensspi.c ../writuart.asm ../uartdata.asm ../sw_serial_delays.c ../readuart.asm ../openuart.asm ../putsuart.c ../getsuart.c ../d4tcyx.asm ../delay.c ../funcoes.c ../interrupt.c ../main.c ../serial.c ../led.c ../SerialPC.c ../status.c ../cpu.c ../device.c ../log.c ../serialNumber.c ../crc32.c ../FlashEprom.c ../e2prom.c ../e2prom_loc.c ../AT45DBxx.c ../modemGSM.c ../timer.c ../bootloader.c ../c018i.c ../prgmem_access.c ../CPU_disableAll_Int.asm ../CPU_EnableAll_Int.asm ../version.c ../hw_spi.c ../timer0.c ../simcardcontrol.c ../d1tcyx.asm

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/wrtsspi.p1 ${OBJECTDIR}/_ext/1472/setcsspi.p1 ${OBJECTDIR}/_ext/1472/rdsspi.p1 ${OBJECTDIR}/_ext/1472/clrcsspi.p1 ${OBJECTDIR}/_ext/1472/opensspi.p1 ${OBJECTDIR}/_ext/1472/writuart.obj ${OBJECTDIR}/_ext/1472/uartdata.obj ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1 ${OBJECTDIR}/_ext/1472/readuart.obj ${OBJECTDIR}/_ext/1472/openuart.obj ${OBJECTDIR}/_ext/1472/putsuart.p1 ${OBJECTDIR}/_ext/1472/getsuart.p1 ${OBJECTDIR}/_ext/1472/d4tcyx.obj ${OBJECTDIR}/_ext/1472/delay.p1 ${OBJECTDIR}/_ext/1472/funcoes.p1 ${OBJECTDIR}/_ext/1472/interrupt.p1 ${OBJECTDIR}/_ext/1472/main.p1 ${OBJECTDIR}/_ext/1472/serial.p1 ${OBJECTDIR}/_ext/1472/led.p1 ${OBJECTDIR}/_ext/1472/SerialPC.p1 ${OBJECTDIR}/_ext/1472/status.p1 ${OBJECTDIR}/_ext/1472/cpu.p1 ${OBJECTDIR}/_ext/1472/device.p1 ${OBJECTDIR}/_ext/1472/log.p1 ${OBJECTDIR}/_ext/1472/serialNumber.p1 ${OBJECTDIR}/_ext/1472/crc32.p1 ${OBJECTDIR}/_ext/1472/FlashEprom.p1 ${OBJECTDIR}/_ext/1472/e2prom.p1 ${OBJECTDIR}/_ext/1472/e2prom_loc.p1 ${OBJECTDIR}/_ext/1472/AT45DBxx.p1 ${OBJECTDIR}/_ext/1472/modemGSM.p1 ${OBJECTDIR}/_ext/1472/timer.p1 ${OBJECTDIR}/_ext/1472/bootloader.p1 ${OBJECTDIR}/_ext/1472/c018i.p1 ${OBJECTDIR}/_ext/1472/prgmem_access.p1 ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj ${OBJECTDIR}/_ext/1472/version.p1 ${OBJECTDIR}/_ext/1472/hw_spi.p1 ${OBJECTDIR}/_ext/1472/timer0.p1 ${OBJECTDIR}/_ext/1472/simcardcontrol.p1 ${OBJECTDIR}/_ext/1472/d1tcyx.obj
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/wrtsspi.p1.d ${OBJECTDIR}/_ext/1472/setcsspi.p1.d ${OBJECTDIR}/_ext/1472/rdsspi.p1.d ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d ${OBJECTDIR}/_ext/1472/opensspi.p1.d ${OBJECTDIR}/_ext/1472/writuart.obj.d ${OBJECTDIR}/_ext/1472/uartdata.obj.d ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d ${OBJECTDIR}/_ext/1472/readuart.obj.d ${OBJECTDIR}/_ext/1472/openuart.obj.d ${OBJECTDIR}/_ext/1472/putsuart.p1.d ${OBJECTDIR}/_ext/1472/getsuart.p1.d ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d ${OBJECTDIR}/_ext/1472/delay.p1.d ${OBJECTDIR}/_ext/1472/funcoes.p1.d ${OBJECTDIR}/_ext/1472/interrupt.p1.d ${OBJECTDIR}/_ext/1472/main.p1.d ${OBJECTDIR}/_ext/1472/serial.p1.d ${OBJECTDIR}/_ext/1472/led.p1.d ${OBJECTDIR}/_ext/1472/SerialPC.p1.d ${OBJECTDIR}/_ext/1472/status.p1.d ${OBJECTDIR}/_ext/1472/cpu.p1.d ${OBJECTDIR}/_ext/1472/device.p1.d ${OBJECTDIR}/_ext/1472/log.p1.d ${OBJECTDIR}/_ext/1472/serialNumber.p1.d ${OBJECTDIR}/_ext/1472/crc32.p1.d ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d ${OBJECTDIR}/_ext/1472/e2prom.p1.d ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d ${OBJECTDIR}/_ext/1472/modemGSM.p1.d ${OBJECTDIR}/_ext/1472/timer.p1.d ${OBJECTDIR}/_ext/1472/bootloader.p1.d ${OBJECTDIR}/_ext/1472/c018i.p1.d ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d ${OBJECTDIR}/_ext/1472/version.p1.d ${OBJECTDIR}/_ext/1472/hw_spi.p1.d ${OBJECTDIR}/_ext/1472/timer0.p1.d ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/wrtsspi.p1 ${OBJECTDIR}/_ext/1472/setcsspi.p1 ${OBJECTDIR}/_ext/1472/rdsspi.p1 ${OBJECTDIR}/_ext/1472/clrcsspi.p1 ${OBJECTDIR}/_ext/1472/opensspi.p1 ${OBJECTDIR}/_ext/1472/writuart.obj ${OBJECTDIR}/_ext/1472/uartdata.obj ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1 ${OBJECTDIR}/_ext/1472/readuart.obj ${OBJECTDIR}/_ext/1472/openuart.obj ${OBJECTDIR}/_ext/1472/putsuart.p1 ${OBJECTDIR}/_ext/1472/getsuart.p1 ${OBJECTDIR}/_ext/1472/d4tcyx.obj ${OBJECTDIR}/_ext/1472/delay.p1 ${OBJECTDIR}/_ext/1472/funcoes.p1 ${OBJECTDIR}/_ext/1472/interrupt.p1 ${OBJECTDIR}/_ext/1472/main.p1 ${OBJECTDIR}/_ext/1472/serial.p1 ${OBJECTDIR}/_ext/1472/led.p1 ${OBJECTDIR}/_ext/1472/SerialPC.p1 ${OBJECTDIR}/_ext/1472/status.p1 ${OBJECTDIR}/_ext/1472/cpu.p1 ${OBJECTDIR}/_ext/1472/device.p1 ${OBJECTDIR}/_ext/1472/log.p1 ${OBJECTDIR}/_ext/1472/serialNumber.p1 ${OBJECTDIR}/_ext/1472/crc32.p1 ${OBJECTDIR}/_ext/1472/FlashEprom.p1 ${OBJECTDIR}/_ext/1472/e2prom.p1 ${OBJECTDIR}/_ext/1472/e2prom_loc.p1 ${OBJECTDIR}/_ext/1472/AT45DBxx.p1 ${OBJECTDIR}/_ext/1472/modemGSM.p1 ${OBJECTDIR}/_ext/1472/timer.p1 ${OBJECTDIR}/_ext/1472/bootloader.p1 ${OBJECTDIR}/_ext/1472/c018i.p1 ${OBJECTDIR}/_ext/1472/prgmem_access.p1 ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj ${OBJECTDIR}/_ext/1472/version.p1 ${OBJECTDIR}/_ext/1472/hw_spi.p1 ${OBJECTDIR}/_ext/1472/timer0.p1 ${OBJECTDIR}/_ext/1472/simcardcontrol.p1 ${OBJECTDIR}/_ext/1472/d1tcyx.obj

# Source Files
SOURCEFILES=../wrtsspi.c ../setcsspi.c ../rdsspi.c ../clrcsspi.c ../opensspi.c ../writuart.asm ../uartdata.asm ../sw_serial_delays.c ../readuart.asm ../openuart.asm ../putsuart.c ../getsuart.c ../d4tcyx.asm ../delay.c ../funcoes.c ../interrupt.c ../main.c ../serial.c ../led.c ../SerialPC.c ../status.c ../cpu.c ../device.c ../log.c ../serialNumber.c ../crc32.c ../FlashEprom.c ../e2prom.c ../e2prom_loc.c ../AT45DBxx.c ../modemGSM.c ../timer.c ../bootloader.c ../c018i.c ../prgmem_access.c ../CPU_disableAll_Int.asm ../CPU_EnableAll_Int.asm ../version.c ../hw_spi.c ../timer0.c ../simcardcontrol.c ../d1tcyx.asm


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F27J13
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/wrtsspi.p1: ../wrtsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/wrtsspi.p1  ../wrtsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/wrtsspi.d ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/setcsspi.p1: ../setcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/setcsspi.p1  ../setcsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/setcsspi.d ${OBJECTDIR}/_ext/1472/setcsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/setcsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/rdsspi.p1: ../rdsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/rdsspi.p1  ../rdsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/rdsspi.d ${OBJECTDIR}/_ext/1472/rdsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/rdsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/clrcsspi.p1: ../clrcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/clrcsspi.p1  ../clrcsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/clrcsspi.d ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/opensspi.p1: ../opensspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/opensspi.p1  ../opensspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/opensspi.d ${OBJECTDIR}/_ext/1472/opensspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/opensspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/sw_serial_delays.p1: ../sw_serial_delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/sw_serial_delays.p1  ../sw_serial_delays.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/sw_serial_delays.d ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/putsuart.p1: ../putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/putsuart.p1  ../putsuart.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/putsuart.d ${OBJECTDIR}/_ext/1472/putsuart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/putsuart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/getsuart.p1: ../getsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/getsuart.p1  ../getsuart.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/getsuart.d ${OBJECTDIR}/_ext/1472/getsuart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/getsuart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/delay.p1: ../delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/delay.p1  ../delay.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/delay.d ${OBJECTDIR}/_ext/1472/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/funcoes.p1: ../funcoes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/funcoes.p1  ../funcoes.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/funcoes.d ${OBJECTDIR}/_ext/1472/funcoes.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/funcoes.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/interrupt.p1: ../interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/interrupt.p1  ../interrupt.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/interrupt.d ${OBJECTDIR}/_ext/1472/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/main.p1: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/main.p1  ../main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/main.d ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/serial.p1: ../serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/serial.p1  ../serial.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/serial.d ${OBJECTDIR}/_ext/1472/serial.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/serial.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/led.p1: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/led.p1  ../led.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/led.d ${OBJECTDIR}/_ext/1472/led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/SerialPC.p1: ../SerialPC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/SerialPC.p1  ../SerialPC.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/SerialPC.d ${OBJECTDIR}/_ext/1472/SerialPC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/SerialPC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/status.p1: ../status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/status.p1  ../status.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/status.d ${OBJECTDIR}/_ext/1472/status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/cpu.p1: ../cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/cpu.p1  ../cpu.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/cpu.d ${OBJECTDIR}/_ext/1472/cpu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/cpu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/device.p1: ../device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/device.p1  ../device.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/device.d ${OBJECTDIR}/_ext/1472/device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/log.p1: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/log.p1  ../log.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/log.d ${OBJECTDIR}/_ext/1472/log.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/log.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/serialNumber.p1: ../serialNumber.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/serialNumber.p1  ../serialNumber.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/serialNumber.d ${OBJECTDIR}/_ext/1472/serialNumber.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/serialNumber.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/crc32.p1: ../crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/crc32.p1  ../crc32.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/crc32.d ${OBJECTDIR}/_ext/1472/crc32.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/crc32.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/FlashEprom.p1: ../FlashEprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/FlashEprom.p1  ../FlashEprom.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/FlashEprom.d ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/e2prom.p1: ../e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/e2prom.p1  ../e2prom.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/e2prom.d ${OBJECTDIR}/_ext/1472/e2prom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/e2prom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/e2prom_loc.p1: ../e2prom_loc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/e2prom_loc.p1  ../e2prom_loc.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/e2prom_loc.d ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/AT45DBxx.p1: ../AT45DBxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/AT45DBxx.p1  ../AT45DBxx.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/AT45DBxx.d ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/modemGSM.p1: ../modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/modemGSM.p1  ../modemGSM.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/modemGSM.d ${OBJECTDIR}/_ext/1472/modemGSM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/modemGSM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/timer.p1: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/timer.p1  ../timer.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/timer.d ${OBJECTDIR}/_ext/1472/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/bootloader.p1: ../bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/bootloader.p1  ../bootloader.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/bootloader.d ${OBJECTDIR}/_ext/1472/bootloader.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/bootloader.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/c018i.p1: ../c018i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/c018i.p1  ../c018i.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/c018i.d ${OBJECTDIR}/_ext/1472/c018i.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/c018i.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/prgmem_access.p1: ../prgmem_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/prgmem_access.p1  ../prgmem_access.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/prgmem_access.d ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/version.p1: ../version.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/version.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/version.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/version.p1  ../version.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/version.d ${OBJECTDIR}/_ext/1472/version.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/version.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/hw_spi.p1: ../hw_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/hw_spi.p1  ../hw_spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/hw_spi.d ${OBJECTDIR}/_ext/1472/hw_spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/hw_spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/timer0.p1: ../timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/timer0.p1  ../timer0.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/timer0.d ${OBJECTDIR}/_ext/1472/timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/simcardcontrol.p1: ../simcardcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/simcardcontrol.p1  ../simcardcontrol.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/simcardcontrol.d ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/wrtsspi.p1: ../wrtsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wrtsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/wrtsspi.p1  ../wrtsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/wrtsspi.d ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/wrtsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/setcsspi.p1: ../setcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/setcsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/setcsspi.p1  ../setcsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/setcsspi.d ${OBJECTDIR}/_ext/1472/setcsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/setcsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/rdsspi.p1: ../rdsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rdsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/rdsspi.p1  ../rdsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/rdsspi.d ${OBJECTDIR}/_ext/1472/rdsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/rdsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/clrcsspi.p1: ../clrcsspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrcsspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/clrcsspi.p1  ../clrcsspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/clrcsspi.d ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/clrcsspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/opensspi.p1: ../opensspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/opensspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/opensspi.p1  ../opensspi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/opensspi.d ${OBJECTDIR}/_ext/1472/opensspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/opensspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/sw_serial_delays.p1: ../sw_serial_delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/sw_serial_delays.p1  ../sw_serial_delays.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/sw_serial_delays.d ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/sw_serial_delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/putsuart.p1: ../putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/putsuart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/putsuart.p1  ../putsuart.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/putsuart.d ${OBJECTDIR}/_ext/1472/putsuart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/putsuart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/getsuart.p1: ../getsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/getsuart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/getsuart.p1  ../getsuart.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/getsuart.d ${OBJECTDIR}/_ext/1472/getsuart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/getsuart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/delay.p1: ../delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/delay.p1  ../delay.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/delay.d ${OBJECTDIR}/_ext/1472/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/funcoes.p1: ../funcoes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/funcoes.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/funcoes.p1  ../funcoes.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/funcoes.d ${OBJECTDIR}/_ext/1472/funcoes.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/funcoes.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/interrupt.p1: ../interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/interrupt.p1  ../interrupt.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/interrupt.d ${OBJECTDIR}/_ext/1472/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/main.p1: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/main.p1  ../main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/main.d ${OBJECTDIR}/_ext/1472/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/serial.p1: ../serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/serial.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/serial.p1  ../serial.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/serial.d ${OBJECTDIR}/_ext/1472/serial.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/serial.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/led.p1: ../led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/led.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/led.p1  ../led.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/led.d ${OBJECTDIR}/_ext/1472/led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/SerialPC.p1: ../SerialPC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SerialPC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/SerialPC.p1  ../SerialPC.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/SerialPC.d ${OBJECTDIR}/_ext/1472/SerialPC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/SerialPC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/status.p1: ../status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/status.p1  ../status.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/status.d ${OBJECTDIR}/_ext/1472/status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/cpu.p1: ../cpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/cpu.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/cpu.p1  ../cpu.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/cpu.d ${OBJECTDIR}/_ext/1472/cpu.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/cpu.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/device.p1: ../device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/device.p1  ../device.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/device.d ${OBJECTDIR}/_ext/1472/device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/log.p1: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/log.p1  ../log.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/log.d ${OBJECTDIR}/_ext/1472/log.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/log.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/serialNumber.p1: ../serialNumber.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/serialNumber.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/serialNumber.p1  ../serialNumber.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/serialNumber.d ${OBJECTDIR}/_ext/1472/serialNumber.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/serialNumber.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/crc32.p1: ../crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/crc32.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/crc32.p1  ../crc32.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/crc32.d ${OBJECTDIR}/_ext/1472/crc32.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/crc32.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/FlashEprom.p1: ../FlashEprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/FlashEprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/FlashEprom.p1  ../FlashEprom.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/FlashEprom.d ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/FlashEprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/e2prom.p1: ../e2prom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/e2prom.p1  ../e2prom.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/e2prom.d ${OBJECTDIR}/_ext/1472/e2prom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/e2prom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/e2prom_loc.p1: ../e2prom_loc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/e2prom_loc.p1  ../e2prom_loc.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/e2prom_loc.d ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/e2prom_loc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/AT45DBxx.p1: ../AT45DBxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/AT45DBxx.p1  ../AT45DBxx.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/AT45DBxx.d ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/AT45DBxx.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/modemGSM.p1: ../modemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/modemGSM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/modemGSM.p1  ../modemGSM.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/modemGSM.d ${OBJECTDIR}/_ext/1472/modemGSM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/modemGSM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/timer.p1: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/timer.p1  ../timer.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/timer.d ${OBJECTDIR}/_ext/1472/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/bootloader.p1: ../bootloader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bootloader.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/bootloader.p1  ../bootloader.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/bootloader.d ${OBJECTDIR}/_ext/1472/bootloader.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/bootloader.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/c018i.p1: ../c018i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/c018i.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/c018i.p1  ../c018i.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/c018i.d ${OBJECTDIR}/_ext/1472/c018i.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/c018i.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/prgmem_access.p1: ../prgmem_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/prgmem_access.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/prgmem_access.p1  ../prgmem_access.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/prgmem_access.d ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/prgmem_access.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/version.p1: ../version.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/version.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/version.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/version.p1  ../version.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/version.d ${OBJECTDIR}/_ext/1472/version.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/version.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/hw_spi.p1: ../hw_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/hw_spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/hw_spi.p1  ../hw_spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/hw_spi.d ${OBJECTDIR}/_ext/1472/hw_spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/hw_spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/timer0.p1: ../timer0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer0.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/timer0.p1  ../timer0.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/timer0.d ${OBJECTDIR}/_ext/1472/timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/simcardcontrol.p1: ../simcardcontrol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/simcardcontrol.p1  ../simcardcontrol.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/simcardcontrol.d ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/simcardcontrol.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/writuart.obj: ../writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/writuart.obj  ../writuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/writuart.d ${OBJECTDIR}/_ext/1472/writuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/writuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/uartdata.obj: ../uartdata.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/uartdata.obj  ../uartdata.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/uartdata.d ${OBJECTDIR}/_ext/1472/uartdata.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/uartdata.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/readuart.obj: ../readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/readuart.obj  ../readuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/readuart.d ${OBJECTDIR}/_ext/1472/readuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/readuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/openuart.obj: ../openuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/openuart.obj  ../openuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/openuart.d ${OBJECTDIR}/_ext/1472/openuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/openuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/d4tcyx.obj: ../d4tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/d4tcyx.obj  ../d4tcyx.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/d4tcyx.d ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj: ../CPU_disableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj  ../CPU_disableAll_Int.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj: ../CPU_EnableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj  ../CPU_EnableAll_Int.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/d1tcyx.obj: ../d1tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/d1tcyx.obj  ../d1tcyx.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/d1tcyx.d ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/writuart.obj: ../writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/writuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/writuart.obj  ../writuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/writuart.d ${OBJECTDIR}/_ext/1472/writuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/writuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/uartdata.obj: ../uartdata.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uartdata.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/uartdata.obj  ../uartdata.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/uartdata.d ${OBJECTDIR}/_ext/1472/uartdata.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/uartdata.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/readuart.obj: ../readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/readuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/readuart.obj  ../readuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/readuart.d ${OBJECTDIR}/_ext/1472/readuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/readuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/openuart.obj: ../openuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/openuart.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/openuart.obj  ../openuart.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/openuart.d ${OBJECTDIR}/_ext/1472/openuart.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/openuart.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/d4tcyx.obj: ../d4tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/d4tcyx.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/d4tcyx.obj  ../d4tcyx.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/d4tcyx.d ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/d4tcyx.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj: ../CPU_disableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj  ../CPU_disableAll_Int.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.d ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/CPU_disableAll_Int.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj: ../CPU_EnableAll_Int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj  ../CPU_EnableAll_Int.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.d ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/CPU_EnableAll_Int.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/d1tcyx.obj: ../d1tcyx.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/d1tcyx.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"  -o${OBJECTDIR}/_ext/1472/d1tcyx.obj  ../d1tcyx.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/d1tcyx.d ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/d1tcyx.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../18f4680.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        -odist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../18f4680.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/SMSBOX.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
