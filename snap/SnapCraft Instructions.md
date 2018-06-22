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
