#include <cmath>
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.


// Ein "Bildschirm", der das Setzen eines Pixels kapselt
// Der Bildschirm hat eine Auflösung (Breite x Höhe)
// Kann zur Ausgabe einer PPM-Datei verwendet werden oder
// mit SDL2 implementiert werden.
class Screen
{
public:
    int width, height;
    std::vector<Vector3df> pixels;

    Screen(const int w, const int h) : width(w), height(h), pixels(w * h, Vector3df{0, 0, 0})
    {
    }

    void setPixel(const int x, const int y, const Vector3df& color)
    {
        pixels[y * width + x] = color;
    }

    void savePPM(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        file << "P6\n" << width << " " << height << "\n255\n";

        for (auto& pixel : pixels)
        {
            file.put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[0]) * 255)))
                .put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[1]) * 255)))
                .put(static_cast<char>(static_cast<unsigned char>(std::min(1.0f, pixel[2]) * 255)));
        }

        file.close();
    }
};


// Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
// Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
// Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.
class Camera
{
public:
    Vector3df position, forward, right, up;
    float fov, aspect_ratio;

    Camera(const Vector3df& pos, const Vector3df& look_at, const float fov, const float aspect_ratio)
        : position(pos), forward((look_at - pos)), right(forward.cross_product(Vector3df{0, 1, 0})),
          up(right.cross_product(forward)),
          fov(fov),
          aspect_ratio(aspect_ratio)
    {
        forward.normalize();
        right.normalize();
        up.normalize();
    }

    [[nodiscard]] Ray3df getRay(const float x, const float y) const
    {
        const float tan_fov = std::tan(fov / 2.0f);
        Vector3df direction = forward + (x * aspect_ratio * tan_fov) * right + (y * tan_fov) * up;
        direction.normalize();

        return Ray3df{position, direction};
    }
};


// Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
// Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
// Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
// kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.


// Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.
struct Material
{
    Vector3df ambient, diffuse, specular;
    float reflectivity;

    Material(const Vector3df& amb, const Vector3df& diff, const Vector3df& spec, const float refl)
        : ambient(amb), diffuse(diff), specular(spec), reflectivity(refl)
    {
    }
};


// Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
// Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
// Kugel und Dreieck finden Sie in geometry.h/tcc
class SphereObject
{
public:
    Sphere3df sphere;
    Material material;

    SphereObject(const Sphere3df& sph, const Material& mat) : sphere(sph), material(mat)
    {
    }

    bool intersect(const Ray3df& ray, Intersection_Context<float, 3>& context) const
    {
        return sphere.intersects(ray, context);
    }
};

// verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
// im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.
class TriangleObject
{
public:
    Triangle3df triangle;
    Material material;

    TriangleObject(const Triangle3df& tri, const Material& mat) : triangle(tri), material(mat)
    {
    }

    bool intersect(const Ray3df& ray, Intersection_Context<float, 3>& context) const
    {
        return triangle.intersects(ray, context);
    }
};

// Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
// oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
// können auch zusammen in eine Datenstruktur für die gesammte zu
// rendernde "Szene" zusammengefasst werden.
Vector3df lambertianShading(const Vector3df& light_dir, const Vector3df& normal, const Material& material,
                            const Vector3df& light_intensity)
{
    const float diffuse_intensity = std::max(0.2f, light_dir * normal);
    Vector3df result = material.diffuse;
    result *= diffuse_intensity;
    result[0] *= light_intensity[0];
    result[1] *= light_intensity[1];
    result[2] *= light_intensity[2];

    return result;
}


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
// NOLINTNEXTLINE
Vector3df trace(const Ray3df& ray, const std::vector<SphereObject>& spheres, const std::vector<TriangleObject>& planes,
                const Vector3df& light_pos, const Vector3df& light_intensity, int depth)
{
    if (depth <= 0) return Vector3df{0.05f, 0.05f, 0.05f}; // Background color

    Intersection_Context<float, 3> closest_context;
    const SphereObject* closest_sphere = nullptr;
    const TriangleObject* closest_plane = nullptr;
    float closest_distance = std::numeric_limits<float>::max();

    // Find the closest intersection
    for (const auto& sphere : spheres)
    {
        if (Intersection_Context<float, 3> context; sphere.intersect(ray, context) && context.t < closest_distance)
        {
            closest_distance = context.t;
            closest_context = context;
            closest_sphere = &sphere;
            closest_plane = nullptr;
        }
    }

    for (const auto& plane : planes)
    {
        if (Intersection_Context<float, 3> context; plane.intersect(ray, context) && context.t < closest_distance)
        {
            closest_distance = context.t;
            closest_context = context;
            closest_plane = &plane;
            closest_sphere = nullptr;
        }
    }

    if (!closest_sphere && !closest_plane) return Vector3df{0.05f, 0.05f, 0.05f};

    Vector3df hit_point = closest_context.intersection;
    Vector3df normal = closest_context.normal;
    Vector3df light_dir = light_pos - hit_point;
    light_dir.normalize();
    // NOLINTNEXTLINE
    Vector3df color{0, 0, 0};

    // Shading calculations
    if (closest_sphere)
    {
        color = lambertianShading(light_dir, normal, closest_sphere->material, light_intensity);

        if (closest_sphere->material.reflectivity > 0)
        {
            Vector3df reflection_dir = ray.direction - 2.0f * (ray.direction * normal) * normal;
            reflection_dir.normalize();
            Ray3df reflection_ray(hit_point + 1e-4f * normal, reflection_dir);
            Vector3df reflected_color = trace(reflection_ray, spheres, planes, light_pos, light_intensity, depth - 1);
            color += closest_sphere->material.reflectivity * reflected_color;
        }
    }
    else
    {
        color = lambertianShading(light_dir, normal, closest_plane->material, light_intensity);

        if (closest_plane->material.reflectivity > 0)
        {
            Vector3df reflection_dir = ray.direction - 2.0f * (ray.direction * normal) * normal;
            reflection_dir.normalize();
            Ray3df reflection_ray(hit_point + 1e-4f * normal, reflection_dir);
            Vector3df reflected_color = trace(reflection_ray, spheres, planes, light_pos, light_intensity, depth - 1);
            color += closest_plane->material.reflectivity * reflected_color;
        }
    }

    // Ambient lighting
    Vector3df ambient_light{0.1f, 0.1f, 0.1f};
    color += ambient_light;
    // Adjusted Shadow Calculation
    Vector3df shadow_ray_dir = light_pos - hit_point;
    shadow_ray_dir.normalize();
    Ray3df shadow_ray(hit_point + 1e-4f * normal, shadow_ray_dir); // Increase offset to 0.01 for accurate shadows
    bool in_shadow = false;

    // Check for shadows cast by spheres
    for (const auto& sphere : spheres)
    {
        if (Intersection_Context<float, 3> context; sphere.intersect(shadow_ray, context))
        {
            in_shadow = true;

            break;
        }
    }

    // Check for shadows cast by planes
    for (const auto& plane : planes)
    {
        if (Intersection_Context<float, 3> context; plane.intersect(shadow_ray, context))
        {
            in_shadow = true;

            break;
        }
    }

    // Apply shadow effect by darkening color
    if (in_shadow)
    {
        color *= 0.5f; // Dim color if in shadow
    }

    return color;
}

