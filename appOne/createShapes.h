#pragma once
int createTriangle();
int createPolygon(int numCorners);
int createStar();
int createHeart();
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
);