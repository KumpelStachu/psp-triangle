#include <SDL.h>
#include <vector>
#include "callbacks.h"
#include "drawingOOP.h"

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
  int offsetx, offsety, d;
  int status;

  // CHECK_RENDERER_MAGIC(renderer, -1);

  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;

  while (offsety >= offsetx)
  {

    status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
    status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
    status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

    if (status < 0)
    {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx)
    {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    }
    else if (d < 2 * (radius - offsety))
    {
      d += 2 * offsety - 1;
      offsety -= 1;
    }
    else
    {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return status;
}

SDL_Renderer *renderer;

void Circle::Draw()
{
  SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
  SDL_RenderFillCircle(renderer, m_x, m_y, m_radius);
}

int max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

int min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

void Triangle::Draw()
{
  SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);

  for (int y = min(m_p1.y, min(m_p2.y, m_p3.y)); y < max(m_p1.y, max(m_p2.y, m_p3.y)); y++)
  {
    for (int x = min(m_p1.x, min(m_p2.x, m_p3.x)); x < max(m_p1.x, max(m_p2.x, m_p3.x)); x++)
    {
      if ((m_p1.x - m_p2.x) * (y - m_p1.y) - (m_p1.y - m_p2.y) * (x - m_p1.x) > 0 &&
          (m_p2.x - m_p3.x) * (y - m_p2.y) - (m_p2.y - m_p3.y) * (x - m_p2.x) > 0 &&
          (m_p3.x - m_p1.x) * (y - m_p3.y) - (m_p3.y - m_p1.y) * (x - m_p3.x) > 0)
      {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

void Rectangle::Draw()
{
  SDL_Rect r;
  r.x = m_x;
  r.y = m_y;
  r.w = m_width;
  r.h = m_height;
  SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
  SDL_RenderFillRect(renderer, &r);
}

int main(int argv, char **args)
{
  setup_callbacks();
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

  SDL_Window *window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 272, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int a = -100;
  int dir = 1;
  int running = 1;
  SDL_Event event;
  while (running)
  {
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running = 0;
        break;
      case SDL_CONTROLLERDEVICEADDED:
        SDL_GameControllerOpen(event.cdevice.which);
        break;
      case SDL_CONTROLLERBUTTONDOWN:
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
          running = 0;
        break;
      }
    }

    if (dir == 1)
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    else
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);
    Color color = Color{1, 2, 3, 4};
    std::vector<Shape *> items;

    a += dir;
    if (a > 100)
      dir = -1;
    else if (a < -100)
      dir = 1;
    int i = a - 100;
    unsigned char col = dir == 1 ? 0 : 255;

    Rectangle *rectangle = new Rectangle(350, 200 + (i < 0 ? i : i * -1), 30 + i + 100, 40, Color{123, 123, 123, 255});
    Circle *circle = new Circle(250 + i, 50 - i, 38, Color{10, 250, 120, 255});
    Triangle *triangle = new Triangle({250 + i, 120}, {190 + i, 200}, {270 + i, 190}, Color{col, col, col, 255});

    items.push_back(rectangle);
    items.push_back(circle);
    items.push_back(triangle);

    for (Shape *it : items)
    {
      it->Draw();
      delete it;
    }

    items.clear();
    SDL_RenderPresent(renderer);
  }

  return 0;
}