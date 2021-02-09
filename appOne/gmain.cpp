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
    //��`�̗v�̈ʒu�����߂邽�߂Ɏg�p����p�x(��`�̒��S�p�ł�����)
    const float deg = 360.0f / numCorners;
    //��`�̒��S�p������ɕ��������p�x�i�p�̊��炩���j
    const float divDeg = deg / numDivisions;
    //�ŏ��ɒ��_��p�ӂ���p�x
    float offsetDeg = (180.0f - deg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //��`�̗v�̈ʒu
        int cornerIdx = i / (numVertices / numCorners);
        float fanCenterX = px + -sin(deg * cornerIdx) * length * scale;
        float fanCenterY = py + -cos(deg * cornerIdx) * length * scale;
        stroke(0, 0, 255);
        strokeWeight(6);
        line(px, py, fanCenterX, fanCenterY);
        //�e��^�̒��_�ʒu
        float fanDeg = offsetDeg + divDeg * (i - cornerIdx);
        float x = fanCenterX + cos(fanDeg) * fanRadius * scale;
        float y = fanCenterY + -sin(fanDeg) * fanRadius * scale;
        stroke(255, 0, 0);
        line(fanCenterX, fanCenterY, x, y);
        stroke(0, 0, 0);
        strokeWeight(20);
        point(x, y);
    }
    //���S�̕`��
    stroke(0, 0, 255);
    strokeWeight(20);
    point(px, py);
    strokeWeight(6);
    //�e�L�X�g���
    fill(0);
    text(" length=" + (let)length + "*scale", px, py - length * scale / 2);
    text("fanRadius=" + (let)fanRadius + "*scale", px + fanRadius * scale / 2, py - length * scale - 10);
    text("numCorners=" + (let)numCorners, px, py - scale - 80);
    text("numDivisions=" + (let)numDivisions, px, py - scale -40);
}
void gmain() {
    window(1000, 1000, full);

    //�p�̊ۂ����p�`������--------------------------------------------------
    //�p��(�p�ɂȂ��`�̐�)
    int numCorners = 3;
    //�p�ƂȂ��^���𕪊����鐔�i�p�̊��炩���j
    int numDivisions = 4;
    //�p�ƂȂ��`�̔��a
    float fanRadius = 0.4f;
    //���S�����`�̗v�܂ł̋���
    float length = 1.0f - fanRadius;
    int roundIdx = createRoundPolygon(numCorners, numDivisions, fanRadius, length);
    
    //�p�̊ۂ����p�`�̕\���ʒu�A��]�p�x�A�X�P�[��--------------------------------
    float px = width / 2;
    float py = height / 2;
    float deg = 0;
    float scale = 300;

    //�����p�̕⏕���̕\����\���t���b�O------------------------------------------
    bool flag = false;
    
    ShowCursor(FALSE);
    while (notQuit) {
        //�p�̊ۂ����p�`��`�悷��------------------------------------------------
        clear(220);
        stroke(156);
        strokeWeight(6);
        fill(255, 255, 0);
        shape(roundIdx, px, py, deg, scale);
        //�����p�̕⏕����\������------------------------------------------------
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