UNIT PLANETY;

INTERFACE

Uses Math;

type
   TPlanets = class(TObject)
    public
      lambdam,betam,dm,alfam,deltam,phasem:double;
      lambdas,betas,ds,alfas,deltas:double;
      l1,b1,r1,lambda1,beta1,d1,phase1,alfa1,delta1:double;
      l2,b2,r2,lambda2,beta2,d2,phase2,alfa2,delta2:double;
      l4,b4,r4,lambda4,beta4,d4,phase4,alfa4,delta4:double;
      l5,b5,r5,lambda5,beta5,d5,       alfa5,delta5:double;
      l6,b6,r6,lambda6,beta6,d6,       alfa6,delta6:double;
      l7,b7,r7,lambda7,beta7,d7,       alfa7,delta7:double;
      l8,b8,r8,lambda8,beta8,d8,       alfa8,delta8:double;
      l9,b9,r9,lambda9,beta9,d9,       alfa9,delta9:double;
      Procedure SetJD(ajd:double);
      Procedure FazeMesice(var jd0,jd1,jd2,jd3:double);
      Procedure MesiceJupitera(var x1,z1,x2,z2,x3,z3,x4,z4:double);
    private
      jd:double;
      t,vt:double;
      m1,u1,VL1:double;    {MERKUR}
      m2,u2,VL2:double;    {VENUSE}
      m4,u4,VL4:double;    {MARS}
      m5,u5,VL5:double;    {JUPITER}
      m6,u6,VL6:double;    {SATURN}
      m7,u7,VL7:double;    {URAN}
      m8,u8,VL8:double;    {NEPTUN}
      m9,u9,VL9:double;    {PLUTO}
      ms,   ls:double;    {SLUNCE}
      mm,um,fm,om,lm:double; {MESIC}
      VT2000,eps:double;
      Procedure Init(jd:double);
      Procedure Done(lr,br:double; var ra,de:double);
      Procedure DoneGeoc(var la,be:double; var ra,de:double);
      Procedure DoneHelioc(var l,b,r:double; var lambda,beta,delta,ra,de:double);
      Procedure Mesic(var la,be,r,f:double);
      Procedure Slunce(var la,be,r:double);
      Procedure Merkur(var l,b,r:double);
      Procedure Venuse(var l,b,r:double);
      Procedure Mars(var l,b,r:double);
      Procedure Jupiter(var l,b,r:double);
      Procedure Saturn(var l,b,r:double);
      Procedure Uran(var l,b,r:double);
      Procedure Neptun(var l,b,r:double);
      Procedure Pluto(var l,b,r:double);
      Procedure FazePlanety(lambda,r,d:double; var f:double);
   end;

IMPLEMENTATION

Procedure JDToDMY(JD:double; var D,M,Y:double);
var Z,F,alfa,A,B,C,X,E:double;
begin
 Z:=int(JD+0.5);
 F:=frac(JD+0.5);
 alfa:=int((Z-1867216.25)/36524.25);
 A:=Z+1+alfa-INT(alfa/4);
 B:=A+1524;
 C:=int((B-122.1)/365.25);
 X:=int(365.25*C);
 E:=int((B-X)/30.6001);
 D:=B-X-int(30.6001*E)+F;
 if (E<=13) then M:=E-1 else M:=E-13;
 if (M>=3)  then Y:=C-4716 else Y:=C-4715;
end;

Procedure TPlanets.Init(jd:double);
begin
t:=jd-2451545;
vt:=1+(t/36525);
VT2000:=t/36525;
eps:=(23.4392911-0.0130042*VT2000-0.00000164*VT2000*VT2000+0.000000503*VT2000*VT2000*VT2000)/180*pi;
       {Mesic}
Lm:=(0.606434 + 0.03660110129*t)*2*pi;
mm:=(0.374897 + 0.03629164709*t)*2*pi;
um:=(0.259091 + 0.03674819520*t)*2*pi;
fm:=(0.827362 + 0.03386319198*t)*2*pi;
om:=(0.347343 - 0.00014709391*t)*2*pi;
       {SLUNCE}
Ls:=(0.779072 + 0.00273790931*t)*2*pi;
ms:=(0.993126 + 0.00273777850*t)*2*pi;
       {MERKUR}
VL1:=(0.700695 + 0.01136771400*t)*2*pi;
m1:=(0.485541 + 0.01136759566*t)*2*pi;
u1:=(0.566441 + 0.01136762384*t)*2*pi;
       {VENUSE}
VL2:=(0.505498 + 0.00445046867*t)*2*pi;
M2:=(0.140023 + 0.00445036173*t)*2*pi;
u2:=(0.292498 + 0.00445040017*t)*2*pi;
       {MARS}
