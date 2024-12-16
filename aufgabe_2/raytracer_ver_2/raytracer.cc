#include "math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.



// Ein "Bildschirm", der das Setzen eines Pixels kapselt
// Der Bildschirm hat eine Auflösung (Breite x Höhe)
// Kann zur Ausgabe einer PPM-Datei verwendet werden oder
// mit SDL2 implementiert werden.



// Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
// Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
// Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.



// Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
// Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
// Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
// kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.


// Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.



// Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
// Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
// Kugel und Dreieck finden Sie in geometry.h/tcc


// verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
// im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.


// Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
// oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
// können auch zusammen in eine Datenstruktur für die gesammte zu
// rendernde "Szene" zusammengefasst werden.

// Die Cornelbox aufgebaut aus den Objekten
// Am besten verwendet man hier einen std::vector< ... > von Objekten.

// Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
// bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
// Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.

// Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
// Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
// Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
// Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

// Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
// Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

// Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.

const int AMOUNT_RAYS = 10;
const int MAX_RECURSION_DEPTH = 5;
typedef Vector3df Vectorclr;

#ifndef MATERIAL_H
#define MATERIAL_H
class Material {
  Vector3df ambient, diffuse, specular;
  float reflective;
public:
  Material(const Vector3df& amb, const Vector3df& diff, const Vector3df& spec, const float ref) :
  ambient(amb),
  diffuse(diff),
  specular(spec),
  reflective(ref)
  {}

};
#endif //MATERIAL_H

#ifndef SPHERE3D_H
#define SPHERE3D_H

class Sphere3d {
  Sphere3df shape;
  Material material;
public:
  Sphere3d() : Sphere3d(Sphere3df({0,0,0},0), Material({0,0,0},{0,0,0},{0,0,0},0)){}
  Sphere3d(const Sphere3df& sphere, const Material& mat) : shape(sphere), material(mat) {
  }

  bool intersects(const Ray3df& ray, Intersection_Context<float, 3>& context) const {
    return shape.intersects(ray, context);
  }
};

#endif //SPHERE3D_H

class Screen {
private:
  //Vector3df left,right,bottom,top;
  std::vector<Vectorclr> pixels;
  //Vector<Vectorclr, WIDTH * HEIGHT> pixels = {}; //include = {}? // old
public:
  Vector3df position{};
  int width;
  int height;
  int length;
  Screen() : Screen(1024,768,{0,0,0}, {0,0,0}) {}
  Screen(const int width, const int height) : Screen(width, height, {0,0,0}, {0,0,0}) {}
  explicit Screen(const int width, const int height, const Vectorclr start_color, const Vector3df position) {
    this->position = position;
    this->width = width;
    this->height = height;
    this->length = width*height;
    this->pixels = {};
    for (int i = 0; i < length; i++) {
      pixels.insert(pixels.end(),start_color);
    }
  }
};

class Camera {
  public:
    Vector3df position{}; //we have this here, as the implementation geometry.h always uses position as a parameter of an object itself
    Vector3df direction{};
    int fov;
    Screen screen;
  public:
    Camera() : Camera(60, {0,0,0},{1,0,0}, 1024, 768) {}
    explicit Camera(const int fov) : Camera(fov, {0,0,0},{1,0,0}, 1024, 768) {}
    explicit Camera(const int fov, const Vectorclr position, Vectorclr direction, const int width, const int height) {
      this->position = position;
      this->direction = direction;
      this->fov = fov;

      direction *= fov;
      Vector3df screenPos = position+direction;
      this->screen = Screen(width, height, {0,0,0}, screenPos); //TODO implement screen placement based on fov value
    }

Light[] find_light_sources(HitContext hit_context) {
      Light[] visible_lights;
      for (Light light : lights) {
        Ray3df shadow_ray(hit_context.intersection,
                            light.position - hit_context.intersection);
        HitContext shadow_context = scene.find_nearest_object(shadow_ray);
        if (shadow_context == NULL) {
          visible_lights.add(light);
        }
      }
      return visible_lights;
    }

int main(void) {
  // Bildschirm erstellen
    int WIDTH = 1024;
    int HEIGHT = 768;
    Scene scene = ...
    //Screen screen(WIDTH, HEIGHT);
      Camera camera(fov);
      Screen* screen = camera.screen;
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        Ray3df ray = camera.get_ray(x,y);
        // normal, t-Param, intersection, object
        HitContext hit_context = null;
        hit_context = find_nearest_object(scene, ray);
        Color color = BACKGROUND_COLOR;
        Light [] lights;
        if (hit_context != NULL) {
          lights = scene.find_light_sources(hit_context);
          n = scene.get_lights().size();
          color = lambertian(n, lights, hit_context);
        }
        screen.set_pixel(x,y, color);
      }
    }
  // Kamera erstellen
  // Für jede Pixelkoordinate x,y
  //   Sehstrahl für x,y mit Kamera erzeugen
  //   Farbe mit raytracing-Methode bestimmen
  //   Beim Bildschirm die Farbe für Pixel x,y, setzten

  return 0;   
}

