LIBPATH = my_lib/mylib.cpp
all: gtime time_srv
gtime: mylib.o daytime_client.o
	g++ mylib.o daytime_client.o -o gtime
time_srv:mylib.o daytime_ser.o
	g++ mylib.o daytime_ser.o -o time_srv
mylib.o:$(LIBPATH)
	g++ -c $(LIBPATH)
daytime_client.o:daytime_client.cpp
	g++ -c -g daytime_client.cpp
daytime_ser.o:daytime_ser.cpp
	g++ -c -g daytime_ser.cpp
clean:
	rm -rf *o daytime_client gtime

