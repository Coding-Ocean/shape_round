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
    //�@�V�F�[�v������Ĕԍ���Ԃ�
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
//�p���ۂ܂������p�`������
int createRoundPolygon(
    //�p��(�p�ɂȂ��`�̐�)
    int numCorners,
    //�p�ƂȂ��^���𕪊����鐔�i�p�̊��炩���j
    int numDivisions,
    //�p�ƂȂ��`�̔��a
    float fanRadius,
    //���S�����`�̗v�܂ł̋���
    float length
) {
    //�K�v�Ȑ��������_�̓��ꕨ��p��
    const int numVertices = (numDivisions + 1) * numCorners;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    //---����̊ۊp���甽���v���Œ��_��p�ӂ��Ă���---
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
