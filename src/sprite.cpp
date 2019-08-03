#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Eternal::Sprite::Sprite() {
    w = h = 0;
}

Eternal::Sprite::~Sprite() {
    if(glIsTexture(myTexID)) {
        glDeleteTextures(1, &myTexID);
    }
}

void Eternal::Sprite::ClearData() {
}

void Eternal::Sprite::Load(std::string sfile) {
    SDL_Surface *surf = IMG_Load(sfile.c_str());
    if(surf == nullptr) {
        std::cout << "Couldn't load " << sfile << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &myTexID);

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);
    glGenBuffers(3, arrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindTexture(GL_TEXTURE_2D, myTexID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

    w = surf->w;
    h = surf->h;

    SDL_FreeSurface(surf);

}

void Eternal::Sprite::Draw(Rect &pos, Rect &clip) {
    glBindTexture(GL_TEXTURE_2D, myTexID);

    vVertexBuffer[0].x = pos.x;             vVertexBuffer[0].y = pos.y;
    vVertexBuffer[1].x = pos.x + pos.w;     vVertexBuffer[1].y = pos.y;
    vVertexBuffer[2].x = pos.x;             vVertexBuffer[2].y = pos.y + pos.h;

    vVertexBuffer[3].x = pos.x + pos.w;     vVertexBuffer[3].y = pos.y;
    vVertexBuffer[4].x = pos.x + pos.w;     vVertexBuffer[4].y = pos.y + pos.h;
    vVertexBuffer[5].x = pos.x;             vVertexBuffer[5].y = pos.y + pos.h;

    vTexCoords[0].x = 0;        vTexCoords[0].y = 0;
    vTexCoords[1].x = 1;        vTexCoords[1].y = 0;
    vTexCoords[2].x = 0;        vTexCoords[2].y = 1;

    vTexCoords[3].x = 1;        vTexCoords[3].y = 0;
    vTexCoords[4].x = 1;        vTexCoords[4].y = 1;
    vTexCoords[5].x = 0;        vTexCoords[5].y = 1;
    for(int i = 0;i < 6;i++) {
        vVertexBuffer[i].x /= 320;
        vVertexBuffer[i].y /= 240;
    }

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (6*2) * sizeof(float), &vVertexBuffer[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, (6*2) * sizeof(float), &vTexCoords[0], GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, (6*4) * sizeof(float), &ColorBuffer, GL_DYNAMIC_DRAW);

	glBindVertexArray(vertArrObj);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}