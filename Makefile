all :
	g++ -I/usr/local/include/eigen3 admm.c -o admm

clean : 
	rm -f admm
