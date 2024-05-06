## Compilation

Pour pouvoir faire la compilation du projet sur un ordinateur, il est nécessaire d’avoir la version 0.12.0
d’OpenFrameworks pour Visual Studio. En effet, il s’agit de la version d’OpenFrameworks qui a été utilisé
pour le développement de l’application sur Visual Studio. Il est possible de faire l’installation de ce framework
en consultant la page suivante : https://openframeworks.cc/download/

Par la suite, il est nécessaire de faire l’installation d’un addon externe qui ne vient pas avec OpenFrameworks
par défaut. Il s’agit d’un addon pour utiliser ImGui directement dans une application OpenFrameworks. Afin
de faire l’installation, on doit se diriger dans le répertoire «addons» qui se trouve à la racine du répertoire
d’OpenFrameworks. Une fois dans ce répertoire il faut faire la commande suivante :

git clone https://github.com/Daandelange/ofxImGui.git

La prochaine étape est de venir faire le clonage du répertoire Git de l’application. Pour ce faire, il suffit d’aller
dans le répertoire «app» qui se trouve à la racine du répertoire d’OpenFrameWorks et de faire la commande
suivante :

git clone https://github.com/NathPaquet/Infographie_IFT-3100.git

Une fois le code source cloné directement dans le répertoire d’OpenFrameWorks, il suffit de lancer le projet-
Generator.exe (qui se trouve dans le répertoire projetGenerator). Puis, de cliquer sur le bouton «import», et
sélectionner le répertoire «Infographie_IFT-3100» que nous avons cloné à l’étape précédente. Il faut ensuite
ajouter les addons suivant en les sélectionnant directement dans le dropbox : ofxAssimpModelLoader, ofxGui,
ofxImGui et ofxSVG. On clique sur le bouton «Generate» par la suite pour générer le projet avec toutes les
dépendances.

Une fois toutes ces étapes complétées, il suffit de venir lancer l’application à partir de Visual Studio en
ouvrant la solution. Il est important d’avoir le Workloads : Desktop development with C++ sur Visual
Studio Community 2022 pour faire le développement.
