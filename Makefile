clara: *.cpp
	g++ -fno-for-scope -fno-operator-names -Wno-write-strings -Wno-deprecated -D__unix__ *.cpp -o $@

source.tgz: *.cpp *.h LICENSE Makefile
	tar -cvf source.tar $^
	zopfli source.tar
	rm source.tar
	mv source.tar.gz $@
