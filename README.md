# DeepLib

Librairie libre et cross-plateforme facilitant le développement de mes projets.

## Objectifs

La librairie a été développée pour répondre à certains besoins qui sont expliqués dans [**Objectifs**](./GOALS.md).

## Compilation

La construction du projet utilise le moteur de production [**CMake**](https://cmake.org/).

### Visual Studio

Pour faciliter l'intégration des dépendances le gestionnaire de paquets [**vcpkg**](https://vcpkg.io/) peut être utilisé.

- `libpng` :
```cmd
vcpkg install libpng
```

Les dernières versions de **Visual Studio** intègrent **CMake** directement dans l'éditeur.<br>
Il suffit donc de **configurer** et **construire** les cibles depuis l'interface.

## Utilisation

### Intégration

> 📝 La manière d'intégrer la librairie sera simplifiée par la suite.

Une fois la librairie compilée, dans le dossier de **sortie** faire la commande :
```bash
cpack -C Release
```
Un fichier `.zip` est généré, selon le système d'exploitation la suite de la procédure diffère.

- #### Windows

    Décompresser le fichier dans `C:\Program Files\DeepLib`. À l'intérieur de ce dossier doit se trouver les dossiers `bin`, `include` et `lib`.

À l'intérieur du fichier `CMakeLists.txt` de votre projet, ajouter ces lignes :
```cmake
find_package(DeepLib REQUIRED) 

target_link_libraries(targetName
    PRIVATE
        Deep::Core
        Deep::Lib)
if (WIN32)
    add_custom_command(TARGET targetName PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Deep::Core>
        $<TARGET_FILE:Deep::Lib>
        $<TARGET_FILE_DIR:targetName>)
endif()
```