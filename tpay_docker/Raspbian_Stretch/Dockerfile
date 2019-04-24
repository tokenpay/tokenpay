FROM raspbian/stretch:latest

# install name
ARG install_name=TOKENPAY_INSTALLER_RASPBIAN_ARM64

# system dependant paths
ARG bin_path=/usr/bin
ARG icon_path=/usr/share/icons
ARG desktop_path=~/.local/share/applications

# filenames to copy to install folder
ARG fname_install=install.sh
ARG fname_uninstall=uninstall.sh
ARG fname_desktop=tokenpay.desktop
ARG fname_icon=tokenpay_icon.png
ARG fname_guiwallet=tokenpay
ARG fname_deamonwallet=tokenpayd
ARG fname_ssl=libssl.so.1.1
ARG fname_crypto=libcrypto.so.1.1
ARG fname_webinstall=web_install.sh

# parallel build or not, tune this if need be (use -j1 on rpi, else it'll crash)
ARG parralel_build=-j1

# package manager
ARG pckg_manager=apt-get

# package list
ARG apt_pckg_list="build-essential \
     libtool autotools-dev automake \
     pkg-config zlib1g-dev libevent-dev \
     bsdmainutils git libboost-all-dev \
     libseccomp-dev libcap-dev libminiupnpc-dev \
     libqt5gui5 libqt5core5a libqt5webkit5-dev \
     libqt5dbus5 qttools5-dev qttools5-dev-tools \
     libprotobuf-dev protobuf-compiler libqrencode-dev \
     libssl-dev qt5-default g++-6 gcc-6 wget"

# dependencies
RUN apt-get update
RUN apt-get install -y ${apt_pckg_list}

RUN rm /usr/bin/g++ && rm /usr/bin/gcc
RUN ln -s /usr/bin/g++-6 /usr/bin/g++
RUN ln -s /usr/bin/gcc-6 /usr/bin/gcc

# openssl
RUN wget https://www.openssl.org/source/openssl-1.1.0e.tar.gz && tar xzf openssl-1.1.0e.tar.gz;
RUN cd openssl-1.1.0e && ./config -Wl,--enable-new-dtags,-rpath,'$(LIBRPATH)' \
	&& make && make install

# tpay
RUN git clone --recurse-submodules https://github.com/tokenpay/tokenpay
RUN cd tokenpay && \ 
	./autogen.sh && \
    ./configure --enable-gui && \
	make

# make the ARM installer
RUN mkdir /${install_name}
RUN cd /${install_name} && \
	strip --strip-debug /tokenpay/src/${fname_guiwallet} && \
	strip --strip-debug /tokenpay/src/${fname_deamonwallet} && \
	cp /tokenpay/src/${fname_guiwallet} . && \
	cp /tokenpay/src/${fname_deamonwallet} . && \
	cp /openssl-1.1.0e/${fname_crypto} . && \
	cp /openssl-1.1.0e/${fname_ssl} . && \
	cp /tokenpay/src/qt/res/icons/${fname_icon} .

# leave this file blank
RUN touch /${install_name}/tokenpay.conf

# build the tokenpay.desktop
RUN touch /${install_name}/${fname_desktop}
RUN echo "#!/usr/bin/env xdg-open" > /${install_name}/${fname_desktop} && \
    echo "[Desktop Entry]" >> /${install_name}/${fname_desktop} && \
	echo "Version=1.0" >> /${install_name}/${fname_desktop} && \
	echo "Type=Application" >> /${install_name}/${fname_desktop} && \
	echo "Terminal=false" >> /${install_name}/${fname_desktop} && \
	echo "Exec=tokenpay" >> /${install_name}/${fname_desktop} && \
	echo "Name=TokenPay Wallet" >> /${install_name}/${fname_desktop} && \
	echo "Comment=TokenPay Wallet" >> /${install_name}/${fname_desktop} && \
	echo "Icon=${icon_path}/${fname_icon}" >> /${install_name}/${fname_desktop}

#  build the ${fname_install} script
RUN echo "#!/bin/sh" > /${install_name}/${fname_install}

RUN echo "TPAYD_BIN=./${fname_deamonwallet}" >> /${install_name}/${fname_install}
RUN echo "TPAY_BIN=./${fname_guiwallet}" >> /${install_name}/${fname_install}
RUN echo "TPAY_ICO=./${fname_icon}" >> /${install_name}/${fname_install}
RUN echo "TPAY_DSK=./${fname_desktop}" >> /${install_name}/${fname_install}
RUN echo "TPAY_BINPATH=${bin_path}" >> /${install_name}/${fname_install}
RUN echo "TPAY_ICOPATH=${icon_path}" >> /${install_name}/${fname_install}
RUN echo "TPAY_DSKPATH=${desktop_path}" >> /${install_name}/${fname_install}
RUN echo "TPAY_LIBPATH=/usr/lib/" >> /${install_name}/${fname_install}

