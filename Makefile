##########################
# Author: CJ McAllister	 #
#						 #
# Created on: 2014-05-09 #
##########################

# Compiler variables
CC = g++
CFLAGS = -c -Wall -std=c++0x

#Linker variables
LD = ar
LFLAGS = rcs

# Static Library variables
LibSrcDir = 	./Egine
LibObjDir = 	./Egine/obj
LibIncDir =		./Egine/inc
LibOutputDir = 	./Egine/lib
LibObjList = 	$(addprefix $(LibObjDir)/,AABB.o Linear.o MPUtils.o Parametric.o PhysicsObject.o \
				Quadratic.o Scene.o StdAfx.o SubTrajectory.o Trajectory.o)
				
#Linux Test variables
LTSrcDir =		./test/LinuxTest
LTObjDir =		./test/LinuxTest/obj
LTOutputDir =	./test/LinuxTest/bin
LTObjList =		$(addprefix $(LTObjDir)/,StdAfx.o TestStub.o Main.o)
	

##### FUNCTIONAL GROUP TARGETS #####
all: linuxtest

linuxtest: library $(LTOutputDir)/LinuxTest
$(LTOutputDir)/LinuxTest: $(LTOutputDir) $(LTObjList)
	$(CC) -static -I$(LibSrcDir) $(LTObjList) -L$(LibOutputDir) -legine -o $@

library: $(LibOutputDir)/libegine.a
$(LibOutputDir)/libegine.a: $(LibOutputDir) $(LibObjList)
	$(LD) $(LFLAGS) $@ $(LibObjList)
	
	
##### STATIC LIBRARY TARGETS #####
$(LibObjDir)/AABB.o: $(LibSrcDir)/AABB.cpp $(LibSrcDir)/AABB.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/AABB.cpp -o $@
$(LibObjDir)/Linear.o: $(LibSrcDir)/Linear.cpp $(LibSrcDir)/Linear.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/Linear.cpp -o $@
$(LibObjDir)/MPUtils.o: $(LibSrcDir)/MPUtils.cpp $(LibSrcDir)/MPUtils.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/MPUtils.cpp -o $@
$(LibObjDir)/Parametric.o: $(LibSrcDir)/Parametric.cpp $(LibSrcDir)/Parametric.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/Parametric.cpp -o $@
$(LibObjDir)/PhysicsObject.o: $(LibSrcDir)/PhysicsObject.cpp $(LibSrcDir)/PhysicsObject.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysicsObject.cpp -o $@
$(LibObjDir)/PhysLogger.o: $(LibSrcDir)/PhysLogger.cpp $(LibSrcDir)/PhysLogger.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysLogger.cpp -o $@
$(LibObjDir)/Quadratic.o: $(LibSrcDir)/Quadratic.cpp $(LibSrcDir)/Quadratic.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/Quadratic.cpp -o $@
$(LibObjDir)/Scene.o: $(LibSrcDir)/Scene.cpp $(LibSrcDir)/Scene.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/Scene.cpp -o $@
$(LibObjDir)/StdAfx.o: $(LibSrcDir)/StdAfx.cpp $(LibSrcDir)/StdAfx.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/StdAfx.cpp -o $@
$(LibObjDir)/SubTrajectory.o: $(LibSrcDir)/SubTrajectory.cpp $(LibSrcDir)/SubTrajectory.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/SubTrajectory.cpp -o $@
$(LibObjDir)/Trajectory.o: $(LibSrcDir)/Trajectory.cpp $(LibSrcDir)/Trajectory.h | $(LibObjDir)
	$(CC) $(CFLAGS) $(LibSrcDir)/Trajectory.cpp -o $@
	
	
##### LINUX TEST TARGETS #####
$(LTObjDir)/Main.o: $(LTSrcDir)/Main.cpp $(LTSrcDir)/Main.h | $(LTObjDir)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/Main.cpp -o $@
$(LTObjDir)/StdAfx.o: $(LTSrcDir)/StdAfx.cpp $(LTSrcDir)/StdAfx.h | $(LTObjDir)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/StdAfx.cpp -o $@
$(LTObjDir)/TestStub.o: $(LTSrcDir)/TestStub.cpp $(LTSrcDir)/TestStub.h | $(LTObjDir)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/TestStub.cpp -o $@

	
##### UTILITY #####
$(LTOutputDir):
	mkdir -p $(LTOutputDir)
$(LibOutputDir):
	mkdir -p $(LibOutputDir)
$(LibObjDir):
	mkdir -p $(LibObjDir)
$(LTObjDir):
	mkdir -p $(LTObjDir)

clean:
	rm -rf $(LibObjDir)
	rm -rf $(LibOutputDir)
	rm -rf $(LTObjDir)
	rm -rf $(LTOutputDir)
