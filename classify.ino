/* integration.ino
** Processing Integration sketch for SIXT33N Speech version
** 
** EE16B Spring 2016
** Emily Naviasky & Nathaniel Mailoa
**
*/

//define constants
#define MIC_INPUT P6_0
#define SIZE 2752
#define SIZE_AFTER_FILTER 172


/*---------------*/
/* CODE BLOCK A1 */
/*---------------*/

// Enveloping and K-means constants
#define SNIPPET_SIZE 90
#define PRELENGTH 15 
#define THRESHOLD 0.5

#define KMEANS_THRESHOLD 1100// YOUR CODE HERE 
#define LOUDNESS_THRESHOLD 700

/*----------------------*/
/* END OF CODE BLOCK A1 */
/*----------------------*/

/*---------------*/
/* CODE BLOCK A2 */
/*---------------*/

//define arrays
float pca_vec1[SNIPPET_SIZE] = {-0.0306148010212,
-0.0295224380089, 
-0.0299687811803, 
-0.0307465468719, 
-0.0311204107468, 
-0.0321112263955, 
-0.0358189201788, 
-0.0303636916196, 
-0.0300336707663, 
-0.0292538798906, 
-0.0283701898111, 
-0.0276056923657, 
-0.0310395071227, 
-0.0295445160669, 
-0.0305730729926, 
-0.0291934544558, 
-0.0301416857043, 
-0.0321355328778, 
-0.0287545365215, 
-0.0297574045618, 
-0.0309461890392, 
-0.0313083741737, 
-0.0311431155337, 
-0.0325795948769, 
-0.0337508254647, 
-0.0307879150952, 
-0.0364473282984, 
-0.0320969515458, 
-0.0321645229373, 
-0.0338237143812, 
-0.0353828678351, 
-0.0326151870065, 
-0.0323069863699, 
-0.0301874616221, 
-0.0312239429967, 
-0.0334910169092, 
-0.0322135512447, 
-0.0348085792236, 
-0.0352776850523, 
-0.0346004381116, 
-0.0357615751631, 
-0.0377996732542, 
-0.0415833719371, 
-0.0467467697428, 
-0.0569299468319, 
-0.0702371337396, 
-0.0783803250608, 
-0.0867228272576, 
-0.0929712115053, 
-0.0980143075732, 
-0.102049674804, 
-0.119293152425, 
-0.12314318913, 
-0.126546834641, 
-0.134988378317, 
-0.132613934962, 
-0.129947400745, 
-0.133894950206, 
-0.139809814641, 
-0.133821325397, 
-0.132199123631, 
-0.138638306992, 
-0.134991139038, 
-0.137030846415, 
-0.12274215907, 
-0.141464786274, 
-0.138171915134, 
-0.129383556737, 
-0.138623619218, 
-0.118570046844, 
-0.116218195227, 
-0.11930700938, 
-0.101069311899, 
-0.10742475592, 
-0.0936890909859, 
-0.0939302691088, 
-0.0893658216322, 
-0.0858376659996, 
-0.0831020161949, 
-0.0727669337671, 
-0.0820177042728, 
-0.0781403525128, 
-0.0829122097913, 
-0.088506000518, 
-0.0871258037492, 
-0.0813860308205, 
-0.0866206074109, 
-0.0822365322787, 
-0.0827081501766, 
-0.0877718763881, 
-0.0844059171072, 
-0.0933517504182, 
-0.0979260295892, 
-0.0955331134889, 
-0.103081766135, 
-0.105465294471, 
-0.106220041334, 
-0.113089797116, 
-0.104990665076, 
-0.11140429542, 
-0.108864850748, 
-0.106359773169, 
-0.107563502182, 
-0.103685383542, 
-0.110698042207, 
-0.103763407547, 
-0.104873597192, 
-0.0984175661418, 
-0.104943152302, 
-0.107430008175, 
-0.10920482253, 
-0.105596335992, 
-0.100823633501, 
-0.0918222535476, 
-0.0928427855706, 
-0.0896263031064, 
-0.0894884426471, 
-0.0875406487867, 
-0.0822906251935, 
-0.0841789952962, 
-0.077671122799, 
-0.0727964485245, 
-0.0682980310039, 
-0.0687153073834, 
-0.0668513994388, 
-0.0605943056625, 
-0.0583082011103, 
-0.0569530619171, 
-0.051425272675, 
-0.0489073675104, 
-0.0510985903326, 
-0.0462125689081, 
-0.0471510215297, 
-0.0434238008373, 
-0.0439161960504, 
-0.0401941168794, 
-0.0431344924688, 
-0.0374821160903, 
-0.0398789020382, 
-0.0373567504688, 
-0.0369905464735, 
-0.034235155233, 
-0.0389688951023, 
-0.0349265764927, 
-0.0366056503128, 
-0.0353419716416, 
-0.0354136430043, 
-0.034388583314, 
-0.0343025307064, 
-0.0370648012054, 
-0.0366440720192, 
-0.0373979939956, 
-0.0368081171547, 
-0.0375453626478, 
-0.0357721262455, 
-0.0375117033501, 
-0.034957437044, 
-0.0374596232234, 
-0.0381398299893, 
-0.0407657075543, 
-0.0363207533184, 
-0.0365955311017, 
-0.0384574642631, 
-0.0352132368371, 
-0.0382096122837, 
-0.0373026209769, 
-0.0342905027445, 
-0.0381713137206, 
-0.0421528138812, 
-0.0373930653329, 
-0.0370715694186, 
-0.0371259949044}; // YOUR CODE HERE
float pca_vec2[SNIPPET_SIZE] = {0.00035849061175, 
-0.000914583314838, 
0.0015873373756, 
-0.00285487768527, 
-0.000711954608312, 
0.000639998279102, 
-0.0250925325459, 
-0.00068391954777, 
-0.0014149079263, 
-0.000136040878194, 
-0.00234664441647, 
-0.00192728264956, 
0.00121785541748, 
-0.0032782610432, 
0.00310292568004, 
-0.000897207764473, 
-0.0015838365139, 
0.00132311713876, 
-0.000147684127062, 
0.000249602821656, 
0.0031685559986, 
-0.00637611493459, 
0.000690396849161, 
0.000868177751925, 
0.00177834330427, 
0.000919348842682, 
0.00588319932272, 
0.00123233031964, 
0.00460870372255, 
0.00192537445645, 
0.00766164164768, 
0.00276079174932, 
-0.00234497688301, 
-0.00139396853692, 
0.0012792168743, 
0.00416973643371, 
0.00240018774135, 
0.00533491564082, 
0.00382576419454, 
-0.000448398639054, 
0.00133215912554, 
0.00747995939361, 
0.00706995417001, 
0.0128535886123, 
0.024165920851, 
0.0456860683316, 
0.0767655901629, 
0.0704065641917, 
0.0757865211044, 
0.104042956858, 
0.114724116423, 
0.143039691592, 
0.152368397731, 
0.154952679359, 
0.184139625099, 
0.182693155776, 
0.168353714202, 
0.185234698729, 
0.200543739821, 
0.181718547343, 
0.190774683406, 
0.194908615697, 
0.169668042967, 
0.174617375747, 
0.129271396573, 
0.131967795081, 
0.120309729013, 
0.0811358800923, 
0.0864044191423, 
0.062181734791, 
0.0556212107506, 
0.0309096312883, 
-0.00553813977856, 
0.0178374636403, 
-0.0108758202577, 
-0.0158378432513, 
-0.045999631167, 
-0.0564317778739, 
-0.0543030281235, 
-0.0671312913998, 
-0.0905732127642, 
-0.0908585972178, 
-0.109201469053, 
-0.109905147975, 
-0.13950044679, 
-0.131001685754, 
-0.127756978503, 
-0.132125279788, 
-0.11462788618, 
-0.133846744646, 
-0.117419600582, 
-0.116656230369, 
-0.109433988184, 
-0.102601311671, 
-0.107490531444, 
-0.0959644504451, 
-0.112995758906, 
-0.0992902248074, 
-0.0940469833859, 
-0.108740477363, 
-0.101121979011, 
-0.0985342453412, 
-0.0849483817738, 
-0.0822580623787, 
-0.0932301396831, 
-0.0825330963152, 
-0.100695064821, 
-0.0833624379475, 
-0.09217992648, 
-0.0829993359075, 
-0.0981506224385, 
-0.0818654007664, 
-0.0821236171417, 
-0.0852654723093, 
-0.0887658976992, 
-0.0954241901695, 
-0.0891302301865, 
-0.0969791851094, 
-0.0828894337043, 
-0.091714277572, 
-0.0760923602492, 
-0.0816007103288, 
-0.0728898788675, 
-0.0733277037709, 
-0.0634912931192, 
-0.0663226167544, 
-0.0531474225978, 
-0.0551670069249, 
-0.0463959119541, 
-0.0389966490521, 
-0.0384098307647, 
-0.0315462773703, 
-0.0253545064932, 
-0.0156201729193, 
-0.0179858909384, 
-0.00967523573546, 
-0.00697773322868, 
-0.0040126590591, 
-0.00166413212807, 
0.00478419131002, 
0.000934912617492, 
0.00242739850421, 
0.00784264014368, 
0.00195898703761, 
0.0041185640999, 
0.00652867884425, 
0.00291545267043, 
0.00141812862037, 
0.00236493554249, 
0.0117674787387, 
0.00594168952654, 
0.0117737170471, 
0.013152093249, 
0.00928037942478, 
0.00625429120997, 
0.0111557912478, 
0.00720039741631, 
0.00636810229071, 
0.0114631721328, 
0.0169047910664, 
0.00711026065221, 
0.0104618340768, 
0.013120577259, 
0.0108938502794, 
0.0091422738789, 
0.0127664294623, 
0.00776178189139, 
0.0172715925059, 
0.0251377254623, 
0.0169888631046, 
0.0218694093153, 
0.0202013884577}; // YOUR CODE HERE
float mean_vec[SNIPPET_SIZE] = {…}; // YOUR CODE HERE
float centroid1[2] = {-585.58448467, 172.53831484}; // YOUR CODE HERE
float centroid2[2] = {-560.3413878, -1525.47522609}; // YOUR CODE HERE
float centroid3[2] = {-278.41104128, -507.34101387}; // YOUR CODE HERE
float centroid4[2] = {-990.50038608, 2051.687557}; // YOUR CODE HERE
float result[SNIPPET_SIZE] = {0};
float proj1 = 0;
float proj2 = 0;
float dist[4] = {0};

