#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 
# Macros
CND_CONF=default

ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/43898991/bitbang.o ${OBJECTDIR}/_ext/43898991/UART.o ${OBJECTDIR}/_ext/43898991/main.o ${OBJECTDIR}/_ext/43898991/base.o ${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o ${OBJECTDIR}/_ext/43898991/raw3wire.o ${OBJECTDIR}/_ext/43898991/selftest.o ${OBJECTDIR}/_ext/43898991/binwire.o ${OBJECTDIR}/_ext/1993222530/en_US.o ${OBJECTDIR}/_ext/43898991/SUMP.o ${OBJECTDIR}/_ext/43898991/OpenOCD.o ${OBJECTDIR}/_ext/43898991/binIOhelpers.o ${OBJECTDIR}/_ext/43898991/baseIO.o ${OBJECTDIR}/_ext/43898991/dio.o ${OBJECTDIR}/_ext/43898991/AUXpin.o ${OBJECTDIR}/_ext/43898991/raw2wire.o ${OBJECTDIR}/_ext/43898991/m_1wire_213.o ${OBJECTDIR}/_ext/43898991/I2C.o ${OBJECTDIR}/_ext/43898991/1wire.o ${OBJECTDIR}/_ext/43898991/binIO.o ${OBJECTDIR}/_ext/43898991/HD44780.o ${OBJECTDIR}/_ext/43898991/busPirateCore.o ${OBJECTDIR}/_ext/43898991/baseUI.o ${OBJECTDIR}/_ext/43898991/basic.o ${OBJECTDIR}/_ext/43898991/SPI.o ${OBJECTDIR}/_ext/43898991/uart2io.o ${OBJECTDIR}/_ext/43898991/procMenu.o ${OBJECTDIR}/_ext/43898991/pic.o ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

OS_ORIGINAL="Linux"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=/opt/microchip/mplabc30/v3.24/bin/pic30-gcc
MP_AS=/opt/microchip/mplabc30/v3.24/bin/pic30-as
MP_LD=/opt/microchip/mplabc30/v3.24/bin/pic30-ld
MP_AR=/opt/microchip/mplabc30/v3.24/bin/pic30-ar
MP_CC_DIR=/opt/microchip/mplabc30/v3.24/bin
MP_AS_DIR=/opt/microchip/mplabc30/v3.24/bin
MP_LD_DIR=/opt/microchip/mplabc30/v3.24/bin
MP_AR_DIR=/opt/microchip/mplabc30/v3.24/bin
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
.PHONY: ${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o
${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o: ../../OpenOCD_asm.S  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=24FJ64GA002 -I"../../translations" -o ${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o ../../OpenOCD_asm.S  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g
.PHONY: ${OBJECTDIR}/_ext/1993222530/en_US.o
${OBJECTDIR}/_ext/1993222530/en_US.o: ../../translations/en_US.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1993222530 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=24FJ64GA002 -I"../../translations" -o ${OBJECTDIR}/_ext/1993222530/en_US.o ../../translations/en_US.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g
else
.PHONY: ${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o
${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o: ../../OpenOCD_asm.S  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${MP_CC}  -omf=elf -c -mcpu=24FJ64GA002 -I"../../translations" -o ${OBJECTDIR}/_ext/43898991/OpenOCD_asm.o ../../OpenOCD_asm.S  -Wa,--defsym=__MPLAB_BUILD=1
.PHONY: ${OBJECTDIR}/_ext/1993222530/en_US.o
${OBJECTDIR}/_ext/1993222530/en_US.o: ../../translations/en_US.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1993222530 
	${MP_CC}  -omf=elf -c -mcpu=24FJ64GA002 -I"../../translations" -o ${OBJECTDIR}/_ext/1993222530/en_US.o ../../translations/en_US.s  -Wa,--defsym=__MPLAB_BUILD=1
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/43898991/bitbang.o: ../../bitbang.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/bitbang.o.d -o ${OBJECTDIR}/_ext/43898991/bitbang.o ../../bitbang.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/bitbang.o.d > ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/bitbang.o.d > ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/UART.o: ../../UART.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/UART.o.d -o ${OBJECTDIR}/_ext/43898991/UART.o ../../UART.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/UART.o.d > ${OBJECTDIR}/_ext/43898991/UART.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/UART.o.tmp ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/UART.o.d > ${OBJECTDIR}/_ext/43898991/UART.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/UART.o.tmp ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/main.o: ../../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/main.o.d -o ${OBJECTDIR}/_ext/43898991/main.o ../../main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/main.o.d > ${OBJECTDIR}/_ext/43898991/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/main.o.tmp ${OBJECTDIR}/_ext/43898991/main.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/main.o.d > ${OBJECTDIR}/_ext/43898991/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/main.o.tmp ${OBJECTDIR}/_ext/43898991/main.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/base.o: ../../base.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/base.o.d -o ${OBJECTDIR}/_ext/43898991/base.o ../../base.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/base.o.d > ${OBJECTDIR}/_ext/43898991/base.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/base.o.tmp ${OBJECTDIR}/_ext/43898991/base.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/base.o.d > ${OBJECTDIR}/_ext/43898991/base.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/base.o.tmp ${OBJECTDIR}/_ext/43898991/base.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/raw3wire.o: ../../raw3wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/raw3wire.o.d -o ${OBJECTDIR}/_ext/43898991/raw3wire.o ../../raw3wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/raw3wire.o.d > ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/raw3wire.o.d > ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/selftest.o: ../../selftest.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/selftest.o.d -o ${OBJECTDIR}/_ext/43898991/selftest.o ../../selftest.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/selftest.o.d > ${OBJECTDIR}/_ext/43898991/selftest.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/selftest.o.d > ${OBJECTDIR}/_ext/43898991/selftest.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binwire.o: ../../binwire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binwire.o.d -o ${OBJECTDIR}/_ext/43898991/binwire.o ../../binwire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binwire.o.d > ${OBJECTDIR}/_ext/43898991/binwire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binwire.o.d > ${OBJECTDIR}/_ext/43898991/binwire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/SUMP.o: ../../SUMP.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/SUMP.o.d -o ${OBJECTDIR}/_ext/43898991/SUMP.o ../../SUMP.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/SUMP.o.d > ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/SUMP.o.d > ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/OpenOCD.o: ../../OpenOCD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d -o ${OBJECTDIR}/_ext/43898991/OpenOCD.o ../../OpenOCD.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d > ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d > ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binIOhelpers.o: ../../binIOhelpers.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d -o ${OBJECTDIR}/_ext/43898991/binIOhelpers.o ../../binIOhelpers.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d > ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d > ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/baseIO.o: ../../baseIO.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/baseIO.o.d -o ${OBJECTDIR}/_ext/43898991/baseIO.o ../../baseIO.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/baseIO.o.d > ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/baseIO.o.d > ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/dio.o: ../../dio.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/dio.o.d -o ${OBJECTDIR}/_ext/43898991/dio.o ../../dio.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/dio.o.d > ${OBJECTDIR}/_ext/43898991/dio.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/dio.o.tmp ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/dio.o.d > ${OBJECTDIR}/_ext/43898991/dio.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/dio.o.tmp ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/AUXpin.o: ../../AUXpin.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/AUXpin.o.d -o ${OBJECTDIR}/_ext/43898991/AUXpin.o ../../AUXpin.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/AUXpin.o.d > ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/AUXpin.o.d > ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/raw2wire.o: ../../raw2wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/raw2wire.o.d -o ${OBJECTDIR}/_ext/43898991/raw2wire.o ../../raw2wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/raw2wire.o.d > ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/raw2wire.o.d > ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/m_1wire_213.o: ../../m_1wire_213.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d -o ${OBJECTDIR}/_ext/43898991/m_1wire_213.o ../../m_1wire_213.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d > ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d > ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/I2C.o: ../../I2C.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/I2C.o.d -o ${OBJECTDIR}/_ext/43898991/I2C.o ../../I2C.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/I2C.o.d > ${OBJECTDIR}/_ext/43898991/I2C.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/I2C.o.d > ${OBJECTDIR}/_ext/43898991/I2C.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/1wire.o: ../../1wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/1wire.o.d -o ${OBJECTDIR}/_ext/43898991/1wire.o ../../1wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/1wire.o.d > ${OBJECTDIR}/_ext/43898991/1wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/1wire.o.d > ${OBJECTDIR}/_ext/43898991/1wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binIO.o: ../../binIO.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binIO.o.d -o ${OBJECTDIR}/_ext/43898991/binIO.o ../../binIO.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binIO.o.d > ${OBJECTDIR}/_ext/43898991/binIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binIO.o.d > ${OBJECTDIR}/_ext/43898991/binIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/HD44780.o: ../../HD44780.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/HD44780.o.d -o ${OBJECTDIR}/_ext/43898991/HD44780.o ../../HD44780.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/HD44780.o.d > ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/HD44780.o.d > ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/busPirateCore.o: ../../busPirateCore.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d -o ${OBJECTDIR}/_ext/43898991/busPirateCore.o ../../busPirateCore.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d > ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d > ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/baseUI.o: ../../baseUI.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/baseUI.o.d -o ${OBJECTDIR}/_ext/43898991/baseUI.o ../../baseUI.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/baseUI.o.d > ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/baseUI.o.d > ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/basic.o: ../../basic.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/basic.o.d -o ${OBJECTDIR}/_ext/43898991/basic.o ../../basic.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/basic.o.d > ${OBJECTDIR}/_ext/43898991/basic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/basic.o.tmp ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/basic.o.d > ${OBJECTDIR}/_ext/43898991/basic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/basic.o.tmp ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/SPI.o: ../../SPI.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/SPI.o.d -o ${OBJECTDIR}/_ext/43898991/SPI.o ../../SPI.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/SPI.o.d > ${OBJECTDIR}/_ext/43898991/SPI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/SPI.o.d > ${OBJECTDIR}/_ext/43898991/SPI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/uart2io.o: ../../uart2io.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/uart2io.o.d -o ${OBJECTDIR}/_ext/43898991/uart2io.o ../../uart2io.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/uart2io.o.d > ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/uart2io.o.d > ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/procMenu.o: ../../procMenu.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/procMenu.o.d -o ${OBJECTDIR}/_ext/43898991/procMenu.o ../../procMenu.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/procMenu.o.d > ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/procMenu.o.d > ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/pic.o: ../../pic.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/pic.o.d -o ${OBJECTDIR}/_ext/43898991/pic.o ../../pic.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/pic.o.d > ${OBJECTDIR}/_ext/43898991/pic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pic.o.tmp ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/pic.o.d > ${OBJECTDIR}/_ext/43898991/pic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pic.o.tmp ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o: ../../pc_at_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d -o ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o ../../pc_at_keyboard.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d > ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d > ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp}
endif
else
${OBJECTDIR}/_ext/43898991/bitbang.o: ../../bitbang.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/bitbang.o.d -o ${OBJECTDIR}/_ext/43898991/bitbang.o ../../bitbang.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/bitbang.o.d > ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/bitbang.o.d > ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp ${OBJECTDIR}/_ext/43898991/bitbang.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/bitbang.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/UART.o: ../../UART.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/UART.o.d -o ${OBJECTDIR}/_ext/43898991/UART.o ../../UART.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/UART.o.d > ${OBJECTDIR}/_ext/43898991/UART.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/UART.o.tmp ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/UART.o.d > ${OBJECTDIR}/_ext/43898991/UART.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/UART.o.tmp ${OBJECTDIR}/_ext/43898991/UART.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/UART.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/main.o: ../../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/main.o.d -o ${OBJECTDIR}/_ext/43898991/main.o ../../main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/main.o.d > ${OBJECTDIR}/_ext/43898991/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/main.o.tmp ${OBJECTDIR}/_ext/43898991/main.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/main.o.d > ${OBJECTDIR}/_ext/43898991/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/main.o.tmp ${OBJECTDIR}/_ext/43898991/main.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/main.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/base.o: ../../base.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/base.o.d -o ${OBJECTDIR}/_ext/43898991/base.o ../../base.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/base.o.d > ${OBJECTDIR}/_ext/43898991/base.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/base.o.tmp ${OBJECTDIR}/_ext/43898991/base.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/base.o.d > ${OBJECTDIR}/_ext/43898991/base.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/base.o.tmp ${OBJECTDIR}/_ext/43898991/base.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/base.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/raw3wire.o: ../../raw3wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/raw3wire.o.d -o ${OBJECTDIR}/_ext/43898991/raw3wire.o ../../raw3wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/raw3wire.o.d > ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/raw3wire.o.d > ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw3wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw3wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/selftest.o: ../../selftest.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/selftest.o.d -o ${OBJECTDIR}/_ext/43898991/selftest.o ../../selftest.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/selftest.o.d > ${OBJECTDIR}/_ext/43898991/selftest.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/selftest.o.d > ${OBJECTDIR}/_ext/43898991/selftest.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp ${OBJECTDIR}/_ext/43898991/selftest.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/selftest.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binwire.o: ../../binwire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binwire.o.d -o ${OBJECTDIR}/_ext/43898991/binwire.o ../../binwire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binwire.o.d > ${OBJECTDIR}/_ext/43898991/binwire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binwire.o.d > ${OBJECTDIR}/_ext/43898991/binwire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp ${OBJECTDIR}/_ext/43898991/binwire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binwire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/SUMP.o: ../../SUMP.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/SUMP.o.d -o ${OBJECTDIR}/_ext/43898991/SUMP.o ../../SUMP.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/SUMP.o.d > ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/SUMP.o.d > ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp ${OBJECTDIR}/_ext/43898991/SUMP.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SUMP.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/OpenOCD.o: ../../OpenOCD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d -o ${OBJECTDIR}/_ext/43898991/OpenOCD.o ../../OpenOCD.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d > ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d > ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp ${OBJECTDIR}/_ext/43898991/OpenOCD.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/OpenOCD.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binIOhelpers.o: ../../binIOhelpers.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d -o ${OBJECTDIR}/_ext/43898991/binIOhelpers.o ../../binIOhelpers.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d > ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d > ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIOhelpers.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/baseIO.o: ../../baseIO.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/baseIO.o.d -o ${OBJECTDIR}/_ext/43898991/baseIO.o ../../baseIO.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/baseIO.o.d > ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/baseIO.o.d > ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp ${OBJECTDIR}/_ext/43898991/baseIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseIO.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/dio.o: ../../dio.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/dio.o.d -o ${OBJECTDIR}/_ext/43898991/dio.o ../../dio.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/dio.o.d > ${OBJECTDIR}/_ext/43898991/dio.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/dio.o.tmp ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/dio.o.d > ${OBJECTDIR}/_ext/43898991/dio.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/dio.o.tmp ${OBJECTDIR}/_ext/43898991/dio.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/dio.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/AUXpin.o: ../../AUXpin.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/AUXpin.o.d -o ${OBJECTDIR}/_ext/43898991/AUXpin.o ../../AUXpin.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/AUXpin.o.d > ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/AUXpin.o.d > ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp ${OBJECTDIR}/_ext/43898991/AUXpin.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/AUXpin.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/raw2wire.o: ../../raw2wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/raw2wire.o.d -o ${OBJECTDIR}/_ext/43898991/raw2wire.o ../../raw2wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/raw2wire.o.d > ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/raw2wire.o.d > ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp ${OBJECTDIR}/_ext/43898991/raw2wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/raw2wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/m_1wire_213.o: ../../m_1wire_213.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d -o ${OBJECTDIR}/_ext/43898991/m_1wire_213.o ../../m_1wire_213.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d > ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d > ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/m_1wire_213.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/I2C.o: ../../I2C.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/I2C.o.d -o ${OBJECTDIR}/_ext/43898991/I2C.o ../../I2C.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/I2C.o.d > ${OBJECTDIR}/_ext/43898991/I2C.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/I2C.o.d > ${OBJECTDIR}/_ext/43898991/I2C.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp ${OBJECTDIR}/_ext/43898991/I2C.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/I2C.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/1wire.o: ../../1wire.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/1wire.o.d -o ${OBJECTDIR}/_ext/43898991/1wire.o ../../1wire.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/1wire.o.d > ${OBJECTDIR}/_ext/43898991/1wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/1wire.o.d > ${OBJECTDIR}/_ext/43898991/1wire.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp ${OBJECTDIR}/_ext/43898991/1wire.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/1wire.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/binIO.o: ../../binIO.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/binIO.o.d -o ${OBJECTDIR}/_ext/43898991/binIO.o ../../binIO.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/binIO.o.d > ${OBJECTDIR}/_ext/43898991/binIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/binIO.o.d > ${OBJECTDIR}/_ext/43898991/binIO.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp ${OBJECTDIR}/_ext/43898991/binIO.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/binIO.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/HD44780.o: ../../HD44780.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/HD44780.o.d -o ${OBJECTDIR}/_ext/43898991/HD44780.o ../../HD44780.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/HD44780.o.d > ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/HD44780.o.d > ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp ${OBJECTDIR}/_ext/43898991/HD44780.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/HD44780.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/busPirateCore.o: ../../busPirateCore.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d -o ${OBJECTDIR}/_ext/43898991/busPirateCore.o ../../busPirateCore.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d > ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d > ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp ${OBJECTDIR}/_ext/43898991/busPirateCore.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/busPirateCore.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/baseUI.o: ../../baseUI.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/baseUI.o.d -o ${OBJECTDIR}/_ext/43898991/baseUI.o ../../baseUI.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/baseUI.o.d > ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/baseUI.o.d > ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp ${OBJECTDIR}/_ext/43898991/baseUI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/baseUI.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/basic.o: ../../basic.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/basic.o.d -o ${OBJECTDIR}/_ext/43898991/basic.o ../../basic.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/basic.o.d > ${OBJECTDIR}/_ext/43898991/basic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/basic.o.tmp ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/basic.o.d > ${OBJECTDIR}/_ext/43898991/basic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/basic.o.tmp ${OBJECTDIR}/_ext/43898991/basic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/basic.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/SPI.o: ../../SPI.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/SPI.o.d -o ${OBJECTDIR}/_ext/43898991/SPI.o ../../SPI.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/SPI.o.d > ${OBJECTDIR}/_ext/43898991/SPI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/SPI.o.d > ${OBJECTDIR}/_ext/43898991/SPI.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp ${OBJECTDIR}/_ext/43898991/SPI.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/SPI.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/uart2io.o: ../../uart2io.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/uart2io.o.d -o ${OBJECTDIR}/_ext/43898991/uart2io.o ../../uart2io.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/uart2io.o.d > ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/uart2io.o.d > ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp ${OBJECTDIR}/_ext/43898991/uart2io.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/uart2io.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/procMenu.o: ../../procMenu.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/procMenu.o.d -o ${OBJECTDIR}/_ext/43898991/procMenu.o ../../procMenu.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/procMenu.o.d > ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/procMenu.o.d > ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp ${OBJECTDIR}/_ext/43898991/procMenu.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/procMenu.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/pic.o: ../../pic.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/pic.o.d -o ${OBJECTDIR}/_ext/43898991/pic.o ../../pic.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/pic.o.d > ${OBJECTDIR}/_ext/43898991/pic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pic.o.tmp ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/pic.o.d > ${OBJECTDIR}/_ext/43898991/pic.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pic.o.tmp ${OBJECTDIR}/_ext/43898991/pic.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pic.o.tmp}
endif
${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o: ../../pc_at_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/43898991 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=24FJ64GA002 -Wall -I"../../translations" -mlarge-code -mlarge-data -Os -MMD -MF ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d -o ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o ../../pc_at_keyboard.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d > ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d > ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${CP} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.d 
	${RM} ${OBJECTDIR}/_ext/43898991/pc_at_keyboard.o.tmp}
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf ${OBJECTFILES}      -Wl,--defsym=__MPLAB_BUILD=1,--script=../../p24FJ64GA002.gld,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-L"../..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem
else
dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -o dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf ${OBJECTFILES}      -Wl,--defsym=__MPLAB_BUILD=1,--script=../../p24FJ64GA002.gld,-L"../..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/busPirate.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist
# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
