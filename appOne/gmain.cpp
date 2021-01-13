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
        vertices[i].x = sin(deg * i);
        vertices[i].y = -cos(deg * i);
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
            pow( sin(t), 3 ) * 0.94f;
        vertices[i].y = -(
            13 * cos(t) -
            5 * cos(2 * t) -
            2 * cos(3 * t) -
            1 * cos(4 * t) ) / 16 * 0.94f;
    }
    return createShape(vertices, NUM);
}
//角が丸まった多角形をつくる
int createRoundPolygon(
    //角数(角になる扇形の数)
    int numCorners,
    //角となる扇型をを分割する数（角の滑らかさ）
    int divNum,
    //角となる扇形の半径
    float fanRadius,
    //中心から扇形の要までの距離
    float length
) {
    //必要な数だけ頂点の入れ物を用意
    const int numVertices = (divNum + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---反時計回りで頂点を用意していく---
    //扇形の要の位置を決めるために使用する角度(扇形の中心角でもある)
    const float deg = 360.0f / numCorners;
    //扇形の中心角をさらに分割した角度（角の滑らかさ）
    const float divDeg = deg / divNum;
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
#define A
#ifdef A
void gmain() {
    window(1000, 1000, full);
    int roundIdx = createRoundPolygon(3, 6, 0.2f, 0.8f);
    while (notQuit) {
        clear(220);
        strokeWeight(6);
        shape(roundIdx, 500, 500, 0, 300);
    }
}
#endif
#ifdef B
void gmain() {
    window(1000, 1000, full);
    int triangleIdx = createTriangle();
    int polygonIdx = createPolygon();
    int starIdx = createStar();
    int heartIdx = createHeart();
    int roundIdx = createRoundPolygon(3, 12, 0.4f, 0.6f);
    float px = width / 2, py = height / 2, deg = 0, scale = 300;
    angleMode(DEGREES);
    ShowCursor(FALSE);
    while (notQuit) {
        deg += 1;
        clear(220);
        strokeWeight(6);
        fill(0, 255, 0, 128);
        shape(polygonIdx, px, py, 0, scale);
        fill(255, 255, 0, 128);
        shape(starIdx, px, py, -deg, scale);
        fill(255, 0, 0, 128);
        shape(heartIdx, px, py, deg, scale);
        fill(160, 200, 255, 128);
        shape(roundIdx, px, py, 0, scale);
    }
    ShowCursor(TRUE);
}
#endif
#ifdef C
void explanation(int numCorners, int divNum, float fanRadius, float length, 
    float px, float py, float scale)
{
    const int numVertices = (divNum + 1) * numCorners;
    //扇形の要の位置を決めるために使用する角度(扇形の中心角でもある)
    const float deg = 360.0f / numCorners;
    //扇形の中心角をさらに分割した角度（角の滑らかさ）
    const float divDeg = deg / divNum;
    //最初に頂点を用意する角度
    float offsetDeg = (180.0f - deg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //扇形の要の位置
        int cornerIdx = i / (numVertices / numCorners);
        float fanCenterX = px + -sin(deg * cornerIdx) * length * scale;
        float fanCenterY = py + -cos(deg * cornerIdx) * length * scale;
        stroke(0, 0, 255);
        strokeWeight(6);
        line(px, py, fanCenterX, fanCenterY);
        //各扇型の頂点位置
        int idx = i - cornerIdx;
        float fanDeg = offsetDeg + divDeg * (i - cornerIdx);
        float x = fanCenterX + cos(fanDeg) * fanRadius * scale;
        float y = fanCenterY + -sin(fanDeg) * fanRadius * scale;
        stroke(255, 0, 0);
        line(fanCenterX, fanCenterY, x, y);
        stroke(0, 0, 0);
        strokeWeight(20);
        point(x, y);
    }
    //中心の描画
    stroke(0, 0, 255);
    strokeWeight(20);
    point(px, py);
    strokeWeight(6);
    //テキスト情報
    fill(0);
    text(" length=" + (let)length + "*scale", px, py - length * scale / 2);
    text("fanRadius=" + (let)fanRadius + "*scale", px + fanRadius * scale / 2, py - length * scale - 10);
    text("numCorners=" + (let)numCorners, px, py - scale - 80);
    text("divNum=" + (let)divNum, px, py - scale -40);
}
void gmain() {
    window(1000, 1000, full);

    //角の丸い多角形をつくる--------------------------------------------------
    //角数(角になる扇形の数)
    int numCorners = 4;
    //角となる扇型をを分割する数（角の滑らかさ）
    int divNum = 4;
    //角となる扇形の半径
    float fanRadius = 0.5f;
    //中心から扇形の要までの距離
    float length = 1.0f - fanRadius;
    int roundIdx = createRoundPolygon(numCorners, divNum, fanRadius, length);
    
    //角の丸い多角形を描画する------------------------------------------------
    clear(220);
    float px = width / 2;
    float py = height / 2;
    float deg = 0;
    float scale = 300;
    stroke(156);
    strokeWeight(6);
    fill(255, 255, 0);
    shape(roundIdx, px, py, deg, scale);
    
    //説明用の補助線を表示する------------------------------------------------
    explanation(numCorners, divNum, fanRadius, length, px, py, scale);


    while (notQuit) {
    }
}
#endif
