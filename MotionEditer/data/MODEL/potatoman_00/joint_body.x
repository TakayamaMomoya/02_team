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
 58;
 -3.20886;-11.03041;3.20886;,
 0.00000;-11.03041;4.53801;,
 0.00000;-8.45984;8.38515;,
 -5.92920;-8.45984;5.92920;,
 3.20886;-11.03041;3.20886;,
 5.92920;-8.45984;5.92920;,
 4.53801;-11.03041;-0.00000;,
 8.38515;-8.45984;-0.00000;,
 3.20886;-11.03041;-3.20886;,
 5.92920;-8.45984;-5.92920;,
 0.00000;-11.03041;-4.53801;,
 0.00000;-8.45984;-8.38515;,
 -3.20886;-11.03041;-3.20886;,
 -5.92920;-8.45984;-5.92920;,
 -4.53801;-11.03041;0.00000;,
 -8.38515;-8.45984;0.00000;,
 0.00000;-4.61269;10.95573;,
 -7.74687;-4.61269;7.74687;,
 7.74687;-4.61269;7.74687;,
 10.95573;-4.61269;-0.00000;,
 7.74687;-4.61269;-7.74687;,
 0.00000;-4.61269;-10.95573;,
 -7.74687;-4.61269;-7.74687;,
 -10.95573;-4.61269;0.00000;,
 0.00000;-0.07468;11.85840;,
 -8.38515;-0.07468;8.38515;,
 8.38515;-0.07468;8.38515;,
 11.85840;-0.07468;-0.00000;,
 8.38515;-0.07468;-8.38515;,
 0.00000;-0.07468;-11.85840;,
 -8.38515;-0.07468;-8.38515;,
 -11.85840;-0.07468;0.00000;,
 0.00000;4.46333;10.95573;,
 -7.74687;4.46333;7.74687;,
 7.74687;4.46333;7.74687;,
 10.95573;4.46333;0.00000;,
 7.74687;4.46333;-7.74687;,
 0.00000;4.46333;-10.95573;,
 -7.74687;4.46333;-7.74687;,
 -10.95573;4.46333;0.00000;,
 0.00000;8.31047;8.38515;,
 -5.92920;8.31047;5.92920;,
 5.92920;8.31047;5.92920;,
 8.38515;8.31047;0.00000;,
 5.92920;8.31047;-5.92920;,
 0.00000;8.31047;-8.38515;,
 -5.92920;8.31047;-5.92920;,
 -8.38515;8.31047;0.00000;,
 0.00000;10.88105;4.53801;,
 -3.20886;10.88105;3.20886;,
 3.20886;10.88105;3.20886;,
 4.53801;10.88105;0.00000;,
 3.20886;10.88105;-3.20886;,
 0.00000;10.88105;-4.53801;,
 -3.20886;10.88105;-3.20886;,
 -4.53801;10.88105;0.00000;,
 0.00000;-11.93308;-0.00000;,
 0.00000;11.78371;0.00000;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,33,41,47;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,41,49,55;,
 3;1,0,56;,
 3;4,1,56;,
 3;6,4,56;,
 3;8,6,56;,
 3;10,8,56;,
 3;12,10,56;,
 3;14,12,56;,
 3;0,14,56;,
 3;49,48,57;,
 3;48,50,57;,
 3;50,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,49,57;;
 
 MeshMaterialList {
  1;
  64;
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
    "data\\TEXTURE\\MATERIAL\\UV_potetoman.png";
   }
  }
 }
 MeshNormals {
  58;
  -0.269132;-0.924735;0.269132;,
  0.000000;-0.924735;0.380611;,
  0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  0.269132;-0.924735;0.269132;,
  0.498494;-0.709230;0.498494;,
  0.380611;-0.924735;-0.000000;,
  0.704977;-0.709230;-0.000000;,
  0.269132;-0.924735;-0.269132;,
  0.498494;-0.709230;-0.498494;,
  0.000000;-0.924735;-0.380611;,
  0.000000;-0.709230;-0.704977;,
  -0.269132;-0.924735;-0.269132;,
  -0.498494;-0.709230;-0.498494;,
  -0.380611;-0.924735;0.000000;,
  -0.704977;-0.709230;0.000000;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384550;0.652733;,
  0.652733;-0.384550;0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384550;-0.652733;,
  0.000000;-0.384551;-0.923104;,
  -0.652733;-0.384550;-0.652733;,
  -0.923104;-0.384551;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  0.707107;0.000000;0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  -0.707107;0.000000;-0.707107;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  0.652733;0.384551;0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;-0.652733;,
  0.000000;0.384551;-0.923104;,
  -0.652733;0.384551;-0.652733;,
  -0.923104;0.384551;0.000000;,
  0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  0.498494;0.709230;0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;-0.498494;,
  0.000000;0.709230;-0.704977;,
  -0.498494;0.709230;-0.498494;,
  -0.704977;0.709230;0.000000;,
  0.000000;0.924735;0.380610;,
  -0.269132;0.924736;0.269132;,
  0.269132;0.924736;0.269132;,
  0.380610;0.924735;0.000000;,
  0.269132;0.924736;-0.269132;,
  0.000000;0.924735;-0.380610;,
  -0.269132;0.924736;-0.269132;,
  -0.380610;0.924735;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  64;
  4;0,1,2,3;,
  4;1,4,5,2;,
  4;4,6,7,5;,
  4;6,8,9,7;,
  4;8,10,11,9;,
  4;10,12,13,11;,
  4;12,14,15,13;,
  4;14,0,3,15;,
  4;3,2,16,17;,
  4;2,5,18,16;,
  4;5,7,19,18;,
  4;7,9,20,19;,
  4;9,11,21,20;,
  4;11,13,22,21;,
  4;13,15,23,22;,
  4;15,3,17,23;,
  4;17,16,24,25;,
  4;16,18,26,24;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,17,25,31;,
  4;25,24,32,33;,
  4;24,26,34,32;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,25,33,39;,
  4;33,32,40,41;,
  4;32,34,42,40;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,33,41,47;,
  4;41,40,48,49;,
  4;40,42,50,48;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,41,49,55;,
  3;1,0,56;,
  3;4,1,56;,
  3;6,4,56;,
  3;8,6,56;,
  3;10,8,56;,
  3;12,10,56;,
  3;14,12,56;,
  3;0,14,56;,
  3;49,48,57;,
  3;48,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,49,57;;
 }
 MeshTextureCoords {
  58;
  0.955000;0.104840;,
  0.941580;0.104840;,
  0.941580;0.094100;,
  0.966370;0.094100;,
  0.928170;0.104840;,
  0.916790;0.094100;,
  0.922610;0.104840;,
  0.906530;0.094100;,
  0.928170;0.104840;,
  0.916790;0.094100;,
  0.941580;0.104840;,
  0.941580;0.094100;,
  0.955000;0.104840;,
  0.966370;0.094100;,
  0.960550;0.104840;,
  0.976640;0.094100;,
  0.941580;0.078010;,
  0.973970;0.078010;,
  0.909190;0.078010;,
  0.895780;0.078010;,
  0.909190;0.078010;,
  0.941580;0.078010;,
  0.973970;0.078010;,
  0.987380;0.078010;,
  0.941580;0.059040;,
  0.976640;0.059040;,
  0.906530;0.059040;,
  0.892010;0.059040;,
  0.906530;0.059040;,
  0.941580;0.059040;,
  0.976640;0.059040;,
  0.991160;0.059040;,
  0.941580;0.040070;,
  0.973970;0.040070;,
  0.909190;0.040070;,
  0.895780;0.040070;,
  0.909190;0.040070;,
  0.941580;0.040070;,
  0.973970;0.040070;,
  0.987380;0.040070;,
  0.941580;0.023990;,
  0.966370;0.023990;,
  0.916790;0.023990;,
  0.906530;0.023990;,
  0.916790;0.023990;,
  0.941580;0.023990;,
  0.966370;0.023990;,
  0.976640;0.023990;,
  0.941580;0.013240;,
  0.955000;0.013240;,
  0.928170;0.013240;,
  0.922610;0.013240;,
  0.928170;0.013240;,
  0.941580;0.013240;,
  0.955000;0.013240;,
  0.960550;0.013240;,
  0.941580;0.108620;,
  0.941580;0.009460;;
 }
}