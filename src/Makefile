CXX   ?= g++
FLAGS ?= -DElara
# -DElara enables Elara's 2026 experimental additions

clara: *.cpp
	$(CXX) -D__unix__ $(FLAGS) *.cpp -o $@

source.tgz: *.cpp *.h LICENSE Makefile
	tar -cvf source.tar $^
	zopfli source.tar
	rm source.tar
	mv source.tar.gz $@
LICENSE: ../LICENSE
	cp $^ $@
