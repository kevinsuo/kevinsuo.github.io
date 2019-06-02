/*
 * Copyright (c) 2017 Tony Suo.
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * 22-Jun-2017	Tony Suo	Created this.
 */



#!/bin/sh
# The following scripts are tested on Ubuntu 16.10

PID=11111

# step 1: install bcc
sudo apt-get install bcc-tools libbcc-examples linux-headers-$(uname -r) -y

# get bcc
git clone https://github.com/iovisor/bcc.git

# trace off cpu data
sudo python ./bcc/tools/offcputime.py -p $PID -f 10 > out.offcpustacks02

# draw flame graph
sudo ./FlameGraph/flamegraph.pl --color=io --countname=us  out.offcpustacks02 > off-cpu.svg


