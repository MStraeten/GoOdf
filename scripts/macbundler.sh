#!/bin/sh

# bases on an macports based build
# after installing macports install GoOdf dependencies via
# sudo port -N install cmake wxWidgets-3.2 imagemagick 
# sudo port select --set wxWidgets wxWidgets-3.2
# then follow https://github.com/GrandOrgue/GoOdf?tab=readme-ov-file#building-from-sources
#
# creating an redistributionable app package uses 
# https://github.com/rkitover/mac-third-party-libs-tool to bundle dependencies
# copy https://github.com/rkitover/mac-third-party-libs-tool/blob/1.3/third_party_libs_tool
# into ./script directory
# run from GoOdf directory: ./scripts/macbundler.sh ./script

    app_name=GoOdf
    app_binary=./build/bin/$app_name
    app_bundle=$app_name.app
    
    sharestuff=./build/share
    PkgInfoContents="APPL????"

    if [ -e $app_bundle ]
    then
      echo "$appfolder already exists, deleting"
      rm -rf $app_bundle
    fi
    
    echo "Creating $app_bundle..."
    mkdir -p $app_bundle/Contents/MacOS/
    mkdir -p $app_bundle/Contents/Frameworks/
    mkdir -p $app_bundle/Contents/Resources/
    mkdir -p $app_bundle/Contents/share/
    
    # Copy App
    cp $app_binary $app_bundle/Contents/MacOS/$app_name
    echo "App copied..."
    # Copy the resource files to the correct place
    cp -r $sharestuff/* $app_bundle/Contents/share
    echo "share copied..."
    #handle icon
    cp ./resources/icons/$app_name.icns $app_bundle/Contents/Resources/

    # Create PkgInfo file.
    echo $PkgInfoContents >$app_bundle/Contents/PkgInfo
    
    # Create information property list file (Info.plist).
    plistfile=$app_bundle/Contents/Info.plist
    echo '<?xml version="1.0" encoding="UTF-8"?>' >$plistfile
    echo '<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >>$plistfile
    echo '<plist version="1.0">' >>$plistfile
    echo '<dict>' >>$plistfile
    echo '  <key>CFBundleDevelopmentRegion</key>' >>$plistfile
    echo '  <string>English</string>' >>$plistfile
    echo '  <key>CFBundleExecutable</key>' >>$plistfile
    echo '  <string>'$app_name'</string>' >>$plistfile
    echo '  <key>CFBundleIconFile</key>' >>$plistfile
    echo '  <string>'$app_name.icns'</string>' >>$plistfile
    echo '  <key>CFBundleIdentifier</key>' >>$plistfile
    echo '  <string>se.palo.'$app_name'</string>' >>$plistfile
    echo '  <key>CFBundleInfoDictionaryVersion</key>' >>$plistfile
    echo '  <string>6.0</string>' >>$plistfile
    echo '  <key>CFBundlePackageType</key>' >>$plistfile
    echo '  <string>APPL</string>' >>$plistfile
    echo '  <key>CFBundleSignature</key>' >>$plistfile
    echo '  <string>????</string>' >>$plistfile
    echo '  <key>CFBundleVersion</key>' >>$plistfile
    echo '  <string>1.0</string>' >>$plistfile
    echo '  <key>NSHighResolutionCapable</key>' >>$plistfile
    echo '  <string>True</string>' >>$plistfile
    echo '</dict>' >>$plistfile
    echo '</plist>' >>$plistfile

#run https://github.com/rkitover/mac-third-party-libs-tool
#tested with version 1.3
$1/third_party_libs_tool $app_bundle
