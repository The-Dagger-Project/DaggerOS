# DaggerOS
DaggerOS is a hobbyist, Unix-like OS built from scratch. It is still in production, and has limited features.

# Download and Install
You can download the ISO from the releases page.

## Build from source
### 1- Requirements
```bash
gcc 
g++ 
GNU Make 
bison (GNU Bison) 
flex 
libgmp3-dev/stable,stable,now 2:6.1.2+dfsg-1 amd64
libmpfr-dev/stable,stable 3.1.5-1 amd64
libisl-dev/stable,stable 0.18-1 amd64
libcloog-isl-dev/stable,stable 0.18.4-1+b1 amd64
libmpc-dev/stable,stable 1.0.3-1+b2 amd64
texinfo/stable,stable,now 6.3.0.dfsg.1-1+b2 amd64
binutils/stable,stable,now 2.28-5 amd64 [installato]
binutils-arm-linux-gnueabi/stable,stable,now 2.28-5 amd64
libgcj17/stable,stable,now 6.3.0-18 amd64 
xorriso
```

### 2- Build cross-compiler
Make a directory at $HOME called src:
```bash
mkdir $HOME/src
cd $HOME/src
```
Run the following commands:
```bash
export PREFIX="$HOME/src"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```
Now we must build binutils and GCC from source.
```bash
cd $HOME/src
mkdir build-binutils
cd build-binutils
git clone git://sourceware.org/git/binutils-gdb.git
cd binutils-gdb
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```

```bash
cd $HOME/src
mkdir build-gcc
cd build-gcc
git clone https://github.com/gcc-mirror/gcc
cd gcc
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make install gcc
```
The cross compiler is now at $HOME/opt/cross/bin. Run the following to add it to PATH:
```bash
export PATH="$HOME/opt/cross/bin:$PATH"
```

### 3- Clone this repo
Clone this repo in a suitable directory:
```bash
git clone https://github.com/The-Dagger-Project/DaggerOS.git
```

### 4- Setup shell scripts
There are 8 shell scripts '.sh' files in the `scripts/` directory of the repo. Make them executable by running:
```bash
chmod +x build.sh
chmod +x clean.sh
chmod +x config.sh
chmod +x default-host.sh
chmod +x headers.sh.sh
chmod +x iso.sh
chmod +x qemu.sh
chmod +x target-triplet-to-arch.sh
```
Then run them. (./build.sh, etc.)

### 5- Run the image
If you set up everything correctly, you should be able to run ./qemu.sh and see the iso image running in QEMU.

# Issues
Please see our Github Repo's issues page.

# Community
Join our Discord server: [https://discord.gg/a558y75tXG](https://discord.gg/a558y75tXG)

# Screenshots
![DaggerOS Boot menu](/images/daggeros-grub.png)
![DaggerOS Welcome](/images/daggeros-welcome.png)
