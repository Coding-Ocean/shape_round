#pragma once
int createTriangle();
int createPolygon(int numCorners);
int createStar();
int createHeart();
//Šp‚ªŠÛ‚Ü‚Á‚½‘½ŠpŒ`‚ğ‚Â‚­‚é
int createRoundPolygon(
    //Šp”(Šp‚É‚È‚éîŒ`‚Ì”)
    int numCorners,
    //Šp‚Æ‚È‚éîŒ^‚ğ‚ğ•ªŠ„‚·‚é”iŠp‚ÌŠŠ‚ç‚©‚³j
    int numDivisions,
    //Šp‚Æ‚È‚éîŒ`‚Ì”¼Œa
    float fanRadius,
    //’†S‚©‚çîŒ`‚Ì—v‚Ü‚Å‚Ì‹——£
    float length
);