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
