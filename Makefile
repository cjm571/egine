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
LFLAGS = rvcs

# Static Library variables
LibSrcDir = 	./Egine
LibObjDir = 	./Egine/obj
LibIncDir =		./Egine/inc
LibOutputDir = 	./Egine/lib
LibObjList = 	$(LibObjDir)/AABB.o $(LibObjDir)/Linear.o $(LibObjDir)/MPUtils.o 
LibObjList += 	$(LibObjDir)/Parametric.o $(LibObjDir)/PhysicsObject.o $(LibObjDir)/Quadratic.o
LibObjList +=	$(LibObjDir)/Scene.o $(LibObjDir)/StdAfx.o $(LibObjDir)/SubTrajectory.o
LibObjList +=	$(LibObjDir)/Trajectory.o

#Linux Test variables
LTSrcDir =		./test/LinuxTest
LTObjDir =		./test/LinuxTest/obj
LTOutputDir =	./test/LinuxTest/bin
LTObjList =		$(LTObjDir)/StdAfx.o $(LTObjDir)/TestStub.o $(LTObjDir)/Main.o
	

##### FUNCTIONAL GROUP TARGETS #####
all: LinuxTest

LinuxTest: Library $(LTOutputDir)/LinuxTest
$(LTOutputDir)/LinuxTest: $(LTObjList)
	$(CC) -static -I$(LibSrcDir) $(LTObjList) -L$(LibOutputDir) -legine -o $@

Library: $(LibOutputDir)/libegine.a
$(LibOutputDir)/libegine.a: $(LibObjList)
	$(LD) $(LFLAGS) $@ $(LibObjList)
	
	
##### STATIC LIBRARY TARGETS #####
$(LibObjDir)/AABB.o: $(LibSrcDir)/AABB.cpp $(LibSrcDir)/AABB.h
	$(CC) $(CFLAGS) $(LibSrcDir)/AABB.cpp -o $@
$(LibObjDir)/Linear.o: $(LibSrcDir)/Linear.cpp $(LibSrcDir)/Linear.h
	$(CC) $(CFLAGS) $(LibSrcDir)/Linear.cpp -o $@
$(LibObjDir)/MPUtils.o: $(LibSrcDir)/MPUtils.cpp $(LibSrcDir)/MPUtils.h
	$(CC) $(CFLAGS) $(LibSrcDir)/MPUtils.cpp -o $@
$(LibObjDir)/Parametric.o: $(LibSrcDir)/Parametric.cpp $(LibSrcDir)/Parametric.h
	$(CC) $(CFLAGS) $(LibSrcDir)/Parametric.cpp -o $@
$(LibObjDir)/PhysicsObject.o: $(LibSrcDir)/PhysicsObject.cpp $(LibSrcDir)/PhysicsObject.h
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysicsObject.cpp -o $@
$(LibObjDir)/PhysLogger.o: $(LibSrcDir)/PhysLogger.cpp $(LibSrcDir)/PhysLogger.h
	$(CC) $(CFLAGS) $(LibSrcDir)/PhysLogger.cpp -o $@
$(LibObjDir)/Quadratic.o: $(LibSrcDir)/Quadratic.cpp $(LibSrcDir)/Quadratic.h
	$(CC) $(CFLAGS) $(LibSrcDir)/Quadratic.cpp -o $@
$(LibObjDir)/Scene.o: $(LibSrcDir)/Scene.cpp $(LibSrcDir)/Scene.h
	$(CC) $(CFLAGS) $(LibSrcDir)/Scene.cpp -o $@
$(LibObjDir)/StdAfx.o: $(LibSrcDir)/StdAfx.cpp $(LibSrcDir)/StdAfx.h
	$(CC) $(CFLAGS) $(LibSrcDir)/StdAfx.cpp -o $@
$(LibObjDir)/SubTrajectory.o: $(LibSrcDir)/SubTrajectory.cpp $(LibSrcDir)/SubTrajectory.h
	$(CC) $(CFLAGS) $(LibSrcDir)/SubTrajectory.cpp -o $@
$(LibObjDir)/Trajectory.o: $(LibSrcDir)/Trajectory.cpp $(LibSrcDir)/Trajectory.h
	$(CC) $(CFLAGS) $(LibSrcDir)/Trajectory.cpp -o $@
	
	
##### LINUX TEST TARGETS #####
$(LTObjDir)/Main.o: $(LTSrcDir)/Main.cpp $(LTSrcDir)/Main.h
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/Main.cpp -o $@
$(LTObjDir)/StdAfx.o: $(LTSrcDir)/StdAfx.cpp $(LTSrcDir)/StdAfx.h
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/StdAfx.cpp -o $@
$(LTObjDir)/TestStub.o: $(LTSrcDir)/TestStub.cpp $(LTSrcDir)/TestStub.h
	$(CC) $(CFLAGS) -I$(LibSrcDir) -L$(LibOutputDir) $(LTSrcDir)/TestStub.cpp -o $@

	
##### UTILITY #####
clean:
	rm -f $(LibObjDir)/*.o
	rm -f $(LibIncDir)/*.h
	rm -f $(LibOutputDir)/*.a
	rm -f $(LTObjDir)/*.o
	rm -f $(LTOutputDir)/*
