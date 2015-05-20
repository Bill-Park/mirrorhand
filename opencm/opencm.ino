// where, open, grab
int tem = 3 ;  // 2000, 1000
int ind = 6 ;  // 2250, 1700
int mid = 4 ;  // 1980, 1100
int rin = 5 ;  // 2250, 1230
int lit = 2 ;  // 1800, 1150 

int tem_ba = 100 ;
int ind_ba = 160 ;
int mid_ba = 150 ;
int rin_ba = 130 ;
int lit_ba = 150 ; 


int N_ch = 8 ;
int te, in, mi, ri, li ;
int len = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(2400) ;
  SerialUSB.begin() ;
  for (int i = 2; i < 7; i++) pinMode(i, INPUT_ANALOG) ;

  Serial3.print('[') ;
  Serial3.print(27) ;
  Serial3.print('a') ;
  Serial3.print(tem_ba) ;
  Serial3.print('b') ;

  Serial3.print('c') ;
  Serial3.print(ind_ba) ;
  Serial3.print('d') ;

  Serial3.print('e') ;
  Serial3.print(mid_ba) ;
  Serial3.print('f') ;

  Serial3.print('g') ;
  Serial3.print(rin_ba) ;
  Serial3.print('h') ;

  Serial3.print('i') ;
  Serial3.print(lit_ba) ;
  Serial3.print('j') ;

  Serial3.print(']') ;
}

void loop() {
  // put your main code here, to run repeatedly: 
  len = 12 ;
  if((te = get_adc(tem)) == -1) te = 0 ;
  if((in = get_adc(ind)) == -1) in = 0 ;
  if((mi = get_adc(mid)) == -1) mi = 0 ;
  if((ri = get_adc(rin)) == -1) ri = 0 ;
  if((li = get_adc(lit)) == -1) li = 0 ;

  te = map(te, 1900, 1000, 100, 0) ;
  in = map(in, 2250, 1750, 160, 60) ;
  mi = map(mi, 1900, 850, 150, 40) ;
  ri = map(ri, 2100, 1050, 130, 30) ;
  li = map(li, 1900, 1100, 150, 40) ;

  te -= te % 10 ;
  in -= in % 10 ;
  mi -= mi % 10 ;
  ri -= ri % 10 ;
  li -= li % 10 ;

  if( (te / 100) >= 1) len += 3 ;
  else if ((te / 10) >= 1) len += 2 ;
  else len += 1 ;
  if( (in / 100) >= 1) len += 3 ;
  else if ((in / 10) >= 1) len += 2 ;
  else len += 1 ;
  if( (mi / 100) >= 1) len += 3 ;
  else if ((mi / 10) >= 1) len += 2 ;
  else len += 1 ;
  if( (ri / 100) >= 1) len += 3 ;
  else if ((ri / 10) >= 1) len += 2 ;
  else len += 1 ;
  if( (li / 100) >= 1) len += 3 ;
  else if ((li / 10) >= 1) len += 2 ;
  else len += 1 ;



  Serial3.print('[') ;

  Serial3.print(len) ;

  if (te > 100 || te < 0) { 
    goto ed ;
  }
  else {
    Serial3.print('a') ;
    Serial3.print(te) ;
    Serial3.print('b') ;
  }

  if (in > 160 || in < 60) {
    goto ed ;
  }
  else {
    Serial3.print('c') ;
    Serial3.print(in) ;
    Serial3.print('d') ;
  }

  if (mi > 150 || mi < 40) {
    goto ed ;
  }
  else {
    Serial3.print('e') ;
    Serial3.print(mi) ;
    Serial3.print('f') ;
  }

  if (ri > 140 || ri < 30) {
    goto ed ;
  }
  else {
    Serial3.print('g') ;
    Serial3.print(ri) ;
    Serial3.print('h') ;
  }

  if (li > 150 || li < 40) {
    goto ed ;
  }
  else {
    Serial3.print('i') ;
    Serial3.print(li) ;
    Serial3.print('j') ;
  }

  Serial3.print(']') ;
ed :
  delay(300) ;
}


int get_adc(unsigned char channel)
{
  short addata[N_ch][10];
  int tempo[10];
  int data_size,bdata_size,j;
  int i,count;	

  while(1)
  {
    data_size = 0;
    count = 0;
    for(i=0;i<10;i++)
    {
      tempo[i] = 0;
      addata[channel][i] = analogRead(channel) ;
      data_size += addata[channel][i];
    }
    bdata_size = data_size/10;
    j = data_size/100*10;
    for(i=0;i<10;i++)
    {
      bdata_size -= addata[channel][i];
      if((bdata_size >  j) || (bdata_size < -j))
      {
        bdata_size = data_size/10;	
      }
      else 
      {
        tempo[i] = addata[channel][i];
        count++;
        bdata_size = data_size/10;
      }
    }
    data_size = 0;
    for(i=0;i<10;i++) data_size += tempo[i];
    if(count > 7) return data_size/count;    
    else return -1 ;
  }
}






