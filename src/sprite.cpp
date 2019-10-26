#include "sprite.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Eternal::Sprite::Sprite() {
    w = h = 0;
    bFlipU = bFlipV = false;
}

Eternal::Sprite::~Sprite() {
    if(glIsTexture(myTexID)) {
        glDeleteTextures(1, &myTexID);
    }
}

void Eternal::Sprite::ClearData() {
}

void Eternal::Sprite::Load(std::string sfile) {
    sName = sfile;

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

    SDL_Surface *surf = IMG_Load(sfile.c_str());
    if(surf == nullptr) {
        std::cout << "Couldn't load " << sfile << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

    w = surf->w;
    h = surf->h;

    SDL_FreeSurface(surf);

}

void Eternal::Sprite::ForceResize(int width, int height ){
    w = width;
    h = height;
}

void Eternal::Sprite::Draw(Rect &pos, Rect &clip) {
    glBindTexture(GL_TEXTURE_2D, myTexID);

    Draw_NoBind(pos, clip);
}

void Eternal::Sprite::Draw_NoBind(Rect &pos, Rect &clip) {
    vVertexBuffer[0].x = pos.x;             vVertexBuffer[0].y = pos.y;
    vVertexBuffer[1].x = pos.x + pos.w;     vVertexBuffer[1].y = pos.y;
    vVertexBuffer[2].x = pos.x;             vVertexBuffer[2].y = pos.y + pos.h;

    vVertexBuffer[3].x = pos.x + pos.w;     vVertexBuffer[3].y = pos.y;
    vVertexBuffer[4].x = pos.x + pos.w;     vVertexBuffer[4].y = pos.y + pos.h;
    vVertexBuffer[5].x = pos.x;             vVertexBuffer[5].y = pos.y + pos.h;


    const float cx = clip.x / w;
    const float cy = clip.y / h;
    if(w == 0 || h == 0) {
        std::cout << "tf???" << sName << std::endl;
    }
    const float cw = (clip.x / w) + clip.w / w;
    const float ch = (clip.y / h) + clip.h / h;

    vTexCoords[0].x = cx;        vTexCoords[0].y = cy;
    vTexCoords[1].x = cw;        vTexCoords[1].y = cy;
    vTexCoords[2].x = cx;        vTexCoords[2].y = ch;

    vTexCoords[3].x = cw;        vTexCoords[3].y = cy;
    vTexCoords[4].x = cw;        vTexCoords[4].y = ch;
    vTexCoords[5].x = cx;        vTexCoords[5].y = ch;
    for(int i = 0;i < 6;i++) {
        vVertexBuffer[i].x /= (WIN_W / 2);
        vVertexBuffer[i].y /= (WIN_H / 2);

        if(bFlipV) {
            vTexCoords[i].y = 1.0f - vTexCoords[i].y;
        }
        if(bFlipU) {
            vTexCoords[i].x = 1.0f - vTexCoords[i].x;
        }
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