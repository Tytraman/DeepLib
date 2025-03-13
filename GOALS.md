# Objectifs

L'objectif principal de cette librairie est de pouvoir l'utiliser dans tous mes projets afin de m'éviter de devoir réécrire le même code en boucle.

L'exécution de la librairie ne doit pas être propre à un système d'exploitation en particulier, c'est-à-dire qu'il ne doit pas y avoir besoin de modifier le code pour supporter un nouveau système.
Pour cela la librairie devra dépendre d'un module nommé 'DeepCore' qui s'occupera de faire le pont avec les différents OS.

# Nécessités

La librairie doit être écrite tout en répondant à ces nécessités :
- Tous les types primitifs doivent être redéfinissables.
- Certaines fonctions primitives doivent pouvoir être modifiées grâce aux macros.
- La librairie doit être cross-plateforme *(au moins Linux et Windows)*.
- Tout code dépendant d'un système d'exploitation doit passer par un utilitaire dédié, aucun code en dur ne doit être fait *(utilisation de DeepCore)*.
- Toute structure de données, fonction ou type doit être documenté.

# Interdictions

Certaines restrictions sont mises en place pour avoir un code plus propre, modulaire et plus maintenable :
- **Aucune** variable globale / statique, excepté le contexte global interne à la librairie.

