xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 69;
 -2.08294;0.26941;-1.92942;,
 -1.52084;1.47481;-1.37852;,
 1.58353;0.89445;-1.37852;,
 1.02144;-0.31095;-1.92942;,
 -1.28801;1.97410;-0.04851;,
 1.81636;1.39374;-0.04851;,
 -1.52084;1.47481;1.28150;,
 1.58353;0.89445;1.28150;,
 -2.08294;0.26941;1.83240;,
 1.02144;-0.31095;1.83240;,
 -2.64502;-0.93599;1.28150;,
 0.45937;-1.51635;1.28150;,
 -2.87785;-1.43528;-0.04851;,
 0.22654;-2.01564;-0.04851;,
 -2.64501;-0.93599;-1.37852;,
 0.45937;-1.51635;-1.37852;,
 -2.08294;0.26941;-1.92942;,
 1.02144;-0.31095;-1.92942;,
 -5.63461;1.57281;-1.92942;,
 -5.07251;2.77826;-1.37851;,
 -5.63460;1.57283;-0.04851;,
 -4.83967;3.27755;-0.04851;,
 -5.63460;1.57283;-0.04851;,
 -5.07251;2.77826;1.28149;,
 -5.63460;1.57283;-0.04851;,
 -5.63460;1.57283;1.83240;,
 -5.63460;1.57283;-0.04851;,
 -6.19670;0.36742;1.28151;,
 -5.63460;1.57283;-0.04851;,
 -6.42953;-0.13186;-0.04852;,
 -5.63460;1.57283;-0.04851;,
 -6.19669;0.36741;-1.37854;,
 -5.63460;1.57283;-0.04851;,
 -5.63461;1.57281;-1.92942;,
 -5.63460;1.57283;-0.04851;,
 -28.66651;30.14076;21.64770;,
 -26.17967;35.65332;23.04656;,
 -24.41759;35.08624;22.14874;,
 -26.90441;29.57369;20.74987;,
 -22.99279;37.93668;27.85900;,
 -21.23070;37.36960;26.96116;,
 -20.97267;35.65332;33.26587;,
 -19.21060;35.08624;32.36805;,
 -21.30269;30.14076;36.09998;,
 -19.54059;29.57369;35.20216;,
 -23.78949;24.62823;34.70111;,
 -22.02741;24.06116;33.80330;,
 -26.97637;22.34486;29.88871;,
 -25.21430;21.77778;28.99089;,
 -28.99649;24.62823;24.48180;,
 -27.23442;24.06116;23.58398;,
 -28.66651;30.14076;21.64770;,
 -26.90441;29.57369;20.74987;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -24.98459;30.14076;28.87386;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;,
 -23.22250;29.57369;27.97603;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;18,19,1,0;,
 3;20,19,18;,
 4;19,21,4,1;,
 3;22,21,19;,
 4;21,23,6,4;,
 3;24,23,21;,
 4;23,25,8,6;,
 3;26,25,23;,
 4;25,27,10,8;,
 3;28,27,25;,
 4;27,29,12,10;,
 3;30,29,27;,
 4;29,31,14,12;,
 3;32,31,29;,
 4;31,33,16,14;,
 3;34,33,31;,
 4;35,36,37,38;,
 4;36,39,40,37;,
 4;39,41,42,40;,
 4;41,43,44,42;,
 4;43,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 3;53,36,35;,
 3;54,39,36;,
 3;55,41,39;,
 3;56,43,41;,
 3;57,45,43;,
 3;58,47,45;,
 3;59,49,47;,
 3;60,51,49;,
 3;61,38,37;,
 3;62,37,40;,
 3;63,40,42;,
 3;64,42,44;,
 3;65,44,46;,
 3;66,46,48;,
 3;67,48,50;,
 3;68,50,52;;
 
 MeshMaterialList {
  1;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.097600;0.147200;0.228800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  59;
  0.000001;-0.000001;-1.000000;,
  0.187994;0.684978;-0.703891;,
  0.264906;0.964274;-0.000000;,
  0.187995;0.684979;0.703891;,
  0.000001;0.000000;1.000000;,
  -0.187992;-0.684981;0.703889;,
  -0.264901;-0.964276;-0.000000;,
  -0.187990;-0.684981;-0.703890;,
  -0.000000;-0.000001;-1.000000;,
  0.131402;0.702875;-0.699071;,
  0.183766;0.982970;0.000000;,
  0.131402;0.702875;0.699071;,
  0.000000;-0.000001;1.000000;,
  -0.131401;-0.702875;0.699071;,
  -0.183765;-0.982970;-0.000000;,
  -0.131401;-0.702875;-0.699071;,
  -0.906307;0.422619;-0.000001;,
  0.000002;-0.000000;-1.000000;,
  0.243923;0.664652;-0.706215;,
  0.344527;0.938776;-0.000000;,
  0.243924;0.664653;0.706214;,
  0.000002;0.000001;1.000000;,
  -0.243919;-0.664656;0.706212;,
  -0.344517;-0.938780;-0.000000;,
  -0.243916;-0.664657;-0.706212;,
  -0.906309;0.422616;0.000005;,
  -0.906310;0.422613;0.000000;,
  -0.906307;0.422621;0.000000;,
  -0.906309;0.422616;-0.000005;,
  -0.906308;0.422617;0.000000;,
  -0.906305;0.422625;0.000002;,
  -0.906304;0.422627;-0.000005;,
  -0.906307;0.422621;-0.000007;,
  -0.856490;0.275637;0.436404;,
  -0.453989;-0.000001;-0.891007;,
  -0.147357;0.679716;-0.718521;,
  0.245596;0.961261;-0.125136;,
  0.494680;0.679715;0.541552;,
  0.453986;0.000001;0.891009;,
  0.147355;-0.679714;0.718523;,
  -0.245596;-0.961261;0.125138;,
  -0.494681;-0.679715;-0.541552;,
  0.856490;-0.275638;-0.436404;,
  -0.856490;0.275639;0.436403;,
  -0.856490;0.275637;0.436404;,
  -0.856490;0.275637;0.436404;,
  -0.856489;0.275638;0.436405;,
  -0.856490;0.275637;0.436404;,
  -0.856491;0.275635;0.436405;,
  -0.856491;0.275635;0.436404;,
  -0.856491;0.275635;0.436404;,
  0.856490;-0.275638;-0.436403;,
  0.856490;-0.275638;-0.436403;,
  0.856491;-0.275638;-0.436403;,
  0.856491;-0.275637;-0.436404;,
  0.856490;-0.275637;-0.436405;,
  0.856490;-0.275638;-0.436405;,
  0.856490;-0.275638;-0.436404;,
  0.856490;-0.275638;-0.436404;;
  48;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;17,18,1,0;,
  3;16,25,26;,
  4;18,19,2,1;,
  3;16,27,25;,
  4;19,20,3,2;,
  3;16,28,27;,
  4;20,21,4,3;,
  3;16,29,28;,
  4;21,22,5,4;,
  3;16,30,29;,
  4;22,23,6,5;,
  3;16,31,30;,
  4;23,24,7,6;,
  3;16,32,31;,
  4;24,17,0,7;,
  3;16,26,32;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,34,34,41;,
  3;33,43,44;,
  3;33,45,43;,
  3;33,46,45;,
  3;33,47,46;,
  3;33,48,47;,
  3;33,49,48;,
  3;33,50,49;,
  3;33,44,50;,
  3;42,51,52;,
  3;42,52,53;,
  3;42,53,54;,
  3;42,54,55;,
  3;42,55,56;,
  3;42,56,57;,
  3;42,57,58;,
  3;42,58,51;;
 }
 MeshTextureCoords {
  69;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
