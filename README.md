# Setting up C++ and OpenGL

This is a project where I'm going to learn how to set up OpenGL with C++. Hopefully this will serve as a future reference for me and anyone who is interested in learning to do this.

## Visual Studio

Visual Studio is a development environment, package manager, and IDE developedby Microsoft. Many choose it for its built-in debugging and ease of use for project management.

#### Installing Visual Studio
For this project, I decided to use VisualStudio 2019 with the community license, largely because of its convenience and building utilities.
You can find the download link [here](https://visualstudio.microsoft.com/vs/features/cplusplus/).

- Go to the link and download visual studio community 2019.
- Start the install (I just followed the install instructions with default settings).
- Restart computer

#### Running a Visual Studio C++ Project

- create an empty c++ project and place it where you want.
- once it opens, you should see a file directory on the right of the interface. Right click the source folder, click add, and add a c++ .cpp file
- create a simple hello world or anything to test
- click build in the top menu and then build solution (or ctr+shift+b)
- click debug, then start without debugging (or ctr+F5)
- this will run your cpp code.

## GLFW

[Here](https://www.glfw.org/faq.html#11---what-is-glfw) you can find the FAQs on GLFW, as well as the rest of the documentation on what it is. My understanding is that GLFW is a utility library for OpenGL that simplifies some of the low-level tasks like creating and managing windows and contexts.

#### Installing GLFW

[Here](https://www.glfw.org/download.html) is the link to download.

- Download the 32 bit binaries from this page.
- On the download page, download the binaries that match your bit count. Extract this download somewhere you will remember.

## Creating an Empty Window Using GLFW and C++

I will be following [this](https://www.youtube.com/watch?v=AwVVt9Ht5Q8) tutorial, but I will type the steps here as well. 

- Open VisualStudio
- Select file, new project
- Select Empty Project
- Choose a project name and directory, and click Create

Your project has now been created. On the right, you should see a tab with the title Solution Explorer. In this window, there is a button called show all files. you can see the tooltip if you mouse over it, and the image below shows the location of this button.
![Show all files option](./readme_files/solutions_explorer.png)

- Click the show all files option.
- Right click your project name in the solutions explorer, click add, new folder, and add a folder named source.
- Open a file explorer window and navigate to your project directory where you see the source folder
- Open a nother file explorer window and navigate to the GLFW extracted flder you created.
- Copy the include and lib-vc2019 folders from the GLFW folder into the project folder at the same level as the source folder, but not in the source folder. This is getting the proper GLFW packages in to our project.
- Now, back in VisualStudio, add a C++ file in the project inside the source folder named main.cpp
- Copy and paste the following code into the main.cpp file. This code was taken from the GLFW website [here](https://www.glfw.org/documentation.html) and is basic code for opening an opengl window.

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

- Right click the project name in the solutions explorer and click properties.
- Change configurations to all configurations
- Under `Configuration Properties`, select `C/C++`, and then `General` 
- Here, you can see `Additional Include Directories` option on the right. 
- Add `$(ProjectDir)include` by manually typing it in, hitting enter, and clicking apply.
- Finally, we have to link our lib folder.
- Under `Configuration Properties` in this same window, now select the `Linker` and then `General` option.
- Under `Additional Library Directories`, add `$(ProjectDir)lib-vc2019`
- Finally, click the `Input` option under `Linker`
- Delete everything in the `Additional Dependencies` option.
- Now we will tell Visual Studio which libraries we will be using by adding `glfw3.lib;opengl32.lib;user32.lib;gdi32.lib;shell32.lib`
- Apply your changes, and return to the main.cpp file.
- Hit ctrl+shift+b to build, then ctrl+F5 to run. You should see a window appear that has hello world as the window title.

Congratulations! You now have a window.
