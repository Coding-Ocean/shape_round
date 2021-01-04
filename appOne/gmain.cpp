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
//�p�ۑ��p�`
int createRoundPolygon(
    //�p��(�p�ɂȂ��`�̐�)
    int numCorners,
    //��^���𕪊����鐔�i�p�̊��炩���j
    int divNum,
    //��`�̔��a
    float radius,
    //���S�����`�̒��S�܂ł̋���
    float vlen
) {
    //�K�v�Ȑ��������_�̓��ꕨ��p��
    const int numVertices = (divNum + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---�����v���Œ��_��p�ӂ��Ă���---
    //��`�̒��S�p
    const float fanDeg = 360.0f / numCorners;
    //��`�̒��S�p������ɕ��������p�x�i�p�̊��炩���j
    const float divDeg = fanDeg / divNum;
    //�ŏ��ɒ��_��p�ӂ���p�x
    float offsetDeg = (180.0f - fanDeg) / 2.0f;
    angleMode(DEGREES);
    for (int i = 0; i < numVertices; i++) {
        //��`�̗v�̈ʒu
        int wi = i / (numVertices / numCorners);
        float vx = -sin(fanDeg * wi) * vlen;
        float vy = -cos(fanDeg * wi) * vlen;
        //���_�ʒu
        float deg = offsetDeg + divDeg * (i - wi);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //�@�V�F�[�v������Ĕԍ���Ԃ�
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
