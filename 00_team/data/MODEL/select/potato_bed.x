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
 192;
 -127.27512;3.88022;-55.05526;,
 -14.94737;3.88022;-55.05526;,
 -6.85121;2.78011;-62.99150;,
 -135.37129;2.78011;-62.99150;,
 0.24439;0.01345;-69.94696;,
 -142.62280;0.01345;-69.94696;,
 -14.94737;3.88022;-55.05526;,
 -14.94737;3.88022;55.05366;,
 -6.85121;2.78011;62.98992;,
 -6.85121;2.78011;-62.99150;,
 0.24439;0.01345;69.94526;,
 0.24439;0.01345;-69.94696;,
 -14.94737;3.88022;55.05366;,
 -127.27512;3.88022;55.05366;,
 -135.37129;2.78011;62.98992;,
 -6.85121;2.78011;62.98992;,
 -142.62280;0.01345;69.94526;,
 0.24439;0.01345;69.94526;,
 -127.27512;3.88022;55.05366;,
 -127.27512;3.88022;-55.05526;,
 -135.37129;2.78011;-62.99150;,
 -135.37129;2.78011;62.98992;,
 -142.62280;0.01345;-69.94696;,
 -142.62280;0.01345;69.94526;,
 -14.94737;3.88022;-55.05526;,
 -127.27512;3.88022;-55.05526;,
 -142.62280;0.01345;-69.94696;,
 0.24439;0.01345;-69.94696;,
 -270.14253;3.88022;-55.05526;,
 -157.81459;3.88022;-55.05526;,
 -149.71836;2.78011;-62.99150;,
 -278.23865;2.78011;-62.99150;,
 -142.62280;0.01345;-69.94696;,
 -285.33428;0.01345;-69.94696;,
 -157.81459;3.88022;-55.05526;,
 -157.81459;3.88022;55.05366;,
 -149.71836;2.78011;62.98992;,
 -149.71836;2.78011;-62.99150;,
 -142.62280;0.01345;69.94526;,
 -142.62280;0.01345;-69.94696;,
 -157.81459;3.88022;55.05366;,
 -270.14253;3.88022;55.05366;,
 -278.23865;2.78011;62.98992;,
 -149.71836;2.78011;62.98992;,
 -285.33428;0.01345;69.94526;,
 -142.62280;0.01345;69.94526;,
 -270.14253;3.88022;55.05366;,
 -270.14253;3.88022;-55.05526;,
 -278.23865;2.78011;-62.99150;,
 -278.23865;2.78011;62.98992;,
 -285.33428;0.01345;-69.94696;,
 -285.33428;0.01345;69.94526;,
 -157.81459;3.88022;-55.05526;,
 -270.14253;3.88022;-55.05526;,
 -285.33428;0.01345;-69.94696;,
 -142.62280;0.01345;-69.94696;,
 135.37129;2.78011;-62.99150;,
 6.85121;2.78011;-62.99150;,
 14.94737;3.88022;-55.05526;,
 127.27512;3.88022;-55.05526;,
 142.62280;0.01345;-69.94696;,
 -0.24439;0.01345;-69.94696;,
 6.85121;2.78011;-62.99150;,
 6.85121;2.78011;62.98992;,
 14.94737;3.88022;55.05366;,
 14.94737;3.88022;-55.05526;,
 -0.24439;0.01345;-69.94696;,
 -0.24439;0.01345;69.94526;,
 6.85121;2.78011;62.98992;,
 135.37129;2.78011;62.98992;,
 127.27512;3.88022;55.05366;,
 14.94737;3.88022;55.05366;,
 -0.24439;0.01345;69.94526;,
 142.62280;0.01345;69.94526;,
 135.37129;2.78011;62.98992;,
 135.37129;2.78011;-62.99150;,
 127.27512;3.88022;-55.05526;,
 127.27512;3.88022;55.05366;,
 142.62280;0.01345;69.94526;,
 142.62280;0.01345;-69.94696;,
 127.27512;3.88022;-55.05526;,
 14.94737;3.88022;-55.05526;,
 -0.24439;0.01345;-69.94696;,
 142.62280;0.01345;-69.94696;,
 278.23865;2.78011;-62.99150;,
 149.71836;2.78011;-62.99150;,
 157.81459;3.88022;-55.05526;,
 270.14253;3.88022;-55.05526;,
 285.33428;0.01345;-69.94696;,
 142.62280;0.01345;-69.94696;,
 149.71836;2.78011;-62.99150;,
 149.71836;2.78011;62.98992;,
 157.81459;3.88022;55.05366;,
 157.81459;3.88022;-55.05526;,
 142.62280;0.01345;-69.94696;,
 142.62280;0.01345;69.94526;,
 149.71836;2.78011;62.98992;,
 278.23865;2.78011;62.98992;,
 270.14253;3.88022;55.05366;,
 157.81459;3.88022;55.05366;,
 142.62280;0.01345;69.94526;,
 285.33428;0.01345;69.94526;,
 278.23865;2.78011;62.98992;,
 278.23865;2.78011;-62.99150;,
 270.14253;3.88022;-55.05526;,
 270.14253;3.88022;55.05366;,
 285.33428;0.01345;69.94526;,
 285.33428;0.01345;-69.94696;,
 270.14253;3.88022;-55.05526;,
 157.81459;3.88022;-55.05526;,
 142.62280;0.01345;-69.94696;,
 285.33428;0.01345;-69.94696;,
 -287.11648;1.42152;-71.77566;,
 287.08851;1.42152;-71.77566;,
 287.08851;-0.05488;-71.77566;,
 -287.11648;-0.05488;-71.77566;,
 287.08851;1.42152;-71.77566;,
 287.08851;1.42152;-69.96195;,
 287.08851;-0.05488;-69.96195;,
 287.08851;-0.05488;-71.77566;,
 287.08851;1.42152;-69.96195;,
 -287.11648;1.42152;-69.96195;,
 -287.11648;-0.05488;-69.96195;,
 287.08851;-0.05488;-69.96195;,
 -287.11648;1.42152;-69.96195;,
 -287.11648;1.42152;-71.77566;,
 -287.11648;-0.05488;-71.77566;,
 -287.11648;-0.05488;-69.96195;,
 287.08851;1.42152;-71.77566;,
 -287.11648;1.42152;-71.77566;,
 -287.11648;-0.05488;-71.77566;,
 287.08851;-0.05488;-71.77566;,
 -287.11648;-0.05488;71.77566;,
 287.08851;-0.05488;71.77566;,
 287.08851;1.42152;71.77566;,
 -287.11648;1.42152;71.77566;,
 287.08851;-0.05488;71.77566;,
 287.08851;-0.05488;69.96195;,
 287.08851;1.42152;69.96195;,
 287.08851;1.42152;71.77566;,
 287.08851;-0.05488;69.96195;,
 -287.11648;-0.05488;69.96195;,
 -287.11648;1.42152;69.96195;,
 287.08851;1.42152;69.96195;,
 -287.11648;-0.05488;69.96195;,
 -287.11648;-0.05488;71.77566;,
 -287.11648;1.42152;71.77566;,
 -287.11648;1.42152;69.96195;,
 -287.11648;1.42152;71.77566;,
 287.08851;1.42152;71.77566;,
 287.08851;-0.05488;71.77566;,
 -287.11648;-0.05488;71.77566;,
 -287.09041;1.42152;71.78591;,
 -287.09041;1.42152;-71.78198;,
 -287.09041;-0.05488;-71.78198;,
 -287.09041;-0.05488;71.78591;,
 -287.09041;1.42152;-71.78198;,
 -285.23987;1.42152;-71.78198;,
 -285.23987;-0.05488;-71.78198;,
 -287.09041;-0.05488;-71.78198;,
 -285.23987;1.42152;-71.78198;,
 -285.23987;1.42152;71.78591;,
 -285.23987;-0.05488;71.78591;,
 -285.23987;-0.05488;-71.78198;,
 -285.23987;1.42152;71.78591;,
 -287.09041;1.42152;71.78591;,
 -287.09041;-0.05488;71.78591;,
 -285.23987;-0.05488;71.78591;,
 -287.09041;1.42152;-71.78198;,
 -287.09041;1.42152;71.78591;,
 -287.09041;-0.05488;71.78591;,
 -287.09041;-0.05488;-71.78198;,
 287.09041;-0.05488;71.78591;,
 287.09041;-0.05488;-71.78198;,
 287.09041;1.42152;-71.78198;,
 287.09041;1.42152;71.78591;,
 287.09041;-0.05488;-71.78198;,
 285.23987;-0.05488;-71.78198;,
 285.23987;1.42152;-71.78198;,
 287.09041;1.42152;-71.78198;,
 285.23987;-0.05488;-71.78198;,
 285.23987;-0.05488;71.78591;,
 285.23987;1.42152;71.78591;,
 285.23987;1.42152;-71.78198;,
 285.23987;-0.05488;71.78591;,
 287.09041;-0.05488;71.78591;,
 287.09041;1.42152;71.78591;,
 285.23987;1.42152;71.78591;,
 287.09041;1.42152;71.78591;,
 287.09041;1.42152;-71.78198;,
 287.09041;-0.05488;-71.78198;,
 287.09041;-0.05488;71.78591;;
 
 64;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;9,8,10,11;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;18,19,20,21;,
 4;21,20,22,23;,
 4;18,7,24,25;,
 4;26,27,10,23;,
 4;28,29,30,31;,
 4;31,30,32,33;,
 4;34,35,36,37;,
 4;37,36,38,39;,
 4;40,41,42,43;,
 4;43,42,44,45;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;46,35,52,53;,
 4;54,55,38,51;,
 4;56,57,58,59;,
 4;60,61,57,56;,
 4;62,63,64,65;,
 4;66,67,63,62;,
 4;68,69,70,71;,
 4;72,73,69,68;,
 4;74,75,76,77;,
 4;78,79,75,74;,
 4;80,81,64,77;,
 4;78,67,82,83;,
 4;84,85,86,87;,
 4;88,89,85,84;,
 4;90,91,92,93;,
 4;94,95,91,90;,
 4;96,97,98,99;,
 4;100,101,97,96;,
 4;102,103,104,105;,
 4;106,107,103,102;,
 4;108,109,92,105;,
 4;106,95,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;124,117,128,129;,
 4;130,131,118,127;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,138,147;,
 4;144,137,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;164,157,168,169;,
 4;170,171,158,167;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,178,187;,
 4;184,177,190,191;;
 
 MeshMaterialList {
  3;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\soil.jpg";
   }
  }
  Material {
   0.800000;0.743200;0.088000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  61;
  -0.045067;0.997926;-0.045958;,
  -0.125630;0.983566;-0.129672;,
  -0.184415;0.964069;-0.191212;,
  0.045067;0.997926;-0.045958;,
  0.127428;0.983327;-0.129729;,
  0.188061;0.963340;-0.191337;,
  0.045067;0.997926;0.045958;,
  0.127428;0.983327;0.129730;,
  0.188061;0.963339;0.191339;,
  -0.045067;0.997926;0.045958;,
  -0.125630;0.983566;0.129673;,
  -0.184415;0.964069;0.191214;,
  -0.045067;0.997926;-0.045958;,
  -0.127428;0.983327;-0.129729;,
  -0.188060;0.963340;-0.191337;,
  0.045066;0.997926;-0.045958;,
  0.127428;0.983327;-0.129729;,
  0.188062;0.963340;-0.191337;,
  0.045066;0.997926;0.045958;,
  0.127428;0.983327;0.129730;,
  0.188062;0.963339;0.191339;,
  -0.045067;0.997926;0.045958;,
  -0.127428;0.983327;0.129730;,
  -0.188060;0.963339;0.191339;,
  0.045067;0.997926;-0.045958;,
  0.125630;0.983566;-0.129672;,
  0.184415;0.964069;-0.191212;,
  -0.045067;0.997926;-0.045958;,
  -0.127428;0.983327;-0.129729;,
  -0.188061;0.963340;-0.191337;,
  -0.045067;0.997926;0.045958;,
  -0.127428;0.983327;0.129730;,
  -0.188061;0.963339;0.191339;,
  0.045067;0.997926;0.045958;,
  0.125630;0.983566;0.129673;,
  0.184415;0.964069;0.191214;,
  0.045067;0.997926;-0.045958;,
  0.127428;0.983327;-0.129729;,
  0.188060;0.963340;-0.191337;,
  -0.045066;0.997926;-0.045958;,
  -0.127428;0.983327;-0.129729;,
  -0.188062;0.963340;-0.191337;,
  -0.045066;0.997926;0.045958;,
  -0.127428;0.983327;0.129730;,
  -0.188062;0.963339;0.191339;,
  0.045067;0.997926;0.045958;,
  0.127428;0.983327;0.129730;,
  0.188060;0.963339;0.191339;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  64;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;9,0,1,10;,
  4;10,1,2,11;,
  4;9,6,3,0;,
  4;48,48,48,48;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;15,18,19,16;,
  4;16,19,20,17;,
  4;18,21,22,19;,
  4;19,22,23,20;,
  4;21,12,13,22;,
  4;22,13,14,23;,
  4;21,18,15,12;,
  4;48,48,48,48;,
  4;25,28,27,24;,
  4;26,29,28,25;,
  4;28,31,30,27;,
  4;29,32,31,28;,
  4;31,34,33,30;,
  4;32,35,34,31;,
  4;34,25,24,33;,
  4;35,26,25,34;,
  4;24,27,30,33;,
  4;48,48,48,48;,
  4;37,40,39,36;,
  4;38,41,40,37;,
  4;40,43,42,39;,
  4;41,44,43,40;,
  4;43,46,45,42;,
  4;44,47,46,43;,
  4;46,37,36,45;,
  4;47,38,37,46;,
  4;36,39,42,45;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;50,50,50,50;,
  4;49,49,49,49;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;57,57,57,57;,
  4;56,56,56,56;,
  4;55,55,55,55;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;;
 }
 MeshTextureCoords {
  192;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;;
 }
}