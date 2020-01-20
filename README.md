# Setting up C++ and OpenGL

This is a project where I'm going to learn how to set up OpenGL with C++. Hopefully this will serve as a future reference for me and anyone who is interested in learning to do this. In this repo you will fin all of my opengl code. You can clone it, but you will still have to follow the instructions to set up GLFW and Visual Studio.

## Visual Studio

Visual Studio is a development environment, package manager, and IDE developedby Microsoft. Many choose it for its built-in debugging and ease of use for project management.

#### Installing Visual Studio
For this project, I decided to use VisualStudio 2019 with the community license, largely because of its convenience and building utilities.
You can find the download link [here](https://visualstudio.microsoft.com/vs/features/cplusplus/).

1. Go to the link and download visual studio community 2019.
2. Start the install (I just followed the install instructions with default settings).
3. Restart computer

#### Running a Visual Studio C++ Project

1. create an empty c++ project and place it where you want.
2. once it opens, you should see a file directory on the right of the interface. Right click the source folder, click add, and add a c++ .cpp file
3. create a simple hello world or anything to test
4. click build in the top menu and then build solution (or ctr+shift+b)
5. click debug, then start without debugging (or ctr+F5)
6. this will run your cpp code.

## GLFW

[Here](https://www.glfw.org/faq.html#11---what-is-glfw) you can find the FAQs on GLFW, as well as the rest of the documentation on what it is. My understanding is that GLFW is a utility library for OpenGL that simplifies some of the low-level tasks like creating and managing windows and contexts.

#### Installing GLFW

[Here](https://www.glfw.org/download.html) is the link to download.

1. Download the 32 bit binaries from this page.
2. On the download page, download the binaries that match your bit count. Extract this download somewhere you will remember.

## Creating an Empty Window Using GLFW and C++

I will be following [this](https://www.youtube.com/watch?v=AwVVt9Ht5Q8) tutorial, but I will type the steps here as well. 

1. Open VisualStudio
2. Select file, new project
3. Select Empty Project
4. Choose a project name and directory, and click Create

Your project has now been created. On the right, you should see a tab with the title Solution Explorer. In this window, there is a button called show all files. you can see the tooltip if you mouse over it, and the image below shows the location of this button.
![Show all files option](./readme_files/solutions_explorer.png)

1. Click the show all files option.
2. Right click your project name in the solutions explorer, click add, new folder, and add a folder named source.
3. Open a file explorer window and navigate to your project directory where you see the source folder
4. Open a nother file explorer window and navigate to the GLFW extracted flder you created.
5. Copy the include and lib-vc2019 folders from the GLFW folder into the project folder at the same level as the source folder, but not in the source folder. This is getting the proper GLFW packages in to our project.
6. Now, back in VisualStudio, add a C++ file in the project inside the source folder named main.cpp
7. Copy and paste the following code into the main.cpp file. This code was taken from the GLFW website [here](https://www.glfw.org/documentation.html) and is basic code for opening an opengl window.

```C++
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```

#### Adding header file and includes from the GLFW Libraries
You will probably notice that most of the functions are marked as errors, and project will not build. This is because, although the GLFW include folder and header files are in the project, they aren't actually known by the project itself, and Visual Studio does not know they exist. To fix this, we have to link the header files in our project.

1. Right click the project name in the solutions explorer and click properties.
2. Change configurations to all configurations
3. Under `Configuration Properties`, select `C/C++`, and then `General` 
4. Here, you can see `Additional Include Directories` option on the right. 
5. Add `$(ProjectDir)include` by manually typing it in, hitting enter, and clicking apply.
6. Finally, we have to link our lib folder.
7. Under `Configuration Properties` in this same window, now select the `Linker` and then `General` option.
7. Under `Additional Library Directories`, add `$(ProjectDir)lib-vc2019`
8. Finally, click the `Input` option under `Linker`
9. Delete everything in the `Additional Dependencies` option.
10. Now we will tell Visual Studio which libraries we will be using by adding `glfw3.lib;opengl32.lib;user32.lib;gdi32.lib;shell32.lib`
11. Apply your changes, and return to the main.cpp file.
12. Hit ctrl+shift+b to build, then ctrl+F5 to run. You should see a window appear that has hello world as the window title.

Congratulations! You now have a window. It is important to note that you actually don't have to install anything for OpenGL because graphics drivers come with OpenGL already. This is why we only have to include the GLFW files.

## Installing GLAD
One final step is to install glad. You can get a more in depth explanation of why this is helpful [here](https://learnopengl.com/Getting-started/Creating-a-window) under the `Setting Up GLAD` section. Basically, it helps you have the proper function bindings for opengl. Without GLAD, you'd have to manually declare all opengl functions you want to use. You can follow the instructions on that page, and I have also added them just below.

1. Go to [this link](https://glad.dav1d.de/)
2. Here, set the GL option to the newest option
3. Set profile to core
4. Make sure generate a loader is clicked
5. Click Generate
6. Click `glad.zip` to download the zip, and then extract it
7. Open the extracted folder, go in the include folder, and copy the two folders in the include folder into your projects include folder. Your project include folder should now have `GLFW`, `glad`, and `KHR`.
8. In the extracted folder, copy `glad.c` into the same directory as your main.cpp file
9. In the Visual Studio file inspector, right click your `source` folder, then click `Include in Project`. Navigate to the glad.c file and add it.
10. Make sure you `#include <glad/glad.h>` ABOVE the `#include <GLFW/glfw3.h>`

Finally, add
```
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
```

after the line:

```
glfwMakeContextCurrent(window);
```

This will initialize glad. You should now be able to build and run your project. You are now also able to add to vertex buffers and follow along with [this](https://learnopengl.com/Getting-started/Hello-Window) tutorial series.
## Further Reading

- [GLFW Documentation](https://www.glfw.org/docs/latest/quick.html) <- Good source for learning about GLFW
- [LearnOpenGL](https://learnopengl.com/Introduction) <- A good source for learning opengl. This is what I will be following.
