# inifile
# C++ class for reading ini-file for configuration of a program.

German version [below](#deutsche-version).

# What can this class do?

The aim of the logfile_class class is to write status messages to a log file in a running program. This class is available in 2 versions, one without threads and one with threads.
3 different levels can be specified with which information is written to the log file: information, warnings and errors. The user has to decide for himself which level the information to be written falls into.
A new line is written for each entry in the log file; the system date plus time is at the beginning of each line. Then the specified level (information, warning, error) follows and then the text.
You can specify a maximum file size that the log file should not exceed. When this limit is reached, the file is reduced by half by deleting the older half of the entries. This prevents the file from growing indefinitely.

# Threads
If you don't use threads in your program, you shouldn't use the thread variant either. The thread variant causes a bit more costs, since it works with locked mutexes. To use the thread variant, the #define thread_safe_logging (in the loggfile.hpp file) must be switched on.

# Sample programs

There are two sample programs that show how the class can be used. ```logfile_example.cpp``` is the example program without threads. ```logfile_example_thread.cpp``` is the sample program for threads.
Both variants can be created with the make file makefile. It should be noted here that the #define mentioned above must be activated in order to create the thread example.
After executing the program logfile_example_thread you can see in the log file logfile_example_thread.log that the 50 generated threads made entries in the log file in an unpredictable order.

# Performance

The sample program logfile_example can be used to test how many lines can be written to the log file at a time. Here are examples of writing 100.000 lines per time that I've found with my systems:  
Intel i7-4720 HQ @ 2.6 GHz: 2.9 seconds  
AMD Ryzen 7 2700 @ 3.7 GHz: 1.8 seconds  
Raspberry Pi 2 Model B Rev 1.1: 11.5 seconds  

# Platform

The class was only tested on Raspberry OS. The Raspberry OS for x86 was used in a virtual machine for development. 

# Outlook
The class is currently writing the content to a file. As a further development, it is conceivable to also send the content to a serial port or an I2C port. This means that the class could also be used for microcontrollers such as the ESP32. 

# Deutsche Version

# Was kann diese Klasse?

Diese Klasse kann sogenannte ini-Dateien lesen und wertet den Inhalt als Konfiguration f√ºr ein Programm aus. Die Klasse kann diese Typen von Parametern unterscheiden:

Strings (Zeichenketten)  
Ganze Zahlen (Integer) ohne Vorzeichen  
Ganze Zahlen (Integer) mit Vorzeichen  
Flie√ükommazahlen (positive wie negative)  
Wahrheitswerte (true oder false)  
Die Klasse hat eine Map, um die Parameter und die Werte mit Angabe des Typs zu den Parametern zu speichern. In der ersten Spalte steht der Name des Parameters und in der zweiten Spalte steht der Wert mit Angabe des Typs dazu.

Beispiel 1: Als Parameter soll in der ini-Datei der Nachname einer Person angegeben werden. Der passende Typ zu diesem Parameter w√§re dann ein String.  
Beispiel 2: Als Parameter soll in der ini-Datei das Alter einer Person angegeben werden. Der passende Typ zu diesem Parameter w√§re dann ein Integer ohne Vorzeichen.  

Die Klasse stellt Methoden zur Verf√ºgung, um aus der Map zu einem Parameter den Wert auszulesen und auch wieder in der Map zu speichern. Damit kann die Map als Speicher f√ºr die Konfiguration des Programms genutzt werden. Ein Schreiben der Map in eine ini-Datei (zum Beispiel beim Beenden des Programms) ist aktuell nicht realisiert.

<<<<<<< HEAD
Flieﬂkommazahlen (positive wie negative). Als Trennzeichen zwischen dem ganzzahligem Teil und dem gebrochenen Teil wird das ```,``` verwendet und nicht der ```.```.

Wahrheitswerte. Diese kˆnnen ```true``` oder ```false``` lauten.
=======
# Fehlersituationen

Beim Anwenden der Klasse kann es zu folgenden Fehlersituationen kommen:  
In der ini-Datei wird ein Parameter gesucht aber nicht gefunden. In diesem Fall wird eine Fehlermeldung ausgegeben.  
In der ini-Datei wird ein Parameter gefunden aber der Wert dazu passt nicht zu dem gew√ºnschten Typ. Beispiele: Es wird eine ganze Zahl als Wert erwartet aber durch einen Tippfehler sind Buchstaben in dem Wert enthalten. Es wird ein Wahrheitswert erwartet (true oder false) aber als Wert ist eine Zahl angegeben.  
Beim Einlesen und Auswerten der ini-Datei finden Plausibilit√§tstests statt, ob der Wert zu dem Typ passt, der in der oben erw√§hnten Map angegeben ist. Scheitern die Plausibilit√§tstests, so wird eine Fehlermeldung erzeugt.
Mit dem Beispielprogramm ```inifile_example.cpp``` und der ini-Datei ```inifile_example.ini``` wird gezeigt, wie auf diese Fehler reagiert werden kann.
>>>>>>> 8cc0eb87a50f771f665ce486204fc2a685bfad23


<<<<<<< HEAD
Beispiel 1: Als Parameter soll in der ini-Datei der Nachname einer Person angegeben werden. Der passende Typ zu diesem Parameter w‰re dann ein String.

Beispiel 2: Als Parameter soll in der ini-Datei das Alter einer Person angegeben werden. Der passende Typ zu diesem Parameter w‰re dann ein Integer ohne Vorzeichen

Die Klasse stellt Methoden zur Verf¸gung, um aus der Map zu einem Parameter den Wert auszulesen und auch wieder in der Map zu speichern. Damit kann die Map als Speicher f¸r die Konfiguration des Programms genutzt werden. Ein Schreiben der Map in eine ini-Datei (zum Beispiel beim Beenden des Programms) ist aktuell nicht realisiert.  
Mit dem Zeichen '\#' kˆnnen Kommentare markiert werden. Alle Zeichen nach dem '\#' werden ignoriert.  
Das '=' wird genutzt, um den Parameter vom Wert zu trennen. Vor und nach dem '=' d¸rfen keine Leerzeichen stehen.

Die oben erw‰hnte Map muss vom Anwender der Klasse mit Werten gef¸llt werden. Dazu muss der Anwender den zu suchenden Parameter und den erwartenden Typ (String, Integer, Wahrheitswert etc.) des Wertes angeben. Die Klasse liest dann die ini-Datei ein und versucht, den Parameter und den Wert dazu zu finden. Der gefundene Wert wird dann nach dem angegebenen Typ in der Map abgelegt. Das hat den Vorteil, dass dies Konvertierung von Strings (die in der ini-Datei stehen) in Integer etc. nicht sp‰ter im Programmablauf vorgenommen werden muss.

# Beispiel f¸r eine ini-Datei

Hier ein Beispiel f¸r eine ini-Datei:
```
# Configuration file for inifile_example 
# All values must be specified in the following way:  
# <parameter>=<value>  
last_name=Miller
average_age=45,87
male=true
size_in_cm=178
```
# Fehlersituationen

Beim Anwenden der Klasse kann es zu folgenden Fehlersituationen kommen:  
In der ini-Datei wird ein Parameter gesucht aber nicht gefunden. In diesem Fall wird eine Fehlermeldung ausgegeben.  
In der ini-Datei wird ein Parameter gefunden aber der Wert dazu passt nicht zu dem gew¸nschten Typ. Beispiele: Es wird eine ganze Zahl als Wert erwartet aber durch einen Tippfehler sind Buchstaben in dem Wert enthalten. Es wird ein Wahrheitswert erwartet (true oder false) aber als Wert ist eine Zahl angegeben.  
Beim Einlesen und Auswerten der ini-Datei finden Plausibilit‰tstests statt, ob der Wert zu dem Typ passt, der in der oben erw‰hnten Map angegeben ist. Scheitern die Plausibilit‰tstests, so wird eine Fehlermeldung erzeugt.
Mit dem Beispielprogramm ```inifile_example.cpp``` und der ini-Datei ```inifile_example.ini``` wird gezeigt, wie auf diese Fehler reagiert werden kann.


# Beispielprogramm

Das Beispielprogramm ```inifile_example.cpp``` liest die ini-Datei ```inifile_example.ini``` ein und zeigt die Werte auf dem Bildschirm an. Um das Programm zu erzeugen, kann das Make-File ```makefile``` genutzt werden. Es wird vorausgesetzt, dass die Klassen-Dateien im Verzeichnis ```/home/pi/cpp_sources``` liegen.

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS f¸r x86 in einer virtuellen Maschine genutzt. Das Programm l‰uft bei mir auf einem Raspberry Pi 2B.  

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS f¸r x86 in einer virtuellen Maschine genutzt. Die Klasse wird aber auf einem Raspberry Pi (ARMHF) eingesetzt.
=======
# Beispielprogramm

Das Beispielprogramm ```inifile_example.cpp``` liest die ini-Datei ```inifile_example.ini``` ein und zeigt die Werte auf dem Bildschirm an. Um das Programm zu erzeugen, kann das Make-File ```makefile``` genutzt werden. Es wird vorausgesetzt, dass die Klassen-Dateien im Verzeichnis ```/home/pi/cpp_sources``` liegen.

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS f√ºr x86 in einer virtuellen Maschine genutzt. Das Programm l√§uft bei mir auf einem Raspberry Pi 2B.  
>>>>>>> 8cc0eb87a50f771f665ce486204fc2a685bfad23

# Ausblick
Es w√§re vielleicht hilfreich, die Map mit den Parametern und den Werten auch wieder in die Ini-Datei zur√ºckzuschreiben. Das ist aber nicht so ganz einfach, weil die Kommentare in der ini-Datei erhalten bleiben sollen.
