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
 50;
 -0.00001;-7.09845;-2.63644;,
 0.00000;-0.09404;-2.63644;,
 1.03360;-0.09404;-2.35161;,
 1.03360;-7.09844;-2.35161;,
 2.40395;-7.09845;-0.00000;,
 2.40395;-0.09404;-0.00000;,
 2.37587;-0.09404;0.65635;,
 2.37587;-7.09845;0.65635;,
 1.03360;-7.09844;2.35161;,
 1.03360;-0.09404;2.35161;,
 -0.00000;-0.09404;2.63644;,
 -0.00001;-7.09845;2.63644;,
 -2.51046;-7.09844;0.86801;,
 -2.51046;-0.09404;0.86801;,
 -2.60520;-0.09404;0.00000;,
 -2.60520;-7.09844;0.00000;,
 1.03360;-0.09404;-0.00000;,
 0.00000;-0.09404;-0.00000;,
 -0.00000;-0.09404;0.86801;,
 1.03360;-0.09404;0.86801;,
 1.03360;-7.09844;0.86801;,
 -0.00000;-7.09845;0.86801;,
 0.00000;-7.09845;-0.00000;,
 1.03360;-7.09844;-0.00000;,
 -1.03361;-7.09844;-2.57266;,
 -1.03361;-0.09404;-2.57266;,
 -1.03361;-0.09404;0.00000;,
 -1.03361;-0.09404;0.86801;,
 -1.03361;-0.09404;2.57266;,
 -1.03361;-7.09844;2.57266;,
 -1.03360;-7.09844;0.86801;,
 -1.03360;-7.09844;0.00000;,
 -2.06721;-7.09844;-1.73603;,
 -2.06721;-0.09404;-1.73603;,
 -2.06721;-0.09404;1.73603;,
 -2.06721;-7.09844;1.73603;,
 1.87592;-7.09845;1.79514;,
 1.87592;-0.09404;1.79514;,
 1.87592;-0.09404;-1.79514;,
 1.87592;-7.09845;-1.79514;,
 2.37587;-7.09845;-0.65635;,
 2.37587;-0.09404;-0.65635;,
 1.03360;-0.09404;-0.86801;,
 0.00000;-0.09404;-0.86801;,
 -1.03361;-0.09404;-0.86801;,
 -2.51046;-0.09404;-0.86801;,
 -2.51046;-7.09844;-0.86801;,
 -1.03360;-7.09844;-0.86801;,
 0.00000;-7.09845;-0.86801;,
 1.03360;-7.09844;-0.86801;;
 
 48;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,1,0;,
 4;17,26,27,18;,
 4;11,10,28,29;,
 4;21,30,31,22;,
 4;32,33,25,24;,
 4;26,14,13,27;,
 4;29,28,34,35;,
 4;30,12,15,31;,
 4;36,37,9,8;,
 4;5,16,19,6;,
 4;3,2,38,39;,
 4;7,20,23,4;,
 4;40,41,5,4;,
 4;41,42,16,5;,
 4;42,43,17,16;,
 4;43,44,26,17;,
 4;44,45,14,26;,
 4;15,14,45,46;,
 4;31,15,46,47;,
 4;22,31,47,48;,
 4;23,22,48,49;,
 4;4,23,49,40;,
 4;39,38,41,40;,
 4;2,42,41,38;,
 4;1,43,42,2;,
 4;25,44,43,1;,
 4;33,45,44,25;,
 4;46,45,33,32;,
 4;47,46,32,24;,
 4;48,47,24,0;,
 4;49,48,0,3;,
 4;40,49,3,39;,
 4;35,34,13,12;,
 4;27,13,34,28;,
 4;18,27,28,10;,
 4;19,18,10,9;,
 4;6,19,9,37;,
 4;7,6,37,36;,
 4;8,20,7,36;,
 4;11,21,20,8;,
 4;29,30,21,11;,
 4;35,12,30,29;;
 
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
  37;
  -0.776800;0.000000;-0.629748;,
  0.764629;0.000000;-0.644471;,
  0.764629;0.000000;0.644471;,
  -0.776800;0.000000;0.629748;,
  0.103448;-0.000000;-0.994635;,
  0.103448;-0.000000;0.994635;,
  -0.362592;0.000000;-0.931948;,
  -0.362592;0.000000;0.931948;,
  0.413557;-0.000000;0.910478;,
  0.413557;-0.000000;-0.910478;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000005;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000001;-1.000000;-0.000000;,
  0.974071;0.000000;-0.226244;,
  -0.958123;0.000000;-0.286356;,
  -0.000005;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.958123;0.000000;0.286356;,
  0.974071;0.000000;0.226244;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000005;-1.000000;-0.000000;,
  -0.000009;-1.000000;-0.000001;,
  -0.000007;-1.000000;0.000000;,
  -0.000009;-1.000000;0.000001;,
  -0.000005;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000001;,
  -0.000010;-1.000000;0.000002;,
  -0.000000;-1.000000;-0.000001;,
  -0.000010;-1.000000;-0.000002;,
  -0.000000;-1.000000;-0.000000;,
  -0.000005;-1.000000;-0.000000;;
  48;
  4;4,4,9,9;,
  4;10,10,22,22;,
  4;8,8,5,5;,
  4;21,21,12,12;,
  4;11,11,11,11;,
  4;23,24,14,15;,
  4;6,6,4,4;,
  4;11,11,11,11;,
  4;5,5,7,7;,
  4;24,25,13,14;,
  4;0,0,6,6;,
  4;11,11,11,11;,
  4;7,7,3,3;,
  4;25,14,14,13;,
  4;2,2,8,8;,
  4;11,11,11,11;,
  4;9,9,1,1;,
  4;26,23,15,27;,
  4;16,16,10,10;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;12,12,17,17;,
  4;13,14,14,18;,
  4;14,13,18,19;,
  4;15,14,19,20;,
  4;27,15,20,28;,
  4;1,1,16,16;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;17,17,0,0;,
  4;18,14,14,29;,
  4;19,18,29,30;,
  4;20,19,30,31;,
  4;28,20,31,32;,
  4;3,3,21,21;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;22,22,2,2;,
  4;33,23,26,34;,
  4;35,24,23,33;,
  4;36,25,24,35;,
  4;14,14,25,36;;
 }
 MeshTextureCoords {
  50;
  0.561668;0.233226;,
  0.561668;0.138938;,
  0.539845;0.138938;,
  0.539845;0.233226;,
  0.510911;0.233226;,
  0.510911;0.138938;,
  0.511504;0.138938;,
  0.511504;0.233226;,
  0.539845;0.233226;,
  0.539845;0.138938;,
  0.561668;0.138938;,
  0.561668;0.233226;,
  0.614674;0.233226;,
  0.614674;0.138938;,
  0.616674;0.138938;,
  0.616674;0.233226;,
  0.539845;0.138938;,
  0.561668;0.138938;,
  0.561668;0.138938;,
  0.539845;0.138938;,
  0.539845;0.233226;,
  0.561668;0.233226;,
  0.561668;0.233226;,
  0.539845;0.233226;,
  0.583491;0.233226;,
  0.583491;0.138938;,
  0.583491;0.138938;,
  0.583491;0.138938;,
  0.583491;0.138938;,
  0.583491;0.233226;,
  0.583491;0.233226;,
  0.583491;0.233226;,
  0.605315;0.233226;,
  0.605315;0.138938;,
  0.605315;0.138938;,
  0.605315;0.233226;,
  0.522060;0.233226;,
  0.522060;0.138938;,
  0.522060;0.138938;,
  0.522060;0.233226;,
  0.511504;0.233226;,
  0.511504;0.138938;,
  0.539845;0.138938;,
  0.561668;0.138938;,
  0.583491;0.138938;,
  0.614674;0.138938;,
  0.614674;0.233226;,
  0.583491;0.233226;,
  0.561668;0.233226;,
  0.539845;0.233226;;
 }
}
