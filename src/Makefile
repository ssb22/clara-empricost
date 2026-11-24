CXX   ?= g++
FLAGS ?= -DElara
# -DElara enables Elara's 2026 experimental additions

clara: *.cpp
	$(CXX) -D__unix__ $(FLAGS) *.cpp -o $@

# If you want to convert the MWR files to modern Lilypond:
install-lilypond-programs:
	sudo apt update
	sudo apt install lilypond timidity ffmpeg btyacc python-is-python3 -y
	git clone --depth 1 https://github.com/ssb22/mwr2ly # (use git clone rather than wget as that can 429 if too many jobs started at once even though same company)
	cd mwr2ly && btyacc mwr2ly.y
	cd mwr2ly && g++ -Wno-write-strings y[._]tab.c -o mwr2ly
	sudo mv mwr2ly/mwr2ly /usr/local/bin/
	sudo mv mwr2ly/midi-add-depth.py /usr/local/bin/midi-add-depth
	rm -rf mwr2ly
%.ly: %.mwr
	mwr2ly < $< > $@
%.midi: %.ly
	lilypond $<
%.mid: %.midi
	midi-add-depth $< $@
%.mp3: %.mid
	timidity -Ow -o - $< | ffmpeg -i - $@
convert-all:
	C=1; for N in *.MWR; do P=$$(head -1 $$N|sed 's/; Movement /mvt-/'); if [ "$$P" == "" ]; then P=out$$C; C=$$[ $$C + 1 ]; fi; mv $$N $$P.mwr; make $$P.mp3; done
.PHONY: install-lilypond-programs convert-all

# For updating the home page:
source.tgz: *.cpp *.h LICENSE Makefile
	tar -cvf source.tar $^
	zopfli source.tar
	rm source.tar
	mv source.tar.gz $@
LICENSE: ../LICENSE
	cp $^ $@
