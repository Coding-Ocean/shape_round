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
int createPolygon() {
    const int NUM = 60;
    struct SHAPE_VERTEX vertices[NUM];
    float deg = 360.0f / NUM;
    angleMode(DEGREES);
    for (int i = 0; i < NUM; i++) {
        vertices[i].x = sin(deg*i);
        vertices[i].y = -cos(deg*i);
    }
    return createShape(vertices, NUM);
}
int createStar() {
    const int NUM = 10;
    struct SHAPE_VERTEX vertices[NUM];
    float deg = 360.0f / NUM;
    angleMode(DEGREES);
    for (int i = 0; i < NUM; i++) {
        float radius = 0.5f + 0.5f * (i%2);
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
            pow( sin(t), 3 ) * 0.95f;
        vertices[i].y = -(
            13 * cos(t) -
            5 * cos(2 * t) -
            2 * cos(3 * t) -
            1 * cos(4 * t) ) / 16 * 0.95f;
    }
    return createShape(vertices, NUM);
}
//角丸多角形
int createRoundPolygon(
    //角数(角になる扇形の数)
    int numCorners,
    //扇型をを分割する数（角の滑らかさ）
    int divNum,
    //扇形の半径
    float radius,
    //中心から扇形の中心までの距離
    float vlen
) {
    //必要な数だけ頂点の入れ物を用意
    const int numVertices = (divNum + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---反時計回りで頂点を用意していく---
    //扇形の中心角
    const float fanDeg = 360.0f / numCorners;
    //扇形の中心角をさらに分割した角度（角の滑らかさ）
    const float divDeg = fanDeg / divNum;
    //最初に頂点を用意する角度
    float offsetDeg = (180.0f - fanDeg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //扇形の要の位置
        int wi = i / (numVertices / numCorners);
        float vx = -sin(fanDeg * wi) * vlen;
        float vy = -cos(fanDeg * wi) * vlen;
        //頂点位置
        float deg = offsetDeg + divDeg * (i - wi);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //　シェープを作って番号を返す
    int shapeIdx = createShape(vertices, numVertices);
    delete[] vertices;
    return shapeIdx;
}

void gmain() {
    window(1000, 1000);
    int triangleIdx = createTriangle();
    int polygonIdx = createPolygon();
    int starIdx = createStar();
    int heartIdx = createHeart();
    int roundIdx = createRoundPolygon(4, 10, 0.4, 0.6);
    float px = width / 2, py = height /2, deg = 0, scale = 300;
    angleMode(DEGREES);
    while (notQuit) {
        deg += 1;
        clear(255);
        strokeWeight(1);
        fill(0, 255, 0, 128);
        shape(polygonIdx, px, py, 0, scale);
        fill(255, 255, 0, 128);
        shape(starIdx, px, py, -deg, scale);
        fill(255, 0, 0, 128);
        shape(heartIdx, px, py, deg, scale);
        fill(160, 200, 255, 128);
        shape(roundIdx, px, py, 0, scale);
    }
}
