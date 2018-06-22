## Specification

Specification | Value
--- | ---
Protocol | **PoSv3**
Block Time | **60 seconds**
Difficulty Re-target | **10 minutes**
Nominal Stake Interest | **5% annually for the first year and 1% after**
Min Stake Age | **2 hours** (no max age)
P2P Port | 8800
RPC Port | 8801
Blockchain Explorer | [Website](http://explorer.tpay.ai)


### Testnet

Specification | Value
--- | ---
Testnet RPC Port | 16600
Testnet P2P Port | 16601
Testnet Coinbase Maturity | 10
Testnet Min Stake Age | 10


### Transactions

| Specification   | Value          |
| --------------- | -------------- |
| Min Fee         | **0.0001 TPAY** |
| Confirmations   | **6**         |
| Maturity        | **100**        |

# Inside:

  * Tor Network on start up
  * Ring Signatures for anonymous transactions
  * Dual key stealth addresses
  * ‘Zero Knowledge’ proofs
  * Full decentralization

# LINKS

  * [Official Website](http://www.tokenpay.com/)



# Wallet Download Links

## Desktop Wallet
- Latest (https://tokenpay.app.box.com/v/tokenpaywindowswallet)

## MAC Wallet 
- Latest (https://tokenpay.app.box.com/v/TokenPayMACWallet)

## Android Wallet
- Latest (https://play.google.com/store/apps/details?id=com.tokenpay.wallet&hl=en)


## Useful Paths

### Windows
```
%appdata%\TokenPay
```

### OSX
```
~/Library/Application Support/TokenPay/ 
```


# Installing TokenPay

TokenPay has snaps available [with GUI](https://snapcraft.io/tokenpay) and [without GUI](https://snapcraft.io/tokenpayd-v2). Snaps are universal Linux packages that should run on any modern Linux distribution. Consult the [documentation for your own distribution](https://docs.snapcraft.io/core/install) to find out how to install ```snapd``` and gain access to the [snap store](https://snapcraft.io/store)

If you are interested in installing and running the daemon, run:

```bash
sudo snap install tokenpayd-v2
```

Which will install just the daemon, without GUI. This is useful if you are planning on running TokenPay on a server. Desktop users will probably be more comfortable running the GUI version. You can install the GUI version by running:

```bash
sudo snap install tokenpay
```

Both snaps are built using the ```strict``` confinement setting. That means that the wallet itself will only have access to the network and just a few folders on disk. Everything else is restricted to the binary itself, but it has enough access to the system to perform its function, while keeping you safe.

The strict confinement level also means that the config files, and therefor the wallet file will be situated in:

```bash
# The GUI snap will save its files in:
$HOME/snap/tokenpay/current/.tokenpay

# The daemon snap will save its file sin:
$HOME/snap/tokenpayd-v2/current/.tokenpay

```

# Building TokenPay (including GUI)

It's worth mentioning that you only have to build from source, if you are testing a change, or if you simply prefer it that way. Otherwise, simply follow the above instructions to get up and running.



## Generic Unix build instructions

It's recommended you use Ubuntu 18.04, which already has the needed build dependencies, and their proper version in the official repositories. If you are running on Ubuntu 16.04, you will need to install an updated version of ```OpenSSL``` and ```Boost```. 



### Clone the repository

Install git:

```bash
sudo apt-get install git
```

Clone the repository:

```bash
# Create a workspace
mkdir $HOME/build
cd $HOME/build

git clone --recurse-submodules https://github.com/tokenpay/tokenpay
cd $HOME/build/tokenpay
```



### Install dependencies

Run the following command to install the needed dependencies:

```bash
sudo apt-get install build-essential \
     libtool autotools-dev automake \
     pkg-config zlib1g-dev libevent-dev \
     bsdmainutils git libboost-all-dev \
     libseccomp-dev libcap-dev libminiupnpc-dev \
     libqt5gui5 libqt5core5a libqt5webkit5-dev \
     libqt5dbus5 qttools5-dev qttools5-dev-tools \
     libprotobuf-dev protobuf-compiler libqrencode-dev \
     libssl-dev qt5-default
```




### Compile Tokenpay

Configure the toolchain:

```bash
./autogen.sh
./configure --enable-gui
```

Compile the code:

```bash
make -j8
```

The ```-j``` option specifies the number of compile jobs to run in parallel. I usually run 2 jobs per CPU core. So if you are sporting a quad core CPU, feel free to use ```-j8```. Otherwise, adapt this value to whatever works best for your setup.

After the build process completes, you should have two binaries in the ```src``` folder:

  * tokenpayd - just the daemon, no GUI
  * tokenpay - GUI version

Simply copy any one of these in your ```$PATH```.


# Building TokenPay snap packages

This is the preferred way of building TokenPay. At the end of this process, you will have a universal package that you can copy to any modern Linux distribution and install it without worrying about dependencies. Snaps are self contained packages, that include all needed dependencies.

## Prepare the build environment

### Install LXD and snapcraft

[LXD](https://linuxcontainers.org/) is the evolution of ```LXC```, which stands for ```linux containers```. It allows us to safely build the code inside a disposable container, that gets torn down after the package gets generated. Don't worry, the process is automatic, but we do need to install LXD first. Feel free to [check the documentation specific for your distribution](https://linuxcontainers.org/lxd/getting-started-cli/) and install ```LXD```.

For Ubuntu 18.04, the installation process is straight forward. Install ```zfsutils```:

```bash
sudo apt-get install zfsutils-linux
```

Then we can install and initialize ```LXD```:

```bash
sudo snap install lxd
```

Configure ```LXD```:

```bash
sudo lxd init
```

Simply follow the wizard. In most cases, defaults should be enough.

Now time to install ```snapcraft```:

```bash
sudo snap install --classic snapcraft
``` 

### Build the snaps

At this point you should have everything you need to build the snap. So let's get cracking.

There is a ```snap``` folder inside the source tree, that has two ```snapcraft``` recipes and assets needed to generate the packages. Change directory to this folder: 

```bash
cd $HOME/build/tokenpay/snap
```

Snapcraft looks for a file called ```snapcraft.yaml``` in the current folder. It uses that file to generate the package from scratch. To build the GUI version, we must link or copy the appropriate recipe to ```snapcraft.yaml```:

```bash
ln -s snapcraft-gui.yaml snapcraft.yaml
```

Now all we have to do is run:

```bash
snapcraft cleanbuild
```

This will spawn a temporary container running Ubuntu 16.04, build any needed dependencies, then TokenPay, and in the end, generate a snap package. After the process is complete, the snap package will be copied over to your current folder, and the temporary container will be deleted.

### Installing the generated packages

Installing packages from outside the snap store requires an extra flag:

```bash
# For the GUI version
sudo snap install --dangerous tokenpay_1.0_amd64.snap

# For the non GUI version
sudo snap install --dangerous tokenpayd_1.0_amd64.snap
```


# Contribute

TokenPay is controlled by all TokenPay users around the world. If you are a developer, you can use your super-powers to do good and contribute. The TokenPay project is hosted on GitHub. This is where developers work hard on the next version(s) of the software. To get involved with developing TokenPay, check out our detailed contributing guidelines. We credit all contributors to the TokenPay project in every major and minor release.

If you think you've found a bug or a problem with TokenPay, please let us know! First, search our issue tracker to search to see if someone has already reported the problem. If they haven't, click here to open a new issue, and fill out the template with as much information as possible. The more you can tell us about the problem and how it occurred, the more likely we are to fix it.

### Please do not report security vulnerabilities publicly.

## How to report a bug
 
### Security-related issues

Contact the developers privately by sending an e-mail to Team@tokenpay.com with the details of the issue. Do not post the issue on github or anywhere else until the issue has been resolved.

### Code issues

We would strongly prefer if you create a pull-request on Github in the proper repository with the necessary fix.