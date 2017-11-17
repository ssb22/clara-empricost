#!/bin/bash
wget -N http://people.ds.cam.ac.uk/ssb22/clara/source.tgz
tar -zxvf source.tgz
git add *.cpp *.h COPYING
git commit -am update && git push
