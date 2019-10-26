#include "framebuffer.h"
#include <stdio.h>
Eternal::FrameBuffer::FrameBuffer() {
    iWidth = iHeight = 0;
}

Eternal::FrameBuffer::~FrameBuffer() {
}

void Eternal::FrameBuffer::Initialize(int w, int h) {
    iWidth = w;
    iHeight = h;

    glGenTextures(1, &myTextureID);
	glBindTexture(GL_TEXTURE_2D, myTextureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // gen renderbuffer
    glGenRenderbuffers(1, &myRenderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, myRenderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, iWidth, iHeight);

    // gen framebuffer
    glGenFramebuffers(1, &myFrameBufferID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, myFrameBufferID);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myTextureID, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("fbo error\n");
    }
}

void Eternal::FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, myFrameBufferID);
    glViewport(0,0,iWidth,iHeight);
}