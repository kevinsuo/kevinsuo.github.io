#!/bin/sh

#server side: sockperf server --tcp -i 129.107.126.89 -p 12321


i=1
var=""
IP="129.107.126.89"
msg=16


while [ $i -le 10 ]
do
        var="log"


        #send packet with TCP
        sockperf under-load --tcp -i $IP  -p 12321 -t 10  >>  $var

        sleep 2 

        i=$(( $i + 1 ))
done


#echo "average latency"
grep "sockperf: Summary: Latency" ./$var | awk ' { print ( $(NF-1) ) }' | awk '{sum+=$1}END{print sum/10 }'

#echo "max 99 latency"
grep "sockperf: ---> percentile 99.000" ./$var | awk ' { print ( $(NF) ) }'  | awk 'BEGIN {max = 0} {if ($1+0 > max+0) max=$1} END {print "", max}'

#echo "max 99.9 latency"
grep "sockperf: ---> percentile 99.900" ./$var | awk ' { print ( $(NF) ) }'  | awk 'BEGIN {max = 0} {if ($1+0 > max+0) max=$1} END {print "", max}'

#echo "max std-dev"
grep "std-dev" ./$var | awk ' { print ( $(NF) ) }' > t0
sed -n 's/^(std-dev=//p' t0 > t1
sed -n 's/)//p' t1 | awk 'BEGIN {max = 0} {if ($1+0 > max+0) max=$1} END {print "", max}'

#echo "avg std-dev"
sed -n 's/)//p' t1 | awk '{sum+=$1}END{print sum/10 }'

rm t0
rm t1
rm $var