VL4:=(0.987353 + 0.00145575328*t)*2*pi;
M4:=(0.053856 + 0.00145561327*t)*2*pi;
u4:=(0.849694 + 0.00145569465*t)*2*pi;
       {JUPITER}
VL5:=(0.089608 + 0.00023080893*t)*2*pi;
M5:=(0.056531 + 0.00023080893*t)*2*pi;
u5:=(0.814734 + 0.00023080893*t)*2*pi;
       {SATURN}
VL6:=(0.133295 + 0.00009294371*t)*2*pi;
M6:=(0.882987 + 0.00009294371*t)*2*pi;
u6:=(0.821218 + 0.00009294371*t)*2*pi;
       {URAN}
VL7:=(0.870169 + 0.00003269438*t)*2*pi;
M7:=(0.400589 + 0.00003269438*t)*2*pi;
u7:=(0.664614 + 0.00003265562*t)*2*pi;
       {NEPTUN}
VL8:=(0.846912 + 0.00001672092*t)*2*pi;
M8:=(0.725368 + 0.00001672092*t)*2*pi;
u8:=(0.480856 + 0.00001663715*t)*2*pi;
       {PLUTO}
VL9:=(0.663854 + 0.00001115482*t)*2*pi;
M9:=(0.041020 + 0.00001104864*t)*2*pi;
u9:=(0.357355 + 0.00001104864*t)*2*pi;
end;

Procedure TPlanets. Done(lr,br:double; var ra,de:double);
begin
 de:=arcsin(sin(br)*cos(eps)+cos(br)*sin(eps)*sin(lr));
 if abs(lr-pi/2)<0.000001 then begin ra:=pi/2; de:=eps; end
 else if abs(lr-3*pi/2)<0.000001 then begin ra:=3*pi/2; de:=-eps; end
 else ra:=arctan2(sin(br)*sin(-eps)+cos(eps)*cos(br)*sin(lr),cos(br)*cos(lr));
 if ra<2*pi then ra:=2*pi+ra; if ra>2*pi then ra:=ra-2*pi;
end;

Procedure TPlanets. DoneGeoc(var la,be:double; var ra,de:double);
begin
 la:=la/3600/180*pi; while (la<0) do la:=la+2*pi; while (la>=2*pi) do la:=la-2*pi;
 be:=be/3600/180*pi;
 Done(la,be,ra,de);
end;

Procedure TPlanets. DoneHelioc(var l,b,r:double; var lambda,beta,delta,ra,de:double);
begin
 l:=l/3600; while (l<0) do l:=l+360; while (l>=360) do l:=l-360;
 l:=l/180*pi;
 b:=b/3600/180*pi;
 delta:=sqrt(ds*ds+r*r+2*r*ds*cos(b)*cos(l-lambdas));
 lambda:=arctan2(r*cos(b)*sin(l-ls),r*cos(b)*cos(l-lambdas)+ds)+lambdas;
 beta:=arcsin(r/delta*sin(b));
 Done(lambda,beta,ra,de);
end;

Procedure TPlanets. Mesic(var la,be,r,f:double);
begin
la:=Lm*3600*180/pi+22640*sin(mm)
     -4586*sin(mm-2*fm)
     +2370*sin(2*fm)
     + 769*sin(2*mm)
     - 668*sin(ms)
     - 412*sin(2*um)
     - 212*sin(2*mm-2*fm)
     - 206*sin(mm-2*fm+ms)
     + 192*sin(mm+2*fm)
     + 165*sin(2*fm-ms)
     + 148*sin(mm-ms)
     - 125*sin(fm)
     - 110*sin(mm+ms)
     -  55*sin(2*um-2*fm)
     -  45*sin(mm+2*um)
     +  40*sin(mm-2*um)
     -  38*sin(mm-4*fm)
     +  36*sin(3*mm)
     -  31*sin(2*mm-4*fm)
     +  28*sin(mm-2*fm-ms)
     -  24*sin(2*fm+ms)
     +  19*sin(mm-fm)
     +  18*sin(fm+ms)
     +  15*sin(mm+2*fm-ms)
     +  14*sin(2*mm+2*fm)
     +  14*sin(4*fm)
     -  13*sin(3*mm-2*fm)
     -  11*sin(mm-16*ls-18*VL2)
     +  10*sin(2*mm-ms)
     +   9*sin(mm-2*um-2*fm)
     +   9*cos(mm+16*ls-18*VL2)
     -   9*sin(2*mm-2*fm+ms)
     -   8*sin(mm-fm)
     +   8*sin(2*fm-2*ms)
     -   8*sin(2*ms+ms)
     -   7*sin(2*ms)
     -   7*sin(mm-2*fm+2*ms)
     +   7*sin(om)
     -   6*sin(mm-2*um+2*fm)
     -   6*sin(2*um+2*fm)
     -   4*sin(mm-4*fm+ms)
    +    4*vt*cos(mm+16*ls-18*VL2)
    -    4*sin(2*mm-2*um)
    +    4*vt*sin(mm+16*ls-18*VL2)
    +    3*sin(mm-3*fm)
    -    3*sin(mm+2*fm+ms)
    -    3*sin(2*mm-4*fm+ms)
    -    3*sin(mm-2*ms)
    +    3*sin(mm-2*fm-2*ms)
    -    2*sin(2*mm-2*fm-ms)
    -    2*sin(2*um-2*fm+ms)
    +    2*sin(mm+4*fm)
    +    2*sin(4*mm)
    +    2*sin(4*fm-ms)
    +    2*sin(2*mm-fm);
