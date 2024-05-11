#pragma once

struct Vertex
{
    Vertex(Vector2 pos)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = 0.0f;
    }

    Vertex(float x, float y)
    {
        pos = Vector3(x, y, 0.0f);
    }

    Vector3 pos;
};

struct VertexColor 
{
    VertexColor(Vector2 pos, Vector4 color)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = 0.0f;

        this->color = color;
    }

    VertexColor(float x, float y, float r, float g, float b)
    {
          pos = Vector3(x, y, 0.0f);
        color = Vector4(r, g, b, 1.0f);
    }

    Vector3 pos;
    Vector4 color;
};

struct VertexTexture
{
    VertexTexture(float x, float y, float u, float v)
    {
        pos = Vector3(x, y, 0.0f);
         uv = Vector2(u, v);
    }

    VertexTexture(Vector2 pos, Vector2 uv)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = 0.0f;

        this->uv    = uv;
    }

    Vector3 pos;
    Vector2 uv;
};
