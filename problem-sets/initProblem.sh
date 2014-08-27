#!/bin/bash

if [ -z "$1" ]
then
	echo "1st arg missing: usage: ./initProblem <probid>";
	exit -1
fi

PROBLEMID="0"
PROBLEMID+="$1"
PDFFILE="$1"
PDFFILE+=".pdf"

echo $1
echo $PROBLEMID
echo $PDFFILE

mkdir $PROBLEMID
cp Makefile $PROBLEMID/
cp main.cpp $PROBLEMID/
touch $PROBLEMID/test1.txt
touch $PROBLEMID/soln1.txt
wget "http://uva.onlinejudge.org/external/1/$PDFFILE"
mv $PDFFILE $PROBLEMID/
