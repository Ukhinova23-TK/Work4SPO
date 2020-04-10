#pragma once
#ifndef APP_H
#define APP_H

struct App
{
	char name[100];
	char prouzvod[100];
	double razmer;
	double zena;
	struct App *next;
	struct App *prev;
};

#endif