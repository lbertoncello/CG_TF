all:
	g++ -std="c++11" tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp main.cpp draw.cpp point.cpp sphere.cpp circle.cpp line.cpp color.cpp game.cpp flightArea.cpp enemy.cpp flightEnemy.cpp terrestrialEnemy.cpp airplane.cpp player.cpp airportRunway.cpp gameRuntime.cpp gameSetup.cpp parametersReading.cpp bullet.cpp bomb.cpp calc.cpp imageloader.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg