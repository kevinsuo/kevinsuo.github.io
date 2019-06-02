#!/bin/sh

i=1
var=""
IP="10.0.0.3"
PORT="11111"
TIMES=10

while [ $i -le $TIMES ]
do
        var="log"

        #send packet
        netperf -H $IP -l 10 -t TCP_STREAM -p $PORT  >> $var

        sleep 3

        i=$(( $i + 1 ))

done

grep "87380" ./$var | awk ' { print ( $(NF) ) }' | awk '{sum+=$1}END{print sum/10 }'

rm $var

