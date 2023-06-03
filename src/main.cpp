#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>

#define EPSILON 0.0001f

struct Coords
{
    int x, y;

    bool operator==(const Coords& other)
    {
        return x == other.x and y == other.y;
    }
};

struct Segment
{
    Coords p1, p2;
};

struct Triangle
{
    Coords p1, p2, p3;
    bool complet=false;
};

struct Application
{
    int width, height;
    Coords focus{100, 100};

    std::vector<Coords> points;
    std::vector<Triangle> triangles;
};

bool compareCoords(Coords point1, Coords point2)
{
    if (point1.y == point2.y)
        return point1.x < point2.x;
    return point1.y < point2.y;
}

void drawPoints(SDL_Renderer *renderer, const std::vector<Coords> &points)
{
    for (std::size_t i = 0; i < points.size(); i++)
    {
        filledCircleRGBA(renderer, points[i].x, points[i].y, 3, 240, 240, 23, SDL_ALPHA_OPAQUE);
    }
}

void drawSegments(SDL_Renderer *renderer, const std::vector<Segment> &segments)
{
    for (std::size_t i = 0; i < segments.size(); i++)
    {
        lineRGBA(
            renderer,
            segments[i].p1.x, segments[i].p1.y,
            segments[i].p2.x, segments[i].p2.y,
            240, 240, 20, SDL_ALPHA_OPAQUE);
    }
}

void drawTriangles(SDL_Renderer *renderer, const std::vector<Triangle> &triangles)
{
    for (std::size_t i = 0; i < triangles.size(); i++)
    {
        const Triangle& t = triangles[i];
        trigonRGBA(
            renderer,
            t.p1.x, t.p1.y,
            t.p2.x, t.p2.y,
            t.p3.x, t.p3.y,
            0, 240, 160, SDL_ALPHA_OPAQUE
        );
    }
}

void draw(SDL_Renderer *renderer, const Application &app)
{
    // Remplissez cette fonction pour faire l'affichage du jeu
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    drawPoints(renderer, app.points);
    drawTriangles(renderer, app.triangles);
}


// Détermine si un point se trouve dans un cercle définit par trois points
// Retourne, par les paramètres, le centre et le rayon
bool CircumCircle(
    float pX, float pY,
    float x1, float y1, float x2, float y2, float x3, float y3,
    float *xc, float *yc, float *rsqr
)
{
    float m1, m2, mx1, mx2, my1, my2;
    float dx, dy, drsqr;
    float fabsy1y2 = fabs(y1 - y2);
    float fabsy2y3 = fabs(y2 - y3);

    // On vérifie si des points coincident
    if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
        return (false);

    if (fabsy1y2 < EPSILON)
    {
        m2 = -(x3 - x2) / (y3 - y2);
        mx2 = (x2 + x3) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (x2 + x1) / 2.0;
        *yc = m2 * (*xc - mx2) + my2;
    }
    else if (fabsy2y3 < EPSILON)
    {
        m1 = -(x2 - x1) / (y2 - y1);
        mx1 = (x1 + x2) / 2.0;
        my1 = (y1 + y2) / 2.0;
        *xc = (x3 + x2) / 2.0;
        *yc = m1 * (*xc - mx1) + my1;
    }
    else
    {
        m1 = -(x2 - x1) / (y2 - y1);
        m2 = -(x3 - x2) / (y3 - y2);
        mx1 = (x1 + x2) / 2.0;
        mx2 = (x2 + x3) / 2.0;
        my1 = (y1 + y2) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (fabsy1y2 > fabsy2y3)
        {
            *yc = m1 * (*xc - mx1) + my1;
        }
        else
        {
            *yc = m2 * (*xc - mx2) + my2;
        }
    }

    dx = x2 - *xc;
    dy = y2 - *yc;
    *rsqr = dx * dx + dy * dy;

    dx = pX - *xc;
    dy = pY - *yc;
    drsqr = dx * dx + dy * dy;

    return ((drsqr - *rsqr) <= EPSILON ? true : false);
}

