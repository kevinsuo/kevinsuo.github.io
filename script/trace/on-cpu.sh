/*
 * Copyright (c) 2017 Tony Suo.
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * 22-Jun-2017	Tony Suo	Created this.
 */


#!/bin/sh

# step 1: install perf

# On Ubuntu
sudo apt install linux-tools-common gawk -y
sudo apt install linux-tools-4.8.0-59-generic  linux-cloud-tools-4.8.0-59-generic  -y


# On CentOS and Fedora
sudo yum install perf gawk -y

# step 2: get FlameGraph
git clone https://github.com/brendangregg/FlameGraph.git

PID=11111
# trace data
sudo perf record -e cpu-clock -g -p $PID
# Ctrl+c结束执行后，在当前目录下会生成采样数据perf.data.

# 用perf script工具对perf.data进行解析
sudo perf script -i perf.data &> perf.unfold

# 将perf.unfold中的符号进行折叠：
sudo ./FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded

# 最后生成svg图：
sudo ./FlameGraph/flamegraph.pl perf.folded > on-cpu.svg

