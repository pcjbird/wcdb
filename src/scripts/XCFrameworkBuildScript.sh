export TERM=xterm-256color

#set -e表示一旦脚本中有命令的返回值为非0，则脚本立即退出，后续命令不再执行;
set -e
#set -o pipefail表示在管道连接的命令序列中，只要有任何一个命令返回非0值，则整个管道返回非0值，即使最后一个命令返回0.
set -o pipefail

#################[ 用于测试: 有助于在Xcode中解决一些基于构建环境的问题 ]########
#################[ Tests: helps workaround any future bugs in Xcode ]########
#
DEBUG_THIS_SCRIPT="true"

if [ $DEBUG_THIS_SCRIPT = "true" ]
then

#set -x表示显示所有执行命令信息;
set -x
echo "########### 用于测试/TESTS #############"
echo "BUILD_DIR = $BUILD_DIR"
echo "BUILD_ROOT = $BUILD_ROOT"
echo "CONFIGURATION_BUILD_DIR = $CONFIGURATION_BUILD_DIR"
echo "BUILT_PRODUCTS_DIR = $BUILT_PRODUCTS_DIR"
echo "CONFIGURATION_TEMP_DIR = $CONFIGURATION_TEMP_DIR"
echo "TARGET_BUILD_DIR = $TARGET_BUILD_DIR"
echo "SRCROOT = $SRCROOT"
echo "PROJECT_NAME = $PROJECT_NAME"
echo "TARGET_NAME = $TARGET_NAME"
echo "PRODUCT_NAME = $PRODUCT_NAME"
echo " "
fi

PROJ_NAME="WCDB"
FRAMEWORK_NAME="$PRODUCT_NAME"
##FRAMEWORK_TYPE="project" # project or workspace
##FRAMEWORK_EXTENSION="xcodeproj" # xcodeproj or xcworkspace
FRAMEWORK_TYPE="project" # project or workspace
FRAMEWORK_EXTENSION="xcodeproj" # xcodeproj or xcworkspace

SCHEME_NAME="$FRAMEWORK_NAME"

ARCHIVE_PATH="./archives"
ARCHIVE_FRAMEWORK_PATH="Products/Library/Frameworks/$FRAMEWORK_NAME.framework"
ARCHIVE_FRAMEWORK_PATH1="Products/Library/Frameworks/sqlcipher.framework"
PHYSICAL_DEVICES_ARCHIVE_PATH="$ARCHIVE_PATH/$FRAMEWORK_NAME.framework-iphoneos.xcarchive"
SIMULATED_DEVICES_ARCHIVE_PATH="$ARCHIVE_PATH/$FRAMEWORK_NAME.framework-iphonesimulator.xcarchive"
MAC_CATALYST_ARCHIVE_PATH="$ARCHIVE_PATH/$FRAMEWORK_NAME.framework-catalyst.xcarchive"

XCFRAMEWORK_OUTPUT_PATH="$ARCHIVE_PATH/xcframework"

restart() {
    clear && rm -rvf $ARCHIVE_PATH; mkdir $ARCHIVE_PATH
    echo "• [Restarted] - Success! •"
}


sliceForPhysicalDevices() {
    xcodebuild archive -$FRAMEWORK_TYPE "$PROJ_NAME.$FRAMEWORK_EXTENSION" \
    -scheme $SCHEME_NAME \
    -configuration Release \
    -destination 'generic/platform=iOS' \
    -archivePath $PHYSICAL_DEVICES_ARCHIVE_PATH SKIP_INSTALL=NO && \
    echo "• [Sliced] {Physical Devices} - Success! •"
}

sliceForSimulatedDevices() {
    xcodebuild archive -$FRAMEWORK_TYPE "$PROJ_NAME.$FRAMEWORK_EXTENSION" \
    -scheme $SCHEME_NAME \
    -configuration Release \
    -destination 'generic/platform=iOS Simulator' \
    -archivePath $SIMULATED_DEVICES_ARCHIVE_PATH SKIP_INSTALL=NO && \
    echo "• [Sliced] {Simulated Devices} - Success! •"
}


createXCFrameworkExcludingAMacCatalystSlice() {
    sliceForPhysicalDevices && \
    sliceForSimulatedDevices && \
    xcodebuild -create-xcframework \
    -framework "$PHYSICAL_DEVICES_ARCHIVE_PATH/$ARCHIVE_FRAMEWORK_PATH1" \
    -framework "$SIMULATED_DEVICES_ARCHIVE_PATH/$ARCHIVE_FRAMEWORK_PATH1" \
    -output "$XCFRAMEWORK_OUTPUT_PATH/sqlcipher.xcframework" && \
    xcodebuild -create-xcframework \
    -framework "$PHYSICAL_DEVICES_ARCHIVE_PATH/$ARCHIVE_FRAMEWORK_PATH" \
    -framework "$SIMULATED_DEVICES_ARCHIVE_PATH/$ARCHIVE_FRAMEWORK_PATH" \
    -output "$XCFRAMEWORK_OUTPUT_PATH/$FRAMEWORK_NAME.xcframework" && \
    echo "• [XCFramework] {Created} - Success! •" && ls $XCFRAMEWORK_OUTPUT_PATH
}


buildExcludingMacCatalystSlice() {
    restart && \
    createXCFrameworkExcludingAMacCatalystSlice && \
    sleep 2 && clear && \
    echo "• [XCFramework] {Creation} - Completed! •" && echo "XCFramework Can Be Located At: $XCFRAMEWORK_OUTPUT_PATH": `ls $XCFRAMEWORK_OUTPUT_PATH` 
}


buildExcludingMacCatalystSlice