be:=  18461*sin(um)
    + 1010*sin(mm+um)
    + 1000*sin(mm-um)
    -  624*sin(um-2*fm)
    -  199*sin(mm-um-2*fm)
    -  167*sin(mm+um-2*fm)
    +  117*sin(um-2*fm)
    +   62*sin(2*mm+um)
    +   33*sin(mm-um+2*fm)
    +   32*sin(2*mm-um)
    +   30*sin(um-2*fm+ms)
    -   16*sin(2*mm+um-2*fm)
    +   15*sin(mm+um+2*fm)
    +   12*sin(um-2*fm-ms)
    -    9*sin(mm-um-2*fm+ms)
    -    8*sin(um-om)
    +    8*sin(um+2*fm-ms)
    -    7*sin(mm+um-2*fm+ms)
    +    7*sin(mm+um-ms)
    -    7*sin(mm+um-4*fm)
    -    6*sin(um+ms)
    -    6*sin(3*um)
    +    6*sin(mm-um-ms)
    -    5*sin(um-fm)
    -    5*sin(mm+um+ms)
    -    5*sin(mm-um+ms)
    +    5*sin(um-ms)
    +    5*sin(um-fm)
    +    4*sin(3*mm+um)
    -    4*sin(um-4*fm)
    -    3*sin(mm-um-4*fm)
    +    3*sin(mm-3*um)
    -    2*sin(2*mm-um-4*fm)
    -    2*sin(3*um-2*fm)
    +    2*sin(2*mm-um+2*fm)
    +    2*sin(mm-um+2*fm-ms)
    +    2*sin(2*mm-um-2*fm)
    +    2*sin(3*mm-um);
r:= 60.36298
    -    3.27746*cos(mm)
    -    0.57994*cos(mm-2*fm)
    -    0.46357*cos(2*fm)
    -    0.08904*cos(2*mm)
    +    0.03865*cos(2*mm-2*fm)
    -    0.03237*cos(2*fm-ms)
    -    0.02688*cos(mm+2*fm)
    -    0.02358*cos(mm-2*fm+ms)
    -    0.02030*cos(mm-ms)
    +    0.01719*cos(fm)
    +    0.01671*cos(mm+ms)
    +    0.01247*cos(mm-2*um)
    +    0.00704*cos(ms)
    +    0.00529*cos(2*fm+ms)
    -    0.00524*cos(mm-4*fm)
    +    0.00398*cos(mm-2*fm-ms)
    -    0.00366*cos(3*mm)
    -    0.00295*cos(2*mm-4*fm)
    -    0.00263*cos(fm+ms)
    +    0.00249*cos(3*mm-2*fm)
    -    0.00221*cos(mm+2*fm-ms)
    +    0.00185*cos(2*um-2*fm)
    -    0.00161*cos(2*fm-2*ms)
    +    0.00147*cos(mm+2*um-2*fm)
    -    0.00142*cos(4*fm)
    +    0.00139*cos(2*mm-2*fm+ms)
    -    0.00118*cos(2*mm-4*fm+ms)
    -    0.00116*cos(2*mm-2*fm)
    -    0.00110*cos(2*mm-ms);
r:=r/23454.8; { v AU }
f:=frac((JD-1721088.5)/29.53059)*360+90; if (f>=360) then f:=f-360;
end;

