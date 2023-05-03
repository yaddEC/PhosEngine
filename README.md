# PhosEngine        
<a href="https://www.isart.fr/"><img width="255" height="255" src = "https://cdn.discordapp.com/attachments/1027192447232643152/1082248746710077451/telechargement.png"></a> <a href="#"><img width="390" height="255" src = "https://cdn.discordapp.com/attachments/1077144912954409033/1084231741121757215/image.png"></a>
## ⭐ About the Project
This project is a Game Engine made for the second year at ISART digital, we have 4 months to complete the project.
- **Some Characteristics :**
  <br/>The engine is written in <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/C%2B%2B-v17-blue"/></a> and compiled with <a href="https://visualstudio.microsoft.com/fr/"><img src="https://img.shields.io/badge/Visual%20Sudio-2019-gray?labelColor=9757cf&style=flat" alt="Visual Sudio" /></a>
  - External library :
    |Functionality	| Library |
    |---------------|---------|
    |Graphic API|<a href="https://www.opengl.org/">OpenGL</a>|
    |Window|<a href="https://www.glfw.org/">GLFW</a>|
    |3D Model Parser	|<a href="https://github.com/assimp/assimp">assimp</a>|
    |Image Parser|<a href="https://github.com/nothings/stb/blob/master/stb_image.h">stb_image</a>|
    |Sound|<a href="https://miniaud.io/">miniaudio</a>|
    |Physics|<a href="https://github.com/NVIDIA-Omniverse/PhysX">Nvidia PhysX</a>|
    |GUI (Editor)|<a href="https://github.com/ocornut/imgui">Dear ImGui</a>|
## Authors

- <a href = "mailto: l.lin@student.isartdigital.com">Laurent LIN</a>
- <a href = "mailto: l.zallio@student.isartdigital.com">Liam ZALIO</a>
- <a href = "mailto: m.robion@student.isartdigital.com">Mathieu ROBION</a>
- <a href = "mailto: y.dechaux@student.isartdigital.com">Yann DECHAUX</a>
## Visual Studio Explanation
- ⚠ The main branch is the editor, it contains all the dll so you should be able to run it. The engine as its own branch. ⚠
- ### PhosEngine.sln
    ```
    Used to open the engine project.

    Will copy all dll by itself.
    ```
- ### PhosEditor.sln
    ```
    Used to open the editor project.
    ```

- ### PhosOpenAll.sln

  ```
  Used to open all branches at once.

  Will copy PhosCore dll and lib by itself.
  need to add command to move header files to the engine.
  ```
  #### Possible issues you might encounter:
    - I just pull and my project can't compile.
    >**Solution:** You have probably pulled a PhosEngine.dll or .lib that doesn't have a function you used or modified an existing one. Try to pull the Engine and if it's not working go in [Build > Rebuild Solution], it will rebuild all projects and will overwrite the dll you pull.

## PhysX Repository
This is another repository used to test physX functions and implement basics architecture before adding it to our engine:

 https://gitlabstudents.isartintra.com/y.dechaux/physx_test