void construitVoronoi(Application &app)
{
    // On tri les points
    std::sort(app.points.begin(), app.points.end(), compareCoords);

    // On vide la liste de triangles
    app.triangles.clear();

    // On créé le très gros triangles :O
    Triangle veryBigTriangle;
    veryBigTriangle.p1.x = -1000;
    veryBigTriangle.p1.y = -1000;
    veryBigTriangle.p2.x = 500;
    veryBigTriangle.p2.y = 3000;
    veryBigTriangle.p3.x = 1500;
    veryBigTriangle.p3.y = -1000;
    // On l'ajoute à la liste de triangles déjà créés
    app.triangles.push_back(veryBigTriangle);

    size_t nb_points = app.points.size();
    // Pour chaque point P du repère...
    for (const Coords& P : app.points)
    {
        // On créé une liste de segments LS
        std::vector<Segment> LS;

        // Pour chaque triangle T déjà créé...
        // (On utilise un itérateur pour pouvoir ensuite utiliser correctement erase)
        for (auto it = app.triangles.begin(); it != app.triangles.end();)
        {
            const Triangle& T = *it;

            // Si le cercle circonscrit contient le point P...
            float xc, yc, rsqr;
            if (CircumCircle(P.x, P.y, T.p1.x, T.p1.y, T.p2.x, T.p2.y, T.p3.x, T.p3.y, &xc, &yc, &rsqr))
            {
                SDL_Log("yo yo yo c dedans !\n");

                // Récupère les segments de ce triangle dans LS
                Segment s1, s2, s3;
                s1.p1 = T.p1;
                s1.p2 = T.p2;
                s2.p1 = T.p2;
                s2.p2 = T.p3;
                s3.p1 = T.p3;
                s3.p2 = T.p1;
                LS.push_back(s1);
                LS.push_back(s2);
                LS.push_back(s3);

                // On enlève le triangle T de la liste
                SDL_Log("test: %i", it);
                it = app.triangles.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Pour chaque segment S de la liste LS...
        for (Segment& segment : LS)
        {
            for (auto it = LS.begin(); it != LS.end();)
            {
                // Si un segment est un doublon d'un autre...
                if (segment.p1 == it->p2 && segment.p2 == it->p1)
                {
                    // On le vire !!!
                    it = LS.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        // Pour chaque segment S de la liste LS...
        for (const Segment& segment : LS)
        {
            // On créé un nouveau triangle composé du segment S et du point P
            Triangle newTriangle;
            newTriangle.p1 = segment.p1;
            newTriangle.p2 = segment.p2;
            newTriangle.p3 = P;
            app.triangles.push_back(newTriangle);
        }
    }
}

bool handleEvent(Application &app)
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return false;
        else if (e.type == SDL_WINDOWEVENT_RESIZED)
        {
            app.width = e.window.data1;
            app.height = e.window.data1;
        }
        else if (e.type == SDL_MOUSEWHEEL)
        {
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
                app.focus.x = e.button.x;
                app.focus.y = e.button.y;
                app.points.clear();
            }
            else if (e.button.button == SDL_BUTTON_LEFT)
            {
                app.focus.y = 0;
                app.points.push_back(Coords{e.button.x, e.button.y});
                construitVoronoi(app);
            }
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    SDL_Window *gWindow;
    SDL_Renderer *renderer;
    Application app{720, 720, Coords{0, 0}};
    bool is_running = true;

    // Creation de la fenetre
    gWindow = init("Awesome Voronoi", 720, 720);

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    // MAIN LOOP
    while (true)
    {
        // INPUTS
        is_running = handleEvent(app);
        if (!is_running)
            break;

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        

        // DESSIN
        draw(renderer, app);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);
    }

    // Libère les ressources et ferme SDL
    close(gWindow, renderer);

    return 0;
}