int main()
{
    // Bildschirm erstellen
    // Kamera erstellen
    // Für jede Pixelkoordinate x,y
    // Sehstrahl für x,y mit Kamera erzeugen
    // Farbe mit raytracing-Methode bestimmen
    // Beim Bildschirm die Farbe für Pixel x,y, setzten
    Screen screen(800, 600);
    // Kamera erstellen
    const Camera camera(Vector3df{0, 0, -7}, Vector3df{0, 0, 0}, M_PI / 2.0f, 800.0f / 600.0f);
    // Szene erstellen: Lichtquelle und Objekte
    const Vector3df light_position{0, -5, 0}; // Lichtquelle in der Mitte der Decke
    const Vector3df light_intensity{10.0f, 10.0f, 10.0f}; // Erhöhte Lichtintensität
    const std::vector spheres{
        SphereObject(Sphere3df(Vector3df{0, 2, 0}, 1),
                     Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.7f, 0.1f, 0.1f}, Vector3df{1, 1, 1}, 0.5f)),
        SphereObject(Sphere3df(Vector3df{2, 2, -3}, 1),
                     Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.1f, 0.7f, 0.1f}, Vector3df{1, 1, 1}, 0.3f)),
        SphereObject(Sphere3df(Vector3df{-2, 2, -3}, 1),
                     Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.1f, 0.1f, 0.7f}, Vector3df{1, 1, 1}, 0.8f)),
        // Kleine Kugel, die die Lichtquelle darstellt
        SphereObject(Sphere3df(light_position, 0.1f),
                     Material(Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1, 1, 1}, 1.0f))
    };
    const std::vector triangles{
        // Left wall (red)
        TriangleObject(Triangle3df(Vector3df{5, -5, -5}, Vector3df{5, 5, -5}, Vector3df{5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 0.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        TriangleObject(Triangle3df(Vector3df{5, -5, -5}, Vector3df{5, 5, 5}, Vector3df{5, -5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 0.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        // Right wall (green)
        TriangleObject(Triangle3df(Vector3df{-5, -5, -5}, Vector3df{-5, 5, -5}, Vector3df{-5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.0f, 1.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        TriangleObject(Triangle3df(Vector3df{-5, -5, -5}, Vector3df{-5, 5, 5}, Vector3df{-5, -5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.0f, 1.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        // Floor (white)
        TriangleObject(Triangle3df(Vector3df{-5, 5, -5}, Vector3df{5, 5, -5}, Vector3df{5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1, 1, 1}, 0.0f)),
        TriangleObject(Triangle3df(Vector3df{-5, 5, -5}, Vector3df{5, 5, 5}, Vector3df{-5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1, 1, 1}, 0.0f)),
        // Ceiling (black)
        TriangleObject(Triangle3df(Vector3df{-5, -5, -5}, Vector3df{5, -5, -5}, Vector3df{5, -5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.0f, 0.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        TriangleObject(Triangle3df(Vector3df{-5, -5, -5}, Vector3df{5, -5, 5}, Vector3df{-5, -5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{0.0f, 0.0f, 0.0f}, Vector3df{1, 1, 1}, 0.0f)),
        // Middle Wall (white)
        TriangleObject(Triangle3df(Vector3df{-5, -5, 5}, Vector3df{5, -5, 5}, Vector3df{5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1, 1, 1}, 0.0f)),
        TriangleObject(Triangle3df(Vector3df{-5, -5, 5}, Vector3df{5, 5, 5}, Vector3df{-5, 5, 5}),
                       Material(Vector3df{0.1f, 0.1f, 0.1f}, Vector3df{1.0f, 1.0f, 1.0f}, Vector3df{1, 1, 1}, 0.0f))
    };

    // Raytracing für jedes Pixel
    for (int y = 0; y < screen.height; ++y)
    {
        for (int x = 0; x < screen.width; ++x)
        {
            const float u = (2.0f * (static_cast<float>(x) + 0.5f) / static_cast<float>(screen.width) - 1.0f) * camera.
                aspect_ratio;
            const float v = 1.0f - 2.0f * (static_cast<float>(y) + 0.5f) / static_cast<float>(screen.height);
            Ray3df ray = camera.getRay(u, v);
            Vector3df color = trace(ray, spheres, triangles, light_position, light_intensity, 3);
            screen.setPixel(x, y, color);
        }
    }

    screen.savePPM("output.ppm");
    std::cout << "Rendering complete. Image saved as output.ppm\n";

    return 0;
}
