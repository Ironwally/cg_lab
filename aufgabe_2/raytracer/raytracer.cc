#include "math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>

#include "raytracer/screen/Screen.h"
#include "raytracer/configuration/configuration.h"
#include "raytracer/objects/Camera.h"
#include "raytracer/tracer/Tracer.h"


// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.

int main(void) {
  // Konfiguration
  // Bildschirm erstellen
  auto screen = Screen(1024, 768);
  // Ein "Bildschirm", der das Setzen eines Pixels kapselt
  // Der Bildschirm hat eine Auflösung (Breite x Höhe)
  // Kann zur Ausgabe einer PPM-Datei verwendet werden oder
  // mit SDL2 implementiert werden.


  // Create camera
  const auto camera = Camera();
  // Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
  // Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
  // Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.

  // Create color
  // Vectorclr <=> Vector<unsigned char, 3> stores: 0 - 255
  // Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
  // Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
  // Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
  // kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.

  // Create material
  // Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.

  // Create 3d objects
  // Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
  // Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
  // Kugel und Dreieck finden Sie in geometry.h/tcc

  // Create materialdefinitions
  // verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
  // im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.

  // ??
  // Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
  // oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
  // können auch zusammen in eine Datenstruktur für die gesammte zu
  // rendernde "Szene" zusammengefasst werden.

  // Create cornelbox/3d scene
  // Die Cornelbox aufgebaut aus den Objekten
  // Am besten verwendet man hier einen std::vector< ... > von Objekten.

  // Create lights (as objects)
  // Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
  // bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
  // Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.

  // Implement Lambertian-Shading
  // Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
  // Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
  // Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
  // Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

  // Implement Sehstrahl (Primary ray) as look-up of closest past objects?
  // Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
  // Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

  // Create tracer
  auto tracer = Tracer(screen, camera);
  // The raytracing method. What does this mean? Raytrace EVERYTHING? (All shaders, etc.?)
  // Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.


  // trace ray per pixel
  tracer.tracePrimary();

  // Für jede Pixelkoordinate x,y
  //   Reihenfolge festlegen
  //     - Schwacher PC -> zufaellige Reihenfolge der Pixel rekursiv besser werdendes Bild zu erzeugen
  //   Sehstrahl für x,y mit Kamera erzeugen
  //   Farbe mit raytracing-Methode bestimmen
  //   Beim Bildschirm die Farbe für Pixel x,y, setzten

  // In SDL umwandeln


  return 0;   
}

