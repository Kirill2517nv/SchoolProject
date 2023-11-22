#pragma once
#include <imgui/imgui.h>

struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 1000) {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};

struct Planet {
    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;
    ScrollingBuffer trace;
    ScrollingBuffer E_k;
    ScrollingBuffer E_p;
    ScrollingBuffer E_f;
};

class Gravity {
public:
	Gravity();
	void calculate(float time, float dt);
	void set_initial_conditions();
	~Gravity() = default;

    Planet get_Sun() { return  Sun; }
    Planet get_Earth() { return Earth; }

    void set_Earth_x(float x) { Earth.x = x; }
    void set_Earth_y(float y) { Earth.y = y; }
    void set_Earth_vx(float vx) { Earth.vx = vx; }
    void set_Earth_vy(float vy) { Earth.vy = vy; }

private:
    Planet Sun;
    Planet Earth;
};