Procedure TPlanets.FazeMesice;

 Function Faze(jd0,jd,a0,a1,a2,a3:double):double;
 var k,T1,jdf,MS0,MM0,UM0:double; Den,Mesic,Rok:double;
 begin
  JDToDMY(jd-28,Den,Mesic,Rok);
  k:=int(12.3685*(Rok+Mesic/12-1900));
  k:=k+a1*0.25+a2*0.5+a3*0.75;
  T1:=k/1236.85;
  jdf:=2415020.75933+29.53058868*k+0.0001178*T1*T1-0.000000155*T1*T1*T1+0.00033*sin(2.90702+2.319019*T1-0.000160099*T1*T1);
  MS0:=(359.2242+ 29.10535608*k-0.0000333*T1*T1-0.00000347*T1*T1*T1)/180*pi;
  MM0:=(306.0253+385.81691806*k+0.0107306*T1*T1+0.00001236*T1*T1*T1)/180*pi;
  UM0:=(21.2964+390.67050646*k-0.0016528*T1*T1-0.00000239*T1*T1*T1)/180*pi;
  Result:=jdf+
         (a0+a2)*(
           (0.1734-0.000393*T1)*sin(MS0)
          -0.4068*sin(MM0)
          +0.0161*sin(2*MM0)
          +0.0104*sin(2*um0)
          -0.0074*sin(ms0-mm0)
          -0.0051*sin(ms0+mm0)
          +0.0021*sin(2*ms0)
          +0.0010*sin(2*um0-mm0)
          -0.0006*sin(2*um0+mm0)
          +0.0005*sin(ms0+2*mm0)
          -0.0004*sin(3*mm0)
          +0.0004*sin(2*um0+ms0)
          -0.0004*sin(2*um0-ms0))
        +(a1+a3)*(
           (0.1721-0.0004*T1)*sin(MS0)
          -0.6280*sin(MM0)
          -0.0119*sin(ms0+mm0)
          +0.0089*sin(2*mm0)
          +0.0079*sin(2*um0)
          -0.0047*sin(ms0-mm0)
          +0.0021*sin(2*um0-mm0)
          +0.0021*sin(2*ms0)
          -0.0006*sin(2*um0+mm0)
          -0.0004*sin(3*mm0)
          -0.0004*sin(2*um0-ms0)
          +0.0004*sin(ms0-2*mm0)
          +0.0003*sin(2*um0+ms0)
          +0.0003*sin(ms0+2*mm0)
          -0.0003*sin(2*ms0+mm0))
       +(a1-a3)*(
           0.0028
          -0.0004*cos(ms0)
          +0.0003*cos(mm0));
   { Pocitej neblizsi nasledujici }
   if (Result<jd0) then Result:=Faze(jd0,jd+28,a0,a1,a2,a3);
 end;

begin
jd0:=Faze(jd,jd,1.0,0.0,0.0,0.0);
jd1:=Faze(jd,jd,0.0,1.0,0.0,0.0);
jd2:=Faze(jd,jd,0.0,0.0,1.0,0.0);
jd3:=Faze(jd,jd,0.0,0.0,0.0,1.0);
end;


Procedure TPlanets. Slunce(var la,be,r:double);
begin
la:=Ls*3600*180/pi+6910*sin(ms)
      +  72*sin(2*ms)
      -17*vt*sin(ms)
      -   7*cos(ms-m5)
      +   6*sin(lm-ls)
      +   5*sin(4*ms+8*m4+3*m5)
      -   5*cos(2*ms-2*m2)
      -   4*sin(ms-m2)
      +   4*cos(4*ms-8*m4+3*m5)
      +   3*sin(2*ms-2*m2)
      -   3*sin(m5)
      -   3*sin(2*ms-2*m5);
be:=0;
r:=1.00014-0.01675*cos(ms)-0.00014*cos(2*ms);
end;

Procedure TPlanets. Merkur(var l,b,r:double);
begin
l:=VL1*3600*180/pi+84378*sin(m1)
      +10733*sin(2*m1)
      + 1892*sin(3*m1)
      -  646*sin(2*u1)
      +  381*sin(4*m1)
      -  306*sin(m1-2*u1)
      -  274*sin(m1+2*u1)
      -   92*sin(2*m1+2*u1)
      +   83*sin(5*m1)
      -   28*sin(3*m1+2*u1)
      +   25*sin(2*m1-2*u1)
      +   19*sin(6*m1)
      -    9*sin(4*m1+2*u1)
      + 8*vt*sin(m1)
      +    7*cos(m1-5*m2);
b:=   24134*sin(u1)
      + 5180*sin(m1-u1)
      + 4910*sin(m1+u1)
      + 1124*sin(2*m1+u1)
      +  271*sin(3*m1+u1)
      +  132*sin(2*m1-u1)
      +   67*sin(4*m1+u1)
      +   18*sin(5*m1+u1)
      -   10*sin(3*u1)
      +    9*sin(m1-3*u1);
r:=0.39528
      -0.07834*cos(m1)
      -0.00795*cos(2*m1)
      -0.00121*cos(3*m1)
      -0.00022*cos(4*m1);
end;
Procedure TPlanets. Venuse(var l,b,r:double);
begin
l:=VL2*3600*180/pi+2814*sin(m2)
      - 181*sin(2*u2)
      -20*vt*sin(m2)
      +  12*sin(2*m2)
      -  10*cos(2*ms-2*m2)
      +   7*cos(3*ms-3*m2);
b:=12215*sin(u2)
     +83*sin(m2+u2)
     +83*sin(m2-u2);
