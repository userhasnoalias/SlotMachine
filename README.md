# Порядок сборки

+ В решении visual studio поставить платформу **x86** (будет работать и для Debug и для Release)

  ![](https://github.com/userhasnoalias/SlotMachine/blob/master/x86.png)
+ Скомпилировать проект
+ Из директории SFML/dll перенести файлы sfml-graphics-2.dll, sfml-system-2.dll, sfml-window-2.dll (sfml-graphics-d-2.dll, sfml-system-d-2.dll, sfml-window-d-2.dll для Debug билда) в директорию с исполняемым файлом (по умолчанию $(SolutionDir)/Debug или $(SolutionDir)/Release)
