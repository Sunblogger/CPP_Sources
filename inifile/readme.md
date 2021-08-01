# inifile
# C++ class for reading ini-file for configuration of a program.

German version [below](#deutsche-version).

# What can this class do?

This class can read so-called ini files and evaluates the content as a configuration for a program. The class can distinguish between these types of parameters:

Strings
Unsigned whole numbers (integers)
Signed whole numbers (integers)
Floating point numbers (positive and negative). The ``.`` Is used as the separator between the integer part and the fractional part and not the ``,``.
Truth values: These can be ``true`` or ``false``.
The class has a map ```var_map``` to save the parameters and the values with specification of the type for the parameters. The name of the parameter is in the first column. In the second column there is a struct that stores both the type of the parameter and the value of the parameter.
Example 1: The surname of a person is to be specified as a parameter in the ini file. The appropriate type for this parameter would then be a string.
Example 2: The age of a person in whole years is to be specified as a parameter in the ini file. The appropriate type for this parameter would then be an unsigned integer.

The class provides methods to read the value of a parameter from the map and to save it again in the map. This means that the map can be used as memory for the configuration of the program. Writing the map to an ini file (for example when exiting the program) is currently not implemented.

The class should be used in these steps: First, the ini file is read in using the ```read_ini_file()``` method. Then the mentioned ```var_map``` is filled with values.

# Error situations

The following error situations can occur when using the class:
A parameter is searched for in the ini file but not found. In this case an error message is issued.
A parameter is found in the ini file, but the associated value does not match the desired type. Example 1: An integer is expected as a value, but letters are included in the value due to a typo. Example 2: A truth value is expected (true or false) but a number is specified as the value.
When reading in and evaluating the ini file, plausibility tests are carried out to determine whether the value matches the type specified in the above-mentioned map. If the plausibility tests fail, an error message is generated. All values entered in the map up to then are correct. However, the program should be aborted if no correct values ​​could be taken from the INI file.
The example program ```inifile_example.cpp``` and the ini file ```inifile_example.ini``` show how to react to these errors.
Example 1: The surname of a person is to be specified as a parameter in the ini file. The appropriate type for this parameter would then be a string.
Example 2: The age of a person is to be specified as a parameter in the ini file. The appropriate type for this parameter would then be an unsigned integer.

The class provides methods to read the value of a parameter from the map and to save it again in the map. This means that the map can be used as memory for the configuration of the program. Writing the map to an ini file (for example when exiting the program) is currently not implemented.
Comments can be marked with the '\ #' character. All characters after the '\ #' are ignored.
The '=' is used to separate the parameter from the value. There must be no spaces before or after the '='.

The above-mentioned map must be filled with values ​​by the user of the class. To do this, the user must specify the parameter to be searched for and the expected type (string, integer, truth value, etc.) of the value. The class then reads the ini file and tries to find the parameter and the value for it. The value found is then stored in the map according to the specified type. This has the advantage that the conversion of strings (which are in the ini file) into integers etc. does not have to be carried out later in the program sequence.

# Example of an ini file

Here is an example of an ini file:
``
# Configuration file for inifile_example
# All values must be specified in the following way:
# <parameter> = <value>
last_name = Miller
average_age = 45.87
male = true
size_in_cm = 178
``

# Sample program

The sample program `` inifile_example.cpp '' reads the ini file `` inifile_example.ini '' and displays the values on the screen. The make file `` makefile '' can be used to generate the program. It is assumed that the class files are in the directory ```/home/pi/cpp_sources```. 

# Platform

The class was only tested on Raspberry OS. The Raspberry OS for x86 was used in a virtual machine for development. However, the class is used on a Raspberry Pi 2B (ARMHF).

# Outlook
It might be helpful to write the map with the parameters and the values back to the ini file. But this is not that easy, because the comments should be retained in the ini file. 

# Deutsche Version

# Was kann diese Klasse?

Diese Klasse kann sogenannte ini-Dateien lesen und wertet den Inhalt als Konfiguration fÃ¼r ein Programm aus. Die Klasse kann diese Typen von Parametern unterscheiden:

Strings (Zeichenketten)  
Ganze Zahlen (Integer) ohne Vorzeichen  
Ganze Zahlen (Integer) mit Vorzeichen  
Fließkommazahlen (positive wie negative). Als Trennzeichen zwischen dem ganzzahligem Teil und dem gebrochenen Teil wird der ```.``` verwendet und nicht das ```,```.   
Wahrheitswerte: Diese können ```true``` oder ```false``` lauten.  
Die Klasse hat eine Map ```var_map```, um die Parameter und die Werte mit Angabe des Typs zu den Parametern zu speichern. In der ersten Spalte steht der Name des Parameters. In der zweiten Spalte steht ein Struct, der sowohl den Typ des Parameters als auch den Wert zum Parameter speichert.  
Beispiel 1: Als Parameter soll in der ini-Datei der Nachname einer Person angegeben werden. Der passende Typ zu diesem Parameter wäre dann ein String.  
Beispiel 2: Als Parameter soll in der ini-Datei das Alter einer Person in ganzen Jahren angegeben werden. Der passende Typ zu diesem Parameter wäre dann ein Integer ohne Vorzeichen.  

Die Klasse stellt Methoden zur Verfügung, um aus der Map zu einem Parameter den Wert auszulesen und auch wieder in der Map zu speichern. Damit kann die Map als Speicher für die Konfiguration des Programms genutzt werden. Ein Schreiben der Map in eine ini-Datei (zum Beispiel beim Beenden des Programms) ist aktuell nicht realisiert.

Die Anwendung der Klasse sollte in diesen Schritten erfolgen: Zuerst wird die Ini-Datei eingelesen mit der Methode ```read_ini_file()```. Anschließend wird die erwähnte ```var_map``` mit Werten aufgefüllt.

# Fehlersituationen

Beim Anwenden der Klasse kann es zu folgenden Fehlersituationen kommen:  
In der ini-Datei wird ein Parameter gesucht aber nicht gefunden. In diesem Fall wird eine Fehlermeldung ausgegeben.  
In der ini-Datei wird ein Parameter gefunden aber der Wert dazu passt nicht zu dem gewünschten Typ. Beispiel 1: Es wird eine ganze Zahl als Wert erwartet aber durch einen Tippfehler sind Buchstaben in dem Wert enthalten. Beispiel 2: Es wird ein Wahrheitswert erwartet (true oder false) aber als Wert ist eine Zahl angegeben.  
Beim Einlesen und Auswerten der ini-Datei finden Plausibilitätstests statt, ob der Wert zu dem Typ passt, der in der oben erwähnten Map angegeben ist. Scheitern die Plausibilitätstests, so wird eine Fehlermeldung erzeugt. Alle bis dahin in die Map eingetragenen Werte sind korrekt. Es sollte aber das Programm abgebrochen werden, wenn keine korrekten Werte aus der Ini-Datei entnommen werden konnten.  
Mit dem Beispielprogramm ```inifile_example.cpp``` und der ini-Datei ```inifile_example.ini``` wird gezeigt, wie auf diese Fehler reagiert werden kann.
Beispiel 1: Als Parameter soll in der ini-Datei der Nachname einer Person angegeben werden. Der passende Typ zu diesem Parameter wäre dann ein String.  
Beispiel 2: Als Parameter soll in der ini-Datei das Alter einer Person angegeben werden. Der passende Typ zu diesem Parameter wäre dann ein Integer ohne Vorzeichen.  

Die Klasse stellt Methoden zur Verfügung, um aus der Map zu einem Parameter den Wert auszulesen und auch wieder in der Map zu speichern. Damit kann die Map als Speicher für die Konfiguration des Programms genutzt werden. Ein Schreiben der Map in eine ini-Datei (zum Beispiel beim Beenden des Programms) ist aktuell nicht realisiert.  
Mit dem Zeichen '\#' können Kommentare markiert werden. Alle Zeichen nach dem '\#' werden ignoriert.  
Das '=' wird genutzt, um den Parameter vom Wert zu trennen. Vor und nach dem '=' dürfen keine Leerzeichen stehen.

Die oben erwähnte Map muss vom Anwender der Klasse mit Werten gefüllt werden. Dazu muss der Anwender den zu suchenden Parameter und den erwartenden Typ (String, Integer, Wahrheitswert etc.) des Wertes angeben. Die Klasse liest dann die ini-Datei ein und versucht, den Parameter und den Wert dazu zu finden. Der gefundene Wert wird dann nach dem angegebenen Typ in der Map abgelegt. Das hat den Vorteil, dass dies Konvertierung von Strings (die in der ini-Datei stehen) in Integer etc. nicht später im Programmablauf vorgenommen werden muss.

# Beispiel für eine ini-Datei

Hier ein Beispiel für eine ini-Datei:
```
# Configuration file for inifile_example 
# All values must be specified in the following way:  
# <parameter>=<value>  
last_name=Miller
average_age=45.87
male=true
size_in_cm=178
```

# Beispielprogramm

Das Beispielprogramm ```inifile_example.cpp``` liest die ini-Datei ```inifile_example.ini``` ein und zeigt die Werte auf dem Bildschirm an. Um das Programm zu erzeugen, kann das Make-File ```makefile``` genutzt werden. Es wird vorausgesetzt, dass die Klassen-Dateien im Verzeichnis ```/home/pi/cpp_sources``` liegen.

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS für x86 in einer virtuellen Maschine genutzt. Die Klasse wird aber auf einem Raspberry Pi 2B (ARMHF) eingesetzt.  

# Ausblick
Es wäre vielleicht hilfreich, die Map mit den Parametern und den Werten auch wieder in die Ini-Datei zurückzuschreiben. Das ist aber nicht so ganz einfach, weil die Kommentare in der ini-Datei erhalten bleiben sollen.
