intro:
	g++ -Wall -o XSampleWindow intro.cpp -lX11 -L/usr/lib/x86_64-linux-gnu -I/usr/include/X11

input:
	g++ -Wall -o InputWindow input.cpp -lX11 -L/usr/lib/x86_64-linux-gnu -I/usr/include/X11

clean:
	rm XSampleWindow
