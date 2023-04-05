<a href="https://www.isart.fr/"><img src = "https://cdn.discordapp.com/attachments/1027192447232643152/1082248746710077451/telechargement.png"></a><a href="#"><img src = "https://cdn.discordapp.com/attachments/1027192447232643152/1082248263014559864/Placeholder.png"></a>
# PhosEngine

This project is a Game Engine made for the second year at ISART digital, we have 4 months to complete the project.


## Authors

- <a href = "mailto: l.lin@student.isartdigital.com">Laurent LIN</a>
- <a href = "mailto: l.zallio@student.isartdigital.com">Liam ZALIO</a>
- <a href = "mailto: m.robion@student.isartdigital.com">Mathieu ROBION</a>
- <a href = "mailto: y.dechaux@student.isartdigital.com">Yann DECHAUX</a>
## Visual Studio Explanation

- ### PhosEngine.sln
    ```
    Used to open the engine project.

    Will copy all dll by itself.
    ```

- ### PhosOpenAll.sln

  ```
  Used to open all branches at once.

  Will copy PhosCore dll and lib by itself.
  need to add command to move header files to the engine.
  ```
  #### Possible issues you might encounter:
    - An Error will appen when trying to lauch.
    >**Solution:** The error is normal it is due to PhosCore trying to execute its dll. Ignore it and the project should start normally.
    - I modified the Core but my project have not changed.
    >**Solution:** This probleme is due to Visual Studio rebuilding only PhosCore but not PhosEngine because it was not modified. Just go in [Build > Rebuild Solution], it will rebuild all project.

## PhysX Repository
This is another repository used to test physX functions and implement basics architecture before adding it to our engine:

 https://gitlabstudents.isartintra.com/y.dechaux/physx_test
