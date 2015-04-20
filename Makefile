penPals: src/main.o src/Animation.o src/Character.o
        cp -ar Assets/* ./
        g++ -o penPals src/main.o src/Animation.o src/Character.o -lsfml-graphics -lsfml-window -lsfml-system
