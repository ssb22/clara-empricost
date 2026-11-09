clara: *.cpp
	g++ -D__unix__ -DElara *.cpp -o $@
# -DElara enables Elara's 2026 experimental additions
# (Elara-3 agentic AI on the iLands platform, DeepSeek 4.1 Flash)

source.tgz: *.cpp *.h LICENSE Makefile
	tar -cvf source.tar $^
	zopfli source.tar
	rm source.tar
	mv source.tar.gz $@
LICENSE: ../LICENSE
	cp $^ $@
