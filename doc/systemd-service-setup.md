# Setting up systemd service

## Before you begin

If you are planning on running tokenpayd on a server, then you will probably want to set up a system service to automatically start the wallet when the system boots, and make sure that process stays up. On most modern GNU/Linux systems you can do this by simply creating a [systemd unit file](https://www.freedesktop.org/software/systemd/man/systemd.service.html).

Before we begin, we need to make sure the wallet is compiled for your system, and available in your ```$PATH```. If you have not done so already, please refer to the [README](https://github.com/tokenpay/tokenpay/blob/master/README.md#unix-build-instructions) on how to build tokenpay. Alternatively, if you are running on a x86_64 machine, and [snapd](https://docs.snapcraft.io/core/snapd) is available on your distribution, you may install tokenpayd [using the snap packages](https://github.com/tokenpay/tokenpay/blob/master/README.md#installing-tokenpay-via-snapcraft) available in the snap store.


## Creating a new user

While ```tokenpayd``` will happily run as any user on your system, it is usually a good practice to use an unprivileged user to run services. Feel free to skip this step.

The following will guide you through creating and using a new ```tokenpay``` user.


```
sudo useradd -m tokenpay -s /bin/false
```

The ```-m``` flag instructs ```useradd``` to create a home folder for this user.

## Creating the tokenpay config

The ```tokenpayd``` daemon requires that a ```RPC``` user and password be set in the config, before the daemon will be able to start. These credentials are used by tokenpayd to allow queries to its [RPC interface](https://github.com/tokenpay/tokenpay/blob/master/doc/RPC%20Commands.md).

Create the tokenpay config folder:

```bash
sudo mkdir /home/tokenpay/.tokenpay
```

If you prefer to use another user instead of the ```tokenpay``` user created in the previous step, make sure you change the path to the appropriate home folder.

Generate a new password and add it to the config file:

```bash
RPC_PASSWD=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1`
echo rpcuser=tokenpayrpc | sudo tee -a /home/tokenpay/.tokenpay/tokenpay.conf 
echo rpcpassword=$RPC_PASSWD | sudo tee -a /home/tokenpay/.tokenpay/tokenpay.conf 
```

Verify that the config has been created:

```bash
$ cat /home/tokenpay/.tokenpay/tokenpay.conf
rpcuser=tokenpayrpc
rpcpassword=Z43zPaxupRIv2g3DZLEds47mzpEN079G
```

This is just an example of a randomly generated password, but feel free to use whichever values you wish.

Change the permissions on the config folder:

```bash
sudo chown tokenpay:tokenpay -R /home/tokenpay/.tokenpay
```

## Create the systemd unit file

We need to identify the full path to the ```tokenpayd``` binary. If you compiled tokenpay yourself, all you need to do is copy the ```tokenpayd``` binary somewhere in your ```$PATH```.

```bash
sudo cp src/tokenpayd /usr/local/bin
sudo chmod +x /usr/local/bin/tokenpayd
# remove debug symbols. Makes the binary considerably smaller.
sudo strip /usr/local/bin/tokenpayd
```

If you already have ```tokenpayd``` copied in your ```$PATH```, the you can get the absolute path to the binary by running:


```bash
$ which tokenpayd
/usr/local/bin/tokenpayd
```

Create a new unit file in ```/lib/systemd/system/tokenpayd.service``` with the following contents:

```ini
[Unit]
Description=TokenPay wallet
After=network-online.target

[Service]
Type=simple
# Make sure the path to the tokenpayd binary is
# correct for both ExecStart and ExecStop
ExecStart=/usr/local/bin/tokenpayd
ExecStop=/usr/local/bin/tokenpayd stop
# Always restart the daemon, even if it exits with a
# non error status code
Restart=always
# Restart interval. Default is 100ms.
RestartSec=5s
# Change this to the user you want the wallet
# daemon to run under
User=tokenpay

[Install]
WantedBy=multi-user.target
```

Make sure that the ```ExecStart```, ```ExecStop``` and ```User``` values are correct. There is also a sample unit file in the contrib folder of this repository.

Reload the systemd daemon. This will pick up the new unit file:

```bash
sudo systemctl daemon-reload
```

Enable the ```tokenpayd``` service:

```bash
sudo systemctl enable tokenpayd
```

Start the ```tokenpayd``` service:

```bash
sudo systemctl start tokenpayd
```

Check the status of ```tokenpayd```:

```bash
sudo systemctl status tokenpayd
```

If you do a:

```bash
ps aux | grep tokenpayd
```

You should see the wallet running under the user you specified in the ```User=``` setting of the ```systemd``` unit file.

## Connect to your tokenpay wallet

In previous steps we created a separate user to run the wallet. This is optional of course, but it is good practice. If you did not opt to create a separate user for the wallet service, then you can skip this section. If you created a new user however, follow these steps to enable your current user to connect to the ```tokenpayd``` wallet.

The config file we created above contains two values: ```rpcuser``` and ```rpcpassword```. The wallet uses those values in two ways:

  * In wallet mode, to only allow access to the RPC interface to users that know the correct user and password
  * In client mode, where the binary uses these 2 values to authenticate against the daemon process running in the background

Considering that the wallet is running under its own unprivileged user, the tokenpay config we created above is only accessible to the user under which the wallet is running. To be able to access the wallets RPC we need to copy that config to our own home folder:


```
mkdir $HOME/.tokenpay
sudo cp /home/tokenpay/.tokenpay/tokenpay.conf $HOME/.tokenpay/
sudo chown $USER -R $HOME/.tokenpay/
```

Now validate that you can connect to the wallet:

```bash
tokenpayd getinfo
```

If you get a valid response, you are all set up. See [the RPC reference](https://github.com/tokenpay/tokenpay/blob/master/doc/RPC%20Commands.md) for more details on how to use tokenpay command line wallet.

### Notes for running the daemon from snaps

If you installed ```tokenpay``` from a snap, then the daemon binary is situated in:

```
/snap/bin/tokenpayd-v2
```

Please note, that if you used a snap package, the config folder location differs from the above steps. The easiest way to set the environment up when using a snap, is to temporarily enable the shell for the ```tokenpay``` user and run the daemon once:

```bash
# enable a shell for the tokenpay user
sudo chsh -s /bin/bash tokenpay

# switch user to tokenpay
sudo su - tokenpay

# Run the tokenpay command and wait for it to exit
/snap/bin/tokenpayd-v2

# logout
exit

# change shell back to false
sudo chsh -s /bin/false tokenpay
```

You should now have a folder in:

```bash
/home/tokenpay/snap/tokenpayd-v2/current/.tokenpay
```

This will be the location in which you need to create the config, with the RPC user and password. The rest of the steps are identical.

