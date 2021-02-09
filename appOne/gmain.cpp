#define B
#ifdef A
#include"libOne.h"
#include"createShapes.h"
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
#include"libOne.h"
#include"createShapes.h"
void explanation(int numCorners, int numDivisions, float fanRadius, float length,
    float px, float py, float scale)
{
    const int numVertices = (numDivisions + 1) * numCorners;
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
        float fanCenterX = px + -sin(deg * cornerIdx) * length * scale;
        float fanCenterY = py + -cos(deg * cornerIdx) * length * scale;
        stroke(0, 0, 255);
        strokeWeight(6);
        line(px, py, fanCenterX, fanCenterY);
        //各扇型の頂点位置
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
    text("numDivisions=" + (let)numDivisions, px, py - scale -40);
}
void gmain() {
    window(1000, 1000, full);

    //角の丸い多角形をつくる--------------------------------------------------
    //角数(角になる扇形の数)
    int numCorners = 3;
    //角となる扇型をを分割する数（角の滑らかさ）
    int numDivisions = 4;
    //角となる扇形の半径
    float fanRadius = 0.4f;
    //中心から扇形の要までの距離
    float length = 1.0f - fanRadius;
    int roundIdx = createRoundPolygon(numCorners, numDivisions, fanRadius, length);
    
    //角の丸い多角形の表示位置、回転角度、スケール--------------------------------
    float px = width / 2;
    float py = height / 2;
    float deg = 0;
    float scale = 300;

    //説明用の補助線の表示非表示フラッグ------------------------------------------
    bool flag = false;
    
    ShowCursor(FALSE);
    while (notQuit) {
        //角の丸い多角形を描画する------------------------------------------------
        clear(220);
        stroke(156);
        strokeWeight(6);
        fill(255, 255, 0);
        shape(roundIdx, px, py, deg, scale);
        //説明用の補助線を表示する------------------------------------------------
        if (isTrigger(KEY_SPACE))flag = !flag;
        if (flag) {
            explanation(numCorners, numDivisions, fanRadius, length, px, py, scale);
        }
    }
    ShowCursor(TRUE);
}
#endif
#ifdef C
#include"libOne.h"
#include"createShapes.h"
void gmain() {
    window(1000, 1000, full);
    int triangleIdx = createTriangle();
    int polygonIdx = createPolygon(60);
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