#!/bin/sh
#server：iperf -s -u
#client：iperf -c 10.1.4.2 -u -b 10m

i=100
var=""
IP="129.107.126.142"

while [ $i -le 1000 ]
do
        var="log"

        #send packet
        iperf -c $IP -u -b ${i}"m"   >> $var
        
        sleep 3

        i=$(( $i + 100 ))

done


grep "%" ./$var | awk ' { print ( $(NF) ) }'
rm $var



