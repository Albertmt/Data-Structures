#ifndef SCENE_H
#define SCENE_H

#include "image.h"
class Scene{
	public:
		Scene(int max);
		~Scene();
		Scene(const Scene &source);
		Scene const & operator=(const Scene &source);
		void changemaxlayers(int newmax);
		void addpicture(const char *Filename, int index, int x, int y);
		void changelayer(int index, int newindex);
		void translate(int index, int xcoord, int ycoord);
		void deletepicture(int index);
		Image* getpicture(int index) const;
		Image drawscene() const;
		

	private:
		int pictureNumber;
		Image ** pictureList;
		int *xcoords;
		int *ycoords;
		/*
		helper functions
		*/
		void _copy(Scene const & source);
		void _clear();
};

#endif
