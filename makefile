setup:
	mkdir dist
gamebuild:
	gcc miniGame.cc -lglut -lGL -o ./dist/miniGame -lm
gamerun: 
	./dist/miniGame	
cubebuild:
	gcc example3d.cc -lglut -lGL -o ./dist/cube -lm
cuberun:
	./dist/cube

terrainbuild:
	gcc terrain.cc -lglut -lGLU -lGL -o ./dist/terrain -lm
terrainrun:
	./dist/terrain

snowbuild:
	gcc snow.cc -lglut -lGLU -lGL -o ./dist/snow -lm

snowrun:
	./dist/snow