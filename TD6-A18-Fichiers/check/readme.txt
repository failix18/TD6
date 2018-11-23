Ce répertoire contient un vérificateur pour trouver des problèmes potentiels dans des programmes qui n'ont pas d'erreurs syntaxique.
Il contient Cppcheck (un analyseur statique de code C/C++) ainsi que des règles ajoutées par Francois-R.Boyer@PolyMtl.ca (fichier ayant le nom "frb*").

Les fichiers sont:
	cppcheck.exe et cppcheck-core.dll: fichiers exécutable pour Cppcheck
	authors.txt:   la liste des auteurs de Cppcheck
	frboyer.rules: quelques règles supplémentaires pour Cppcheck
	cppcheck.targets, cppcheck.props, et cppcheck.xml: fichiers MSBuild pour ajouter les options de Cppcheck à VisualStudio 2013 (sélectionner le projet, et dans le menu "Projet" > "Personnalisations de la build...", faire "Rechercher un fichier existant..." et ouvrir le fichier "cppcheck.targets").

Voici le contenu original du "readme.txt" de Cppcheck:

=========
Cppcheck
=========


About

    The original name of this program is "C++check" but it was later changed to "cppcheck".

Manual

    A manual is available online:
    http://cppcheck.sf.net/manual.pdf

Compiling

    Any C++ compiler should work.

    To build the GUI, you need Qt.

    When building the command line tool, PCRE is normally used.
    PCRE is optional.

    There are multiple compilation choices:
      * qmake - cross platform build tool
      * Windows: Visual Studio
      * Windows: Qt Creator + mingw
      * gnu make
      * g++

    qmake
    =====
        You can use the gui/gui.pro file to build the GUI.
            cd gui
            qmake
            make

    Visual Studio
    =============
        Use the cppcheck.sln file. The rules are normally enabled.

        To compile with rules (pcre dependency):
            * the pcre dll is needed. it can be downloaded from:
                http://cppcheck.sf.net/pcre-8.10-vs.zip

        To compile without rules (no dependencies):
            * remove the preprocessor define HAVE_RULES from the project
            * remove the pcre.lib from the project

    Qt Creator + mingw
    ==================
        The PCRE dll is needed to build the CLI. It can be downloaded here:
            http://software-download.name/pcre-library-windows/

    gnu make
    ========
        To build Cppcheck with rules (pcre dependency):
            make HAVE_RULES=yes

        To build Cppcheck without rules (no dependencies):
            make

        If you have python it is recommended that you add "SRCDIR=build". When
        that is used, the Makefile uses python to compile Cppcheck (but python
        is not used at runtime). The advantage is that it makes Cppcheck faster.

    g++ (for experts)
    =================
        If you just want to build Cppcheck without dependencies then you can use this command:
            g++ -o cppcheck -Ilib cli/*.cpp lib/*.cpp

        If you want to use --rule and --rule-file then dependencies are needed:
            g++ -o cppcheck -lpcre -DHAVE_RULES -Ilib -Iexternals cli/*.cpp lib/*.cpp externals/tinyxml/*.cpp

    mingw
    =====
        The "LDFLAGS=-lshlwapi" is needed when building with mingw
            mingw32-make LDFLAGS=-lshlwapi

Cross compiling Win32 (CLI) version of Cppcheck in Linux

    sudo apt-get install mingw32
    make CXX=i586-mingw32msvc-g++ LDFLAGS="-lshlwapi"
    mv cppcheck cppcheck.exe

Webpage

    http://cppcheck.sourceforge.net/
