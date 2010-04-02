/*
 
 Copyright (c) 2010 David Petrie
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 */
 
/**
 * Unicode fonts
 */

#include "ViewController.h"

static FTFont *font;
static FTSimpleLayout layout;
static int renderMode = FTGL::RENDER_FRONT | FTGL::RENDER_BACK;
const wchar_t *mystring = L"OpenGL™ 是行业领域中最为广泛接纳的 2D/3D 图形 API, "
"其自诞生至今已催生了各种计算机平台及设备上的数千优秀应用程序。"
"OpenGL™ 是独立于视窗操作系统或其它操作系统的，亦是网络透明的。"
"在包含CAD、内容创作、能源、娱乐、游戏开发、制造业、制药业及虚拟"
"现实等行业领域中， OpenGL™ 帮助程序员实现在 PC、工作站、超级计算"
"机等硬件设备上的高性能、极具冲击力的高视觉表现力图形处理软件的开"
"发。";

ViewController::ViewController(const char* path)
{
	glDepthFunc(GL_LEQUAL);
	glClearDepthf(1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	char fontname[256];
	snprintf(fontname, 256, "%s/zh_cn.ttf", path);
	font = new FTTextureFont(fontname);
	if(font->Error())
    {
        printf("Could not load font `%s'\n", fontname);
    }
	font->FaceSize(25);
	font->CharMap(ft_encoding_unicode);
	
	layout.SetLineLength(320.0f);
	layout.SetLineSpacing(0.75f);
    layout.SetFont(font);
	layout.SetAlignment(FTGL::ALIGN_LEFT);
}


ViewController::~ViewController() 
{
	delete font;
}


void ViewController::Draw()
{
	glClearColor(0.0f, 0.0f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	glPushMatrix();
	glOrthof(0.0f, 320.0f, 
			 0.0f, 480.0f, 
			 1000.0f, -1000.0f);
	
	glDisable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	
	glTranslatef(0.0f, 340.0f, 0.0f);
	
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	layout.Render(mystring, -1, FTPoint(), renderMode);
	glPopMatrix();
	
	glPopMatrix();
	
	glDisable(GL_BLEND);
	
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

