#include "font.h"
#include <iostream>
#include <fstream>

Eternal::Font::Font() {
    glyphList = new glyph[128];
    iFontSize = 1;
}

Eternal::Font::~Font() {
    delete [] glyphList;
}

void Eternal::Font::Load(std::string sfilename) {
    std::string filename_meta = sfilename;
    std::string filename_sheet = sfilename + ".bmp";

    std::ifstream infile;
    infile.open(filename_meta);
    if(infile.fail()) {
        std::cout << "bad filename: " << sfilename << std::endl;
    }
    infile >> iFontSize;
    for(int i = 0;i < 128;i++) {
        infile >> glyphList[i].minX;
        infile >> glyphList[i].maxX;
        infile >> glyphList[i].minY;
        infile >> glyphList[i].maxY;
        infile >> glyphList[i].advance;
    }
    infile.close();

    myFontSheet.Load(filename_sheet);
}

void Eternal::Font::DrawString(std::string str, float fromX, float fromY, float fScale, float red, float green, float blue, float alpha) {

    myFontSheet.SetColor(red, green, blue, alpha);

    float fScaledSize = (float)iFontSize * fScale;
    Eternal::Rect r(fromX, fromY, fScaledSize, fScaledSize);
    Eternal::Rect c(0 ,0, iFontSize, iFontSize);
    bool firstChar = true;
    for(int i = 0;i < str.length();i++) {
        c.x = ((int)str[i] % 16) * (iFontSize*2);
        c.y = ((int)str[i] / 16) * (iFontSize*2);

        if(str[i] == '\n') {
            r.y += (float)iFontSize * fScale;
            r.x = fromX;
            firstChar = true;
            continue;
        }
        if(!firstChar) {
            r.x += (float)(glyphList[(int)str[i-1]].advance+1) * fScale;
        }

        myFontSheet.Draw(r, c);
        
        firstChar = false;
    }
}