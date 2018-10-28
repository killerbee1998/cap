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

install : cap
	sudo cp cap /bin/cap
	mkdir --parents ~/Documents/cap
	cp -r config  ~/Documents/cap/config
	cp -r docs ~/Documents/cap/docs

.PHONY : update

update : cap
	sudo cp cap /bin/cap

.PHONY : uninstall

uninstall : cap
	sudo rm -f /bin/cap
	sudo rm -rf ~/Documents/cap/config
	sudo rm -rf ~/Documents/cap/docs
