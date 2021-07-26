# logfile
# C++ class for logging.

German version [below](#deutsche-version).

# What can this class do?

The aim of the logfile_class class is to write status messages to a log file in a running program. This class is available in 2 versions, one without threads and one with threads.
3 different levels can be specified with which information is written to the log file: information, warnings and errors. The user has to decide for himself which level the information to be written falls into.
A new line is written for each entry in the log file; the system date plus time is at the beginning of each line. Then the specified level (information, warning, error) follows and then the text.
You can specify a maximum file size that the log file should not exceed. When this limit is reached, the file is reduced by half by deleting the older half of the entries. This prevents the file from growing indefinitely.

# Threads
If you don't use threads in your program, you shouldn't use the thread variant either. The thread variant causes a bit more costs, since it works with locked mutexes. To use the thread variant, the #define thread_safe_logging (in the loggfile.hpp file) must be switched on.

# Sample programs

There are two sample programs that show how the class can be used. logfile_example is the example program without threads. logfile_example_thread is the sample program for threads.
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

Die Klasse logfile_class hat das Ziel, in einem laufenden Programm Statusmeldungen in eine Log-Datei zu schreiben. Diese Klasse liegt in 2 Versionen vor, einmal ohne Threads und einmal mit Threads.
Es können 3 unterschiedliche Stufen angegeben werden, mit denen Informationen in die Log-Datei geschrieben werden: Informationen, Warnungen und Fehler. Der Anwender muss selbst entscheiden, in welche Stufe die zu schreibende Information fällt.
Es wird je Eintrag in die Logdatei eine neue Zeile geschrieben, zu Beginn einer jeden Zeile steht das System-Datum plus Uhrzeit. Dann erfolgt die angegebene Stufe (Information, Warnung, Fehler) und dann der Text.
Man kann eine maximale Dateigröße angeben, die die Logdatei nicht überschreiten soll. Bei Erreichen dieser Grenze wird die Datei auf die Hälfte verkleinert, indem die ältere Hälfte der Einträge gelöscht wird. Damit wird ein unbegrenztes Wachsen der Datei verhindert.

# Threads

Wenn man keine Threads in seinem Programm nutzt, so sollte man auch nicht die Thread-Variante nutzen. Die Thread-Variante verursacht etwas mehr Kosten, da mit gelockten Mutexen gearbeitet wird. Um die Thread-Variante zu nutzen, muss das #define thread_safe_logging (in der Datei loggfile.hpp) angeschaltet werden.

# Beispielprogramme

Es gibt zwei Beispielprogramme, die die Anwendung der Klasse zeigen. logfile_example ist das Beispielprogramm ohne Threads. logfile_example_thread ist das Beispielprogramm für Threads.
Mit der make-Datei makefile können beide Varianten erzeugt werden. Es ist hier zu beachten, dass für die Erstellung des Thread-Beispiels das oben erwähnte #define aktiviert werden muss.
Nach Ausführung des Programms logfile_example_thread kann man in der Logdatei logfile_example_thread.log sehen, dass die 50 erzeugten Threads in nicht vorhersehbarer Reihenfolge Einträge in die Logdatei vorgenommen haben.

# Leistung

Mit dem Beispielprogramm logfile_example kann man testen, wie viele Zeilen pro Zeit in die Logdatei geschrieben werden können. Hier sind Beispiele für das Schreiben von 100.000 Zeilen pro Zeit, die ich mit meinen Systemen ermittelt habe:  
Intel i7-4720 HQ @ 2.6 GHz : 2,9 Sekunden  
AMD Ryzen 7 2700 @ 3.7 GHz : 1,8 Sekunden  
Raspberry Pi 2 Model B Rev 1.1 : 11,5 Sekunden  

# Plattform

Die Klasse wurde nur auf Raspberry OS getestet. Zur Entwicklung wurde das Raspberry OS für x86 in einer virtuellen Maschine genutzt.

# Ausblick
AKtuell schreibt die Klasse die Inhalte in eine Datei. Denkbar ist als Weiterentwicklung, die Inhalte auch auch an einen seriellen Port oder einen I2C-Port zu senden. Damit könnte die Klasse auch für Microcontroller wie dem ESP32 verwendet werden. 
