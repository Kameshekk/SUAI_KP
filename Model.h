#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
//#include "View.h"

#define WIDTH 1200
#define HEIGHT 600

#define MARGIN_TOP 100
#define MARGIN_LEFT 150
#define MARGIN_BETWEEN_FIELDS 300

#define CELL_SIZE 30

using namespace std;

enum Ship_state
{
    empt = 0,
    located,
    damaged,
    miss,
    kill
};

class Model
{
    //View* View_of_game;
    HWND hWnd;
public:
    //Ship_state state_ship;
    int heals_my;
    int heals_his;
    int** field_my;
    int** field_his;
    Model(HWND _hWnd);
    ~Model();
    bool check();
    void set_heals(char who, int health);
    int get_heals(char who);
    int set_on_field(char who, int horizontal, int vertical, int set_cell);
    int get_from_field(char who, int horizontal, int vertical);
};

#endif

