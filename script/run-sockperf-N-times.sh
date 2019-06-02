#!/bin/sh

i=1
var=""
IP="129.107.126.142"

while [ $i -le 10 ]
do
        var="log"

        #send packet
        sockperf throughput --tcp -i $IP -p 12321 -t 10  >> $var
        
        sleep 3

        i=$(( $i + 1 ))

done

grep "sockperf: Summary: BandWidth" ./$var | awk ' { print ( $(NF-3) ) }' | awk '{sum+=$1}END{print sum/10 }'

rm $var
