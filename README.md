–––––––––––––––––––
Dieses Programm ist Freie Software: Sie können es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation, Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren veröffentlichten Version, weiter verteilen und/oder modifizieren.

Dieses Programm wird in der Hoffnung bereitgestellt, dass es nützlich sein wird, jedoch OHNE JEDE GEWÄHR; sogar ohne die implizite Gewähr der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK. Siehe die GNU General Public License für weitere Einzelheiten.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem Programm erhalten haben. Wenn nicht, siehe https://www.gnu.org/licenses/.
–––––––––––––––––––



Dieses Programm ermöglicht es, das Brettspiel Mühle auf der Kommandozeile zu spielen. Das Programm lässt den Spieler entscheiden, ob er gemeinsam mit einem anderen vor dem Computer oder gegen den Computer spielen möchte. Es ist vollständig in C geschrieben, zur Ausführung benötigt man einen C-Compiler.

Die folgenden Dateien sind enthalten:

* checkmuehle.c
* checkmuehle.h
* main.c
* muehleio.c
* muehleio.h
* muehleio_win.c
* muehleio_win.h
* diese readme-Datei

Um zu spielen, werden zunächst die einzelnen Programmteile kompiliert und dann das gesamte Programm. Hierbei ist zu beachten, dass die Programmteile muehleio_win.c und muehleio_win.h für die Ausführung unter Windows vorgesehen sind, während die ansonsten gleichnamigen Programmteile muehleio.c und muehleio.h für die Ausführung unter Linux sowie macOS vorgesehen sind. Der einzige Unterschied zwischen den Dateien ist die farbige Ausgabe für den Benutzer, die unter Windows nicht funktioniert. Sollten bei Ihnen ebenfalls Probleme bei der farbigen Ausgabe auftreten, können Sie aber natürlich auch mit anderen Betriebssystemen als Windows die farblosen _win-Dateien nutzen. Beim Kompilieren sollten folgende Befehle benutzt werden (mit gcc):

gcc muehleio.c -c
gcc checkmuehle.c -c
gcc main.c muehleio.o checkmuehle.o

Oder für die farblose Version: 

gcc muehleio_win.c -c
gcc checkmuehle.c -c
gcc main.c muehleio.o checkmuehle.o

Die anschließende Ausführung des Programms ist abhängig vom Betriebssystem.

Das Programm leitet den bzw. die Spieler vollständig durch den Spielablauf und gibt hierbei Rückmeldung über falsche Eingaben und Regelbrüche. Es berücksichtigt hierbei sämtliche offizielle Spielregeln, wie beispielsweise:

* Kann ein Spieler keinen Zug mehr machen, weil er von den Steinen des Gegners eingesperrt ist, hat er verloren.
* In der Ziehphase darf man sich immer nur ein Feld weiter bewegen, und dieses Feld muss leer sein.
* Bei einer gebildeten Mühle darf man einen Stein des Gegners entfernen, wenn mindestens ein Stein von ihm nicht in einer Mühle ist.

Das Mühlebrett wird hierbei als zweidimensionales Koordinatensystem dargestellt:

1       ._________________._________________.
        |                 |                 |
2       |     .___________.___________.     |
        |     |           |           |     |
3       |     |     ._____._____.     |     |
        |     |     |           |     |     |
4       ._____._____.           ._____._____.
        |     |     |           |     |     |
5       |     |     ._____._____.     |     |
        |     |           |           |     |
6       |     .___________.___________.     |
        |                 |                 |
7       ._________________._________________.

        a     b     c     d     e     f     g

Positionen auf dem Spielbrett werden im Spiel über Koordinaten adressiert.

Falls ein Fehler gefunden werden sollte, wird darum gebeten, ihn an einen der Programmentwickler zu melden.

Zur Zeit sind keine Fehler bekannt.

Wir wünschen viel Spaß beim Spielen!
