EXENAME1 = testimage
EXENAME2 = testscene

OBJS1 = png.o rgbapixel.o image.o testimage.o
OBJS2 = png.o rgbapixel.o image.o scene.o testscene.o


CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME1) $(EXENAME2)

$(EXENAME1) : $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXENAME1)

$(EXENAME2) : $(OBJS2) 
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)


image.o: image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp 

testimage.o: testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp	

testscene.o: testscene.cpp image.h
	$(CXX) $(CXXFLAGS) testscene.cpp	

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

scene.o : scene.cpp scene.h
	$(CXX) $(CXXFLAGS) scene.cpp

clean :
	-rm -f *.o $(EXENAME1) $(EXENAME2)
