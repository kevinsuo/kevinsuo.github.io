#!/bin/sh

i=1
var=""
IP="129.107.126.142"
msg=16
port=12345


while [ $msg -le 1024 ]
do
        while [ $i -le 10 ]
        do
                var="log"

                #send packet with TCP
                #sockperf throughput --tcp -i $IP -p $port -m $msg -t 10  >> $var
                
                #send packet with UDP
                sockperf throughput -i $IP -p $port -m $msg -t 10  >> $var

                sleep 2 

                i=$(( $i + 1 ))
        done

        #echo "msg:"$msg
        grep "sockperf: Summary: BandWidth" ./$var | awk ' { print ( $(NF-3) ) }' | awk '{sum+=$1}END{print sum/10 }'
        rm $var
        i=1

msg=$(( $msg * 2 ))
done

