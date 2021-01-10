#include "mesh.h"


Eternal::Mesh::Mesh() {
}

Eternal::Mesh::~Mesh() {
    if(glIsVertexArray(vertArrObj)) {
        glDeleteVertexArrays(1, &vertArrObj);
    }

    if(glIsBuffer(arrayBuffers[0])) {
        glDeleteBuffers(3, arrayBuffers);
    }

    vVertBuffer.clear();
    vTexCoords.clear();
    ColorBuffer.clear();
}

void Eternal::Mesh::Vert2(float x, float y) {
    Vec2 v(x,y);
    vVertBuffer.push_back(v);
}

void Eternal::Mesh::TexCoord2(float x, float y) {
    Vec2 v(x,y);
    vTexCoords.push_back(v);
}

void Eternal::Mesh::Color4(float r, float g, float b, float a) {
    RGBA col(r,g,b,a);
    ColorBuffer.push_back(col);
}

void Eternal::Mesh::Draw() {

    if(!glIsVertexArray(vertArrObj)) {
        glGenVertexArrays(1, &vertArrObj);
        glBindVertexArray(vertArrObj);
        glGenBuffers(3, arrayBuffers);

        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);  
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (vVertBuffer.size()*2) * sizeof(float), &vVertBuffer[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, (vTexCoords.size()*2) * sizeof(float), &vTexCoords[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, (ColorBuffer.size()*4) * sizeof(float), &ColorBuffer[0], GL_DYNAMIC_DRAW);

	glBindVertexArray(vertArrObj);
	glDrawArrays(GL_TRIANGLES, 0, vVertBuffer.size());
}

void Eternal::Mesh::Clean() {
    vVertBuffer.clear();
    vTexCoords.clear();
    ColorBuffer.clear();
}