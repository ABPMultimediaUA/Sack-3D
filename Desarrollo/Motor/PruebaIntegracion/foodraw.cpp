#include "foodraw.h"
#include <GL/gl.h>
FooDraw::FooDraw()
{
    //ctor
}

FooDraw::~FooDraw()
{
    //dtor
}


void FooDraw::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color&  color){}
void FooDraw::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
    //set up vertex array
    GLfloat glverts[16]; //allow for polygons up to 8 vertices
    glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
    glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

    //fill in vertex positions as directed by Box2D
    for (int i = 0; i < vertexCount; i++) {
      glverts[i*2]   = vertices[i].x;
      glverts[i*2+1] = vertices[i].y;
    }

    //draw solid area
    glColor4f( color.r, color.g, color.b, 1);
   glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
 /*  glDrawElements(GL_TRIANGLE_FAN, 0, vertexCount);
    glDrawElements()*//*
    int indices[]={0,1,2,3,4,5};
glBindVertexArray(6);
 glDrawElements(GL_TRIANGLES,vertexCount, GL_UNSIGNED_INT,indices);*/
    //draw lines
    glLineWidth(3); //fat lines
    glColor4f( 1, 0, 1, 1 ); //purple
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
   // glDrawElements(GL_LINE_LOOP, vertexCount,GL_UNSIGNED_INT,indices);

//        glBindVertexArray(0);

}

void FooDraw::DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color){}
void FooDraw::DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){}
void FooDraw::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){}
void FooDraw::DrawTransform(const b2Transform& xf){}


