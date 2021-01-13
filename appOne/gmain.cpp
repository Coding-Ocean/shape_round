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
//�p���ۂ܂������p�`������
int createRoundPolygon(
    //�p��(�p�ɂȂ��`�̐�)
    int numCorners,
    //�p�ƂȂ��^���𕪊����鐔�i�p�̊��炩���j
    int divNum,
    //�p�ƂȂ��`�̔��a
    float fanRadius,
    //���S�����`�̗v�܂ł̋���
    float length
) {
    //�K�v�Ȑ��������_�̓��ꕨ��p��
    const int numVertices = (divNum + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---�����v���Œ��_��p�ӂ��Ă���---
    //��`�̗v�̈ʒu�����߂邽�߂Ɏg�p����p�x(��`�̒��S�p�ł�����)
    const float deg = 360.0f / numCorners;
    //��`�̒��S�p������ɕ��������p�x�i�p�̊��炩���j
    const float divDeg = deg / divNum;
    //�ŏ��ɒ��_��p�ӂ���p�x
    float offsetDeg = (180.0f - deg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //��`�̗v�̈ʒu
        int cornerIdx = i / (numVertices / numCorners);
        float fanCenterX = -sin(deg * cornerIdx) * length;
        float fanCenterY = -cos(deg * cornerIdx) * length;
        //�e��^�̒��_�ʒu
        float fanDeg = offsetDeg + divDeg * (i - cornerIdx);
        vertices[i].x = fanCenterX + cos(fanDeg) * fanRadius;
        vertices[i].y = fanCenterY + -sin(fanDeg) * fanRadius;
    }
    //�@�V�F�[�v������Ĕԍ���Ԃ�
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
    //��`�̗v�̈ʒu�����߂邽�߂Ɏg�p����p�x(��`�̒��S�p�ł�����)
    const float deg = 360.0f / numCorners;
    //��`�̒��S�p������ɕ��������p�x�i�p�̊��炩���j
    const float divDeg = deg / divNum;
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
    text("divNum=" + (let)divNum, px, py - scale -40);
}
void gmain() {
    window(1000, 1000, full);

    //�p�̊ۂ����p�`������--------------------------------------------------
    //�p��(�p�ɂȂ��`�̐�)
    int numCorners = 4;
    //�p�ƂȂ��^���𕪊����鐔�i�p�̊��炩���j
    int divNum = 4;
    //�p�ƂȂ��`�̔��a
    float fanRadius = 0.5f;
    //���S�����`�̗v�܂ł̋���
    float length = 1.0f - fanRadius;
    int roundIdx = createRoundPolygon(numCorners, divNum, fanRadius, length);
    
    //�p�̊ۂ����p�`��`�悷��------------------------------------------------
    clear(220);
    float px = width / 2;
    float py = height / 2;
    float deg = 0;
    float scale = 300;
    stroke(156);
    strokeWeight(6);
    fill(255, 255, 0);
    shape(roundIdx, px, py, deg, scale);
    
    //�����p�̕⏕����\������------------------------------------------------
    explanation(numCorners, divNum, fanRadius, length, px, py, scale);


    while (notQuit) {
    }
}
#endif
