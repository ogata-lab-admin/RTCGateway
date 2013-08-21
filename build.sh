#!/bin/bash
TARGET=RTCGateway

mkdir -p externals

xcodebuild -project "${TARGET}-i386.xcodeproj" -configuration "Deployment"
xcodebuild -project "${TARGET}-x86_64.xcodeproj" -configuration "Deployment"

rm -rf ${TARGET}.mxo 
cp -R externals/x86_64/${TARGET}.mxo ./
rm -rf ${TARGET}.mxo/Contents/MacOS/${TARGET}
lipo -create -output ${TARGET}.mxo/Contents/MacOS/${TARGET} -arch i386 externals/i386/${TARGET}.mxo/Contents/MacOS/${TARGET}  -arch x86_64 externals/x86_64/${TARGET}.mxo/Contents/MacOS/${TARGET} 

rm -rf externals/i386 externals/x86_64 build