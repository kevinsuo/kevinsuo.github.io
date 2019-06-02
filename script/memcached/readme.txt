server: 
(4 threads, 4096MB memory, min object size 550bytes, port is 11212)
memcached -t 4 -m 4096 -n 550 -p 11212




client:
create scaled file:
./loader -a ../twitter_dataset/twitter_dataset_unscaled -o ../twitter_dataset/twitter_dataset_30x -s servers.txt -w 1 -S 30 -D 4096 -j -T 1 

warm up:
./loader -a ../twitter_dataset/twitter_dataset_30x -s servers.txt -w 1 -S 1 -D 4096 -j -T 1 

run:
./loader -a ../twitter_dataset/twitter_dataset_30x -s servers.txt -g 0.8 -T 1 -c 200 -w 8 -e -r rps


