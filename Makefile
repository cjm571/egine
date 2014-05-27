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
$(LTOutputDir)/LinuxTest: $(LTObjList)
	mkdir -p $(@D)
	$(CC) -static -I$(LibSrcDir) $(LTObjList) -L$(LibOutputDir) -legine -o $@

library: $(LibOutputDir)/libegine.a
$(LibOutputDir)/libegine.a: $(LibObjList)
	mkdir -p $(@D)
	$(LD) $(LFLAGS) $@ $(LibObjList)
	
	
##### STATIC LIBRARY TARGETS #####
$(LibObjDir)/AABB.o: $(LibSrcDir)/AABB.cpp $(LibSrcDir)/AABB.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/AABB.cpp -o $@
$(LibObjDir)/Linear.o: $(LibSrcDir)/Linear.cpp $(LibSrcDir)/Linear.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/Linear.cpp -o $@
$(LibObjDir)/MPUtils.o: $(LibSrcDir)/MPUtils.cpp $(LibSrcDir)/MPUtils.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/MPUtils.cpp -o $@
$(LibObjDir)/Parametric.o: $(LibSrcDir)/Parametric.cpp $(LibSrcDir)/Parametric.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/Parametric.cpp -o $@
$(LibObjDir)/PhysicsObject.o: $(LibSrcDir)/PhysicsObject.cpp $(LibSrcDir)/PhysicsObject.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysicsObject.cpp -o $@
$(LibObjDir)/PhysLogger.o: $(LibSrcDir)/PhysLogger.cpp $(LibSrcDir)/PhysLogger.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysLogger.cpp -o $@
$(LibObjDir)/Quadratic.o: $(LibSrcDir)/Quadratic.cpp $(LibSrcDir)/Quadratic.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/Quadratic.cpp -o $@
$(LibObjDir)/Scene.o: $(LibSrcDir)/Scene.cpp $(LibSrcDir)/Scene.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/Scene.cpp -o $@
$(LibObjDir)/StdAfx.o: $(LibSrcDir)/StdAfx.cpp $(LibSrcDir)/StdAfx.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/StdAfx.cpp -o $@
$(LibObjDir)/SubTrajectory.o: $(LibSrcDir)/SubTrajectory.cpp $(LibSrcDir)/SubTrajectory.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/SubTrajectory.cpp -o $@
$(LibObjDir)/Trajectory.o: $(LibSrcDir)/Trajectory.cpp $(LibSrcDir)/Trajectory.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LibSrcDir)/Trajectory.cpp -o $@
	
	
##### LINUX TEST TARGETS #####
$(LTObjDir)/Main.o: $(LTSrcDir)/Main.cpp $(LTSrcDir)/Main.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/Main.cpp -o $@
$(LTObjDir)/StdAfx.o: $(LTSrcDir)/StdAfx.cpp $(LTSrcDir)/StdAfx.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/StdAfx.cpp -o $@
$(LTObjDir)/TestStub.o: $(LTSrcDir)/TestStub.cpp $(LTSrcDir)/TestStub.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/TestStub.cpp -o $@

	
##### UTILITY #####
clean:
	rm -f $(LibObjDir)/*.o
	rm -f $(LibOutputDir)/*.a
	rm -f $(LTObjDir)/*.o
	rm -f $(LTOutputDir)/*