/*----------------------*/
/* END OF CODE BLOCK A2 */
/*----------------------*/


//data array and index pointer
int i=0;
int re[SIZE]={0};
volatile int re_pointer = 0;

//timer period
float timer_ms = 0.35;

// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int*, float*);

// Compute the L2 norm of (dim1, dim2) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        centroid: size-2 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm(float dim1, float dim2, float* centroid){
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2));
}

// Compute the L2 norm of (dim1, dim2, dim3) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        dim3: 3rd dimension coordinate
//        centroid: size-3 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm3(float dim1, float dim2, float dim3, float* centroid){
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2), pow(dim3-centroid[2],2));
}


void setup()
{
  //microphone ADC
  pinMode(MIC_INPUT, INPUT);
  pinMode(P6_1, INPUT);
  pinMode(P6_5, INPUT);
  //recording light
  pinMode(RED_LED, OUTPUT);

  re_pointer = 0;
  reset_blinker();
  setTimer();
  
  Serial.begin(38400); 
}

void loop()
{  
  if(re_pointer == SIZE){
    digitalWrite(RED_LED, LOW);

    // Apply enveloping function and get snippet with speech. Do classification only if loud enough
    if(envelope(re, result)){

      /*--------------*/
      /* CODE BLOCK B */
      /*--------------*/

      // Perform principal component projection
      // YOUR CODE HERE 

      // Classification - Hint: use the function l2_norm defined below
      // YOUR CODE HERE 
      
      /*---------------------*/
      /* END OF CODE BLOCK B */
      /*---------------------*/

    }
    
    delay(2000);
    re_pointer = 0;
  }
}


// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int* data, float* data_out){
  int32_t avg = 0;
  float maximum = 0;
  int thres_index = 0;
  int32_t total = 0;
  int block;

  // Apply enveloping filter while finding maximum value
  for (block = 0; block < SIZE_AFTER_FILTER; block++){
    avg = 0;
    for (int i = 0; i < 16; i++) {
      avg += data[i+block*16];
    }
    avg = avg >> 4;
    data[block] = abs(data[block*16] - avg);
    for (int i = 1; i < 16; i++) {
      data[block] += abs(data[i+block*16] - avg);
    }
    if (data[block] > maximum) {
      maximum = data[block];
    }
  }
  
  // If not loud enough, return false
  if (maximum < LOUDNESS_THRESHOLD) return false;

  // Determine threshold
  float thres = THRESHOLD * maximum;

  // Figure out when interesting snippet starts and write to data_out
  block = PRELENGTH;
  while (data[block++] < thres);
  if (block > SIZE_AFTER_FILTER - SNIPPET_SIZE) 
    block = SIZE_AFTER_FILTER - SNIPPET_SIZE;
  for (int i = 0; i < SNIPPET_SIZE; i++){
    data_out[i] = data[block-PRELENGTH+i];
    total += data_out[i];
  }

  // Normalize data_out 
  for (int i = 0; i < SNIPPET_SIZE; i++)
    data_out[i] = data_out[i] / total;

  return true;
}



// Timer ISR for ADC sampling
#pragma vector=TIMER0_A0_VECTOR    // Timer A ISR
__interrupt void Timer1_A0_ISR( void )
{
  if(re_pointer < SIZE){
    digitalWrite(RED_LED, HIGH);
    re[re_pointer] = (analogRead(MIC_INPUT) >> 4) - 128;
    re_pointer += 1;
  }
}

// Set timer for ADC
void setTimer(){
  // set the timer based on 25MHz clock
  TA0CCR0 = (unsigned int)(25000*timer_ms);       
  // enable interrupts for Timer A
  TA0CCTL0 = CCIE;             
  __bis_SR_register(GIE);
  TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_0;
}

void reset_blinker(){
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
}

