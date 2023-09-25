Cloth Simulation - Alexandru Miron

IMPORTANT: Inside MyForm.cpp, at lines 144-149, there is an if condition which is responsible for printing every frame to
.obj file. This GREATLY decreases performance. I recommend commenting those lines unless planning to test the saving feature.
If that is commented the program will not save any frames, but it will run smoother.

Steps to run: Load File > Save .obj location (OPTIONAL) > Check scenario > Press Play

This program should be runnable inside Visual Studio 2019 C++.

Additional libraries used were GLM (for math operations) GLUT(for rendering openGL),OpenGL and stb_image.
These libraries are linked dinamically to the project, so the project should run straightaway.
The project also uses Windows Forms for the GUI interface.

To test it, LOAD the cloth file called "CLOTH1.obj". This is the only .obj file that is required to run the scenarios.
Another cloth file is "CLOTH2.obj". This has fewer vertices and will not look as realistic.
The sphere is a GLUT object at location (0,0,0) with a certain radius, not an .obj file.

Other .obj files can also be loaded, but not all are guaranteed to show in the scene. "cube.obj" and "sphere.obj" do fit in the scene, though.
"newcube.obj" is the result of me saving the cube object into a new file.

Check any one of the implemented checkboxes to run that particular scenario. In each case, the cloth file will also needed to
be loaded. Then simply press play.

Saving the .obj file is done inside the OBJLoader class and loads individual obj objects into a new file. This is not required 
every time you run the program.


References:

GLM: https://glm.g-truc.net/0.9.9/ [Accessed 05/12/2022]

GLUT: https://www.opengl.org/resources/libraries/glut/glut_downloads.php [Accessed 05/12/2022]

OpenGL: https://www.opengl.org/ [Accessed 05/12/2022]

STBImage: https://github.com/nothings/stb/blob/master/stb_image.h


