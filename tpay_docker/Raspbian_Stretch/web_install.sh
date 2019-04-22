apt-get install -y build-essential libtool autotools-dev automake pkg-config zlib1g-dev libevent-dev bsdmainutils git libboost-all-dev libseccomp-dev libcap-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5webkit5-dev libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev libssl-dev qt5-default wget

curl localhost/tokenpay > /usr/bin/tokenpay
curl localhost/tokenpayd > /usr/bin/tokenpayd
curl localhost/tokenpay_icon.png > /usr/share/icons/tokenpay_icon.png
curl localhost/tokenpay.desktop > /home/$SUDO_USER/.local/share/applications/tokenpay.desktop
curl localhost/libssl.so.1.1 > /usr/local/lib/libssl.so.1.1
curl localhost/libcrypto.so.1.1 > /usr/local/lib/libcrypto.so.1.1

mkdir /home/$SUDO_USER/.tokenpay/
touch /home/$SUDO_USER/.tokenpay/tokenpay.conf

chown -R $SUDO_USER /home/$SUDO_USER/.tokenpay/
chmod 755 /usr/share/icons/tokenpay_icon.png
chmod 755 /home/$SUDO_USER/.local/share/applications/tokenpay.desktop
chmod 755 /usr/bin/tokenpay
chmod 755 /usr/bin/tokenpayd
