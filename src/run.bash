#!/bin/bash

# Constants
buildDir=bin/
srcDir=src/
renderPackage=cortona3d/cortonaj3d.jar
inFileDir=input/
outFileDir=out/

# Build the project
function build {
	echo Building the Project
	cd $buildDir
	cmake ../$srcDir
	make install
	cd ..
	echo Build Done!
}

# Run and render
function runAndRender {
	echo Running
	./proj -m $inFileDir$1.in
	./proj -t $inFileDir$1.in
	echo Rendering
	java -jar $renderPackage $outFileDir$1-t.wrl &
	java -jar $renderPackage $outFileDir$1-m.wrl &
}

# Pack together
function pack {
	build
	echo Plese Select the Geometry to Generate and Render
	OPTIONS="testCircle testDoubleTorus GDLImage"
	select opt in $OPTIONS; do
		runAndRender $opt
	done
}

pack
