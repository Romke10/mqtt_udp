#/bin/sh
#gawk -f preprocess.awk -v ver=0.55 conf.py.in  |grep version
# pass version number as 1st arg
gawk -f preprocess.awk -v ver=$1 -v rel=$1-$2 conf.py.in >conf.py 
