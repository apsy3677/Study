Course Material for Design Patterns Course

The course material for our Design Patterns Course on 2020-10-19
is available from a private git repository:

  URL: https://www.javaspecialists.eu/git/safari/dpc5-5447.git
  Username: safari5447
  Password: oFKQxFrB

The repository contains the exercises, solutions and slides in the master
branch, plus the code written by the instructor during the course in the
"kabutz" branch. In order to get the most out of the course, we recommend that
you clone the repository to your local disk. Please do not share this course
material or push it to a public repository.

Note: The https URL is only meant to be accessed via git and not via your
browser. If you do try to connect to the URL, you will get a 404 Page Not Found
error. Instead use your IDE or the git command `git clone {URL}` in a terminal
or command prompt to clone the repository (details below).

This repository will remain accessible after the course is completed in case
you would like to review it at a later date. For further help, please contact
heinz@javaspecialists.eu.

Recommended setup:

  - Java Development Kit (JDK) 15
  - IntelliJ IDEA 2020.2

Minimum setup:

  - JDK 11
  - git

===

Detailed instructions:

1. Download and install the JDK. We recommend Azul Zulu at

     https://www.azul.com/downloads/zulu-community/

   We recommend the latest JDK as we will see the newest language features
   during the course.

2. Download and install the latest free IntelliJ IDEA at

     https://www.jetbrains.com/idea/download/

   Either the Community or Ultimate editions will work. Another IDE may be
   used if you are already familiar with it. However, we might not be able to
   help you with setup issues if you get stuck.

3. Clone the repository:

   3.1. In IntelliJ, use the menu: File -> New -> Project from Version Control
        Paste in the URL, choose a Directory then complete the dialog.

   3.2. If you use Eclipse, use the menu: File -> Import...
        In the dialog which follows, accept the defaults except for:

        * Choose Git -> Projects from Git (with smart import)
        * Paste in the Clone URI, User and Password
        * Select the master branch
        * Choose a Directory

   3.3. You can also clone from the command line by downloading git from

          https://git-scm.com/downloads/

        Then issue this command in a terminal or command prompt:

          git clone https://www.javaspecialists.eu/git/safari/dpc5-5447.git
          Username: safari5447
          Password: oFKQxFrB

        [!] We recommend that you use step 3.1 if using IntelliJ IDEA
        so that the settings in the .ipr file will be used.

4. In IntelliJ, go to [File -> Project Structure] and set the Project SDK.
   If you are using another IDE, set the project compiler appropriately.
