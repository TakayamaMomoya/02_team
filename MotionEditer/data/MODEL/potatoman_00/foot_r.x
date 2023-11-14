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
 139;
 -2.30311;-3.72061;-9.78655;,
 -2.30311;-4.15657;-9.99645;,
 -2.99507;-4.15657;-9.99645;,
 -2.82657;-3.81662;-9.63328;,
 -2.30311;-0.02758;2.35372;,
 -2.30311;-0.02758;-3.49280;,
 -2.74553;-0.45942;-3.49280;,
 -2.74553;-0.45942;2.35372;,
 -2.30311;-2.41491;2.32630;,
 -2.30311;-1.30299;2.33907;,
 -2.99507;-1.30299;2.33907;,
 -2.99507;-2.41491;2.32630;,
 -2.30311;-5.00516;-3.01913;,
 -2.30311;-5.00516;2.29655;,
 -2.99507;-5.00516;2.29655;,
 -2.99507;-5.00516;-3.01913;,
 -2.99507;-1.30299;2.33907;,
 -2.99507;-1.30299;-3.37143;,
 -2.99507;-2.41491;-3.26562;,
 -2.99507;-2.41491;2.32630;,
 -2.30311;-2.98617;-5.06646;,
 -2.30311;-3.22056;-6.77484;,
 -2.74553;-3.65240;-6.77484;,
 -2.74553;-3.41801;-5.06646;,
 -2.99507;-3.50350;-4.97294;,
 -2.99507;-3.67783;-6.77484;,
 -2.99507;-4.07648;-6.77484;,
 -2.99507;-3.95451;-4.89141;,
 -2.30311;-5.00516;-6.77484;,
 -2.30311;-5.00516;-4.70148;,
 -2.99507;-5.00516;-4.70148;,
 -2.99507;-5.00516;-6.77484;,
 -2.30311;-3.22056;-9.54578;,
 -2.99507;-4.15657;-9.99645;,
 -2.82657;-3.81662;-9.63328;,
 -2.30311;-5.00516;-9.54578;,
 -2.99507;-5.00516;-9.54578;,
 -2.99507;-1.98058;-3.86458;,
 -2.99507;-2.88900;-3.76624;,
 -2.30311;-0.93861;-3.97737;,
 -2.74553;-1.37044;-3.97737;,
 -2.30311;-5.00516;-3.53717;,
 -2.99507;-5.00516;-3.53717;,
 -2.30311;-5.00516;-9.54578;,
 -2.99507;-5.00516;-9.54578;,
 -2.99507;-5.00516;-9.54578;,
 -2.99507;-5.00516;-6.77484;,
 -2.99507;-5.00516;-4.70148;,
 -2.99507;-5.00516;-3.53717;,
 -2.99507;-5.00516;-3.01913;,
 -2.99507;-5.00516;2.29655;,
 -2.30311;-5.00516;2.29655;,
 -2.99507;-5.00516;2.29655;,
 -2.30311;-0.02758;2.35372;,
 -2.74553;-0.45942;2.35372;,
 -2.74553;-0.45942;-3.49280;,
 -2.74553;-0.45942;2.35372;,
 -2.74553;-1.37044;-3.97737;,
 -2.74553;-3.41801;-5.06646;,
 -2.74553;-3.65240;-6.77484;,
 0.00000;-5.00516;-9.54578;,
 0.00000;-5.00516;-6.77484;,
 0.00000;-5.00516;-4.70148;,
 0.00000;-5.00516;-3.53717;,
 0.00000;-5.00516;-3.01913;,
 -0.00000;-5.00516;2.29655;,
 -0.00000;-5.00516;2.29655;,
 -0.00000;-2.41491;2.32630;,
 -0.00000;-1.30299;2.33907;,
 -0.00000;-0.02758;2.35372;,
 -0.00000;-0.02758;2.35372;,
 0.00000;-0.02758;-3.49280;,
 0.00000;-0.93861;-3.97737;,
 0.00000;-2.98617;-5.06646;,
 0.00000;-3.22056;-6.77484;,
 0.00000;-3.22056;-9.54578;,
 0.00000;-3.72061;-9.78655;,
 0.00000;-4.15657;-9.99645;,
 0.00000;-5.00516;-9.54578;,
 2.30311;-3.72061;-9.78655;,
 2.82657;-3.81662;-9.63328;,
 2.99508;-4.15657;-9.99645;,
 2.30311;-4.15657;-9.99645;,
 2.30311;-0.02758;2.35372;,
 2.74553;-0.45942;2.35372;,
 2.74553;-0.45942;-3.49280;,
 2.30311;-0.02758;-3.49280;,
 2.30311;-2.41491;2.32630;,
 2.99508;-2.41491;2.32630;,
 2.99508;-1.30299;2.33907;,
 2.30311;-1.30299;2.33907;,
 2.30311;-5.00516;-3.01913;,
 2.99508;-5.00516;-3.01913;,
 2.99508;-5.00516;2.29655;,
 2.30311;-5.00516;2.29655;,
 2.99508;-1.30299;2.33907;,
 2.99508;-2.41491;2.32630;,
 2.99508;-2.41491;-3.26562;,
 2.99508;-1.30299;-3.37143;,
 2.30311;-2.98617;-5.06646;,
 2.74553;-3.41801;-5.06646;,
 2.74553;-3.65240;-6.77484;,
 2.30311;-3.22056;-6.77484;,
 2.99508;-3.50350;-4.97294;,
 2.99508;-3.95451;-4.89141;,
 2.99508;-4.07648;-6.77484;,
 2.99508;-3.67783;-6.77484;,
 2.30311;-5.00516;-6.77484;,
 2.99508;-5.00516;-6.77484;,
 2.99508;-5.00516;-4.70148;,
 2.30311;-5.00516;-4.70148;,
 2.30311;-3.22056;-9.54578;,
 2.99508;-4.15657;-9.99645;,
 2.82657;-3.81662;-9.63328;,
 2.30311;-5.00516;-9.54578;,
 2.99508;-5.00516;-9.54578;,
 2.99508;-1.98058;-3.86458;,
 2.99508;-2.88900;-3.76624;,
 2.30311;-0.93861;-3.97737;,
 2.74553;-1.37044;-3.97737;,
 2.99508;-5.00516;-3.53717;,
 2.30311;-5.00516;-3.53717;,
 2.99508;-5.00516;-9.54578;,
 2.30311;-5.00516;-9.54578;,
 2.99508;-5.00516;-9.54578;,
 2.99508;-5.00516;-6.77484;,
 2.99508;-5.00516;-4.70148;,
 2.99508;-5.00516;-3.53717;,
 2.99508;-5.00516;2.29655;,
 2.99508;-5.00516;-3.01913;,
 2.30311;-5.00516;2.29655;,
 2.99508;-5.00516;2.29655;,
 2.74553;-0.45942;2.35372;,
 2.30311;-0.02758;2.35372;,
 2.74553;-0.45942;-3.49280;,
 2.74553;-0.45942;2.35372;,
 2.74553;-1.37044;-3.97737;,
 2.74553;-3.41801;-5.06646;,
 2.74553;-3.65240;-6.77484;;
 
 94;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;21,32,3,22;,
 4;33,26,25,34;,
 4;35,28,31,36;,
 4;37,24,27,38;,
 4;39,20,23,40;,
 4;29,41,42,30;,
 4;1,43,44,2;,
 4;45,46,26,33;,
 4;27,26,46,47;,
 4;48,38,27,47;,
 4;19,18,49,50;,
 4;51,8,11,52;,
 4;18,38,48,49;,
 4;17,37,38,18;,
 4;5,39,40,6;,
 4;41,12,15,42;,
 4;9,53,54,10;,
 4;55,17,16,56;,
 4;57,37,17,55;,
 4;58,24,37,57;,
 4;59,25,24,58;,
 3;34,25,59;,
 3;32,0,3;,
 4;60,61,28,35;,
 4;61,62,29,28;,
 4;62,63,41,29;,
 4;63,64,12,41;,
 4;64,65,13,12;,
 4;66,67,8,51;,
 4;67,68,9,8;,
 4;68,69,53,9;,
 4;70,71,5,4;,
 4;71,72,39,5;,
 4;72,73,20,39;,
 4;73,74,21,20;,
 4;74,75,32,21;,
 4;75,76,0,32;,
 4;76,77,1,0;,
 4;77,78,43,1;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;102,101,80,111;,
 4;112,113,106,105;,
 4;114,115,108,107;,
 4;116,117,104,103;,
 4;118,119,100,99;,
 4;110,109,120,121;,
 4;82,81,122,123;,
 4;124,112,105,125;,
 4;104,126,125,105;,
 4;127,126,104,117;,
 4;96,128,129,97;,
 4;130,131,88,87;,
 4;97,129,127,117;,
 4;98,97,117,116;,
 4;86,85,119,118;,
 4;121,120,92,91;,
 4;90,89,132,133;,
 4;134,135,95,98;,
 4;136,134,98,116;,
 4;137,136,116,103;,
 4;138,137,103,106;,
 3;113,138,106;,
 3;111,80,79;,
 4;60,114,107,61;,
 4;61,107,110,62;,
 4;62,110,121,63;,
 4;63,121,91,64;,
 4;64,91,94,65;,
 4;66,130,87,67;,
 4;67,87,90,68;,
 4;68,90,133,69;,
 4;70,83,86,71;,
 4;71,86,118,72;,
 4;72,118,99,73;,
 4;73,99,102,74;,
 4;74,102,111,75;,
 4;75,111,79,76;,
 4;76,79,82,77;,
 4;77,82,123,78;;
 
 MeshMaterialList {
  1;
  94;
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
  74;
  0.000000;-1.000000;-0.000000;,
  -0.559200;0.711530;-0.425465;,
  -0.856392;0.516326;0.000000;,
  -0.821297;0.464268;-0.331551;,
  -0.460552;0.884700;-0.072099;,
  -0.556936;0.695735;-0.453625;,
  -0.167402;0.587795;-0.791501;,
  -0.998237;0.058651;-0.009065;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.011484;0.999934;,
  -0.620067;0.390843;-0.680263;,
  0.002803;-0.012954;0.999912;,
  -0.985582;0.136060;-0.100580;,
  -0.946949;0.173621;-0.270450;,
  -0.963381;0.146071;-0.224855;,
  -0.992905;0.117512;-0.018162;,
  0.001401;-0.012220;0.999924;,
  -0.377086;0.926178;0.000000;,
  -0.337661;0.790911;-0.510338;,
  -0.213244;0.458798;-0.862573;,
  -0.325381;0.760722;-0.561631;,
  -0.385338;0.920435;-0.065673;,
  -0.322061;0.777250;-0.540517;,
  -0.124627;0.472438;-0.872508;,
  -0.063420;0.209335;-0.975785;,
  0.000000;0.469599;-0.882880;,
  0.000000;0.820133;-0.572174;,
  0.000000;0.433814;-0.901003;,
  0.000000;-0.011485;0.999934;,
  0.000000;-0.011486;0.999934;,
  0.000000;1.000000;0.000000;,
  0.000000;0.997677;-0.068122;,
  0.000000;-0.019744;-0.999805;,
  0.559198;0.711532;-0.425465;,
  0.856389;0.516331;0.000000;,
  0.821293;0.464272;-0.331554;,
  0.460549;0.884701;-0.072099;,
  0.556930;0.695738;-0.453628;,
  0.167402;0.587795;-0.791501;,
  0.998237;0.058654;-0.009065;,
  1.000000;0.000000;0.000000;,
  0.620061;0.390846;-0.680268;,
  -0.002803;-0.012954;0.999912;,
  0.985581;0.136065;-0.100583;,
  0.946946;0.173625;-0.270457;,
  0.963380;0.146074;-0.224859;,
  0.992905;0.117518;-0.018163;,
  -0.001401;-0.012220;0.999924;,
  0.377086;0.926178;0.000000;,
  0.337661;0.790911;-0.510338;,
  0.213244;0.458798;-0.862573;,
  0.325381;0.760722;-0.561631;,
  0.385338;0.920435;-0.065673;,
  0.322061;0.777250;-0.540517;,
  0.124627;0.472438;-0.872508;,
  0.063420;0.209335;-0.975785;,
  -0.989678;0.143311;0.000000;,
  0.000000;-0.469039;-0.883178;,
  0.000000;-0.469039;-0.883178;,
  0.000000;-0.011485;0.999934;,
  0.000000;-0.011485;0.999934;,
  0.002803;-0.012955;0.999912;,
  0.005605;-0.014425;0.999880;,
  -0.165348;0.982639;-0.084142;,
  -0.228615;0.966860;-0.113652;,
  0.000000;0.469598;-0.882881;,
  0.000000;0.433823;-0.900998;,
  0.989677;0.143316;0.000000;,
  0.000000;-0.011485;0.999934;,
  0.000000;-0.011485;0.999934;,
  -0.005605;-0.014425;0.999880;,
  -0.002803;-0.012955;0.999912;,
  0.228607;0.966862;-0.113652;,
  0.165342;0.982640;-0.084142;;
  94;
  4;23,24,6,1;,
  4;17,18,3,2;,
  4;9,16,11,9;,
  4;0,0,0,0;,
  4;56,12,8,8;,
  4;20,21,4,5;,
  4;14,15,7,8;,
  4;0,0,0,0;,
  4;21,22,1,4;,
  4;15,7,15,1;,
  4;0,0,0,0;,
  4;13,14,8,8;,
  4;19,20,5,10;,
  4;0,0,0,0;,
  4;57,58,57,57;,
  4;8,8,7,15;,
  4;8,7,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;59,9,9,60;,
  4;8,8,8,8;,
  4;12,13,8,8;,
  4;18,19,10,3;,
  4;0,0,0,0;,
  4;16,61,62,11;,
  4;3,12,56,2;,
  4;10,13,12,3;,
  4;5,14,13,10;,
  4;4,63,64,5;,
  3;1,63,4;,
  3;22,23,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;59,9,9,59;,
  4;9,28,16,9;,
  4;28,29,61,16;,
  4;30,30,18,17;,
  4;65,25,19,18;,
  4;25,26,20,19;,
  4;26,31,21,20;,
  4;31,30,22,21;,
  4;66,27,23,22;,
  4;27,32,24,23;,
  4;32,58,58,24;,
  4;54,33,38,55;,
  4;48,34,35,49;,
  4;9,9,42,47;,
  4;0,0,0,0;,
  4;67,40,40,43;,
  4;51,37,36,52;,
  4;45,40,39,46;,
  4;0,0,0,0;,
  4;52,36,33,53;,
  4;46,33,46,39;,
  4;0,0,0,0;,
  4;44,40,40,45;,
  4;50,41,37,51;,
  4;0,0,0,0;,
  4;57,57,57,58;,
  4;40,46,39,40;,
  4;40,40,40,39;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;68,69,9,9;,
  4;40,40,40,40;,
  4;43,40,40,44;,
  4;49,35,41,50;,
  4;0,0,0,0;,
  4;47,42,70,71;,
  4;35,34,67,43;,
  4;41,35,43,44;,
  4;37,41,44,45;,
  4;36,37,72,73;,
  3;33,36,73;,
  3;53,33,54;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;59,68,9,9;,
  4;9,9,47,28;,
  4;28,47,71,29;,
  4;30,48,49,30;,
  4;65,49,50,25;,
  4;25,50,51,26;,
  4;26,51,52,31;,
  4;31,52,53,30;,
  4;66,53,54,27;,
  4;27,54,55,32;,
  4;32,55,58,58;;
 }
 MeshTextureCoords {
  139;
  0.974010;0.468270;,
  0.974230;0.475930;,
  0.984420;0.476230;,
  0.980730;0.469290;,
  0.981650;0.261940;,
  0.976110;0.344470;,
  0.982210;0.351390;,
  0.988510;0.269420;,
  0.851850;0.185500;,
  0.851850;0.163220;,
  0.863370;0.163220;,
  0.863370;0.185500;,
  0.978060;0.183400;,
  0.978060;0.138050;,
  0.989740;0.138050;,
  0.989740;0.183400;,
  0.865130;0.318380;,
  0.709210;0.339300;,
  0.704760;0.370630;,
  0.863510;0.361930;,
  0.979780;0.396460;,
  0.978390;0.421250;,
  0.985170;0.428710;,
  0.987850;0.403770;,
  0.647280;0.397030;,
  0.596460;0.403890;,
  0.594030;0.416180;,
  0.647790;0.412740;,
  0.978060;0.215450;,
  0.978060;0.197760;,
  0.989740;0.197760;,
  0.989740;0.215450;,
  0.974060;0.459420;,
  0.511000;0.427200;,
  0.509390;0.422980;,
  0.978060;0.239100;,
  0.989740;0.239100;,
  0.688860;0.356160;,
  0.687050;0.383590;,
  0.976900;0.360510;,
  0.984780;0.367250;,
  0.978060;0.187830;,
  0.989740;0.187830;,
  0.974590;0.490740;,
  0.984950;0.490810;,
  0.516760;0.451900;,
  0.589550;0.446650;,
  0.648200;0.447680;,
  0.682540;0.450560;,
  0.697840;0.451660;,
  0.853110;0.452190;,
  0.851850;0.237400;,
  0.863370;0.237400;,
  0.851850;0.137660;,
  0.859210;0.146310;,
  0.682350;0.331560;,
  0.836220;0.305020;,
  0.683330;0.343270;,
  0.637480;0.395200;,
  0.588510;0.402680;,
  0.939210;0.239100;,
  0.939210;0.215450;,
  0.939210;0.197760;,
  0.939210;0.187830;,
  0.939210;0.183400;,
  0.939210;0.138050;,
  0.813500;0.237400;,
  0.813500;0.185500;,
  0.813500;0.163220;,
  0.813500;0.137660;,
  0.942020;0.261140;,
  0.942200;0.345110;,
  0.942240;0.360680;,
  0.942310;0.395820;,
  0.942370;0.420990;,
  0.942460;0.460670;,
  0.942480;0.469030;,
  0.942490;0.476380;,
  0.942530;0.491080;,
  0.910940;0.468410;,
  0.904220;0.469460;,
  0.900560;0.476420;,
  0.910750;0.476070;,
  0.902390;0.262120;,
  0.895560;0.269620;,
  0.902220;0.351570;,
  0.908290;0.344620;,
  0.775150;0.185500;,
  0.763630;0.185500;,
  0.763630;0.163220;,
  0.775150;0.163220;,
  0.900360;0.183400;,
  0.888690;0.183400;,
  0.888690;0.138050;,
  0.900360;0.138050;,
  0.866900;0.319030;,
  0.865040;0.363000;,
  0.704700;0.370990;,
  0.709340;0.339370;,
  0.904850;0.396630;,
  0.896820;0.403970;,
  0.899600;0.428900;,
  0.906350;0.421410;,
  0.646520;0.397350;,
  0.646950;0.413220;,
  0.592650;0.416410;,
  0.595170;0.404020;,
  0.900360;0.215450;,
  0.888690;0.215450;,
  0.888690;0.197760;,
  0.900360;0.197760;,
  0.910850;0.459560;,
  0.508760;0.427120;,
  0.507160;0.422850;,
  0.900360;0.239100;,
  0.888690;0.239100;,
  0.688710;0.356290;,
  0.686740;0.383980;,
  0.907570;0.360660;,
  0.899720;0.367440;,
  0.888690;0.187830;,
  0.900360;0.187830;,
  0.900100;0.490990;,
  0.910460;0.490890;,
  0.514450;0.452090;,
  0.587970;0.447170;,
  0.647190;0.448500;,
  0.681860;0.451580;,
  0.854080;0.454090;,
  0.697300;0.452770;,
  0.775150;0.237400;,
  0.763630;0.237400;,
  0.767790;0.146310;,
  0.775150;0.137660;,
  0.682260;0.331420;,
  0.837770;0.305400;,
  0.683190;0.343240;,
  0.636630;0.395450;,
  0.587150;0.402760;;
 }
}
