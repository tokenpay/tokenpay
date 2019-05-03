# How to generate the installer using docker :

## Build the docker image

```
cd distrib_folder
docker build --tag=tpay .  
```

## Retrieve the installer from the image 

### Run an interactive image :

```bash
docker run -ti tpay /bin/bash
```

### Retrieve the image name

```bash
docker ps
```

### Retrieve the install archive 

```bash
docker cp image_name:/TOKENPAY_INSTALLER_distrib_name_x86-x64.tar.gz .
```

# How to install TPAY wallet using the install archive :

```bash
tar xzf TOKENPAY_INSTALLER_distrib_name_x86-x64.tar.gz
cd TOKENPAY_INSTALLER_distrib_name_x86-x64
chmod +x install.sh
sudo ./install.sh # This operation will take several minutes, depending on your connection
```

