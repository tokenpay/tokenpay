FROM raspbian/stretch:latest

#dependencies
RUN apt-get update
RUN apt-get install -y build-essential \
     libtool autotools-dev automake \
     pkg-config zlib1g-dev libevent-dev \
     bsdmainutils git libboost-all-dev \
     libseccomp-dev libcap-dev libminiupnpc-dev \
     libqt5gui5 libqt5core5a libqt5webkit5-dev \
     libqt5dbus5 qttools5-dev qttools5-dev-tools \
     libprotobuf-dev protobuf-compiler libqrencode-dev \
     libssl-dev qt5-default g++-6 gcc-6

RUN rm /usr/bin/g++ && rm /usr/bin/gcc
RUN ln -s /usr/bin/g++-6 /usr/bin/g++
RUN ln -s /usr/bin/gcc-6 /usr/bin/gcc

RUN apt-get install -y wget

#openssl
RUN wget https://www.openssl.org/source/openssl-1.1.0e.tar.gz && tar xzf openssl-1.1.0e.tar.gz;
RUN cd openssl-1.1.0e && ./config -Wl,--enable-new-dtags,-rpath,'$(LIBRPATH)' \
	&& make && make install

#tpay
RUN git clone --recurse-submodules https://github.com/tokenpay/tokenpay
RUN cd tokenpay && \ 
	./autogen.sh && \
    ./configure --enable-gui && \
	make

#make the ARM installer
RUN mkdir TPAY_INSTALLER_ARM
RUN cd TPAY_INSTALLER_ARM && \
	cp /tokenpay/src/tokenpay . && \
	cp /tokenpay/src/tokenpayd . && \
	cp /openssl-1.1.0e/libcrypto.so.1.1 . && \
	cp /openssl-1.1.0e/libssl.so.1.1 . && \
	cp /tokenpay/src/qt/res/icons/tokenpay_icon.png .

RUN touch /TPAY_INSTALLER_ARM/tokenpay.conf
RUN touch /TPAY_INSTALLER_ARM/tokenpay.desktop

#build the tokenpay.desktop
RUN echo "#!/usr/bin/env xdg-open" > /TPAY_INSTALLER_ARM/tokenpay.desktop && \
    echo "[Desktop Entry]" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Version=1.0" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Type=Application" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Terminal=false" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Exec=tokenpay" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Name=TokenPay Wallet" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Comment=TokenPay Wallet" >> /TPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Icon=/usr/share/icons/tokenpay_icon.png" >> /TPAY_INSTALLER_ARM/tokenpay.desktop

# build the install.sh script
RUN echo "#!/bin/sh" > /TPAY_INSTALLER_ARM/install.sh

RUN echo "TPAY_LIBS=./*.so*" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAYD_BIN=./tokenpayd" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_BIN=./tokenpay" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_ICO=./tokenpay_icon.png" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_DSK=./tokenpay.desktop" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "TPAY_LIBPATH=/usr/lib/" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_BINPATH=/usr/bin/" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_ICOPATH=/usr/share/icons/" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_DSKPATH=~/.local/share/applications/" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "apt-get install -y build-essential \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libtool autotools-dev automake \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "pkg-config zlib1g-dev libevent-dev \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "bsdmainutils git libboost-all-dev \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libseccomp-dev libcap-dev libminiupnpc-dev \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libqt5gui5 libqt5core5a libqt5webkit5-dev \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libqt5dbus5 qttools5-dev qttools5-dev-tools \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libprotobuf-dev protobuf-compiler libqrencode-dev \\" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "libssl-dev qt5-default" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying dependencies to \${TPAY_LIBPATH} :\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "for i in \${TPAY_LIBS}; do" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "echo \"- copying \${i}\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${i} \${TPAY_LIBPATH}" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "done" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay binary to \${TPAY_BINPATH} :\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpayd binary to \${TPAY_BINPATH} :\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay icon to \${TPAY_ICOPATH} :\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_ICO} \${TPAY_ICOPATH}" >> /TPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay.desktop to \${TPAY_DSKPATH}\"" >> /TPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_DSK} \${TPAY_DSKPATH}" >> /TPAY_INSTALLER_ARM/install.sh

# build the installer archive
RUN tar czf TOKENPAY_INSTALLER_ARM.tar.gz TPAY_INSTALLER_ARM
