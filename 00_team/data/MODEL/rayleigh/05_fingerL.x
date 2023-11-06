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
 128;
 0.70355;-0.12185;-0.24578;,
 0.15379;-0.12789;-0.24020;,
 0.15265;0.12111;-0.24019;,
 0.70241;0.12715;-0.24577;,
 0.15379;-0.12789;-0.24020;,
 0.15872;-0.12789;0.24577;,
 0.15758;0.12111;0.24578;,
 0.15265;0.12111;-0.24019;,
 0.15872;-0.12789;0.24577;,
 0.70849;-0.12185;0.24019;,
 0.70735;0.12715;0.24020;,
 0.15758;0.12111;0.24578;,
 0.70849;-0.12185;0.24019;,
 0.70355;-0.12185;-0.24578;,
 0.70241;0.12715;-0.24577;,
 0.70735;0.12715;0.24020;,
 0.70241;0.12715;-0.24577;,
 0.15265;0.12111;-0.24019;,
 0.15758;0.12111;0.24578;,
 0.70735;0.12715;0.24020;,
 0.70849;-0.12185;0.24019;,
 0.15872;-0.12789;0.24577;,
 0.15379;-0.12789;-0.24020;,
 0.70355;-0.12185;-0.24578;,
 0.71090;-0.25893;-0.22711;,
 0.40081;-0.45433;-0.23079;,
 0.36602;-0.37183;-0.23093;,
 0.67610;-0.17643;-0.22726;,
 0.40081;-0.45433;-0.23079;,
 0.39938;-0.45486;-0.09077;,
 0.36458;-0.37237;-0.09092;,
 0.36602;-0.37183;-0.23093;,
 0.39938;-0.45486;-0.09077;,
 0.70946;-0.25946;-0.08710;,
 0.67466;-0.17697;-0.08724;,
 0.36458;-0.37237;-0.09092;,
 0.70946;-0.25946;-0.08710;,
 0.71090;-0.25893;-0.22711;,
 0.67610;-0.17643;-0.22726;,
 0.67466;-0.17697;-0.08724;,
 0.67610;-0.17643;-0.22726;,
 0.36602;-0.37183;-0.23093;,
 0.36458;-0.37237;-0.09092;,
 0.67466;-0.17697;-0.08724;,
 0.70946;-0.25946;-0.08710;,
 0.39938;-0.45486;-0.09077;,
 0.40081;-0.45433;-0.23079;,
 0.71090;-0.25893;-0.22711;,
 0.77005;-0.21865;-0.06106;,
 0.63114;-0.01688;-0.05965;,
 0.68198;0.03541;-0.06017;,
 0.82088;-0.16636;-0.06158;,
 0.63114;-0.01688;-0.05965;,
 0.63389;-0.01688;0.21141;,
 0.68473;0.03541;0.21089;,
 0.68198;0.03541;-0.06017;,
 0.63389;-0.01688;0.21141;,
 0.77280;-0.21865;0.21000;,
 0.82364;-0.16636;0.20948;,
 0.68473;0.03541;0.21089;,
 0.77280;-0.21865;0.21000;,
 0.77005;-0.21865;-0.06106;,
 0.82088;-0.16636;-0.06158;,
 0.82364;-0.16636;0.20948;,
 0.82088;-0.16636;-0.06158;,
 0.82364;-0.16636;0.20948;,
 0.77280;-0.21865;0.21000;,
 0.77005;-0.21865;-0.06106;,
 0.41143;-0.15216;-0.05742;,
 0.67256;-0.38443;-0.06007;,
 0.63135;-0.44813;-0.05965;,
 0.37021;-0.21586;-0.05700;,
 0.67256;-0.38443;-0.06007;,
 0.67532;-0.38443;0.21099;,
 0.63410;-0.44813;0.21141;,
 0.63135;-0.44813;-0.05965;,
 0.67532;-0.38443;0.21099;,
 0.41418;-0.15216;0.21364;,
 0.37297;-0.21586;0.21406;,
 0.63410;-0.44813;0.21141;,
 0.41418;-0.15216;0.21364;,
 0.41143;-0.15216;-0.05742;,
 0.37021;-0.21586;-0.05700;,
 0.37297;-0.21586;0.21406;,
 0.37021;-0.21586;-0.05700;,
 0.37297;-0.21586;0.21406;,
 0.41418;-0.15216;0.21364;,
 0.41143;-0.15216;-0.05742;,
 0.39110;-0.42784;-0.22386;,
 0.18617;-0.08277;-0.22861;,
 0.24763;-0.02827;-0.22973;,
 0.45255;-0.37335;-0.22499;,
 0.18617;-0.08277;-0.22861;,
 0.18673;-0.07940;-0.08861;,
 0.24819;-0.02490;-0.08974;,
 0.24763;-0.02827;-0.22973;,
 0.18673;-0.07940;-0.08861;,
 0.39165;-0.42448;-0.08387;,
 0.45311;-0.36998;-0.08499;,
 0.24819;-0.02490;-0.08974;,
 0.39165;-0.42448;-0.08387;,
 0.39110;-0.42784;-0.22386;,
 0.45255;-0.37335;-0.22499;,
 0.45311;-0.36998;-0.08499;,
 0.45255;-0.37335;-0.22499;,
 0.45311;-0.36998;-0.08499;,
 0.18673;-0.07940;-0.08861;,
 0.18617;-0.08277;-0.22861;,
 0.63407;-0.34928;-0.05968;,
 0.77990;-0.15495;-0.06116;,
 0.82886;-0.20984;-0.06166;,
 0.68303;-0.40418;-0.06018;,
 0.77990;-0.15495;-0.06116;,
 0.78265;-0.15495;0.20990;,
 0.83161;-0.20984;0.20940;,
 0.82886;-0.20984;-0.06166;,
 0.78265;-0.15495;0.20990;,
 0.63682;-0.34928;0.21138;,
 0.68578;-0.40418;0.21088;,
 0.83161;-0.20984;0.20940;,
 0.63682;-0.34928;0.21138;,
 0.63407;-0.34928;-0.05968;,
 0.68303;-0.40418;-0.06018;,
 0.68578;-0.40418;0.21088;,
 0.68303;-0.40418;-0.06018;,
 0.68578;-0.40418;0.21088;,
 0.63682;-0.34928;0.21138;,
 0.63407;-0.34928;-0.05968;;
 
 36;
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
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,55,54,65;,
 4;66,53,52,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,75,74,85;,
 4;86,73,72,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,95,94,105;,
 4;100,106,107,101;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,115,114,125;,
 4;126,113,112,127;;
 
 MeshMaterialList {
  2;
  36;
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
  0,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1;;
  Material {
   0.335686;0.335686;0.335686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.778039;0.680784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  -0.010149;-0.000006;-0.999949;,
  -0.999938;-0.004578;0.010144;,
  0.010149;0.000006;0.999949;,
  0.010238;0.002560;-0.999944;,
  -0.921333;-0.388622;-0.010928;,
  -0.010237;-0.002561;0.999944;,
  -0.010196;-0.000032;-0.999948;,
  -0.716923;0.697115;0.007273;,
  0.010195;0.000031;0.999948;,
  -0.010163;-0.000017;-0.999948;,
  0.839530;-0.543247;-0.008533;,
  0.010163;0.000017;0.999948;,
  -0.004004;-0.016126;-0.999862;,
  -0.663551;0.747974;-0.015351;,
  0.004003;0.016125;0.999862;,
  -0.010183;0.000026;-0.999948;,
  0.746212;0.665665;-0.007571;,
  0.010183;-0.000026;0.999948;,
  0.999938;0.004578;-0.010165;,
  -0.010985;0.999940;0.000112;,
  0.010985;-0.999940;-0.000112;,
  0.921312;0.388669;0.010960;,
  -0.533114;0.846040;-0.002220;,
  0.533108;-0.846044;0.002261;,
  0.716957;-0.697079;-0.007287;,
  0.823627;0.567070;-0.008371;,
  -0.823618;-0.567084;0.008356;,
  -0.839530;0.543246;0.008533;,
  -0.664550;-0.747213;0.006754;,
  0.664550;0.747213;-0.006754;,
  0.663547;-0.747977;0.015348;,
  0.859812;0.510369;-0.015725;,
  -0.859803;-0.510384;0.015677;,
  -0.746273;-0.665597;0.007571;,
  0.799796;-0.600217;-0.008114;,
  -0.799781;0.600237;0.008114;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;;
 }
 MeshTextureCoords {
  128;
  0.101420;0.874100;,
  0.101420;0.792420;,
  0.125330;0.792420;,
  0.125330;0.874100;,
  0.097590;0.669130;,
  0.097590;0.568110;,
  0.131040;0.568110;,
  0.131040;0.669130;,
  0.098410;0.782020;,
  0.098410;0.676290;,
  0.129350;0.676290;,
  0.129350;0.782020;,
  0.097990;0.991080;,
  0.097990;0.884720;,
  0.133210;0.884720;,
  0.133210;0.991080;,
  0.011520;0.875180;,
  0.011520;0.788040;,
  0.088540;0.788040;,
  0.088540;0.875180;,
  0.139520;0.876620;,
  0.139520;0.788760;,
  0.217190;0.788760;,
  0.217190;0.876620;,
  0.173440;0.770650;,
  0.154260;0.732780;,
  0.162500;0.728610;,
  0.181690;0.766480;,
  0.165030;0.755180;,
  0.164980;0.738140;,
  0.173230;0.738200;,
  0.173270;0.755240;,
  0.147280;0.768020;,
  0.166470;0.730150;,
  0.174710;0.734320;,
  0.155520;0.772190;,
  0.155560;0.755240;,
  0.155610;0.738200;,
  0.163860;0.738140;,
  0.163800;0.755180;,
  0.152550;0.767470;,
  0.151720;0.729600;,
  0.168760;0.729250;,
  0.169590;0.767120;,
  0.153790;0.766100;,
  0.154620;0.728230;,
  0.171660;0.728570;,
  0.170830;0.766440;,
  0.154400;0.740150;,
  0.171170;0.760360;,
  0.164940;0.765520;,
  0.148180;0.745310;,
  0.180480;0.731880;,
  0.180480;0.764870;,
  0.174250;0.764870;,
  0.174250;0.731880;,
  0.145130;0.759330;,
  0.161900;0.739120;,
  0.168120;0.744280;,
  0.151360;0.764500;,
  0.188000;0.722540;,
  0.188000;0.755540;,
  0.181770;0.755540;,
  0.181770;0.722540;,
  0.157490;0.731880;,
  0.157490;0.764870;,
  0.163720;0.764870;,
  0.163720;0.731880;,
  0.184880;0.732870;,
  0.161520;0.764490;,
  0.155220;0.759430;,
  0.178570;0.727810;,
  0.176660;0.762280;,
  0.143670;0.762280;,
  0.143670;0.757220;,
  0.176660;0.757220;,
  0.157880;0.729810;,
  0.181230;0.761430;,
  0.174930;0.766490;,
  0.151570;0.734870;,
  0.182640;0.766490;,
  0.182640;0.733500;,
  0.187700;0.733500;,
  0.187700;0.766490;,
  0.176660;0.725600;,
  0.143670;0.725600;,
  0.143670;0.730660;,
  0.176660;0.730660;,
  0.158980;0.727140;,
  0.183660;0.761680;,
  0.176150;0.767060;,
  0.151460;0.732520;,
  0.169760;0.722440;,
  0.186800;0.722330;,
  0.186740;0.729850;,
  0.169700;0.729960;,
  0.149130;0.760560;,
  0.173820;0.726020;,
  0.181340;0.731390;,
  0.156650;0.765930;,
  0.172290;0.748570;,
  0.189330;0.748670;,
  0.189390;0.756190;,
  0.172350;0.756080;,
  0.170530;0.754650;,
  0.187570;0.754540;,
  0.173120;0.723880;,
  0.190160;0.723980;,
  0.180490;0.735500;,
  0.162600;0.754720;,
  0.156680;0.749210;,
  0.174570;0.729990;,
  0.173920;0.732390;,
  0.173920;0.765390;,
  0.168000;0.765390;,
  0.168000;0.732390;,
  0.171220;0.756260;,
  0.153330;0.737040;,
  0.159250;0.731530;,
  0.177140;0.750760;,
  0.177340;0.730850;,
  0.177340;0.763840;,
  0.171420;0.763840;,
  0.171420;0.730850;,
  0.185890;0.732390;,
  0.185890;0.765390;,
  0.191810;0.765390;,
  0.191810;0.732390;;
 }
}