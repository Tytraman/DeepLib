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