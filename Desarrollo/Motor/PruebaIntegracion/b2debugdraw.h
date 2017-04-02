#ifndef B2DEBUGDRAW_H
#define B2DEBUGDRAW_H


class b2debugDraw
{
    public:

        virtual ~b2debugDraw() {}
      virtual      void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)=0;
      virtual  void DrawSolidPolygon( const b2Vec2* vertices, int vertexCount, const b2Color& color)=0;
      virtual  void DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color)=0;
       virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)=0;
       virtual void DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)=0;
       virtual void DrawTransform(const b2Transform& xf)=0;

    protected:

    private:
};

#endif // B2DEBUGDRAW_H
