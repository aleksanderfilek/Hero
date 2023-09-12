#pragma once

#ifdef HERO_EXPORTS
#define HERO_API __declspec(dllexport)
#else
#define HERO_API __declspec(dllimport)
#endif