r:=0.72335-0.00493*cos(m2);
end;

Procedure TPlanets. Mars(var l,b,r:double);
begin
l:=VL4*3600*180/pi
    +38451*sin(m4)
    + 2238*sin(2*m4)
    +  181*sin(3*m4)
    -   52*sin(2*u4)
    +37*vt*sin(m4)
    -   22*cos(m4-2*m5)
    -   19*sin(m4-m5)
    +   17*cos(m4-m5)
    +   17*sin(4*m4)
    -   16*cos(2*m4-2*m5)
    +   13*cos(ms-2*m4)
    -   10*sin(m4-2*u2)
    -   10*sin(m4+2*u4)
    +    7*cos(ms-m4)
    -    7*cos(2*ms-3*m4)
    -    5*sin(m2-3*m4)
    -    5*sin(ms-m4)
    -    5*sin(ms-2*m4)
    -    4*cos(2*ms-4*m4)
    + 4*vt*sin(2*m4)
    +    4*cos(m5)
    +    3*cos(m2-3*m4)
    +    3*cos(2*m4-2*m5);
b:=6603*sin(u4)
   +622*sin(m4-u4)
   +615*sin(m4+u4)
   + 64*sin(2*m4+u4);
r:=1.53031-0.14170*cos(m4)
          -0.00660*cos(2*m4)
          -0.00047*cos(3*m4);
end;

Procedure TPlanets. Jupiter(var l,b,r:double);
begin
Init(jd);
l:=VL5*3600*180/pi
     +19934*sin(m5)
     +5023*vt
     +2511
     + 1093*cos(2*m5-5*m6)
     +  601*sin(2*m5)
     -  479*sin(2*m5-5*m6)
     -  185*sin(2*m5-2*m6)
     +  137*sin(3*m5-5*m6)
     -  131*sin(m5-2*m6)
     +   79*cos(m5-m6)
     -   76*cos(2*m5-2*m6)
     -74*vt*cos(m5)
     +68*vt*sin(m5)
     +   66*cos(2*m5-3*m6)
     +   63*cos(3*m5-5*m6)
     +   53*cos(m5-5*m6)
     +   49*sin(2*m5-3*m6)
     -43*vt*sin(2*m5-5*m6)
     -   37*cos(m5)
     +   25*sin(2*VL5)
     +   25*sin(3*m5)
     -   23*sin(m5-5*m6)
     -19*vt*sin(2*m5-5*m6)
     +   17*cos(2*m5-4*m6)
     +   17*cos(3*m5-3*m6)
     -   14*sin(m5-m6)
     -   13*sin(3*m5-4*m6)
     -    9*cos(VL5)
     +    9*cos(m6)
     -    9*sin(m6)
     -    9*sin(3*m5-2*m6)
     +    9*sin(4*m5-5*m6)
     +    9*sin(2*m5-6*m6+3*m7)
     -    8*cos(4*m5-10*m6)
     +    7*cos(3*m5-4*m6)
     -    7*cos(m5-3*m6)
     -    7*sin(4*m5-10*m6)
     -    7*sin(m5-3*m6)
     +    6*cos(4*m5-5*m6)
     -    6*sin(3*m5-3*m6)
     +    5*cos(2*m6)
     -    4*sin(4*m5-4*m6)
     -    4*cos(3*m6)
     +    4*cos(2*m5-m6)
     -    4*cos(3*m5-2*m6)
     - 4*vt*cos(2*m5)
     + 3*vt*sin(2*m5)
     +    3*cos(5*m6)
     +    3*cos(5*m5-10*m6)
     +    3*sin(2*m6)
     -    2*sin(2*VL5-m5)
     +    2*sin(2*VL5+m5)
     - 2*vt*sin(3*m5-5*m6)
     - 2*vt*sin(m5-5*m6);
b:=-4692*cos(m5)
    + 259*sin(m5)
    + 227
    - 227*cos(2*m5)
    +30*vt*sin(m5)
    +21*vt*cos(m5)
    +  16*sin(3*m5-5*m6)
    -  13*sin(m5-5*m6)
    -  12*cos(3*m5)
    +  12*sin(2*m5)
    +   7*cos(3*m5-5*m6)
    -   5*cos(m5-5*m6);
r:=5.20883
    -0.25122*cos(m5)
    -0.00604*cos(2*m5)
    +0.00260*cos(2*m5-2*m6)
    -0.00170*cos(3*m5-5*m6)
    -0.00091*vt*sin(m5)
    -0.00084*vt*cos(m5)
    +0.00069*sin(2*m5-3*m6)
    -0.00067*sin(m5-5*m6)
    +0.00066*sin(3*m5-5*m6)
    +0.00063*sin(m5-m6)
    -0.00051*cos(2*m5-3*m6)
    -0.00046*sin(m5)
    -0.00029*cos(m5-5*m6)
    +0.00027*cos(m5-2*m6)
    -0.00022*cos(3*m5)
    -0.00021*sin(2*m5-5*m6);
