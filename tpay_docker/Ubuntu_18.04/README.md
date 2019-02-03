# How to generate the installer using docker :

1. Build the docker image

docker build --tag=tpay .  

2. Retrieve the installer from the image 

* Run an interactive image :

```bash
docker run -ti tpay /bin/bash
```

* Retrieve the image name

```bash
docker ps
```

* Retrieve the install archive 

```bash
docker cp serene_boyd:/TOKENPAY_INSTALLER_x86-x64.tar.gz .
```

# How to install TPAY wallet using the install archive :

```bash
tar xzf TOKENPAY_INSTALLER_x86-x64.tar.gz
cd TPAY_INSTALLER_x86-x64.tar.gz
chmod +x install.sh
sudo ./install.sh # This operation will take several minutes, depending on your connection
```

