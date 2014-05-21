##########################
# Author: CJ McAllister	 #
#						 #
# Created on: 2014-05-09 #
##########################

# Compiler variables
CC = g++
CFLAGS = -c -Wall -std=c++0x
LFLAGS = -static -Wl,--subsystem,windows

# Static Library variables
LibSrcDir = 	./Egine
LibObjDir = 	./Egine/obj
LibObjList = 	$(LibObjDir)/AABB.o $(LibObjDir)/Linear.o $(LibObjDir)/MPUtils.o 
LibObjList += 	$(LibObjDir)/Parametric.o $(LibObjDir)/PhysicsObject.o $(LibObjDir)/Quadratic.o
LibObjList +=	$(LibObjDir)/Scene.o $(LibObjDir)/StdAfx.o $(LibObjDir)/SubTrajectory.o
LibObjList +=	$(LibObjDir)/Trajectory.o
LibOutputDir = 	./Egine/bin
	
all: $(LibOutputDir)/Egine.lib

$(LibOutputDir)/Egine.lib: $(LibObjList)
	$(CC) $(LFLAGS) -o $@ $(LibObjList)
	
	
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
	
##### UTILITY #####
clean:
	rm $(LibObjDir)/*.o