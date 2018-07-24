CXX = g++
CXXFLAGS = -g -Wall

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)


 cap : $(obj)
	$(CXX) $(CXXFLAGS) -o cap $^

.PHONY : clean

clean:
	rm -f $(obj) cap
	rm -f *~
	rm -f *#

.PHONY : install
PREFIX = /usr/local
DESTDIR = 

install : cap
	mkdir -p $(DESTDIR)$(PREFIX)/bin/cap
	cp $<$(DESTDIR)$(PREFIX)/bin/cap

.PHONY : uninstall

uninstall : cap
	rm -f $(DESTDIR)$(PREFIX)/bin/cap