end;

Procedure TPlanets. Saturn(var l,b,r:double);
begin
l:=VL6*3600*180/pi
    +23045*sin(m6)
    + 5014*vt
    - 2689*cos(2*m5-5*m6)
    + 2507
    + 1177*sin(2*m5-5*m6)
    -  826*cos(2*m5-4*m6)
    +  802*sin(2*m6)
    +  425*sin(m5-2*m6)
    -229*vt*cos(m6)
    -  153*cos(2*m5-6*m6)
    -142*vt*sin(m6)
    -  114*cos(m6)
    +101*vt*sin(2*m5-5*m6)
    -   70*cos(2*VL6)
    +   67*sin(2*VL6)
    +   66*sin(2*m5-6*m6)
    +60*vt*cos(2*m5-5*m6)
    +   41*sin(m5-3*m6)
    +   39*sin(3*m6)
    +   31*sin(m5-m6)
    +   31*sin(2*m5-2*m6)
    -   29*cos(2*m5-3*m6)
    -   28*sin(2*m5-6*m6+3*m7)
    +   28*cos(m5-3*m6)
    +22*vt*sin(2*m5-4*m6)
    -   22*sin(m6-3*m7)
    +   20*sin(2*m5-3*m6)
    +   20*cos(4*m5-10*m6)
    +   19*cos(2*m6-3*m7)
    +   19*sin(4*m5-10*m6)
    -17*vt*cos(2*m6)
    -   16*cos(m6-3*m7)
    -   12*sin(2*m5-4*m6)
    +   12*cos(m5)
    -   12*sin(2*m6-2*m7)
    -11*vt*sin(2*m6)
    -   11*cos(2*m5-7*m6)
    +   10*sin(2*m6-3*m7)
    +   10*cos(2*m5+2*m6)
    +    9*sin(4*m5-9*m6)
    -    8*sin(m6-2*m7)
    -    8*cos(VL6+m6)
    +    8*cos(VL6-m6)
    +    8*sin(m6-m7)
    -    8*sin(2*VL6-m6)
    +    7*sin(2*VL6+m6)
    -    7*cos(m5-2*m6)
    -    7*cos(2*m6)
    - 6*vt*sin(4*m5-10*m6)
    + 6*vt*cos(4*m5-10*m6)
    + 6*vt*sin(2*m5-6*m6)
    -    5*sin(3*m5-7*m6)
    -    5*cos(3*m5-3*m6)
    -    5*cos(2*m6-2*m7)
    +    5*sin(3*m5-4*m6)
    +    5*sin(2*m5-7*m6)
    +    4*sin(3*m5-5*m6)
    + 4*vt*cos(m5-2*m6)
    + 3*vt*cos(3*m5-4*m6)
    +    3*cos(2*m5-6*m6+3*m7)
    - 3*vt*sin(2*VL6)
    + 3*vt*cos(2*m5-6*m6)
    - 3*vt*cos(2*VL6)
    +    3*cos(3*m5-7*m6)
    +    3*cos(4*m5-9*m6)
    +    3*sin(3*m5-6*m6)
    +    3*sin(2*m5-m6)
    +    3*sin(m5-4*m6)
    +    2*cos(3*m6-3*m7)
    + 2*vt*sin(m5-2*m6)
    +    2*sin(4*m6)
    -    2*cos(3*m5-4*m6)
    -    2*cos(2*m5-m6)
    -    2*sin(2*m5-7*m6+3*m7)
    +    2*cos(m5-4*m6)
    +    2*cos(4*m5-11*m6)
    -    2*sin(m6-m7);
b:=8297*sin(m6)
  -3346*cos(m6)
  + 462*sin(2*m6)
  - 189*cos(2*m6)
  + 185
  -79*vt*cos(m6)
  -  71*cos(2*m5-4*m6)
  +  46*sin(2*m5-4*m6)
  -  45*cos(2*m5-6*m6)
  +  29*sin(3*m6)
  -  20*cos(2*m5-3*m6)
  +18*vt*sin(m6)
  -  14*cos(2*m5-5*m6)
  -  11*cos(3*m6)
  -10*vt
  +   9*sin(m5-3*m6)
  +   8*sin(m5-m6)
  -   6*sin(2*m5-3*m6)
  +   5*sin(2*m5-7*m6)
  -   5*cos(2*m5-7*m6)
  +   4*sin(2*m5-5*m6)
  -4*vt*sin(2*m6)
  -   3*cos(m5-m6)
  +   3*cos(m5-3*m6)
  +3*vt*sin(2*m5-4*m6)
  +   3*sin(m5-2*m6)
  +   2*sin(4*m6)
  -   2*cos(2*m5-2*m6);
