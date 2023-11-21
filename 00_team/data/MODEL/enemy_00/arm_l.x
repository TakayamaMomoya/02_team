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
 41;
 -0.10202;1.83636;-1.18014;,
 -0.10202;-0.00001;-1.18014;,
 -0.10202;-0.00001;0.00000;,
 -0.10202;1.83636;0.00000;,
 -0.10202;-1.83636;-1.18014;,
 -0.10202;-1.83636;0.00000;,
 -0.10202;-4.46023;-1.18014;,
 -0.10202;-4.62853;0.00000;,
 -0.10202;4.22110;-0.89237;,
 -0.10202;4.27099;0.00000;,
 -0.10202;-4.46023;1.18014;,
 -0.10202;-1.83636;1.18014;,
 -0.10202;-0.00001;1.18014;,
 -0.10202;1.83636;1.18014;,
 -0.10202;4.22110;0.89237;,
 -0.10202;-3.67272;2.36027;,
 -0.10202;-1.83636;3.49775;,
 -0.10202;-0.00001;3.58445;,
 -0.10202;1.83636;3.19721;,
 -0.10202;3.33287;2.44064;,
 -0.10202;1.83636;-3.19721;,
 -0.10202;3.33287;-2.44064;,
 -0.10202;-0.00001;-3.58445;,
 -0.10202;-1.83636;-3.49775;,
 -0.10202;-3.67272;-2.36027;,
 10.70959;-4.07958;1.14607;,
 10.70959;-3.36209;2.21058;,
 10.70959;-4.23293;-0.00000;,
 10.70959;-4.07958;-1.14607;,
 10.70959;-3.36209;-2.21058;,
 10.70959;-1.68899;-3.23662;,
 10.70959;-0.01589;-3.31482;,
 10.70959;1.65720;-2.96552;,
 10.70959;3.02067;-2.28307;,
 10.70959;3.82994;-0.88649;,
 10.70959;3.87538;0.00000;,
 10.70959;3.82994;0.88649;,
 10.70959;3.02067;2.28307;,
 10.70959;1.65720;2.96552;,
 10.70959;-0.01590;3.31482;,
 10.70959;-1.68899;3.23662;;
 
 46;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,0,3,9;,
 4;5,7,10,11;,
 4;2,5,11,12;,
 4;3,2,12,13;,
 4;9,3,13,14;,
 4;11,10,15,16;,
 4;12,11,16,17;,
 4;13,12,17,18;,
 4;14,13,18,19;,
 4;20,0,8,21;,
 4;22,1,0,20;,
 4;23,4,1,22;,
 4;24,6,4,23;,
 4;10,25,26,15;,
 4;7,27,25,10;,
 4;6,28,27,7;,
 4;24,29,28,6;,
 4;23,30,29,24;,
 4;22,31,30,23;,
 4;20,32,31,22;,
 4;21,33,32,20;,
 4;8,34,33,21;,
 4;9,35,34,8;,
 4;14,36,35,9;,
 4;19,37,36,14;,
 4;18,38,37,19;,
 4;17,39,38,18;,
 4;16,40,39,17;,
 4;15,26,40,16;,
 3;31,32,30;,
 3;30,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;29,34,28;,
 3;28,34,27;,
 3;34,35,27;,
 3;35,36,27;,
 3;27,36,25;,
 3;36,37,25;,
 3;25,37,26;,
 3;26,37,40;,
 3;37,38,40;,
 3;38,39,40;;
 
 MeshMaterialList {
  1;
  46;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\enemy00.png";
   }
  }
 }
 MeshNormals {
  18;
  -1.000000;0.000000;0.000000;,
  0.029973;-0.693075;0.720242;,
  0.034402;-0.933904;0.355864;,
  0.036100;-0.999348;-0.000000;,
  0.034402;-0.933904;-0.355864;,
  0.029973;-0.693075;-0.720242;,
  0.026900;-0.295064;-0.955099;,
  0.024861;0.079831;-0.996498;,
  0.025628;0.330026;-0.943624;,
  0.030403;0.686355;-0.726630;,
  0.035101;0.958140;-0.284140;,
  0.036375;0.999338;0.000000;,
  0.035101;0.958140;0.284140;,
  0.030403;0.686355;0.726630;,
  0.025628;0.330026;0.943624;,
  0.024861;0.079831;0.996498;,
  0.026900;-0.295064;0.955099;,
  1.000000;-0.000000;0.000000;;
  46;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,1,1;,
  4;3,3,2,2;,
  4;4,4,3,3;,
  4;5,5,4,4;,
  4;6,6,5,5;,
  4;7,7,6,6;,
  4;8,8,7,7;,
  4;9,9,8,8;,
  4;10,10,9,9;,
  4;11,11,10,10;,
  4;12,12,11,11;,
  4;13,13,12,12;,
  4;14,14,13,13;,
  4;15,15,14,14;,
  4;16,16,15,15;,
  4;1,1,16,16;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;;
 }
 MeshTextureCoords {
  41;
  0.785180;0.039840;,
  0.785180;0.060590;,
  0.785180;0.060590;,
  0.785180;0.039840;,
  0.785180;0.081350;,
  0.785180;0.081350;,
  0.785180;0.111000;,
  0.785180;0.112900;,
  0.785180;0.012890;,
  0.785180;0.012320;,
  0.785180;0.111000;,
  0.785180;0.081350;,
  0.785180;0.060590;,
  0.785180;0.039840;,
  0.785180;0.012890;,
  0.785180;0.102100;,
  0.785180;0.081350;,
  0.785180;0.060590;,
  0.785180;0.039840;,
  0.785180;0.022930;,
  0.785180;0.039840;,
  0.785180;0.022930;,
  0.785180;0.060590;,
  0.785180;0.081350;,
  0.785180;0.102100;,
  0.844650;0.106700;,
  0.844650;0.098590;,
  0.844650;0.108430;,
  0.844650;0.106700;,
  0.844650;0.098590;,
  0.844650;0.079680;,
  0.844650;0.060770;,
  0.844650;0.041860;,
  0.844650;0.026450;,
  0.844650;0.017310;,
  0.844650;0.016790;,
  0.844650;0.017310;,
  0.844650;0.026450;,
  0.844650;0.041860;,
  0.844650;0.060770;,
  0.844650;0.079680;;
 }
}
