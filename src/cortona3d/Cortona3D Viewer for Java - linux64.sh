#!/bin/sh

java -Xmx512m -classpath "cortonaj3d.jar:jogl/gluegen-rt.jar:jogl/jogl.jar:." -Djava.library.path=jogl/linux64 com.parallelgraphics.cortonaj3d.Viewer
