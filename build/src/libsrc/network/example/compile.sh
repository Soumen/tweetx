#lame way  to compile
# need to learn how to write Makefile
g++ -ggdb -I../ -L../  http_client.C  -lSocket -o http_client
export LD_LIBRARY_PATH=../
