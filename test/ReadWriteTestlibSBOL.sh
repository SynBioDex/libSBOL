#!/bin/sh

for f in SBOL2/*
do
  echo $f
  ./ReadWriteTestlibSBOL $f Out/$f
  java -jar libSBOLj.jar $f -e Out/$f -i -n -no -mf originalFile -cf outputFile 
  echo 
done
