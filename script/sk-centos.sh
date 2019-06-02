#!/bin/sh

yum update -y

cd /etc/yum.repos.d/
wget http://download.opensuse.org/repositories/shells:fish:release:2/CentOS_7/shells:fish:release:2.repo
yum install fish -y

cd ~
yum install vim net-tools wget gcc git autoconf automake libtool ncurses-devel ncurses -y
yum install openssl-devel -y

yum group install "Development Tools" -y



# Download netperf
cd ~
wget https://fossies.org/linux/misc/netperf-2.7.0.tar.gz
tar -zxvf netperf-2.7.0.tar.gz
cd netperf-2.7.0/
./autogen.sh
./configure
make
make install


# Download sockperf
cd ~
git clone https://github.com/Mellanox/sockperf.git
cd sockperf/ && ./autogen.sh && ./configure && make && make install




