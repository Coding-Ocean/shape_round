#include"libOne.h"
int createTriangle() {
    struct SHAPE_VERTEX vertices[3];
    vertices[0].x = 0;
    vertices[0].y = -0.8f;
    vertices[1].x = 0.5f;
    vertices[1].y = 1;
    vertices[2].x = -0.5f;
    vertices[2].y = 1;
    return createShape(vertices, 3);
}
int createPolygon(int numCorners) {
    struct SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numCorners];
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    for (int i = 0; i < numCorners; i++) {
        vertices[i].x = sin(deg * i);
        vertices[i].y = -cos(deg * i);
    }
    //　シェープを作って番号を返す
    int shapeIdx = createShape(vertices, numCorners);
    delete[] vertices;
    return shapeIdx;
}
int createStar() {
    const int NUM = 10;
    struct SHAPE_VERTEX vertices[NUM];
    float deg = 360.0f / NUM;
    angleMode(DEGREES);
    for (int i = 0; i < NUM; i++) {
        float radius = 0.5f + 0.5f * (i % 2);
        vertices[i].x = sin(deg * i) * radius;
        vertices[i].y = cos(deg * i) * radius;
    }
    return createShape(vertices, NUM);
}
int createHeart() {
    const int NUM = 90;
    struct SHAPE_VERTEX vertices[NUM];
    float deg = 360.0f / NUM;
    angleMode(DEGREES);
    for (int i = 0; i < NUM; i++) {
        float t = deg * i;
        vertices[i].x =
            pow(sin(t), 3) * 0.94f;
        vertices[i].y = -(
            13 * cos(t) -
            5 * cos(2 * t) -
            2 * cos(3 * t) -
            1 * cos(4 * t)) / 16 * 0.94f;
    }
    return createShape(vertices, NUM);
}
//角が丸まった多角形をつくる
int createRoundPolygon(
    //角数(角になる扇形の数)
    int numCorners,
    //角となる扇型をを分割する数（角の滑らかさ）
    int numDivisions,
    //角となる扇形の半径
    float fanRadius,
    //中心から扇形の要までの距離
    float length
) {
    //必要な数だけ頂点の入れ物を用意
    const int numVertices = (numDivisions + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---上方の丸角から反時計回りで頂点を用意していく---
    //扇形の要の位置を決めるために使用する角度(扇形の中心角でもある)
    const float deg = 360.0f / numCorners;
    //扇形の中心角をさらに分割した角度（角の滑らかさ）
    const float divDeg = deg / numDivisions;
    //最初に頂点を用意する角度
    float offsetDeg = (180.0f - deg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //扇形の要の位置
        int cornerIdx = i / (numVertices / numCorners);
        float fanCenterX = -sin(deg * cornerIdx) * length;
        float fanCenterY = -cos(deg * cornerIdx) * length;
        //各扇型の頂点位置
        float fanDeg = offsetDeg + divDeg * (i - cornerIdx);
        vertices[i].x = fanCenterX + cos(fanDeg) * fanRadius;
        vertices[i].y = fanCenterY + -sin(fanDeg) * fanRadius;
    }
    //　シェープを作って番号を返す
    int shapeIdx = createShape(vertices, numVertices);
    delete[] vertices;
    return shapeIdx;
}