RUN echo "${pckg_manager} install -y ${apt_pckg_list}" >> /${install_name}/${fname_install}

# copy crypto libs to /usr/lib
RUN echo "echo \"Copying crypto libs to \${TPAY_LIBPATH} :\"" >> /${install_name}/${fname_install}
RUN echo "cp ./${fname_crypto} \${TPAY_LIBPATH}" >> /${install_name}/${fname_install}
RUN echo "cp ./${fname_ssl} \${TPAY_LIBPATH}" >> /${install_name}/${fname_install}

RUN echo "echo \"Copying tokenpay binary to \${TPAY_BINPATH} :\"" >> /${install_name}/${fname_install}
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /${install_name}/${fname_install}

RUN echo "echo \"Copying tokenpayd binary to \${TPAY_BINPATH} :\"" >> /${install_name}/${fname_install}
RUN echo "cp \${TPAY_BIN} \${TPAY_BINPATH}" >> /${install_name}/${fname_install}

RUN echo "echo \"Copying tokenpay icon to \${TPAY_ICOPATH} :\"" >> /${install_name}/${fname_install}
RUN echo "cp \${TPAY_ICO} \${TPAY_ICOPATH}" >> /${install_name}/${fname_install}

RUN echo "echo \"Copying tokenpay.desktop to \${TPAY_DSKPATH}\"" >> /${install_name}/${fname_install}
RUN echo "cp \${TPAY_DSK} \${TPAY_DSKPATH}" >> /${install_name}/${fname_install}

#  build the ${fname_uninstall} script
RUN echo "#!/bin/sh" > /${install_name}/${fname_uninstall}

#  as for now, don't remove ~/.tokenpay folder, maybe the user just want to re-install the wallet for some reason
RUN echo "rm -rf ${bin_path}/${fname_deamonwallet} ${bin_path}/${fname_guiwallet} ${icon_path}/${fname_icon} ${desktop_path}/${fname_desktop}" >> /${install_name}/${fname_uninstall}

# build the web install script
RUN echo "apt-get install -y build-essential libtool autotools-dev automake pkg-config zlib1g-dev libevent-dev bsdmainutils git libboost-all-dev libseccomp-dev libcap-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5webkit5-dev libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev libssl-dev qt5-default wget" > ${install_name}/${fname_webinstall}

RUN echo "curl localhost/tokenpay > /usr/bin/tokenpay">> ${install_name}/${fname_webinstall}
RUN echo "curl localhost/tokenpayd > /usr/bin/tokenpayd">> ${install_name}/${fname_webinstall}
RUN echo "curl localhost/tokenpay_icon.png > /usr/share/icons/tokenpay_icon.png">> ${install_name}/${fname_webinstall}
RUN echo "curl localhost/tokenpay.desktop > /home/\$SUDO_USER/.local/share/applications/tokenpay.desktop">> ${install_name}/${fname_webinstall}
RUN echo "curl localhost/libssl.so.1.1 > /usr/local/lib/libssl.so.1.1">> ${install_name}/${fname_webinstall}
RUN echo "curl localhost/libcrypto.so.1.1 > /usr/local/lib/libcrypto.so.1.1">> ${install_name}/${fname_webinstall}
RUN echo "mkdir /home/\$SUDO_USER/.tokenpay" >> ${install_name}/${fname_webinstall}
RUN echo "touch /home/\$SUDO_USER/.tokenpay/tokenpay.conf">> ${install_name}/${fname_webinstall}
RUN echo "chown -R \$SUDO_USER /home/\$SUDO_USER/.tokenpay/">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /usr/share/icons/tokenpay_icon.png">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /home/\$SUDO_USER/.local/share/applications/tokenpay.desktop">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /usr/bin/tokenpay">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /usr/bin/tokenpayd">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /usr/local/lib/libssl.so.1.1">> ${install_name}/${fname_webinstall}
RUN echo "chmod 755 /usr/local/lib/libcrypto.so.1.1">> ${install_name}/${fname_webinstall}

#  build the installer archive
RUN tar czf ${install_name}.tar.gz ${install_name}
	
