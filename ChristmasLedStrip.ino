const unsigned int nonlinear[256] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3,
3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8,
9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 13, 13, 14, 14, 14, 15, 15, 16,
16, 17, 17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 
27, 27, 28, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 37, 37, 38, 39, 40, 
41, 42, 43, 44, 44, 45, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 
59, 60, 61, 62, 64, 65, 66, 67, 69, 70, 71, 72, 74, 75, 76, 78, 79, 81,
82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 97, 98, 100, 102, 103, 105, 107,
108, 110, 112, 114, 115, 117, 119, 121, 123, 124, 126, 128, 130, 132, 134,
136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 157, 159, 161, 163, 165,
168, 170, 172, 175, 177, 179, 182, 184, 187, 189, 192, 194, 197, 199, 202,
204, 207, 209, 212, 215, 217, 220, 223, 226, 228, 231, 234, 237, 240, 243, 
246, 249, 252, 255};

// gamma correction table
const unsigned int gamma25[256] = {
0, 0, 0, 0, 0, 0, 1, 1, 
1, 2, 2, 3, 4, 5, 6, 7, 
8, 9, 11, 12, 14, 16, 18, 20, 
22, 25, 27, 30, 33, 36, 39, 42, 
46, 49, 53, 57, 61, 66, 70, 75, 
80, 85, 90, 96, 101, 107, 113, 119, 
126, 133, 139, 147, 154, 161, 169, 177, 
185, 193, 202, 211, 220, 229, 239, 249, 
258, 269, 279, 290, 301, 312, 323, 335, 
347, 359, 372, 384, 397, 410, 424, 438, 
452, 466, 480, 495, 510, 525, 541, 557, 
573, 589, 606, 623, 640, 658, 676, 694, 
712, 731, 750, 769, 789, 809, 829, 849, 
870, 891, 913, 934, 956, 978, 1001, 1024, 
1047, 1071, 1095, 1119, 1143, 1168, 1193, 1219, 
1244, 1270, 1297, 1324, 1351, 1378, 1406, 1434, 
1462, 1491, 1520, 1549, 1579, 1609, 1640, 1670, 
1702, 1733, 1765, 1797, 1829, 1862, 1895, 1929, 
1963, 1997, 2032, 2067, 2102, 2138, 2174, 2210, 
2247, 2284, 2322, 2359, 2398, 2436, 2475, 2515, 
2554, 2594, 2635, 2676, 2717, 2759, 2801, 2843, 
2886, 2929, 2972, 3016, 3061, 3105, 3150, 3196, 
3242, 3288, 3335, 3382, 3429, 3477, 3525, 3574, 
3623, 3672, 3722, 3772, 3823, 3874, 3925, 3977, 
4029, 4082, 4135, 4189, 4243, 4297, 4352, 4407, 
4462, 4518, 4575, 4632, 4689, 4746, 4805, 4863, 
4922, 4981, 5041, 5101, 5162, 5223, 5285, 5347, 
5409, 5472, 5535, 5599, 5663, 5728, 5793, 5858, 
5924, 5990, 6057, 6124, 6192, 6260, 6329, 6398, 
6467, 6537, 6607, 6678, 6749, 6821, 6893, 6966, 
7039, 7113, 7187, 7261, 7336, 7411, 7487, 7564, 
7640, 7718, 7795, 7874, 7952, 8031, 8111, 8191 };

wvoid change_color(unsigned int H, unsigned int S, unsigned int V) {
    unsigned char Hi;
    unsigned char fr;
    unsigned int hue;
    unsigned char Vmin;
    unsigned char Vinc;
    unsigned char Vdec;
    unsigned int a;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
    if (!S){
        red=V;
        green=V;
        blue=V;
    } else {
        hue = H;
        Hi = hue/60;
        fr = hue - (Hi * 60); // mod 256
        Vmin = ((255 - S) * V) / 256;
        a = (V - Vmin) * fr / 60;
        Vinc = Vmin + a;
        Vdec = V - a;
       
        if (Hi==0) { red = V;     green = Vinc;  blue = Vmin; }
        if (Hi==1) { red = Vdec;  green = V;     blue = Vmin; }
        if (Hi==2) { red = Vmin;  green = V;     blue = Vinc; }
        if (Hi==3) { red = Vmin;  green = Vdec;  blue = V; }
        if (Hi==4) { red = Vinc;  green = Vmin;  blue = V; }
        if (Hi==5) { red = V;     green = Vmin;  blue = Vdec;  }
    }
    
    OCR4A = gamma22[red];
    OCR4B = gamma22[green];
    OCR4C = gamma22[blue];

}

void setup() {
  // Set as outputs.
  DDRH |= (1 << DDH3) | (1 << DDH4) | (1 << DDH5);

  TCCR4A =
      (1 << COM4A1) | (0 << COM4A0) |
      (1 << COM4B1) | (0 << COM4B0) |
      (1 << COM4C1) | (0 << COM4C0) |
      // Fast PWM 14-bit mode.
      (1 << WGM41) | (0 << WGM40);
  TCCR4B =
      // Fast PWM 14-bit mode.
      (1 << WGM43) | (1 << WGM42) |
      // no prescaler
      (0 << CS42) | (0 << CS41) | (1 << CS40);
  OCR4A = 0;
  OCR4B = 0;
  OCR4C = 0;
  ICR4 = 8191;
  randomSeed(analogRead(0));
}

unsigned int target_hue = 0;
unsigned int fadeSValue = 0;
unsigned int fadeVValue = 0;
long randNumber;
void loop() {
// 1  
//  target_hue++;
//  if(target_hue >= 360) target_hue = 0;
//  change_color(target_hue, 210, 255); 
//  delay(50);

// 2
//  for (int i=10; i <= 255; i++) {
//    change_color(180, 255, i);
//    delay(10);
//  }
//  
//  for (int i=0; i <= 255 ; i++) {
//    change_color(180, 255 - nonlinear[i], 255);
//    delay(10);
//  }
//    
//  for (int i=0; i <= 255 ; i++) {
//    change_color(27, 255 - nonlinear[255 - i], 255);
//    delay(10);
//  }
//  
//  for (int i=255; i > 10 ; i--) {
//    change_color(27, 255, i);
//    delay(10);
//  }

//3
randNumber = random(360);
  for (int i=10; i <= 255; i++) {
    change_color(randNumber, 210, i);
    delay(50);
  }
  delay(1000);
  for (int i=255; i > 10 ; i--) {
    change_color(randNumber, 200, i);
    delay(50);
  }
  
}










