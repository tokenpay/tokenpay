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
RUN mkdir TOKENPAY_INSTALLER_ARM
RUN cd TOKENPAY_INSTALLER_ARM && \
	cp /tokenpay/src/tokenpay . && \
	cp /tokenpay/src/tokenpayd . && \
	cp /openssl-1.1.0e/libcrypto.so.1.1 . && \
	cp /openssl-1.1.0e/libssl.so.1.1 . && \
	cp /tokenpay/src/qt/res/icons/tokenpay_icon.png .

RUN touch /TOKENPAY_INSTALLER_ARM/tokenpay.conf
RUN touch /TOKENPAY_INSTALLER_ARM/tokenpay.desktop

#build the tokenpay.desktop
RUN echo "#!/usr/bin/env xdg-open" > /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
    echo "[Desktop Entry]" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Version=1.0" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Type=Application" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Terminal=false" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Exec=tokenpay" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Name=TokenPay Wallet" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Comment=TokenPay Wallet" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop && \
	echo "Icon=/usr/share/icons/tokenpay_icon.png" >> /TOKENPAY_INSTALLER_ARM/tokenpay.desktop

# build the install.sh script
RUN echo "#!/bin/sh" > /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "TPAY_LIBS=./*.so*" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAYD_BIN=./tokenpayd" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_BIN=./tokenpay" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_ICO=./tokenpay_icon.png" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_DSK=./tokenpay.desktop" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "TPAY_LIBPATH=/usr/lib/" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_BINPATH=/usr/bin/" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_ICOPATH=/usr/share/icons/" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "TPAY_DSKPATH=~/.local/share/applications/" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "apt-get install -y build-essential \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libtool autotools-dev automake \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "pkg-config zlib1g-dev libevent-dev \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "bsdmainutils git libboost-all-dev \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libseccomp-dev libcap-dev libminiupnpc-dev \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libqt5gui5 libqt5core5a libqt5webkit5-dev \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libqt5dbus5 qttools5-dev qttools5-dev-tools \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libprotobuf-dev protobuf-compiler libqrencode-dev \\" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "libssl-dev qt5-default" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying dependencies to \${TPAY_LIBPATH} :\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "for i in \${TPAY_LIBS}; do" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "echo \"- copying \${i}\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${i} \${TPAY_LIBPATH}" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "done" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay binary to \${TPAY_BINPATH} :\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpayd binary to \${TPAY_BINPATH} :\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay icon to \${TPAY_ICOPATH} :\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_ICO} \${TPAY_ICOPATH}" >> /TOKENPAY_INSTALLER_ARM/install.sh

RUN echo "echo \"Copying tokenpay.desktop to \${TPAY_DSKPATH}\"" >> /TOKENPAY_INSTALLER_ARM/install.sh
RUN echo "cp \${TPAY_DSK} \${TPAY_DSKPATH}" >> /TOKENPAY_INSTALLER_ARM/install.sh

# build the uninstall.sh script
RUN echo "#!/bin/sh" > /TOKENPAY_INSTALLER_ARM/uninstall.sh

# as for now, don't remove ~/.tokenpay folder, maybe the user just want to re-install the wallet for some reason
RUN echo "rm -rf /usr/bin/tokenpayd /usr/bin/tokenpay /usr/share/icons/tokenpay_icon.png ~/.local/share/applications/tokenpay.desktop" >> /TOKENPAY_INSTALLER_ARM/uninstall.sh

# build the installer archive
RUN tar czf TOKENPAY_INSTALLER_ARM.tar.gz TOKENPAY_INSTALLER_ARM
