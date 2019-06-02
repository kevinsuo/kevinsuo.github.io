#!/bin/sh

# apt-get update -y; apt install wget -y; wget http://omega.uta.edu/~kxs2503/script/sk-ubuntu.sh; chmod +x sk-ubuntu.sh; ./sk-ubuntu.sh

# Satisfy deps
apt-get update -y && \
apt install wget htop dh-autoreconf  iputils-ping fish gcc openssh-client openssh-server  net-tools g++ make vim git autoconf automake libtool libncurses5-dev libncursesw5-dev  -y &&\
apt install python-pip python-dev libffi-dev libssl-dev libxml2-dev libxslt1-dev libjpeg8-dev zlib1g-dev -y
apt install iperf iperf3 psmisc -y
apt install netperf -y

# Download nmon
cd ~
wget http://omega.uta.edu/~kxs2503/script/nmon/nmon16g_x86.tar.gz
tar zxvf nmon16g_x86.tar.gz
mv nmon16g_x86_ubuntu1604 nmon
chmod +x nmon
cp nmon /usr/local/bin/


# install redis
cd ~
wget http://download.redis.io/releases/redis-3.0.7.tar.gz
tar -zxvf redis-3.0.7.tar.gz
cd redis-3.0.7
make
make install


# Download sockperf
cd ~
git clone https://github.com/Mellanox/sockperf.git
cd sockperf/ && ./autogen.sh && ./configure && make && make install


# Download sparkyfish
cd ~
wget https://github.com/chrissnell/sparkyfish/releases/download/v1.2/sparkyfish-cli-v1.2-linux-amd64.gz
wget https://github.com/chrissnell/sparkyfish/releases/download/v1.2/sparkyfish-server-v1.2-linux-amd64.gz
gunzip sparkyfish-cli-v1.2-linux-amd64.gz
gunzip sparkyfish-server-v1.2-linux-amd64.gz
chmod 755 sparkyfish-cli-v1.2-linux-amd64
chmod 755 sparkyfish-server-v1.2-linux-amd64
mv sparkyfish-cli-v1.2-linux-amd64 /usr/local/bin/sparkyfish-cli
mv sparkyfish-server-v1.2-linux-amd64 /usr/local/bin/sparkyfish-server



# download script
cd ~
wget http://omega.uta.edu/~kxs2503/script/run-sockperf-N-times.sh
chmod +x run-sockperf-N-times.sh

wget http://omega.uta.edu/~kxs2503/script/run-sockperf-different-packet-size.sh
chmod +x run-sockperf-different-packet-size.sh

wget http://omega.uta.edu/~kxs2503/script/run-sockperf-latency-std-dev.sh
chmod +x run-sockperf-latency-std-dev.sh


# install mpi
cd ~
apt install mpich -y
wget http://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-5.3.2.tar.gz
tar -zxvf osu-micro-benchmarks-5.3.2.tar.gz
cd osu-micro-benchmarks-5.3.2
./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx
make
make install


# install OpenResty webserver
cd ~
mkdir OpenResty
cd OpenResty
wget -qO - https://openresty.org/package/pubkey.gpg |  apt-key add -
apt-get -y install software-properties-common
add-apt-repository -y "deb http://openresty.org/package/ubuntu $(lsb_release -sc) main"
apt-get update -y
apt-get install openresty -y
echo "install OpenResty successfully"

cd ~/OpenResty
mkdir work
cd work
mkdir conf/ logs/
cd conf
wget http://omega.uta.edu/~kxs2503/script/OpenResty/conf/nginx.conf
/usr/local/openresty/nginx/sbin/nginx -p ../ -c ./nginx.conf



# install apache server
cd ~
mkdir Apache
cd Apache
wget http://mirror.olnevhost.net/pub/apache//apr/apr-1.6.3.tar.gz
tar -zxvf apr-1.6.3.tar.gz
cd apr-1.6.3
./configure; make; make install

cd ..
wget http://apache.claz.org//apr/apr-util-1.6.1.tar.gz
tar -zxvf apr-util-1.6.1.tar.gz
cd apr-util-1.6.1
./configure --with-apr=/usr/local/apr ; make ; make install

cd ..
wget https://sourceforge.net/projects/pcre/files/pcre/8.36/pcre-8.36.tar.gz
tar -zxvf pcre-8.36.tar.gz
cd pcre-8.36
./configure; make; make install

cd ..
wget https://www.apache.org/dist/httpd/httpd-2.2.34.tar.gz
tar -zxvf httpd-2.2.34.tar.gz


# install http_load 
cd ~
mkdir http_load
cd http_load
wget https://acme.com/software/http_load/http_load-09Mar2016.tar.gz
tar -zxvf http_load-09Mar2016.tar.gz
cd http_load-09Mar2016/
make; make install

















