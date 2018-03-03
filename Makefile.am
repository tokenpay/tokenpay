ACLOCAL_AMFLAGS = -I m4

if OS_WINDOWS_CROSSCOMPILE
# for leveldb
AM_MAKEFLAGS = TARGET_OS=OS_WINDOWS_CROSSCOMPILE
endif

export CC CXX AR LD
SUBDIRS = tor db4.8/build_unix leveldb src

TokenPay.app: all-am
	mkdir -p TokenPay.app/Contents/{MacOS,Resources}
	cp Info.plist TokenPay.app/Contents
	cp tokenpay.icns TokenPay.app/Contents/Resources
	cp src/tokenpay TokenPay.app/Contents/MacOS/TokenPay
	echo "APPL????" > TokenPay.app/Contents/PkgInfo
	@MACDEPLOYQT@ TokenPay.app @MACDEPLOYQT_LIBPATH@ 

.PHONY: tokenPay.app
