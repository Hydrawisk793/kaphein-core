#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-w64-msys2-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/e7dc6662/Copyable.o \
	${OBJECTDIR}/_ext/e7dc6662/ErrorCode.o \
	${OBJECTDIR}/_ext/e7dc6662/byteOrder.o \
	${OBJECTDIR}/_ext/59f34679/ByteBuffer.o \
	${OBJECTDIR}/_ext/59f34679/List.o \
	${OBJECTDIR}/_ext/b0836b1a/Aabb.o \
	${OBJECTDIR}/_ext/b0836b1a/Capsule.o \
	${OBJECTDIR}/_ext/b0836b1a/Matrix4x4.o \
	${OBJECTDIR}/_ext/b0836b1a/Quaternion_internal.o \
	${OBJECTDIR}/_ext/b0836b1a/Ray.o \
	${OBJECTDIR}/_ext/b0836b1a/Vector3.o \
	${OBJECTDIR}/_ext/b0836b1a/Vector3_internal.o \
	${OBJECTDIR}/_ext/b0836b1a/Vector4.o \
	${OBJECTDIR}/_ext/b0836b1a/Vector4_internal.o \
	${OBJECTDIR}/_ext/e7dc6662/internal.o \
	${OBJECTDIR}/_ext/adb52387/Quaternion.o \
	${OBJECTDIR}/_ext/59f79e95/scalar.o \
	${OBJECTDIR}/_ext/3cb568a8/Allocator.o \
	${OBJECTDIR}/_ext/3cb568a8/SegmentPool.o \
	${OBJECTDIR}/_ext/3cb568a8/utils.o \
	${OBJECTDIR}/_ext/59fadcba/encoding.o \
	${OBJECTDIR}/_ext/59fae733/Mutex.o \
	${OBJECTDIR}/_ext/59fae733/ResetEvent.o \
	${OBJECTDIR}/_ext/59fae733/ThreadPool.o \
	${OBJECTDIR}/_ext/59fae733/internal.o \
	${OBJECTDIR}/_ext/59fae733/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_PLATFORM}/${CND_CONF}/kaphein.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_PLATFORM}/${CND_CONF}/kaphein.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_PLATFORM}/${CND_CONF}
	${LINK.c} -o ${CND_DISTDIR}/${CND_PLATFORM}/${CND_CONF}/kaphein.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--out-implib,${CND_DISTDIR}/${CND_PLATFORM}/${CND_CONF}/kaphein.a -shared

${OBJECTDIR}/_ext/e7dc6662/Copyable.o: ../../../src/kaphein/Copyable.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/e7dc6662
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e7dc6662/Copyable.o ../../../src/kaphein/Copyable.c

${OBJECTDIR}/_ext/e7dc6662/ErrorCode.o: ../../../src/kaphein/ErrorCode.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/e7dc6662
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e7dc6662/ErrorCode.o ../../../src/kaphein/ErrorCode.c

${OBJECTDIR}/_ext/e7dc6662/byteOrder.o: ../../../src/kaphein/byteOrder.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/e7dc6662
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e7dc6662/byteOrder.o ../../../src/kaphein/byteOrder.c

${OBJECTDIR}/_ext/59f34679/ByteBuffer.o: ../../../src/kaphein/coll/ByteBuffer.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59f34679
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59f34679/ByteBuffer.o ../../../src/kaphein/coll/ByteBuffer.c

${OBJECTDIR}/_ext/59f34679/List.o: ../../../src/kaphein/coll/List.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59f34679
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59f34679/List.o ../../../src/kaphein/coll/List.c

${OBJECTDIR}/_ext/b0836b1a/Aabb.o: ../../../src/kaphein/geom3d/Aabb.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Aabb.o ../../../src/kaphein/geom3d/Aabb.c

${OBJECTDIR}/_ext/b0836b1a/Capsule.o: ../../../src/kaphein/geom3d/Capsule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Capsule.o ../../../src/kaphein/geom3d/Capsule.c

${OBJECTDIR}/_ext/b0836b1a/Matrix4x4.o: ../../../src/kaphein/geom3d/Matrix4x4.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Matrix4x4.o ../../../src/kaphein/geom3d/Matrix4x4.c

