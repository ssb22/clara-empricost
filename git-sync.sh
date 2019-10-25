#!/bin/bash
git pull --no-edit
wget -N http://ssb22.user.srcf.net/clara/source.tgz
tar -zxvf source.tgz
git add *.cpp *.h COPYING
git commit -am update && git push