r:=9.55774
  -0.53252*cos(m6)
  -0.01878*sin(2*m5-4*m6)
  -0.01482*cos(2*m6)
  +0.00817*sin(m5-m6)
  -0.00539*cos(m5-2*m6)
  -0.00524*vt*sin(m6)
  +0.00349*sin(2*m5-5*m6)
  +0.00328*vt*cos(m6)
  -0.00225*sin(m6)
  +0.00149*cos(2*m5-6*m6)
  -0.00126*cos(2*m5-2*m6)
  +0.00104*cos(m5-m6)
  +0.00101*cos(2*m5-5*m6)
  +0.00098*cos(m5-3*m6)
  -0.00073*cos(2*m5-3*m6)
  -0.00062*cos(3*m6)
  +0.00042*sin(2*m6-3*m7)
  +0.00041*sin(2*m5-2*m6)
  -0.00040*sin(m5-3*m6)
  +0.00040*cos(2*m5-4*m6)
  -0.00028*vt
  -0.00023*sin(m5)
  +0.00020*sin(2*m5-7*m6);
end;

Procedure TPlanets. Uran(var l,b,r:double);
begin
l:=VL7*3600*180/pi
  +19397*sin(m7)
  +  570*sin(2*m7)
  -536*vt*cos(m7)
  +  143*sin(m6-2*m7)
  +110*vt*sin(m7)
  +  102*sin(m6-3*m7)
  +   76*cos(m6-3*m7)
  -   49*sin(m5-m7)
  +32*vt*vt
  -30*vt*cos(2*m7)
  +   29*sin(2*m5-6*m6+3*m7)
  +   29*cos(2*m7-2*m8)
  -   28*cos(m7-m8)
  +   23*sin(3*m7)
  -   21*cos(m5-m7)
  +   20*sin(m7-m8)
  +   20*cos(m6-2*m7)
  -   19*cos(m6-m7)
  +   17*sin(2*m7-3*m8)
  +   14*sin(3*m7-3*m8)
  +   13*sin(m6-m7)
  -12*vt*vt*cos(m7)
  -   12*cos(m7)
  +   10*sin(2*m7-2*m8)
  -    9*sin(2*u7)
  -9*vt*vt*sin(m7)
  +    9*cos(2*m7-3*m8)
  +8*vt*cos(m6-2*m7)
  +7*vt*cos(m6-3*m7)
  -7*vt*sin(m6-3*m7)
  +7*vt*sin(2*m7)
  +    6*sin(2*m5-6*m6+2*m7)
  +    6*cos(2*m5-6*m6+2*m7)
  +    5*sin(m6-4*m7)
  -    4*sin(3*m7-4*m8)
  +    4*cos(3*m7-3*m8)
  -    3*cos(m8)
  -    2*sin(m8);
b:=2775*sin(u7)
   +131*sin(m7-u7)
   +130*sin(m7+u7);
r:=19.21216
   -0.90154*cos(m7)
   -0.02488*vt*sin(m7)
   -0.00585*cos(m6-2*m7)
   -0.00508*vt*cos(m7)
   -0.00451*cos(m5-m7)
   +0.00336*sin(m6-m7)
   +0.00198*sin(m5-m7)
   +0.00118*cos(m6-3*m7)
   +0.00107*sin(m6-2*m7)
   -0.00103*vt*sin(2*m7)
   -0.00081*cos(3*m7-3*m8);
end;

Procedure TPlanets. Neptun(var l,b,r:double);
begin
l:=VL8*3600*180/pi
   +3523*sin(m8)
   -  50*sin(2*u8)
   -43*vt*cos(m8)
   +  29*sin(m5-m8)
   +  19*sin(2*m8)
   +  19*sin(2*m8)
   -  18*cos(m5-m8)
   +  13*cos(m6-m8)
   +  13*sin(m6+m8)
   -   9*sin(2*m7-3*m8)
   +   9*cos(2*m7-2*m8)
   -   5*cos(2*m7-3*m8)
   -4*vt*sin(m8)
   +   4*cos(m7-2*m8)
   +4*vt*vt*sin(m8);
b:=6404*sin(u8)
   + 55*sin(m8+u8)
   + 55*sin(m8-u8)
   -33*vt*sin(u8);
r:=30.07175
   -0.25701*cos(m8)
   -0.00787*cos(2*VL7-M7-2*VL8)
   +0.00409*cos(m5-m8)
   -0.00314*vt*sin(m8)
   +0.00250*sin(m5-m8)
   -0.00194*sin(m6-m8)
   +0.00185*cos(m6-m8);
end;