${OBJECTDIR}/_ext/b0836b1a/Quaternion_internal.o: ../../../src/kaphein/geom3d/Quaternion_internal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Quaternion_internal.o ../../../src/kaphein/geom3d/Quaternion_internal.c

${OBJECTDIR}/_ext/b0836b1a/Ray.o: ../../../src/kaphein/geom3d/Ray.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Ray.o ../../../src/kaphein/geom3d/Ray.c

${OBJECTDIR}/_ext/b0836b1a/Vector3.o: ../../../src/kaphein/geom3d/Vector3.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Vector3.o ../../../src/kaphein/geom3d/Vector3.c

${OBJECTDIR}/_ext/b0836b1a/Vector3_internal.o: ../../../src/kaphein/geom3d/Vector3_internal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Vector3_internal.o ../../../src/kaphein/geom3d/Vector3_internal.c

${OBJECTDIR}/_ext/b0836b1a/Vector4.o: ../../../src/kaphein/geom3d/Vector4.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Vector4.o ../../../src/kaphein/geom3d/Vector4.c

${OBJECTDIR}/_ext/b0836b1a/Vector4_internal.o: ../../../src/kaphein/geom3d/Vector4_internal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/b0836b1a
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0836b1a/Vector4_internal.o ../../../src/kaphein/geom3d/Vector4_internal.c

${OBJECTDIR}/_ext/e7dc6662/internal.o: ../../../src/kaphein/internal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/e7dc6662
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e7dc6662/internal.o ../../../src/kaphein/internal.c

${OBJECTDIR}/_ext/adb52387/Quaternion.o: ../../../src/kaphein/math/geom3d/Quaternion.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/adb52387
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/adb52387/Quaternion.o ../../../src/kaphein/math/geom3d/Quaternion.c

${OBJECTDIR}/_ext/59f79e95/scalar.o: ../../../src/kaphein/math/scalar.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59f79e95
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59f79e95/scalar.o ../../../src/kaphein/math/scalar.c

${OBJECTDIR}/_ext/3cb568a8/Allocator.o: ../../../src/kaphein/mem/Allocator.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3cb568a8
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3cb568a8/Allocator.o ../../../src/kaphein/mem/Allocator.c

${OBJECTDIR}/_ext/3cb568a8/SegmentPool.o: ../../../src/kaphein/mem/SegmentPool.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3cb568a8
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3cb568a8/SegmentPool.o ../../../src/kaphein/mem/SegmentPool.c

${OBJECTDIR}/_ext/3cb568a8/utils.o: ../../../src/kaphein/mem/utils.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3cb568a8
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3cb568a8/utils.o ../../../src/kaphein/mem/utils.c

${OBJECTDIR}/_ext/59fadcba/encoding.o: ../../../src/kaphein/text/encoding.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fadcba
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fadcba/encoding.o ../../../src/kaphein/text/encoding.c

${OBJECTDIR}/_ext/59fae733/Mutex.o: ../../../src/kaphein/thrd/Mutex.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fae733
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fae733/Mutex.o ../../../src/kaphein/thrd/Mutex.c

${OBJECTDIR}/_ext/59fae733/ResetEvent.o: ../../../src/kaphein/thrd/ResetEvent.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fae733
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fae733/ResetEvent.o ../../../src/kaphein/thrd/ResetEvent.c

${OBJECTDIR}/_ext/59fae733/ThreadPool.o: ../../../src/kaphein/thrd/ThreadPool.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fae733
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fae733/ThreadPool.o ../../../src/kaphein/thrd/ThreadPool.c

${OBJECTDIR}/_ext/59fae733/internal.o: ../../../src/kaphein/thrd/internal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fae733
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fae733/internal.o ../../../src/kaphein/thrd/internal.c

${OBJECTDIR}/_ext/59fae733/utils.o: ../../../src/kaphein/thrd/utils.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/59fae733
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -DKAPHEIN_COMPOPT_THREAD_MODEL_MODE=0 -DKAPHEIN_COMPOPT_THREAD_MODEL_VALUE=KAPHEIN_THREAD_MODEL_PTHREAD -I../../../include  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59fae733/utils.o ../../../src/kaphein/thrd/utils.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
