penPals:
	cp -ar Assets/* ./
	cp -ar src/* ./
	cp -ar include/* ./
	g++ -c main.cpp
	g++ -c Animation.cpp
	g++ -c Character.cpp
	g++ -o penPals main.o Animation.o Character.o -lsfml-graphics -lsfml-window -lsfml-system