Procedure TPlanets. Pluto(var l,b,r:double);
begin
l:=VL9*3600*180/pi
   +101577*sin(m9)
   + 15517*sin(2*m9)
   -  3593*sin(2*u9)
   +  3414*sin(3*m9)
   -  2201*sin(m9-2*u9)
   -  1871*sin(m9-2*u9)
   +   839*sin(4*m9)
   -   757*sin(2*m9+2*u9)
   -   285*sin(3*m9+2*u9)
   +227*vt*vt*sin(m9)
   +   218*sin(2*m9-2*u9)
   +200*vt*sin(m9);
b:=57726*sin(u9)
  +15257*sin(m9-u9)
  +14102*sin(m9+u9)
  +3870*sin(2*m9+u9)
  +1138*sin(3*m9+u9)
  +472*sin(2*m9-u9)
  +353*sin(4*m9+u9)
  -144*sin(m9-3*u9)
  -119*sin(3*u9)
  -111*sin(m9+3*u9);
r:=40.74638
   -9.58235*cos(m9)
   -1.16703*cos(2*m9)
   -0.22649*cos(3*m9)
   -0.04996*cos(4*m9);
end;

Procedure TPlanets. FazePlanety(lambda,r,d:double; var f:double);
var fi:double;
begin
 fi:=arccos((r*r+d*d-ds*ds)/2/r/d);
 if sin(lambdas-lambda)<=0 then f:=pi-fi
 else f:=pi+fi;
 f:=f*180/pi;
end;

Procedure TPlanets. SetJD;
begin
 jd:=ajd;
 Init(jd);
 Slunce(lambdas,deltas,ds); DoneGeoc(lambdas,deltas,alfas,deltas);
 Mesic(lambdam,betam,dm,phasem); DoneGeoc(lambdam,betam,alfam,deltam);
 Merkur(l1,b1,r1); DoneHelioc(l1,b1,r1,lambda1,beta1,d1,alfa1,delta1); FazePlanety(lambda1,r1,d1,phase1);
 Venuse(l2,b2,r2); DoneHelioc(l2,b2,r2,lambda2,beta2,d2,alfa2,delta2); FazePlanety(lambda2,r2,d2,phase2);
 Mars(l4,b4,r4); DoneHelioc(l4,b4,r4,lambda4,beta4,d4,alfa4,delta4); FazePlanety(lambda4,r4,d4,phase4);
 Jupiter(l5,b5,r5); DoneHelioc(l5,b5,r5,lambda5,beta5,d5,alfa5,delta5);
 Saturn(l6,b6,r6); DoneHelioc(l6,b6,r6,lambda6,beta6,d6,alfa6,delta6);
 Uran(l7,b7,r7); DoneHelioc(l7,b7,r7,lambda7,beta7,d7,alfa7,delta7);
 Neptun(l8,b8,r8); DoneHelioc(l8,b8,r8,lambda8,beta8,d8,alfa8,delta8);
 Pluto(l9,b9,r9); DoneHelioc(l9,b9,r9,lambda9,beta9,d9,alfa9,delta9);
end;

Procedure TPlanets.MesiceJupitera;
var d,Mz,Mj,Lzj,A,B,K,Dl,Fi,g1,g2,g3,g4:double;
begin
d:=jd-2415020;
Mz:=358.476+0.9856003*d; Mz:=frac(Mz/360)*360;
Mj:=225.328+0.0830853*d; Mj:=frac(Mj/360)*360;
Lzj:=221.647+0.9025179*d; Lzj:=frac(Lzj/360)*360;
A:=1.92*sin(Mz*pi/180)+0.02*sin(Mz*pi/90);
B:=5.537*sin(Mj*pi/180)+0.167*sin(Mj*pi/90);
K:=(Lzj+A-B)*pi/180;
Dl:=sqrt(28.07-10.406*cos(K));
fi:=arcsin(sin(K)/Dl);
g1:= 84.5506+203.4058630*(d-Dl/173)+fi-B; g1:=frac(g1/360)*360; if g1<0 then g1:=g1+360;
g2:= 41.5015+101.2916323*(d-Dl/173)+fi-B; g2:=frac(g2/360)*360; if g2<0 then g2:=g2+360;
g3:=109.9770+ 50.2345169*(d-Dl/173)+fi-B; g3:=frac(g3/360)*360; if g3<0 then g3:=g3+360;
g4:=176.3586+ 21.4879802*(d-Dl/173)+fi-B; g4:=frac(g4/360)*360; if g4<0 then g4:=g4+360;
x1:=5.906*sin(g1*pi/180);
x2:=9.397*sin(g2*pi/180);
x3:=14.989*sin(g3*pi/180);
x4:=26.364*sin(g4*pi/180);
z1:=cos(g1*pi/180);
z2:=cos(g2*pi/180);
z3:=cos(g3*pi/180);
z4:=cos(g4*pi/180);
end;

end.

