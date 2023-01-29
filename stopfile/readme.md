# stopfile
# C++ class for reading stop-file for a program.

German version [below](#deutsche-version).

# What can this class do?

This class can read so-called stop files and optionally also evaluates the content of the file.
If you run a program that runs as a daemon (systemd service), for example, you can no longer tell the program to stop using the command line. In order to notify the program that it should end, the program can regularly check for the presence of a stop file. If this file is available, the program can interpret it as a signal that it should terminate. This class can be used to check the existence of such a stop file.  
Optionally, the content can also be evaluated so that there is a higher level of security.  
The regular checking of whether a stop file is present takes place in a separate thread. The waiting time after a check is currently set hard at 100 milliseconds.  
To generate the stop file, simply ```touch <file name>``` can be called. If the file should have a certain content, ```echo "<content>" >> <file name>``` can be called.  

# Sample program

The sample program ```stopfile_example.cpp``` reads the stop file ```stopfile_example.stop``` and evaluates the presence of the file as a signal that the program should terminate. The program also shows an example that reads the content of the file and expects a certain command (```stopme```) in the file so that it should end.  
The make file ```makefile``` can be used to generate the program. It is assumed that the class files ```stopfile.cpp``` and ```stopfile.hpp``` are located in the directory ```/home/pi/cpp_sources```.

# Platform

The class was only tested on Raspberry OS. The Raspberry OS for x86 was used in a virtual machine for development. However, the class is used on a Raspberry Pi 2B (ARMHF).

# Outlook

The waiting time between the tests should be adjustable as a parameter. 

# Deutsche Version

# Was kann diese Klasse?

Diese Klasse kann sogenannte stop-Dateien lesen und wertet optional den den Inhalt der Datei auch aus.  
Wenn ein Programm als Daemon (systemd-Dienst) läuft, so kann man dem Programm das Anhalten nicht mehr per Kommandozeile mitteilen. Um dem Programm nun mitzuteilen, dass es sich beenden soll, kann das Programm regelmässig das Vorhandensein einer Stop-Datei prüfen. Wenn diese Datei vorhanden ist, kann das Programm das als Signal werten, dass es sich beeenden soll. Mit dieser Klasse kann das Vorhandensein einer solchen Stop-Datei geprüft werden. 
Optional kann noch der Inhalt der Stop-Datei ausgewertet werden, so dass eine höhere Sicherheit besteht, wenn auch der Inhalt der Stop-Datei korrekt sein muss, um ein Anhalten des Programms zu signalisieren.  
Das regelmässige Überprüfen, ob eine Stop-Datei vorhanden ist, geschieht in einem eigenen Thread. Die Wartezeit nach einem Prüfen ist aktuell mit 100 Millisekunden hart eingestellt.
Um die Stop-Datei zu erzeugen, kann einfach ```touch <Dateiname>``` aufgerufen werden. Wenn die Datei einen bestimmten Inhalt haben soll, so kann ```echo "<Inhalt>" >> <Dateiname>``` aufgerufen werden.

# Beispielprogramm

Das Beispielprogramm ```stopfile_example.cpp``` liest die stop-Datei ```stopfile_example.stop``` ein und wertet das Vorhandensein der Datei als Signal, dass sich das Programm beenden soll. In dem Programm wird auch ein Beispiel gezeigt, dass den Inhalt der Datei ausliest und ein bestimmtes Kommando (```stopme```) in der Datei erwartet, damit es sich beenden soll.
Um das Programm zu erzeugen, kann das Make-File ```makefile``` genutzt werden. Es wird vorausgesetzt, dass die Klassen-Dateien ```stopfile.cpp``` und ```stopfile.hpp``` im Verzeichnis ```/home/pi/cpp_sources``` liegen.

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS für x86 in einer virtuellen Maschine genutzt. Die Klasse wird aber auf einem Raspberry Pi 2B (ARMHF) eingesetzt.  

# Ausblick

Die Wartezeit zwischen den Prüfungen, ob eine Stop-Datei vorhanden ist, sollte als Parameter einstellbar sein.
