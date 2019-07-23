#include "renderer.h"
#include <stdio.h>

Eternal::Renderer::Renderer() {
    bInitialized = false;
}

Eternal::Renderer::~Renderer() {
    if(bInitialized) {
        glDeleteVertexArrays(1, &vertArrObj);
        glDeleteBuffers(3, arrayBuffers);
    }
}

void Eternal::Renderer::Initialize() {
    bInitialized = true;

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);
    glGenBuffers(3, arrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Eternal::Renderer::SetColor(float r, float g, float b, float a) {
    for(int i = 0;i < 6;i++) {
        ColorBuffer[i].r = r;
        ColorBuffer[i].g = g;
        ColorBuffer[i].b = b;
        ColorBuffer[i].a = a;
    }
}

void Eternal::Renderer::DrawQuad(Eternal::Quad &quad) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    vVertexBuffer[0].x = quad.v[0].x; vVertexBuffer[0].y = quad.v[0].y;
    vVertexBuffer[1].x = quad.v[1].x; vVertexBuffer[1].y = quad.v[1].y;
    vVertexBuffer[2].x = quad.v[2].x; vVertexBuffer[2].y = quad.v[2].y;

    vVertexBuffer[3].x = quad.v[0].x; vVertexBuffer[3].y = quad.v[0].y;
    vVertexBuffer[4].x = quad.v[2].x; vVertexBuffer[4].y = quad.v[2].y;
    vVertexBuffer[5].x = quad.v[3].x; vVertexBuffer[5].y = quad.v[3].y;

    for(int i = 0;i < 6;i++) {
        vVertexBuffer[i].x /= 320;
        vVertexBuffer[i].y /= 240;
    }

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (6*2) * sizeof(float), &vVertexBuffer[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, (6*4) * sizeof(float), &ColorBuffer, GL_DYNAMIC_DRAW);

	glBindVertexArray(vertArrObj);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Eternal::Renderer::DrawTriangle(Eternal::Triangle &triangle) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    vVertexBuffer[0].x = triangle.v[0].x; vVertexBuffer[0].y = triangle.v[0].y;
    vVertexBuffer[1].x = triangle.v[1].x; vVertexBuffer[1].y = triangle.v[1].y;
    vVertexBuffer[2].x = triangle.v[2].x; vVertexBuffer[2].y = triangle.v[2].y;

    for(int i = 0;i < 3;i++) {
        vVertexBuffer[i].x /= 320;
        vVertexBuffer[i].y /= 240;
    }

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (3*2) * sizeof(float), &vVertexBuffer[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, (3*4) * sizeof(float), &ColorBuffer, GL_DYNAMIC_DRAW);
	glBindVertexArray(vertArrObj);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Eternal::Renderer::DrawLine(float sx, float sy, float fx, float fy) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    vVertexBuffer[0].x = sx;    vVertexBuffer[0].y = sy;
    vVertexBuffer[1].x = fx;    vVertexBuffer[1].y = fy;
    for(int i = 0;i < 2;i++) {
        vVertexBuffer[i].x /= 320;
        vVertexBuffer[i].y /= 240;
    }

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (2*2) * sizeof(float), &vVertexBuffer[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, (2*4) * sizeof(float), &ColorBuffer, GL_DYNAMIC_DRAW);

	glBindVertexArray(vertArrObj);
	glDrawArrays(GL_LINES, 0, 2);
}