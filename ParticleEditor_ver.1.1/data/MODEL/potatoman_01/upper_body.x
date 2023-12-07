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
 309;
 -5.23294;4.43723;-13.84101;,
 -3.85441;4.43723;-14.32654;,
 -3.78955;-9.50187;-13.83402;,
 -5.14488;-9.50187;-13.36519;,
 -0.75374;23.54825;1.18193;,
 -0.55518;23.54825;1.18193;,
 -0.55518;23.54825;0.00000;,
 -0.75374;23.54825;0.00000;,
 -5.24914;-9.50187;15.14491;,
 -3.86634;-9.50187;15.14491;,
 -3.93395;4.43721;15.68409;,
 -5.34092;4.43721;15.68409;,
 -12.84404;4.43723;7.16827;,
 -13.18297;4.43721;0.00000;,
 -12.82160;-9.50187;0.00000;,
 -12.49432;-9.50187;6.92184;,
 13.18297;4.43723;0.00000;,
 12.84404;4.43721;7.16827;,
 12.49432;-9.50187;6.92184;,
 12.82160;-9.50187;-0.00000;,
 -0.00000;-9.50187;15.14491;,
 3.86634;-9.50187;15.14491;,
 3.93395;4.43723;15.68409;,
 0.00000;4.43723;15.68409;,
 0.00000;23.54825;1.18193;,
 0.55518;23.54825;1.18193;,
 0.55518;23.54825;0.00000;,
 0.00000;23.54825;0.00000;,
 0.00000;4.43721;-15.68409;,
 3.85441;4.43721;-14.32654;,
 3.78955;-9.50187;-13.83402;,
 0.00000;-9.50187;-15.14491;,
 9.94594;4.43721;12.57915;,
 5.34092;4.43723;15.68409;,
 5.24914;-9.50187;15.14491;,
 9.69585;-9.50187;12.14671;,
 2.59192;23.54825;0.00000;,
 0.75374;23.54825;0.00000;,
 0.75374;23.54825;1.18193;,
 2.51247;23.54825;1.08038;,
 9.32480;-9.50187;-10.25512;,
 5.14488;-9.50187;-13.36519;,
 5.23294;4.43721;-13.84101;,
 9.58793;4.43723;-10.63161;,
 -9.58793;4.43723;-10.63161;,
 -9.32480;-9.50187;-10.25512;,
 -2.51247;23.54825;1.08038;,
 -2.59192;23.54825;0.00000;,
 -9.69585;-9.50187;12.14671;,
 -9.94594;4.43721;12.57915;,
 2.35346;23.54825;-1.00214;,
 0.75374;23.54825;-1.18193;,
 0.75374;23.54825;0.00000;,
 2.59192;23.54825;0.00000;,
 0.00000;23.54825;0.00000;,
 0.55518;23.54825;0.00000;,
 0.55518;23.54825;-1.18193;,
 0.00000;23.54825;-1.18193;,
 -0.75374;23.54825;0.00000;,
 -0.55518;23.54825;0.00000;,
 -0.55518;23.54825;-1.18193;,
 -0.75374;23.54825;-1.18193;,
 -2.59192;23.54825;0.00000;,
 -2.35346;23.54825;-1.00214;,
 -13.18297;4.43721;0.00000;,
 -12.16569;4.43721;-6.64914;,
 -11.83929;-9.50187;-6.42055;,
 -12.82160;-9.50187;0.00000;,
 12.16569;4.43723;-6.64914;,
 13.18297;4.43723;0.00000;,
 12.82160;-9.50187;-0.00000;,
 11.83929;-9.50187;-6.42055;,
 1.18468;23.54825;-1.33064;,
 0.72843;23.54825;-2.08608;,
 0.53653;23.54825;-2.15926;,
 0.00000;23.54825;-2.36386;,
 -0.53653;23.54825;-2.15926;,
 -0.72843;23.54825;-2.08608;,
 -1.18468;23.54825;-1.33065;,
 -0.75374;23.54825;2.36386;,
 -1.83316;23.54825;1.89590;,
 -0.55518;23.54825;2.36386;,
 0.55518;23.54825;2.36386;,
 0.00000;23.54825;2.36386;,
 0.75374;23.54825;2.36386;,
 1.83316;23.54825;1.89590;,
 8.68867;14.46338;8.87494;,
 5.43969;14.46338;11.06556;,
 5.41318;11.77258;12.30508;,
 9.02609;11.77258;9.86906;,
 0.00000;11.77258;12.30508;,
 3.98717;11.77258;12.30508;,
 4.00670;14.46338;11.06556;,
 0.00000;14.46338;11.06556;,
 -5.41318;11.77258;12.30508;,
 -3.98717;11.77258;12.30508;,
 -4.00670;14.46338;11.06556;,
 -5.43969;14.46338;11.06556;,
 -9.02609;11.77258;9.86906;,
 -8.68867;14.46338;8.87494;,
 -10.73335;14.46338;5.05741;,
 -11.29981;11.77258;5.62392;,
 -10.97247;14.46338;0.00000;,
 -11.56572;11.77258;0.00000;,
 -10.97247;14.46338;0.00000;,
 -10.25475;14.46338;-4.69114;,
 -10.76761;11.77258;-5.21663;,
 -11.56572;11.77258;0.00000;,
 -8.58634;11.77258;-8.27218;,
 -8.21893;14.46338;-7.40668;,
 -5.36351;14.46338;-9.76521;,
 -6.62590;11.58354;-10.34067;,
 -5.02637;13.93737;-8.49341;,
 -3.61771;13.92352;-8.84032;,
 -3.57296;11.23472;-9.97715;,
 -6.27144;11.05945;-9.07304;,
 0.00000;13.89409;-9.76768;,
 3.61771;13.92352;-8.84032;,
 3.57296;11.23472;-9.97715;,
 0.00000;11.20337;-11.00716;,
 8.58634;11.77258;-8.27218;,
 6.62590;11.58354;-10.34067;,
 5.36351;14.46338;-9.76521;,
 8.21893;14.46338;-7.40668;,
 10.25475;14.46338;-4.69114;,
 10.76761;11.77258;-5.21663;,
 10.97247;14.46338;0.00000;,
 11.56572;11.77258;0.00000;,
 10.97247;14.46338;0.00000;,
 10.73335;14.46338;5.05741;,
 11.29981;11.77258;5.62392;,
 11.56572;11.77258;0.00000;,
 4.41779;22.25853;4.22484;,
 2.01239;22.25853;5.26767;,
 5.45659;16.17862;10.27544;,
 8.47358;16.17862;8.24124;,
 0.00000;16.17862;10.27544;,
 4.01914;16.17862;10.27544;,
 1.48226;22.25853;5.26767;,
 0.00000;22.25853;5.26767;,
 -5.45659;16.17862;10.27544;,
 -4.01914;16.17862;10.27544;,
 -1.48226;22.25853;5.26767;,
 -2.01239;22.25853;5.26767;,
 -8.47358;16.17862;8.24124;,
 -4.41779;22.25853;4.22484;,
 -5.93158;22.25853;2.40754;,
 -10.37226;16.17862;4.69629;,
 -6.10862;22.25853;0.00000;,
 -10.59431;16.17862;0.00000;,
 -5.57725;22.25853;-2.23318;,
 -9.92783;16.17862;-4.35618;,
 -10.59431;16.17862;0.00000;,
 -6.10862;22.25853;0.00000;,
 -7.98473;16.17862;-6.85497;,
 -3.87855;22.25853;-3.35825;,
 -1.95599;22.25853;-4.64865;,
 -5.38585;16.17862;-9.06794;,
 -1.44071;22.25853;-4.81172;,
 -3.96704;16.17862;-9.38603;,
 1.44071;22.25853;-4.81172;,
 3.96704;16.17862;-9.38603;,
 0.00000;16.17862;-10.27544;,
 0.00000;22.25853;-5.26767;,
 7.98473;16.17862;-6.85497;,
 5.38585;16.17862;-9.06794;,
 1.95599;22.25853;-4.64865;,
 3.87855;22.25853;-3.35825;,
 5.57725;22.25853;-2.23318;,
 9.92783;16.17862;-4.35618;,
 6.10862;22.25853;0.00000;,
 10.59431;16.17862;0.00000;,
 5.93158;22.25853;2.40754;,
 10.37226;16.17862;4.69629;,
 10.59431;16.17862;0.00000;,
 6.10862;22.25853;0.00000;,
 9.74489;6.04049;11.98681;,
 5.35672;6.04050;14.94553;,
 12.50652;6.04049;6.83072;,
 12.82948;6.04050;0.00000;,
 11.86011;6.04050;-6.33603;,
 12.82948;6.04050;0.00000;,
 9.36902;6.04050;-10.11591;,
 5.25382;6.04049;-13.18925;,
 0.00000;5.47041;-13.64753;,
 3.47763;5.50584;-12.39886;,
 3.43295;3.90440;-13.08233;,
 0.00000;3.89354;-14.44574;,
 -5.25382;6.04050;-13.18925;,
 -9.36902;6.04050;-10.11591;,
 -11.86011;6.04049;-6.33603;,
 -12.82948;6.04049;0.00000;,
 -12.50652;6.04050;6.83072;,
 -12.82948;6.04049;0.00000;,
 -9.74489;6.04049;11.98681;,
 -5.35672;6.04049;14.94553;,
 -3.94558;6.04050;14.94553;,
 3.94558;6.04050;14.94553;,
 0.00000;6.04050;14.94553;,
 0.00000;15.62175;-9.00625;,
 3.66428;15.63368;-8.11332;,
 -3.66428;15.63370;-8.11332;,
 -3.43295;3.90442;-13.08233;,
 -3.47763;5.50584;-12.39886;,
 5.02638;13.93737;-8.49341;,
 6.27144;11.05944;-9.07304;,
 4.86245;5.51944;-11.93054;,
 -4.86245;5.51945;-11.93054;,
 -6.27144;11.05838;-9.07304;,
 -6.62590;11.58354;-10.34067;,
 -5.36351;14.46338;-9.76521;,
 -5.02637;13.93631;-8.49341;,
 3.85441;4.43721;-14.32654;,
 0.00000;4.43721;-15.68409;,
 0.00000;3.89354;-14.44574;,
 3.43295;3.90440;-13.08233;,
 0.00000;16.17862;-10.27544;,
 3.96704;16.17862;-9.38603;,
 3.66428;15.63263;-8.11332;,
 0.00000;15.62068;-9.00625;,
 -3.96704;16.17862;-9.38603;,
 -3.66428;15.63263;-8.11332;,
 -3.85441;4.43723;-14.32654;,
 -3.43295;3.90442;-13.08233;,
 5.36351;14.46338;-9.76521;,
 5.02638;13.93631;-8.49341;,
 6.62590;11.58354;-10.34067;,
 6.27144;11.05838;-9.07304;,
 5.25382;6.04049;-13.18925;,
 4.86245;5.51944;-11.93054;,
 -5.25382;6.04050;-13.18925;,
 -4.86245;5.51945;-11.93054;,
 5.38216;8.62311;13.75586;,
 9.42103;8.62309;11.03264;,
 11.96283;8.62309;6.28699;,
 12.26009;8.62311;0.00000;,
 12.26009;8.62311;0.00000;,
 11.36788;8.62311;-5.83168;,
 9.01637;8.62311;-9.28520;,
 6.58489;8.43406;-11.62096;,
 6.58489;8.43406;-11.62096;,
 6.21015;7.91116;-10.35824;,
 6.21015;7.91222;-10.35824;,
 3.52058;8.08758;-11.30774;,
 0.00000;8.05400;-12.45790;,
 -3.52058;8.08759;-11.30774;,
 -6.21015;7.91223;-10.35824;,
 -6.21015;7.91116;-10.35824;,
 -6.58489;8.43406;-11.62096;,
 -6.58489;8.43406;-11.62096;,
 -9.01637;8.62311;-9.28520;,
 -11.36788;8.62309;-5.83168;,
 -12.26009;8.62309;0.00000;,
 -12.26009;8.62309;0.00000;,
 -11.96283;8.62311;6.28699;,
 -9.42103;8.62309;11.03264;,
 -5.38216;8.62309;13.75586;,
 -3.96432;8.62310;13.75586;,
 0.00000;8.62311;13.75586;,
 3.96432;8.62311;13.75586;,
 3.52058;8.08651;-11.30774;,
 6.21015;7.91116;-10.35824;,
 0.00000;8.05294;-12.45790;,
 -3.52058;8.08653;-11.30774;,
 -6.21015;7.91116;-10.35824;,
 12.82160;-9.50187;-0.00000;,
 12.49432;-9.50187;6.92184;,
 11.83929;-9.50187;-6.42055;,
 9.69585;-9.50187;12.14671;,
 9.32480;-9.50187;-10.25512;,
 5.24914;-9.50187;15.14491;,
 5.14488;-9.50187;-13.36519;,
 3.86634;-9.50187;15.14491;,
 3.78955;-9.50187;-13.83402;,
 -0.00000;-9.50187;15.14491;,
 0.00000;-9.50187;-15.14491;,
 -3.86634;-9.50187;15.14491;,
 -3.78955;-9.50187;-13.83402;,
 -5.14488;-9.50187;-13.36519;,
 -5.24914;-9.50187;15.14491;,
 -9.32480;-9.50187;-10.25512;,
 -9.69585;-9.50187;12.14671;,
 -11.83929;-9.50187;-6.42055;,
 -12.49432;-9.50187;6.92184;,
 -12.82160;-9.50187;0.00000;,
 -6.27144;11.05838;-9.07304;,
 -5.02637;13.93631;-8.49341;,
 -5.02637;13.93737;-8.49341;,
 -6.27144;11.05945;-9.07304;,
 0.00000;15.62068;-9.00625;,
 3.66428;15.63263;-8.11332;,
 3.66428;15.63368;-8.11332;,
 0.00000;15.62175;-9.00625;,
 -3.66428;15.63263;-8.11332;,
 -3.66428;15.63370;-8.11332;,
 5.02638;13.93631;-8.49341;,
 5.02638;13.93737;-8.49341;,
 6.27144;11.05838;-9.07304;,
 6.27144;11.05944;-9.07304;,
 6.21015;7.91116;-10.35824;,
 3.52058;8.08651;-11.30774;,
 3.52058;8.08758;-11.30774;,
 6.21015;7.91222;-10.35824;,
 0.00000;8.05294;-12.45790;,
 0.00000;8.05400;-12.45790;,
 -3.52058;8.08653;-11.30774;,
 -3.52058;8.08759;-11.30774;,
 -6.21015;7.91116;-10.35824;,
 -6.21015;7.91223;-10.35824;;
 
 232;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,0,3,45;,
 4;46,4,7,47;,
 4;48,8,11,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,58,61,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,51,50;,
 4;57,56,74,75;,
 4;61,60,76,77;,
 4;63,61,77,78;,
 4;45,66,65,44;,
 4;43,68,71,40;,
 4;49,12,15,48;,
 4;79,4,46,80;,
 4;81,5,4,79;,
 4;82,25,24,83;,
 4;39,38,84,85;,
 4;35,18,17,32;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,94,97,99;,
 4;99,100,101,98;,
 4;100,102,103,101;,
 4;104,105,106,107;,
 4;108,106,105,109;,
 4;109,110,111,108;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;123,124,125,120;,
 4;124,126,127,125;,
 4;128,129,130,131;,
 4;89,130,129,86;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,140,143,145;,
 4;146,147,144,145;,
 4;148,149,147,146;,
 4;150,151,152,153;,
 4;154,151,150,155;,
 4;156,157,154,155;,
 4;158,159,157,156;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,164,167;,
 4;170,171,169,168;,
 4;172,173,174,175;,
 4;135,173,172,132;,
 4;172,175,36,39;,
 4;148,146,46,47;,
 4;170,168,50,53;,
 4;150,153,62,63;,
 4;167,166,73,72;,
 4;168,167,72,50;,
 4;74,160,163,75;,
 4;76,158,156,77;,
 4;156,155,78,77;,
 4;155,150,63,78;,
 4;146,145,80,46;,
 4;145,143,79,80;,
 4;143,142,81,79;,
 4;139,138,82,83;,
 4;133,132,85,84;,
 4;132,172,39,85;,
 4;176,177,33,32;,
 4;32,17,178,176;,
 4;179,178,17,16;,
 4;180,181,69,68;,
 4;182,180,68,43;,
 4;43,42,183,182;,
 4;184,185,186,187;,
 3;188,1,0;,
 4;189,188,0,44;,
 4;44,65,190,189;,
 4;191,190,65,64;,
 4;192,193,13,12;,
 4;194,192,12,49;,
 4;49,11,195,194;,
 4;11,10,196,195;,
 4;23,22,197,198;,
 4;135,134,87,86;,
 4;93,92,137,136;,
 4;97,96,141,140;,
 4;99,97,140,144;,
 4;144,147,100,99;,
 4;147,149,102,100;,
 4;152,151,105,104;,
 4;109,105,151,154;,
 4;154,157,110,109;,
 3;157,159,110;,
 4;199,200,117,116;,
 4;123,122,165,164;,
 4;164,169,124,123;,
 4;169,171,126,124;,
 4;174,173,129,128;,
 4;86,129,173,135;,
 4;10,9,20,23;,
 4;196,10,23,198;,
 4;96,95,90,93;,
 4;141,96,93,136;,
 4;142,141,136,139;,
 4;81,142,139,83;,
 4;83,24,5,81;,
 4;6,5,24,27;,
 4;60,59,54,57;,
 4;76,60,57,75;,
 4;163,158,76,75;,
 4;163,162,159,158;,
 4;113,201,199,116;,
 4;119,114,113,116;,
 4;202,203,184,187;,
 4;2,1,28,31;,
 4;22,21,34,33;,
 4;197,22,33,177;,
 4;92,91,88,87;,
 4;137,92,87,134;,
 4;138,137,134,133;,
 4;82,138,133,84;,
 4;84,38,25,82;,
 4;26,25,38,37;,
 4;56,55,52,51;,
 4;74,56,51,73;,
 4;166,160,74,73;,
 4;166,165,161,160;,
 3;117,200,204;,
 4;205,118,117,204;,
 3;186,185,206;,
 4;30,29,42,41;,
 3;112,201,113;,
 3;122,161,165;,
 3;207,203,202;,
 3;29,183,42;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,216,219,221;,
 4;213,222,223,214;,
 4;217,224,225,218;,
 4;224,226,227,225;,
 4;228,212,215,229;,
 4;210,220,221,211;,
 4;222,230,231,223;,
 4;89,88,232,233;,
 4;233,234,130,89;,
 4;131,130,234,235;,
 4;125,127,236,237;,
 4;120,125,237,238;,
 4;238,239,121,120;,
 4;227,226,240,241;,
 4;242,243,118,205;,
 4;119,118,243,244;,
 4;244,245,114,119;,
 4;115,114,245,246;,
 4;247,248,209,208;,
 4;108,111,249,250;,
 4;250,251,106,108;,
 4;107,106,251,252;,
 4;101,103,253,254;,
 4;98,101,254,255;,
 4;255,256,94,98;,
 4;256,257,95,94;,
 4;90,95,257,258;,
 4;258,259,91,90;,
 4;88,91,259,232;,
 4;233,232,177,176;,
 4;176,178,234,233;,
 4;235,234,178,179;,
 4;237,236,181,180;,
 4;238,237,180,182;,
 4;182,183,239,238;,
 4;241,240,228,229;,
 4;185,260,261,206;,
 4;262,260,185,184;,
 4;203,263,262,184;,
 4;264,263,203,207;,
 4;230,248,247,231;,
 4;250,249,188,189;,
 4;189,190,251,250;,
 4;252,251,190,191;,
 4;254,253,193,192;,
 4;255,254,192,194;,
 4;194,195,256,255;,
 4;195,196,257,256;,
 4;258,257,196,198;,
 4;198,197,259,258;,
 4;232,259,197,177;,
 3;265,266,267;,
 3;266,268,267;,
 3;267,268,269;,
 3;268,270,269;,
 3;269,270,271;,
 3;270,272,271;,
 3;271,272,273;,
 3;272,274,273;,
 3;273,274,275;,
 3;274,276,275;,
 3;275,276,277;,
 3;277,276,278;,
 3;276,279,278;,
 3;278,279,280;,
 3;279,281,280;,
 3;280,281,282;,
 3;281,283,282;,
 3;283,284,282;,
 4;285,286,287,288;,
 4;289,290,291,292;,
 4;293,289,292,294;,
 4;290,295,296,291;,
 4;295,297,298,296;,
 4;286,293,294,287;,
 4;299,300,301,302;,
 4;297,299,302,298;,
 4;300,303,304,301;,
 4;303,305,306,304;,
 4;305,307,308,306;,
 4;307,285,288,308;;
 
 MeshMaterialList {
  1;
  232;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\MATERIAL\\UV_potetoman_01.png";
   }
  }
 }
 MeshNormals {
  215;
  0.365270;0.806604;-0.464723;,
  -0.365270;0.806604;-0.464723;,
  0.361884;0.830925;0.422615;,
  -0.361884;0.830925;0.422614;,
  0.000000;0.796153;0.605095;,
  0.000000;0.803839;-0.594847;,
  0.129023;0.819413;0.558494;,
  0.273200;0.812409;-0.515125;,
  -0.273200;0.812409;-0.515125;,
  -0.129023;0.819413;0.558494;,
  0.596092;0.801793;-0.042442;,
  -0.596092;0.801793;-0.042442;,
  0.486128;0.815532;-0.313985;,
  -0.486129;0.815532;-0.313985;,
  -0.537581;0.821467;0.190259;,
  0.537581;0.821467;0.190259;,
  0.735157;0.146518;0.661874;,
  0.289249;0.186164;0.938977;,
  -0.000000;0.195247;0.980754;,
  -0.289249;0.186163;0.938977;,
  -0.735157;0.146518;0.661874;,
  -0.958073;0.111982;0.263736;,
  -0.994089;0.095286;-0.052036;,
  -0.928769;0.109860;-0.354005;,
  -0.721839;0.133599;-0.679043;,
  -0.463298;0.154565;-0.872619;,
  -0.000000;-0.037784;-0.999286;,
  0.463298;0.154565;-0.872619;,
  0.721839;0.133599;-0.679043;,
  0.928769;0.109861;-0.354005;,
  0.994089;0.095286;-0.052035;,
  0.958073;0.111982;0.263736;,
  0.614087;0.514080;0.598848;,
  0.227299;0.546812;0.805811;,
  0.000000;0.531472;0.847076;,
  -0.227299;0.546812;0.805811;,
  -0.614087;0.514080;0.598848;,
  -0.853180;0.454671;0.255653;,
  -0.907843;0.415905;-0.053335;,
  -0.804376;0.454250;-0.382931;,
  -0.603515;0.483598;-0.633958;,
  -0.379542;0.513346;-0.769691;,
  0.000000;0.649028;-0.760765;,
  0.379542;0.513346;-0.769691;,
  0.603515;0.483598;-0.633958;,
  0.804376;0.454250;-0.382931;,
  0.907843;0.415905;-0.053335;,
  0.853180;0.454671;0.255653;,
  0.000000;1.000000;0.000000;,
  0.174674;0.984522;-0.014318;,
  0.155512;0.985819;0.063055;,
  -0.155512;0.985819;0.063055;,
  -0.174674;0.984522;-0.014318;,
  0.132516;0.983995;-0.119138;,
  -0.132516;0.983995;-0.119138;,
  0.151453;0.963372;-0.221307;,
  0.104373;0.980076;-0.168991;,
  0.000000;0.979045;-0.203643;,
  -0.104373;0.980076;-0.168992;,
  -0.151454;0.963372;-0.221307;,
  -0.038334;0.980630;0.192081;,
  -0.141512;0.970964;0.192881;,
  0.000000;0.978241;0.207470;,
  0.038334;0.980630;0.192081;,
  0.141512;0.970964;0.192881;,
  0.271840;0.400428;0.875077;,
  0.704693;0.321961;0.632257;,
  0.933628;0.250472;0.256129;,
  0.975273;0.215023;-0.051062;,
  0.904838;0.246156;-0.347382;,
  0.706496;0.278682;-0.650538;,
  0.504344;0.309937;-0.805963;,
  -0.504344;0.309938;-0.805962;,
  -0.706497;0.278682;-0.650537;,
  -0.904839;0.246156;-0.347382;,
  -0.975273;0.215023;-0.051062;,
  -0.933628;0.250472;0.256129;,
  -0.704693;0.321961;0.632257;,
  -0.271841;0.400427;0.875077;,
  -0.000000;0.418394;0.908266;,
  0.704694;0.321958;0.632257;,
  0.271840;0.400425;0.875079;,
  0.000000;0.418392;0.908267;,
  -0.271840;0.400425;0.875079;,
  -0.704694;0.321958;0.632257;,
  -0.933629;0.250469;0.256128;,
  -0.975273;0.215022;-0.051063;,
  -0.893570;0.250678;-0.372414;,
  -0.698481;0.306165;-0.646828;,
  -0.492070;0.353804;-0.795418;,
  0.492070;0.353804;-0.795418;,
  0.698481;0.306165;-0.646828;,
  0.893570;0.250678;-0.372414;,
  0.975273;0.215022;-0.051063;,
  0.933629;0.250469;0.256128;,
  -0.000001;0.195246;0.980754;,
  -0.000001;0.418394;0.908266;,
  -0.070549;0.976755;-0.202417;,
  -0.173295;0.793386;-0.583531;,
  -0.203591;0.554551;-0.806860;,
  -0.328864;0.096428;-0.939442;,
  0.000000;0.195248;0.980754;,
  0.000000;0.418395;0.908265;,
  0.070549;0.976755;-0.202417;,
  0.173295;0.793386;-0.583531;,
  0.203591;0.554551;-0.806860;,
  0.328864;0.096429;-0.939441;,
  0.821267;-0.416295;-0.390151;,
  -0.306307;0.380806;-0.872446;,
  -0.303442;0.371585;-0.877410;,
  0.306308;0.380805;-0.872446;,
  0.000001;0.410069;-0.912055;,
  0.308499;0.382193;-0.871067;,
  0.000001;0.418365;-0.908279;,
  0.000000;-0.921298;-0.388857;,
  -0.373465;-0.811526;-0.449387;,
  0.373465;-0.811525;-0.449389;,
  -0.308496;0.382197;-0.871066;,
  -0.821268;-0.416297;-0.390149;,
  0.303443;0.371584;-0.877410;,
  0.271841;0.400424;0.875079;,
  0.704695;0.321957;0.632257;,
  0.933629;0.250468;0.256129;,
  0.975274;0.215021;-0.051062;,
  0.897905;0.248913;-0.363054;,
  0.717883;0.301969;-0.627263;,
  0.645644;0.329130;-0.689070;,
  -0.946063;-0.101632;-0.307630;,
  0.946062;-0.101633;-0.307631;,
  -0.645644;0.329130;-0.689070;,
  -0.717883;0.301969;-0.627263;,
  -0.897906;0.248913;-0.363054;,
  -0.975274;0.215021;-0.051062;,
  -0.933629;0.250469;0.256129;,
  -0.704695;0.321957;0.632258;,
  -0.271841;0.400423;0.875079;,
  -0.000000;0.418390;0.908268;,
  -0.000000;0.418390;0.908267;,
  0.000000;0.418390;0.908267;,
  0.271841;0.400424;0.875079;,
  0.704694;0.321958;0.632257;,
  0.933629;0.250470;0.256129;,
  0.975274;0.215020;-0.051062;,
  0.901947;0.247294;-0.354029;,
  0.723640;0.272859;-0.633951;,
  0.642639;0.272259;-0.716164;,
  -0.936474;0.319619;-0.144431;,
  0.318949;0.193360;-0.927838;,
  0.000000;0.205778;-0.978599;,
  -0.318949;0.193359;-0.927838;,
  0.936474;0.319620;-0.144431;,
  -0.723640;0.272859;-0.633951;,
  -0.901948;0.247293;-0.354029;,
  -0.975274;0.215020;-0.051062;,
  -0.933629;0.250470;0.256129;,
  -0.704694;0.321959;0.632257;,
  -0.271841;0.400423;0.875079;,
  -0.000001;0.418389;0.908268;,
  -0.000000;0.418389;0.908268;,
  0.000000;0.418389;0.908268;,
  -0.329356;-0.035130;-0.943552;,
  -0.467374;-0.033707;-0.883417;,
  0.329356;-0.035127;-0.943552;,
  0.467374;-0.033704;-0.883417;,
  0.727633;-0.031295;-0.685253;,
  0.933890;-0.028213;-0.356445;,
  0.998299;-0.025881;-0.052244;,
  0.963510;-0.028878;0.266111;,
  0.741653;-0.034090;0.669917;,
  0.292082;-0.038887;0.955602;,
  0.000000;-0.038652;0.999253;,
  0.000000;-0.038652;0.999253;,
  0.000000;-0.038652;0.999253;,
  -0.292082;-0.038887;0.955602;,
  -0.741653;-0.034090;0.669917;,
  -0.963510;-0.028878;0.266111;,
  -0.998299;-0.025881;-0.052244;,
  -0.933890;-0.028213;-0.356445;,
  -0.727633;-0.031295;-0.685253;,
  -0.243764;0.362610;-0.899496;,
  -0.237011;0.375236;-0.896116;,
  -0.275177;0.371292;-0.886803;,
  -0.297028;0.353213;-0.887139;,
  0.000000;0.398478;-0.917178;,
  0.237011;0.375237;-0.896116;,
  0.275178;0.371292;-0.886803;,
  0.000000;0.402163;-0.915568;,
  0.000000;0.394689;-0.918815;,
  0.219884;0.380826;-0.898122;,
  -0.219884;0.380823;-0.898123;,
  0.243763;0.362612;-0.899496;,
  0.297028;0.353212;-0.887139;,
  0.334279;0.182032;-0.924728;,
  0.314678;0.189851;-0.930019;,
  0.000000;0.206798;-0.978384;,
  -0.314677;0.189851;-0.930019;,
  -0.334279;0.182033;-0.924728;,
  -0.486873;0.846299;0.216175;,
  0.000002;0.926085;0.377314;,
  0.486874;0.846299;0.216175;,
  -0.812320;0.583107;-0.011106;,
  0.812319;0.583108;-0.011105;,
  -0.642639;0.272259;-0.716163;,
  0.328619;0.191009;-0.924946;,
  -0.328619;0.191008;-0.924946;,
  0.000000;-1.000000;-0.000000;,
  -0.422047;0.000000;0.906574;,
  -0.346572;0.000000;0.938023;,
  0.000000;0.000000;1.000000;,
  0.016548;0.000000;0.999863;,
  -0.016549;0.000000;0.999863;,
  0.346573;0.000000;0.938023;,
  0.422050;0.000000;0.906573;,
  0.998865;0.000000;-0.047635;,
  -0.998865;0.000000;-0.047635;;
  232;
  4;25,100,160,161;,
  4;48,48,48,48;,
  4;173,172,95,19;,
  4;21,22,176,175;,
  4;30,31,167,166;,
  4;171,170,101,18;,
  4;48,48,48,48;,
  4;26,106,162,26;,
  4;16,17,169,168;,
  4;49,48,48,50;,
  4;164,163,27,28;,
  4;24,25,161,178;,
  4;51,48,48,52;,
  4;174,173,19,20;,
  4;53,48,48,49;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;52,48,48,54;,
  4;22,23,177,176;,
  4;29,30,166,165;,
  4;55,56,48,53;,
  4;48,48,103,57;,
  4;48,48,97,58;,
  4;54,48,58,59;,
  4;178,177,23,24;,
  4;28,29,165,164;,
  4;20,21,175,174;,
  4;60,48,51,61;,
  4;62,48,48,60;,
  4;62,48,48,62;,
  4;50,48,63,64;,
  4;168,167,31,16;,
  4;80,81,120,121;,
  4;137,138,82,82;,
  4;135,136,82,83;,
  4;134,135,83,84;,
  4;84,85,133,134;,
  4;85,86,132,133;,
  4;86,87,131,132;,
  4;130,131,87,88;,
  4;88,89,129,130;,
  4;179,180,181,182;,
  4;183,184,185,186;,
  4;125,126,90,91;,
  4;91,92,124,125;,
  4;92,93,123,124;,
  4;93,94,122,123;,
  4;121,122,94,80;,
  4;2,6,33,32;,
  4;34,34,4,4;,
  4;35,34,4,9;,
  4;36,35,9,3;,
  4;14,37,36,3;,
  4;11,38,37,14;,
  4;13,39,38,11;,
  4;40,39,13,1;,
  4;8,41,40,1;,
  4;98,99,41,8;,
  4;104,105,42,5;,
  4;44,43,7,0;,
  4;12,45,44,0;,
  4;10,46,45,12;,
  4;15,47,46,10;,
  4;32,47,15,2;,
  4;15,10,49,50;,
  4;11,14,51,52;,
  4;10,12,53,49;,
  4;13,11,52,54;,
  4;0,7,56,55;,
  4;12,0,55,53;,
  4;103,104,5,57;,
  4;97,98,8,58;,
  4;8,1,59,58;,
  4;1,13,54,59;,
  4;14,3,61,51;,
  4;3,9,60,61;,
  4;9,4,62,60;,
  4;4,4,62,62;,
  4;6,2,64,63;,
  4;2,15,50,64;,
  4;66,65,17,16;,
  4;16,31,67,66;,
  4;68,67,31,30;,
  4;69,68,30,29;,
  4;70,69,29,28;,
  4;28,27,71,70;,
  4;111,110,112,113;,
  3;72,100,25;,
  4;73,72,25,24;,
  4;24,23,74,73;,
  4;75,74,23,22;,
  4;76,75,22,21;,
  4;77,76,21,20;,
  4;20,19,78,77;,
  4;19,95,96,78;,
  4;18,101,102,79;,
  4;32,33,81,80;,
  4;82,82,34,34;,
  4;83,82,34,35;,
  4;84,83,35,36;,
  4;36,37,85,84;,
  4;37,38,86,85;,
  4;38,39,87,86;,
  4;88,87,39,40;,
  4;40,41,89,88;,
  3;41,99,89;,
  4;187,188,184,183;,
  4;91,90,43,44;,
  4;44,45,92,91;,
  4;45,46,93,92;,
  4;46,47,94,93;,
  4;80,94,47,32;,
  4;95,172,171,18;,
  4;96,95,18,79;,
  4;82,136,137,82;,
  4;34,82,82,34;,
  4;4,34,34,4;,
  4;62,4,4,62;,
  4;62,48,48,62;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;97,48,48,57;,
  4;5,98,97,57;,
  4;5,42,99,98;,
  4;180,189,187,183;,
  4;186,181,180,183;,
  4;117,108,111,113;,
  4;160,100,26,26;,
  4;101,170,169,17;,
  4;102,101,17,65;,
  4;82,138,120,81;,
  4;34,82,81,33;,
  4;4,34,33,6;,
  4;62,4,6,63;,
  4;63,48,48,62;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;103,48,48,56;,
  4;7,104,103,56;,
  4;7,43,105,104;,
  3;184,188,190;,
  4;191,185,184,190;,
  3;112,110,119;,
  4;162,106,27,163;,
  3;179,189,180;,
  3;90,105,43;,
  3;109,108,117;,
  3;106,71,27;,
  4;128,128,107,107;,
  4;197,198,198,197;,
  4;114,115,115,114;,
  4;116,114,114,116;,
  4;198,199,199,198;,
  4;115,118,118,115;,
  4;118,127,127,118;,
  4;200,197,197,200;,
  4;107,116,116,107;,
  4;199,201,201,199;,
  4;121,120,139,140;,
  4;140,141,122,121;,
  4;123,122,141,142;,
  4;124,123,142,143;,
  4;125,124,143,144;,
  4;144,145,126,125;,
  4;127,127,146,146;,
  4;192,193,185,191;,
  4;186,185,193,194;,
  4;194,195,181,186;,
  4;182,181,195,196;,
  4;150,150,128,128;,
  4;130,129,202,151;,
  4;151,152,131,130;,
  4;132,131,152,153;,
  4;133,132,153,154;,
  4;134,133,154,155;,
  4;155,156,135,134;,
  4;156,157,136,135;,
  4;137,136,157,158;,
  4;158,159,138,137;,
  4;120,138,159,139;,
  4;140,139,65,66;,
  4;66,67,141,140;,
  4;142,141,67,68;,
  4;143,142,68,69;,
  4;144,143,69,70;,
  4;70,71,145,144;,
  4;146,146,200,200;,
  4;110,147,203,119;,
  4;148,147,110,111;,
  4;108,149,148,111;,
  4;204,149,108,109;,
  4;201,150,150,201;,
  4;151,202,72,73;,
  4;73,74,152,151;,
  4;153,152,74,75;,
  4;154,153,75,76;,
  4;155,154,76,77;,
  4;77,78,156,155;,
  4;78,96,157,156;,
  4;158,157,96,79;,
  4;79,102,159,158;,
  4;139,159,102,65;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  3;205,205,205;,
  4;206,207,207,206;,
  4;208,209,209,208;,
  4;210,208,208,210;,
  4;209,211,211,209;,
  4;211,212,212,211;,
  4;207,210,210,207;,
  4;203,147,193,192;,
  4;213,213,213,213;,
  4;147,148,194,193;,
  4;148,149,195,194;,
  4;149,204,196,195;,
  4;214,214,214,214;;
 }
 MeshTextureCoords {
  309;
  0.173840;0.642840;,
  0.162140;0.642840;,
  0.161590;0.737150;,
  0.173090;0.737150;,
  0.384600;0.516820;,
  0.382960;0.516820;,
  0.382960;0.516820;,
  0.384600;0.516820;,
  0.421900;0.735550;,
  0.410430;0.735550;,
  0.410980;0.643300;,
  0.422660;0.643300;,
  0.484900;0.643300;,
  0.487720;0.643300;,
  0.484720;0.735550;,
  0.482000;0.735550;,
  0.268980;0.643300;,
  0.271790;0.643300;,
  0.274700;0.735550;,
  0.271980;0.735550;,
  0.378350;0.735550;,
  0.346270;0.735550;,
  0.345710;0.643300;,
  0.378350;0.643300;,
  0.378350;0.516820;,
  0.373740;0.516820;,
  0.373740;0.516820;,
  0.378350;0.516820;,
  0.129450;0.642840;,
  0.096760;0.642840;,
  0.097310;0.737150;,
  0.129450;0.737150;,
  0.295840;0.643300;,
  0.334040;0.643300;,
  0.334800;0.735550;,
  0.297910;0.735550;,
  0.356850;0.516820;,
  0.372100;0.516820;,
  0.372100;0.516820;,
  0.357500;0.516820;,
  0.050370;0.737150;,
  0.085820;0.737150;,
  0.085070;0.642840;,
  0.048130;0.642840;,
  0.210770;0.642840;,
  0.208540;0.737150;,
  0.399190;0.516820;,
  0.399850;0.516820;,
  0.458790;0.735550;,
  0.460860;0.643300;,
  0.109490;0.513530;,
  0.123060;0.513530;,
  0.123060;0.513530;,
  0.107470;0.513530;,
  0.129450;0.513530;,
  0.124740;0.513530;,
  0.124740;0.513530;,
  0.129450;0.513530;,
  0.135850;0.513530;,
  0.134160;0.513530;,
  0.134160;0.513530;,
  0.135850;0.513530;,
  0.151440;0.513530;,
  0.149410;0.513530;,
  0.241260;0.642840;,
  0.232640;0.642840;,
  0.229870;0.737150;,
  0.238200;0.737150;,
  0.026270;0.642840;,
  0.017640;0.642840;,
  0.020710;0.737150;,
  0.029040;0.737150;,
  0.119410;0.513530;,
  0.123270;0.513530;,
  0.124900;0.513530;,
  0.129450;0.513530;,
  0.134000;0.513530;,
  0.135630;0.513530;,
  0.139500;0.513530;,
  0.384600;0.516820;,
  0.393560;0.516820;,
  0.382960;0.516820;,
  0.373740;0.516820;,
  0.378350;0.516820;,
  0.372100;0.516820;,
  0.363140;0.516820;,
  0.306270;0.576940;,
  0.333220;0.576940;,
  0.333440;0.594750;,
  0.303470;0.594750;,
  0.378350;0.594750;,
  0.345270;0.594750;,
  0.345110;0.576940;,
  0.378350;0.576940;,
  0.423260;0.594750;,
  0.411430;0.594750;,
  0.411590;0.576940;,
  0.423480;0.576940;,
  0.453230;0.594750;,
  0.450430;0.576940;,
  0.467390;0.576940;,
  0.472090;0.594750;,
  0.469380;0.576940;,
  0.474300;0.594750;,
  0.222520;0.575000;,
  0.216430;0.575000;,
  0.220780;0.593210;,
  0.227550;0.593210;,
  0.202280;0.593210;,
  0.199160;0.575000;,
  0.174940;0.575000;,
  0.185650;0.594490;,
  0.434290;0.087570;,
  0.382550;0.088110;,
  0.380900;0.193620;,
  0.480020;0.200500;,
  0.249670;0.089270;,
  0.116800;0.088110;,
  0.118440;0.193620;,
  0.249670;0.194850;,
  0.056630;0.593210;,
  0.073260;0.594490;,
  0.083960;0.575000;,
  0.059740;0.575000;,
  0.042480;0.575000;,
  0.038130;0.593210;,
  0.036390;0.575000;,
  0.031360;0.593210;,
  0.287320;0.576940;,
  0.289300;0.576940;,
  0.284600;0.594750;,
  0.282400;0.594750;,
  0.341700;0.525350;,
  0.361650;0.525350;,
  0.333080;0.565590;,
  0.308050;0.565590;,
  0.378350;0.565590;,
  0.345010;0.565590;,
  0.366050;0.525350;,
  0.378350;0.525350;,
  0.423620;0.565590;,
  0.411690;0.565590;,
  0.390650;0.525350;,
  0.395040;0.525350;,
  0.448650;0.565590;,
  0.415000;0.525350;,
  0.427560;0.525350;,
  0.464400;0.565590;,
  0.429030;0.525350;,
  0.466240;0.565590;,
  0.176760;0.522260;,
  0.213650;0.563390;,
  0.219310;0.563390;,
  0.181260;0.522260;,
  0.197170;0.563390;,
  0.162350;0.522260;,
  0.146040;0.522260;,
  0.175130;0.563390;,
  0.141670;0.522260;,
  0.163100;0.563390;,
  0.117230;0.522260;,
  0.095810;0.563390;,
  0.129450;0.563390;,
  0.129450;0.522260;,
  0.061730;0.563390;,
  0.083770;0.563390;,
  0.112860;0.522260;,
  0.096560;0.522260;,
  0.082150;0.522260;,
  0.045250;0.563390;,
  0.077640;0.522260;,
  0.039600;0.563390;,
  0.329140;0.525350;,
  0.292300;0.565590;,
  0.290460;0.565590;,
  0.327670;0.525350;,
  0.297500;0.632690;,
  0.333910;0.632690;,
  0.274590;0.632690;,
  0.271910;0.632690;,
  0.028860;0.631990;,
  0.020640;0.631990;,
  0.049990;0.631990;,
  0.084890;0.631990;,
  0.249670;0.419820;,
  0.121940;0.418430;,
  0.123580;0.481270;,
  0.249670;0.481690;,
  0.174010;0.631990;,
  0.208910;0.631990;,
  0.230040;0.631990;,
  0.238260;0.631990;,
  0.482100;0.632690;,
  0.484780;0.632690;,
  0.459190;0.632690;,
  0.422790;0.632690;,
  0.411080;0.632690;,
  0.345620;0.632690;,
  0.378350;0.632690;,
  0.249670;0.021470;,
  0.115080;0.021000;,
  0.384260;0.021000;,
  0.375760;0.481270;,
  0.377400;0.418430;,
  0.065060;0.087570;,
  0.019330;0.200500;,
  0.071080;0.417890;,
  0.428270;0.417890;,
  0.182890;0.597950;,
  0.185870;0.594400;,
  0.175250;0.574930;,
  0.172420;0.578500;,
  0.097750;0.642720;,
  0.130160;0.642720;,
  0.130160;0.646390;,
  0.101300;0.646320;,
  0.130160;0.563340;,
  0.096810;0.563340;,
  0.099350;0.567030;,
  0.130160;0.567110;,
  0.163510;0.563340;,
  0.160970;0.567030;,
  0.162570;0.642720;,
  0.159020;0.646320;,
  0.085070;0.574930;,
  0.087900;0.578500;,
  0.074450;0.594400;,
  0.077430;0.597950;,
  0.085990;0.631880;,
  0.089280;0.635400;,
  0.174330;0.631880;,
  0.171040;0.635400;,
  0.333700;0.615590;,
  0.300190;0.615590;,
  0.279100;0.615590;,
  0.276640;0.615590;,
  0.025470;0.614520;,
  0.033040;0.614520;,
  0.052980;0.614520;,
  0.073600;0.615800;,
  0.074800;0.615690;,
  0.077950;0.619230;,
  0.021580;0.324000;,
  0.120360;0.317120;,
  0.249670;0.318430;,
  0.378980;0.317120;,
  0.477760;0.324000;,
  0.182370;0.619230;,
  0.185520;0.615690;,
  0.185300;0.615800;,
  0.205920;0.614520;,
  0.225870;0.614520;,
  0.233440;0.614520;,
  0.480060;0.615590;,
  0.477590;0.615590;,
  0.456510;0.615590;,
  0.423000;0.615590;,
  0.411240;0.615590;,
  0.378350;0.615590;,
  0.345460;0.615590;,
  0.120360;0.317160;,
  0.021580;0.324040;,
  0.249670;0.318480;,
  0.378980;0.317160;,
  0.477760;0.324040;,
  0.125770;0.768980;,
  0.174000;0.768980;,
  0.081040;0.768980;,
  0.210410;0.768980;,
  0.054320;0.768980;,
  0.231300;0.768980;,
  0.032650;0.768980;,
  0.231300;0.768980;,
  0.029380;0.768980;,
  0.231300;0.768980;,
  0.020250;0.768980;,
  0.231300;0.768980;,
  0.029380;0.768980;,
  0.032650;0.768980;,
  0.231300;0.768980;,
  0.054320;0.768980;,
  0.210410;0.768980;,
  0.081040;0.768980;,
  0.174000;0.768980;,
  0.125770;0.768980;,
  0.175970;-0.065510;,
  0.175970;-0.081260;,
  0.175970;-0.081260;,
  0.175970;-0.065510;,
  0.113470;-0.091300;,
  0.067440;-0.091300;,
  0.067440;-0.091300;,
  0.113470;-0.091300;,
  0.159510;-0.091300;,
  0.159510;-0.091300;,
  0.050970;-0.081260;,
  0.050970;-0.081260;,
  0.050970;-0.065510;,
  0.050970;-0.065510;,
  0.050970;-0.047070;,
  0.067440;-0.047070;,
  0.067440;-0.047070;,
  0.050970;-0.047070;,
  0.113470;-0.047070;,
  0.113470;-0.047070;,
  0.159510;-0.047070;,
  0.159510;-0.047070;,
  0.175970;-0.047070;,
  0.175970;-0.047070;;
 }
}
