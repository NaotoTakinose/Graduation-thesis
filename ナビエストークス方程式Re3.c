#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
//#include <omp.h>
static int xmax=240;
static int ymax=44;
static double ulowx=2.5;
static double out=2.5;
static double ulowy;
static double uupx;
static double uupy;
static double vlowx=0;
static double vlowy=0;
static double vupx=0;
static double vupy=0;
static double pupx=0;
static double pupy=0;
static double plowx=0;
static double plowy=0;
static double delta_t=0.001;
static double delta_x=0.5;
static double delta_y=0.5;
static double r=10*10;
static double μ=1.83/100000;
static double rho=1.206;
static double kappa=(1.83/100000)/1.206;
static char *s="circle";
int shape3(char *s,int i, int j){
if (strcmp(s,"circle")==0){
     
      //if (i==240-5){
        //return -1;
      //}
      if ((i==58) && 11<=j && j<=14){
        return -1;
      }
      if ((i==63) && 11<=j && j<=14){
        return 1;
      }
      if ((i==63) && 44-14<=j && j<=44-11){
        return 1;
      }
      if ((i==58) && 44-14<=j && j<=44-11){
        return -1;
      }
      if ((i==240-58) && 11<=j && j<=14){
        return 1;
      }
      if ((i==240-63) && 11<=j && j<=14){
        return -1;
      }
      if ((i==240-63) && 44-14<=j && j<=44-11){
        return -1;
      }
      if ((i==240-58) && 44-14<=j && j<=44-11){
        return 1;
      }
    }
}
int shape2(char *s,int i, int j){
  if (strcmp(s,"circle")==0){
      
      //if (i==240-5){
        //return -1;
      //}
      //if ((i==58) && 2<=j && j<=7){
        //return -1;
      //}
      if (i==63 && 11<=j && j<=14){
        return 1;
      }
      if (i==63 && 44-14<=j && j<=44-11){
        return 1;
      }
      //if ((i==58) && 22-7<=j && j<=22-2){
        //return -1;
      //}
      //if ((i==240-58) && 2<=j && j<=7){
        //return 1;
      //}
      if (i==240-63 && 11<=j && j<=14){
        return -1;
      }
      if (i==240-63 && 44-14<=j && j<=44-11){
        return -1;
      }
      //if ((i==240-58) && 22-7<=j && j<=22-2){
        //return 1;
      //}
    }
    return 0;
}
int shape(char *s,int i, int j){
    if (strcmp(s,"triangle")==0){
      if ((ymax/2)-(ymax/5)<=j && j<=(ymax/2)+(ymax/5)/2){
        if ((j-((ymax/2)-(ymax/5)))*17/30+ymax/2>=i && i>=ymax/2-(j-((ymax/2)-(ymax/5)))*17/30){
          return 1;
        }
      }
    }
    if (strcmp(s,"square")==0){
      if ((ymax/2)-(ymax/5)<=i && i<=(ymax/2)+(ymax/5) && (ymax/2)-(ymax/5)<=j && j<=(ymax/2)+(ymax/5)){
        return 1;
      }
    }
    if (strcmp(s,"circle")==0){

      
      //if (240-5<=i && i<=240-0 ){
        //return 1;
      //}
      if (59<=i && i<=62 && 10<=j && j<=15){
        return 1;
      }
      if (59<=i && i<=62 && 44-15<=j && j<=44-10){
        return 1;
      }
      if (240-62<=i && i<=240-59 && 10<=j && j<=15){
        return 1;
      }
      if (240-62<=i && i<=240-59 && 44-15<=j && j<=44-10){
        return 1;
      }
      if ((58==i || i==63) && 11<=j && j<=14){
        return 1;
      }
      if ((58==i || i==63) && 44-14<=j && j<=44-11){
        return 1;
      }
      if ((240-63==i || i==240-58) && 11<=j && j<=14){
        return 1;
      }
      if ((240-63==i || i==240-58) && 44-14<=j && j<=44-11){
        return 1;
      }
    }
    if (strcmp(s,"pentagon")==0){
      if ((ymax/2)-20<=j && j<=(ymax/2)-6){
        int r=(j-30)*1.4;
        if ((ymax/2)-r<=i && i<=(ymax/2)+r){
          return 1;
        }
      }
      if ((ymax/2)-6<=j && j<=(ymax/2)+16){
        int r=(j-44)/3;
        if ((ymax/2)-19+r<=i && i<=(ymax/2)+19-r){
          return 1;
        }
      }
    }
    if (strcmp(s,"hexagon")==0){
      if ((ymax/2)-17<=j && j<=(ymax/2)){
        int r=(j-33)*10/17;
        if ((ymax/2)-10-r<=i && i<=(ymax/2)+10+r){
          return 1;
        }
      }
      if ((ymax/2)<=j && j<=(ymax/2)+17){
        int r=(j-50)*10/17;
        if ((ymax/2)-20+r<=i && i<=(ymax/2)+20-r){
          return 1;
        }
      }
    }
    if (strcmp(s,"pillar")==0){
      if ((ymax/2)-30<=j && j<=(ymax/2)+30){
        if ((ymax/2)-5<=i && i<=(ymax/2)+5){
          return 1;
        }
      }
    }
    if (strcmp(s,"people")==0){
      if ((i-50)*(i-50)+(j-50)*(j-50)<=400){
        return 1;
        }
    }
    if (strcmp(s,"car")==0){
      if ((i-50)*(i-50)+(j-50)*(j-50)<=400){
        return 1;
        }
    }
    if (strcmp(s,"house")==0){
      if ((i-50)*(i-50)+(j-50)*(j-50)<=400){
        return 1;
        }
    }
    if (strcmp(s,"bicycle")==0){
      if ((i-50)*(i-50)+(j-50)*(j-50)<=400){
        return 1;
        }
    }
    return 0;
}
int wall(char *s,int i,int j){
  //if ((i-10)*(i-10)+(j-10)*(j-10)<=100 || (i-10)*(i-10)+(j-40)*(j-40)<=100 || (i-40)*(i-40)+(j-10)*(j-10)<=100 || (i-40)*(i-40)+(j-40)*(j-40)<=100){
    //return 1;
  //}
  if (shape(s,i,j)==1){
    return 1;
  }
  //if ((i-80)*(i-80)+(j-80)*(j-80)<=100 || (i-80)*(i-80)+(j-120)*(j-120)<=100 || (i-115)*(i-115)+(j-100)*(j-100)<=100
  //|| (30<i && i<50 && 30<j && j<50)){
    //return 1;
  //}
  else{
    return 0;
  }
}
int wall2(char *s,int i,int j){
  //if ((i-10)*(i-10)+(j-10)*(j-10)<=100 || (i-10)*(i-10)+(j-40)*(j-40)<=100 || (i-40)*(i-40)+(j-10)*(j-10)<=100 || (i-40)*(i-40)+(j-40)*(j-40)<=100){
    //return 1;
  //}
  if (shape2(s,i,j)==1){
    return 1;
  }
  if (shape2(s,i,j)==-1){
    return -1;
  }
  //if ((i-80)*(i-80)+(j-80)*(j-80)<=100 || (i-80)*(i-80)+(j-120)*(j-120)<=100 || (i-115)*(i-115)+(j-100)*(j-100)<=100
  //|| (30<i && i<50 && 30<j && j<50)){
    //return 1;
  //}
  else{
    return 0;
  }
}
void calc(double u[xmax][ymax],double v[xmax][ymax],double c[xmax][ymax]){
  for (int i=0;i<xmax;i++){
    for (int j=0;j<ymax;j++){
      //if (wall2(s,i,j)==1){
        //u[i][j]=out;
      //}
      //else if (wall2(s,i,j)==-1){
        //u[i][j]=-1*out;
      //}
      if (v[i][j]<=0){
          ulowy=u[i][j];
          vlowy=v[i][j];
          uupy=u[i][j];
          vupy=v[i][j];
        }
        else{
          uupy=u[i][j];
          vupy=v[i][j];
          ulowy=u[i][j];
          vlowy=v[i][j];
        }
        if(u[i][j]<=0){
          //ulowx=u[i][j];
          //vlowx=v[i][j];
          uupx=u[i][j];
          vupx=v[i][j];
        }
        else{
          //ulowx=0;
          //vlowx=0;
          uupx=u[i][j];
          vupx=v[i][j];
        }
      
    if (i==0 &j==0){
      c[i][j]=(((u[i+1][j]-ulowx)/(2*delta_x)+(v[i][j+1]-vlowy)/(2*delta_y))/delta_t
      -((u[i+1][j]-ulowx)/(2*delta_x))*((u[i+1][j]-ulowx)/(2*delta_x))
      -2*((u[i][j+1]-ulowy)/(2*delta_y))*((v[i+1][j]-vlowx)/(2*delta_x))
      -((v[i][j+1]-vlowy)/(2*delta_y))*((v[i][j+1]-vlowy)/(2*delta_y)))*rho;
    }
    else if (i==0 & j==ymax-1){
      c[i][j]=(((u[i+1][j]-ulowx)/(2*delta_x)+(vupy-v[i][j-1])/(2*delta_y))/delta_t
      -((u[i+1][j]-ulowx)/(2*delta_x))*((u[i+1][j]-ulowx)/(2*delta_x))
      -2*((uupy-u[i][j-1])/(2*delta_y))*((v[i+1][j]-vlowx)/(2*delta_x))
      -((vupy-v[i][j-1])/(2*delta_y))*((vupy-v[i][j-1])/(2*delta_y)))*rho;
    }
    else if (j==0 & i==xmax-1){
      c[i][j]=(((uupx-u[i-1][j])/(2*delta_x)+(v[i][j+1]-vlowy)/(2*delta_y))/delta_t
      -((uupx-u[i-1][j])/(2*delta_x))*((uupx-u[i-1][j])/(2*delta_x))
      -2*((u[i][j+1]-ulowy)/(2*delta_y))*((vupx-v[i-1][j])/(2*delta_x))
      -((v[i][j+1]-vlowy)/(2*delta_y))*((v[i][j+1]-vlowy)/(2*delta_y)))*rho;
    }
    else if (i==0){
      c[i][j]=(((u[i+1][j]-ulowx)/(2*delta_x)+(v[i][j+1]-v[i][j-1])/(2*delta_y))/delta_t
      -((u[i+1][j]-ulowx)/(2*delta_x))*((u[i+1][j]-ulowx)/(2*delta_x))
      -2*((u[i][j+1]-u[i][j-1])/(2*delta_y))*((v[i+1][j]-vlowx)/(2*delta_x))
      -((v[i][j+1]-v[i][j-1])/(2*delta_y))*((v[i][j+1]-v[i][j-1])/(2*delta_y)))*rho;
    }
    else if (j==0){
      c[i][j]=(((u[i+1][j]-u[i-1][j])/(2*delta_x)+(v[i][j+1]-vlowy)/(2*delta_y))/delta_t
      -((u[i+1][j]-u[i-1][j])/(2*delta_x))*((u[i+1][j]-u[i-1][j])/(2*delta_x))
      -2*((u[i][j+1]-ulowy)/(2*delta_y))*((v[i+1][j]-v[i-1][j])/(2*delta_x))
      -((v[i][j+1]-vlowy)/(2*delta_y))*((v[i][j+1]-vlowy)/(2*delta_y)))/rho;
    }
    else if (i==xmax-1 & j==ymax-1){
      c[i][j]=(((uupx-u[i-1][j])/(2*delta_x)+(vupy-v[i][j-1])/(2*delta_y))/delta_t
      -((uupx-u[i-1][j])/(2*delta_x))*((uupx-u[i-1][j])/(2*delta_x))
      -2*((uupy-u[i][j-1])/(2*delta_y))*((vupx-v[i-1][j])/(2*delta_x))
      -((vupy-v[i][j-1])/(2*delta_y))*((vupy-v[i][j-1])/(2*delta_y)))*rho;
    }
    else if (i==xmax-1){
      c[i][j]=(((uupx-u[i-1][j])/(2*delta_x)+(v[i][j+1]-v[i][j-1])/(2*delta_y))/delta_t
      -((uupx-u[i-1][j])/(2*delta_x))*((uupx-u[i-1][j])/(2*delta_x))
      -2*((u[i][j+1]-u[i][j-1])/(2*delta_y))*((vupx-v[i-1][j])/(2*delta_x))
      -((v[i][j+1]-v[i][j-1])/(2*delta_y))*((v[i][j+1]-v[i][j-1])/(2*delta_y)))*rho;
    }
    else if (j==ymax-1){
      c[i][j]=(((u[i+1][j]-u[i-1][j])/(2*delta_x)+(vupy-v[i][j-1])/(2*delta_y))/delta_t
      -((u[i+1][j]-u[i-1][j])/(2*delta_x))*((u[i+1][j]-u[i-1][j])/(2*delta_x))
      -2*((uupy-u[i][j-1])/(2*delta_y))*((v[i+1][j]-v[i-1][j])/(2*delta_x))
      -((vupy-v[i][j-1])/(2*delta_y))*((vupy-v[i][j-1])/(2*delta_y)))*rho;
    }
    else{
      c[i][j]=(((u[i+1][j]-u[i-1][j])/(2*delta_x)+(v[i][j+1]-v[i][j-1])/(2*delta_y))/delta_t
      -((u[i+1][j]-u[i-1][j])/(2*delta_x))*((u[i+1][j]-u[i-1][j])/(2*delta_x))
      -2*((u[i][j+1]-u[i][j-1])/(2*delta_y))*((v[i+1][j]-v[i-1][j])/(2*delta_x))
      -((v[i][j+1]-v[i][j-1])/(2*delta_y))*((v[i][j+1]-v[i][j-1])/(2*delta_y)))*rho;
    }
    }
  }
}
void calp(double p[xmax][ymax],double c[xmax][ymax]){
  for (int count=0;count<=500;count++){
    double new[xmax][ymax];
    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
        if (i==0 &j==0){
          new[i][j]=((p[i+1][j]+plowx)*(delta_y*delta_y)+(p[i][j+1]+plowy)*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (i==0 & j==ymax-1){
          new[i][j]=((p[i+1][j]+plowx)*(delta_y*delta_y)+(pupy+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (j==0 & i==xmax-1){
          new[i][j]=((pupx+p[i-1][j])*(delta_y*delta_y)+(p[i][j+1]+plowy)*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (i==0){
          new[i][j]=((p[i+1][j]+plowx)*(delta_y*delta_y)+(p[i][j+1]+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (j==0){
          new[i][j]=((p[i+1][j]+p[i-1][j])*(delta_y*delta_y)+(p[i][j+1]+plowy)*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (i==xmax-1 & j==ymax-1){
          new[i][j]=((pupx+p[i-1][j])*(delta_y*delta_y)+(pupy+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (i==xmax-1){
          new[i][j]=((pupx+p[i-1][j])*(delta_y*delta_y)+(p[i][j+1]+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else if (j==ymax-1){
          new[i][j]=((p[i+1][j]+p[i-1][j])*(delta_y*delta_y)+(pupy+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
        else{
          new[i][j]=((p[i+1][j]+p[i-1][j])*(delta_y*delta_y)+(p[i][j+1]+p[i][j-1])*(delta_x*delta_x)-c[i][j]*delta_x*delta_x*delta_y*delta_y)/(2*(delta_x*delta_x+delta_y*delta_y));
        }
      }
    }
    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
        p[i][j]=new[i][j];
      }
    }
  }
}
void calb(char *s,double u[xmax][ymax],double v[xmax][ymax],double c[xmax][ymax],double p[xmax][ymax],double bu[xmax][ymax],double bv[xmax][ymax]){
  calc(u,v,c);
  calp(p,c);
  //omp_set_num_threads(6);
  //#pragma omp parallel for private(j)
  ///double dts=omp_get_wtime();

  //omp_set_num_threads(6);
  //#pragma omp parallel for private(j)
  
  for (int i=0;i<xmax;i++){
    //#pragma omp parallel for
    for (int j=0;j<ymax;j++){
      //if (wall2(s,i,j)==1){
        //u[i][j]=out;
      //}
      //if (wall2(s,i,j)==-1){
        //u[i][j]=-1*out;
      //}
        if (v[i][j]<=0){
          ulowy=u[i][j];
          vlowy=v[i][j];
          uupy=u[i][j];
          vupy=v[i][j];
        }
        else{
          uupy=u[i][j];
          vupy=v[i][j];
          ulowy=u[i][j];
          vlowy=v[i][j];
        }
        if(u[i][j]<=0){
          //ulowx=u[i][j];
          //vlowx=v[i][j];
          uupx=u[i][j];
          vupx=v[i][j];
        }
        else{
          //ulowx=0;
          //vlowx=0;
          uupx=u[i][j];
          vupx=v[i][j];
        }
      //printf("myid=%d, i=%d,j=%d\n",omp_get_thread_num(), i,j);
      //printf("%d %d\n",i,j);
    if (i==0 &j==0){
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-ulowx)/(2*delta_x)-1*v[i][j]*(u[i][j+1]-ulowy)/(2*delta_y)
      -1*(p[i+1][j]-plowx)/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+ulowx)/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+ulowy)/(delta_y*delta_y);
    }
    else if (i==0 & j==ymax-1){
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-ulowx)/(2*delta_x)-1*v[i][j]*(uupy-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-plowx)/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+ulowx)/(delta_x*delta_x)+kappa*(uupy-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (j==0 & i==xmax-1){
      bu[i][j]=-1*u[i][j]*(uupx-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-ulowy)/(2*delta_y)
      -1*(pupx-p[i-1][j])/(2*delta_x*rho)
      +kappa*(uupx-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+ulowy)/(delta_y*delta_y);
    }
    else if (i==0){
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-ulowx)/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-plowx)/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+ulowx)/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (j==0){
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-ulowy)/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+ulowy)/(delta_y*delta_y);
    }
    else if (i==xmax-1 & j==ymax-1){
      bu[i][j]=-1*u[i][j]*(uupx-u[i-1][j])/(2*delta_x)-1*v[i][j]*(uupy-u[i][j-1])/(2*delta_y)
      -1*(pupx-p[i-1][j])/(2*delta_x*rho)
      +kappa*(uupx-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(uupy-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (i==xmax-1){
      bu[i][j]=-1*u[i][j]*(uupx-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(pupx-p[i-1][j])/(2*delta_x*rho)
      +kappa*(uupx-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (j==ymax-1){
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(uupy-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(uupy-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j)==1){
      bu[i][j]=0;
    }
    else if (wall(s,i+1,j)==1){
      u[i+1][j]=0;
      v[i+1][j]=0;
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i-1,j)==1){
      u[i-1][j]=0;
      v[i-1][j]=0;
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j+1)==1){
      u[i][j+1]=0;
      v[i][j+1]=0;
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j-1)==1){
      u[i][j-1]=0;
      v[i][j-1]=0;
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
    }
    
    else{
      bu[i][j]=-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x)-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y)
      -1*(p[i+1][j]-p[i-1][j])/(2*delta_x*rho)
      +kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x)+kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y);
      //if (i==49 && j==29){
        //printf("%f %f %f %f %f",u[i][j],-1*u[i][j]*(u[i+1][j]-u[i-1][j])/(2*delta_x),-1*v[i][j]*(u[i][j+1]-u[i][j-1])/(2*delta_y),kappa*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(delta_x*delta_x),kappa*(u[i][j+1]-2*u[i][j]+u[i][j-1])/(delta_y*delta_y));
      //}
    }
    //if (bu[i][j]<-1){
      //printf("%d %d %f %f %f %f %F %f",i,j,u[i][j],u[i-1][j],u[i+1][j],u[i][j-1],u[i][j+1],bu[i][j]);
    //}
    }
  }
  for (int i=0;i<xmax;i++){
    //#pragma omp parallel for
    for (int j=0;j<ymax;j++){
      //if (wall2(s,i,j)==1){
        //u[i][j]=out;
      //}
     //if (wall2(s,i,j)==-1){
       // u[i][j]=-1*out;
      //}
          if (v[i][j]<=0){
          ulowy=u[i][j];
          vlowy=v[i][j];
          uupy=u[i][j];
          vupy=v[i][j];
        }
        else{
          uupy=u[i][j];
          vupy=v[i][j];
          ulowy=u[i][j];
          vlowy=v[i][j];
        }
        if(u[i][j]<=0){
          //ulowx=u[i][j];
          //vlowx=v[i][j];
          uupx=u[i][j];
          vupx=v[i][j];
        }
        else{
          //ulowx=0;
          //vlowx=0;
          uupx=u[i][j];
          vupx=v[i][j];
        }
      
      //printf("myid=%d, i=%d,j=%d\n",omp_get_thread_num(), i,j);
      //printf("%d %d\n",i,j);
    if (i==0 &j==0){
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-vlowx)/(2*delta_x)-1*v[i][j]*(v[i][j+1]-vlowy)/(2*delta_y)
      -1*(p[i][j+1]-plowy)/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+vlowx)/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+vlowy)/(delta_y*delta_y);
    }
    else if (i==0 & j==ymax-1){
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-vlowx)/(2*delta_x)-1*v[i][j]*(vupy-v[i][j-1])/(2*delta_y)
      -1*(pupy-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+vlowx)/(delta_x*delta_x)+kappa*(vupy-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (j==0 & i==xmax-1){
      bv[i][j]=-1*u[i][j]*(vupx-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-vlowy)/(2*delta_y)
      -1*(p[i][j+1]-plowy)/(2*delta_x*rho)
      +kappa*(vupx-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+vlowy)/(delta_y*delta_y);
    }
    else if (i==0){
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-vlowx)/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+vlowx)/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (j==0){
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-vlowy)/(2*delta_y)
      -1*(p[i][j+1]-plowy)/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+vlowy)/(delta_y*delta_y);
    }
    else if (i==xmax-1 & j==ymax-1){
      bv[i][j]=-1*u[i][j]*(vupx-v[i-1][j])/(2*delta_x)-1*v[i][j]*(vupy-v[i][j-1])/(2*delta_y)
      -1*(pupy-p[i][j-1])/(2*delta_x*rho)
      +kappa*(vupx-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(vupy-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (i==xmax-1){
      bv[i][j]=-1*u[i][j]*(vupx-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(vupx-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (j==ymax-1){
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(vupy-v[i][j-1])/(2*delta_y)
      -1*(pupy-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(vupy-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j)==1){
      bv[i][j]=0;
    }
    else if (wall(s,i+1,j)==1){
      u[i+1][j]=0;
      v[i+1][j]=0;
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i-1,j)==1){
      u[i-1][j]=0;
      v[i-1][j]=0;
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j+1)==1){
      u[i][j+1]=0;
      v[i][j+1]=0;
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    else if (wall(s,i,j-1)==1){
      u[i][j-1]=0;
      v[i][j-1]=0;
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    
    else{
      bv[i][j]=-1*u[i][j]*(v[i+1][j]-v[i-1][j])/(2*delta_x)-1*v[i][j]*(v[i][j+1]-v[i][j-1])/(2*delta_y)
      -1*(p[i][j+1]-p[i][j-1])/(2*delta_x*rho)
      +kappa*(v[i+1][j]-2*v[i][j]+v[i-1][j])/(delta_x*delta_x)+kappa*(v[i][j+1]-2*v[i][j]+v[i][j-1])/(delta_y*delta_y);
    }
    }
  }
  //double dtend=omp_get_wtime();
  //return dts-dtend;
}
int next(char *s,double u[xmax][ymax],double v[xmax][ymax],double c[xmax][ymax],double p[xmax][ymax],double bu[xmax][ymax],double bv[xmax][ymax]){
  //printf("%f",d);
  //int yy=0;
    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
        u[i][j]=u[i][j]+delta_t*(bu[i][j]);
        v[i][j]=v[i][j]+delta_t*(bv[i][j]);
        //if (isnan(u[i][j])==1 && yy==0){
          //yy=1;
          //printf("%d %d %f",i,j,bu[i][j]);
        //}
      }
    }
    //omp_set_num_threads(6);
  //#pragma omp parallel for private(j)
    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
        if (shape3(s,i,j)==1 || shape3(s,i,j)==-1){
          continue;
        }
        if(wall(s,i,j)==1){
          if (u[i][j]!=0 || v[i][j]!=0){
            int neighbors[4]={0,0,0,0};
            int neighbor=0;
            if (wall(s,i-1,j)==0 && i!=0){
              neighbors[0] =1;
              neighbor+=1;
            }
            if (wall(s,i+1,j)==0 && i!=xmax-1){
              neighbors[1] =1;
              neighbor+=1;
            }
            if (wall(s,i,j-1)==0 && j!=0){
              neighbors[2] =1;
              neighbor+=1;
            }
            if (wall(s,i,j+1)==0 && j!=ymax-1){
              neighbors[3] =1;
              neighbor+=1;
            }
            double ppu=u[i][j];
            double ppv=v[i][j];
            double ppp=p[i][j];
            if (u[i][j]!=0 && neighbor!=0){
                if (i!=0 && neighbors[0]==1){
                u[i-1][j]-=ppu/neighbor;
                u[i][j]-=ppu/neighbor;
                }
                if(i!=xmax-1 && neighbors[1]==1){
                u[i+1][j]+=ppu/neighbor;
                u[i][j]-=ppu/neighbor;
                }
                if (j!=0 && neighbors[2]==1){
                v[i][j-1]-=ppu/neighbor;
                u[i][j]-=ppu/neighbor;
                }
                if(j!=ymax-1 && neighbors[3]==1){
                v[i][j+1]+=ppu/neighbor;
                u[i][j]-=ppu/neighbor;
                }
            }
            if (v[i][j]!=0 && neighbor!=0){
                if (i!=0 && neighbors[0]==1){
                u[i-1][j]-=ppv/neighbor;
                v[i][j]-=ppv/neighbor;
                }
                if(i!=xmax-1 && neighbors[1]==1){
                u[i+1][j]+=ppv/neighbor;
                v[i][j]-=ppv/neighbor;
                }
                if (j!=0 && neighbors[2]==1){
                v[i][j-1]-=ppv/neighbor;
                v[i][j]-=ppv/neighbor;
                }
                if(j!=ymax-1 && neighbors[3]==1){
                v[i][j+1]+=ppv/neighbor;
                v[i][j]-=ppv/neighbor;
                }
            }
            if (p[i][j]!=0 && neighbor!=0){
                if (i!=0 && neighbors[0]==1){
                p[i-1][j]+=ppp/neighbor;
                p[i][j]-=ppp/neighbor;
                }
                if(i!=xmax-1 && neighbors[1]==1){
                p[i+1][j]+=ppp/neighbor;
                p[i][j]-=ppp/neighbor;
                }
                if (j!=0 && neighbors[2]==1){
                p[i][j-1]+=ppp/neighbor;
                p[i][j]-=ppp/neighbor;
                }
                if(j!=ymax-1 && neighbors[3]==1){
                p[i][j+1]+=ppp/neighbor;
                p[i][j]-=ppp/neighbor;
                }
            }
          }
            //temp[i][j]=0;
        }
        //printf("%f",temp[i][j]);
      }
    }



    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
        if(wall(s,i,j)==1){
          u[i][j]=0;
          v[i][j]=0;
          p[i][j]=0;
        }
        if (i==0 || i==xmax-1 || j==0 || j==ymax-1){
          p[i][j]=0;
        }
      }
    }
    for (int i=0;i<xmax;i++){
      for (int j=0;j<ymax;j++){
    //if (wall2(s,i,j)==1  && 5<=i && 39>=i){
        //u[i][j]=out;
      //}
     // if (wall2(s,i,j)==-1  && 5<=i && 39>=i){
      // u[i][j]=-1*out;
      //}
      //if (wall2(s,i,j)==1  && (5>=i || 39<=i)){
        //u[i][j]=0;
      //}
      //if (wall2(s,i,j)==-1  && (5>=i || 39<=i)){
        //u[i][j]=0;
      //}
      }
      }
  //calb(u,v,c,p,bu,bv);
  return 0;
}


 
int main(void) {
  double Re=ulowx*sqrt(r)*2*delta_x/kappa;
  double k=1;
  //char s[][20]={"triangle", "square", "circle", "pentagon", "hexagon", "pillar", "people", "car", "house","bicycle"};
  //char s[][20]={"triangle", "square", "circle", "pentagon", "hexagon", "pillar"};
  char s[][20]={"circle"};
  printf("%s",s[0]);
  //for (int step=0;step < sizeof(s) / sizeof(s[0]); step++){
  for (int step=0;step < 1; step++){
    printf("%s",s[step]);
  int n;
  //n = omp_get_max_threads(); 
  //printf("max threads (set): %d\n", n);
  double st, ed;
  double times[2005];
  int xx[2005];
  double u[xmax][ymax];
  double v[xmax][ymax];
  double p[xmax][ymax];
  //#pragma omp parallel for
  ///omp_set_num_threads(2);
  //#pragma omp parallel for 
  //for (int tt=100;tt<=100;tt++){
    //printf("myid=%d, i=%d\n",omp_get_thread_num(), tt);
    //xx[tt]=tt;
    // 計測開始
    //st = omp_get_wtime();

  
  //double **b;
  //if((b=malloc(sizeof(double*)*max))==NULL){
    //fprintf(stderr,"メモリーが確保できませんでした\n");
  //}
  //for(int i=0;i<n;i++){
    //if((b[i]=malloc(sizeof(double)*max))==NULL){
      //fprintf(stderr,"メモリーが確保できませんでした\n");
      //for(int j=0;j<i;j++){
	//free(b[j]);
      //}
      //free(b);
    //}
  //}
  //double a[max][max];
  double bu[xmax][ymax];
  double bv[xmax][ymax];
  double c[xmax][ymax];
  for (int i=0;i<xmax;i++){
    for (int j=0;j<ymax;j++){
      //if (wall2(s,i,j)==1 && 5<=i && 39>=i){
      //  u[i][j]=out;
      //}
      //if (wall2(s,i,j)==-1  && 5<=i && 39>=i){
       // u[i][j]=-1*out;
      //}
      //if (wall2(s,i,j)==1  && (5>=i || 39<=i)){
        //u[i][j]=0;
      //}
      //if (wall2(s,i,j)==-1  && (5>=i || 39<=i)){
        //u[i][j]=0;
      //}
      u[i][j]=0;
      v[i][j]=0;
      p[i][j]=0;
      //if (0<=i && i<=10 ){
        //u[i][j]=4;
        //v[i][j]=4;
      //}
    }
  }
  //temp[0][0]=200000;
  
  
  //double **temp;
  //if((temp=malloc(sizeof(double*)*max))==NULL){
    //fprintf(stderr,"メモリーが確保できませんでした\n");
  //}
  //for(int i=0;i<n;i++){
    //if((temp[i]=malloc(sizeof(double)*max))==NULL){
      //fprintf(stderr,"メモリーが確保できませんでした\n");
      //for(int j=0;j<i;j++){
	//free(temp[j]);
      //}
      //free(b);
    //}
  //}
  
  //temp[0][0]=200000;
  
  
  //不要
  //double a[max][max]={};
  //for (int i=0;i<max;i++){
    //for (int j=0;j<max;j++){
      //if (i==j){
        //a[i][j]=2*(1/d+1);
      //}
      //else if (i==j-1){
        //a[i][j]=-1;
      //}
      //else if (i==j+1){
      //  a[i][j]=-1;
      //}
      //}
  //}
  //ed=clock();
  //double ttt;
  calb(s[step],u,v,c,p,bu,bv);
  //double st2,end2;
  //st2=clock();
  
  int max_step=(int)(300/delta_t)+1;
  //int i;
  int q;
  char uu[1000];
  FILE   *gp;
  gp = popen("gnuplot --persist", "w");
  fprintf(gp,"set term gif animate delay 10\n");
  fprintf(gp,"set output 'Navier-Stokes/Re=%.3f,shape=%sδt=%.5f,δx=%.3f,δy=%.2f,lowx=%f,utest.gif'\n",Re,s[step],delta_t,delta_x,delta_y,ulowx); 
  fprintf(gp, "set xlabel \"x\"\n");
  fprintf(gp, "set ylabel \"y\"\n");
  fprintf(gp, "set title \"δt=%.2f,δx=%.3f,δy=%.2f,lowx=%f\"\n",delta_t,delta_x,delta_y,ulowx);
  fprintf(gp,"set size ratio 1\n");
  fprintf(gp,"set zrange [0:10]\n");
  FILE   *gp2;
  gp2 = popen("gnuplot --persist", "w");
  fprintf(gp2,"set term gif animate delay 10\n");
  fprintf(gp2,"set output 'Navier-Stokes/Re=%.3f,shape=%sδt=%.5f,δx=%.3f,δy=%.2f,lowx=%f,utest2.gif'\n",Re,s[step],delta_t,delta_x,delta_y,ulowx);
  fprintf(gp2, "pm3d\n");
  fprintf(gp2, "set pm3d map\n");
  fprintf(gp2,"set cbrange[0:%.6f]\n",ulowx);
  double tt=ulowx/8;
  fprintf(gp2,"set xrange[0:%d]\n",xmax);
  fprintf(gp2,"set palette defined ( 0 '#000090',%.6f '#000fff',%.6f '#0090ff',%.6f '#0fffee',%.6f '#90ff70',%.6f '#ffee00',%.6f '#ff7000',%.6f '#ee0000',%.6f '#7f0000')\n",0+tt,0+2*tt,0+3*tt,0+4*tt,0+5*tt,0+6*tt,0+7*tt,0+8*tt);
  //fprintf(gp2, "set title \"δt=%.2f,δx=%.3f,δy=%.2f,lowx=%f\"\n",delta_t,delta_x,delta_y,ulowx);
  fprintf(gp2,"set size ratio -1\n");
  fprintf(gp2,"unset key\n");
  fprintf(gp2, "set xlabel \"x\"\n");
  fprintf(gp2, "set ylabel \"y\"\n");
  
  FILE   *gp3;
  gp3 = popen("gnuplot --persist", "w");
  fprintf(gp3,"set term gif animate delay 10\n");
  fprintf(gp3,"set output 'Navier-Stokes/Re=%.3f,shape=%sδt=%.5f,δx=%.3f,δy=%.2f,lowx=%f,vtest2.gif'\n",Re,s[step],delta_t,delta_x,delta_y,ulowx);
  fprintf(gp3, "pm3d\n");
  fprintf(gp3, "set pm3d map\n");
  fprintf(gp3,"set cbrange[-0.058:0.058]\n");
  double ttt=0.116/8;
  fprintf(gp3,"set xrange[0:%d]\n",xmax);
  fprintf(gp3,"set palette defined ( -0.058 '#000090',%.5f '#000fff',%.5f '#0090ff',%.5f '#0fffee',%.5f '#90ff70',%.5f '#ffee00',%.5f '#ff7000',%.5f '#ee0000',0.00058 '#7f0000')\n",-0.058+ttt,-0.058+2*ttt,-0.058+3*ttt,-0.058+4*ttt,-0.058+5*ttt,-0.058+6*ttt,-0.058+7*ttt);
  //fprintf(gp3, "set title \"δt=%.2f,δx=%.3f,δy=%.2f,lowx=%f\"\n",delta_t,delta_x,delta_y,ulowx);
  fprintf(gp3,"set size ratio -1\n");
  fprintf(gp3,"unset key\n");
  fprintf(gp3, "set xlabel \"x\"\n");
  fprintf(gp3, "set ylabel \"y\"\n");
  
  FILE   *gp4;
  gp4 = popen("gnuplot --persist", "w");
  fprintf(gp4,"set term gif animate delay 10\n");
  fprintf(gp4,"set output 'Navier-Stokes/Re=%.3f,shape=%sδt=%.5f,δx=%.3f,δy=%.2f,lowx=%f,ptest2.gif'\n",Re,s[step],delta_t,delta_x,delta_y,ulowx);
  fprintf(gp4, "pm3d\n");
  fprintf(gp4, "set pm3d map\n");
  fprintf(gp4,"set cbrange[-0.0024:0.0059]\n");
  ttt=0.0083/8;
  fprintf(gp4,"set xrange[0:%d]\n",xmax);
  fprintf(gp4,"set palette defined ( -0.0024 '#000090',%.10f '#000fff',%.10f '#0090ff',%.10f '#0fffee',%.10f '#90ff70',%.10f '#ffee00',%.10f '#ff7000',%.10f '#ee0000',0.000006 '#7f0000')\n",-0.0024+ttt,-0.0024+2*ttt,-0.0024+3*ttt,-0.0024+4*ttt,-0.0024+5*ttt,-0.0024+6*ttt,-0.0024+7*ttt);
  //fprintf(gp4, "set title \"δt=%.2f,δx=%.3f,δy=%.2f,lowx=%f\"\n",delta_t,delta_x,delta_y,ulowx);
  fprintf(gp4,"set size ratio -1\n");
  fprintf(gp4,"unset key\n");
  fprintf(gp4, "set xlabel \"x\"\n");
  fprintf(gp4, "set ylabel \"y\"\n");
  //fprintf(gp2,"set size ratio 1\n");
  //fprintf(gp2,"set palette defined(0 '#1126B9', 100'#116CB9',200 '#8DF589',300 '#F9F51B',400 '#F98B1B', 500 '#9D1315')\n");
  //printf("%f",b[5][5]);
  //end2=clock();
  //double timetime=ed-st + end2-st2 +ttt*CLOCKS_PER_SEC;
  for (int g=0;g<max_step;g++){
    calb(s[step],u,v,c,p,bu,bv);
    
    //double st3=0,ed3=0,tttt=0;
    //st3=clock();
    //printf("%d",g);
    q=next(s[step],u,v,c,p,bu,bv);
    //if (g==0){
    //for (int i=0;i<xmax;i++){
    //for (int j=0;j<ymax;j++){
      //printf("%f %f",u[i][j],v[i][j]);
    //}
  //}
    //}
    //int ra=rand()%50;
   // int ra2=rand()%max;
    //int ra3=rand()%max;
    //int ra4=rand()%max;
    //if (ra==5){
      //if(wall(s[step],ra2,ra3)==0){
        //temp[ra2][ra3]=ra4*1000;
      //}
    //}
    //vx+=(ra5-50)/3000;
    //vy+=(ra6-50)/3000;
    //ed3=clock();
    
    //printf("%f",vx);
    //temp[0][0]=200000;
    ///double wq=0;
    //for (int zz=0;zz<max;zz++){
      ///for (int zzz=0;zzz<max;zzz++){
        //wq+=temp[zz][zzz];
      //}
    //}
    //printf("%f\n",wq);
   if (g%(int)(1/delta_t)==0){
    FILE *fo;
    char ss[100];
    sprintf(ss,"Navier-Stokes/Re=%.3f,shape=%su(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,g/(int)(1/delta_t));
    //printf ("%s",ss);
    if ((fo=fopen(ss,"w"))==NULL){
        printf("%s","Can't open file\n");
        exit(1);
    }
    for (int i = 0; i < xmax; ++i) {
      fprintf(fo,"\n");
      for (int j=0;j<ymax;j++){
          fprintf(fo,"%d %d %f\n",i, j,u[i][j]);
      }
      }
      fclose(fo);
      FILE *fo2;
    char ss2[100];
    sprintf(ss2,"Navier-Stokes/Re=%.3f,shape=%sv(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,g/(int)(1/delta_t));
    //printf ("%s",ss);
    if ((fo2=fopen(ss2,"w"))==NULL){
        printf("%s","Can't open file\n");
        exit(1);
    }
    for (int i = 0; i < xmax; ++i) {
      fprintf(fo2,"\n");
      for (int j=0;j<ymax;j++){
        fprintf(fo2,"%d %d %f\n",i, j,v[i][j]);
      }
      }
      fclose(fo2);

      FILE *fo3;
    char ss3[100];
    sprintf(ss3,"Navier-Stokes/Re=%.3f,shape=%sp(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,g/(int)(1/delta_t));
    //printf ("%s",ss);
    if ((fo3=fopen(ss3,"w"))==NULL){
        printf("%s","Can't open file\n");
        exit(1);
    }
    for (int i = 0; i < xmax; ++i) {
      fprintf(fo3,"\n");
      for (int j=0;j<ymax;j++){
        fprintf(fo3,"%d %d %.10f\n",i, j,p[i][j]);
      }
      }
      fclose(fo3);
    //printf ("%s",ss);
    //sprintf(uu[g/10],"splot '%s' with linespoints\n",ss);
    //printf("%s",uu[g/10]);

   }
   //printf("%s","yyyy");
   //timetime+=ed3-st3+tttt*CLOCKS_PER_SEC;
   //printf("%f\n",timetime/ CLOCKS_PER_SEC);
   if (g==max_step-1){
    char t1[100];
    char t2[100];
    char t3[100];
    sprintf(t1,"Navier-Stokes/Re=%.3f,shape=%s,lowx=%f,ResultU(t=%d).txt",Re,s[step],ulowx,g/(int)(1/delta_t));
    sprintf(t2,"Navier-Stokes/Re=%.3f,shape=%s,lowx=%f,ResultV(t=%d).txt",Re,s[step],ulowx,g/(int)(1/delta_t));
    sprintf(t3,"Navier-Stokes/Re=%.3f,shape=%s,lowx=%f,Resultp(t=%d).txt",Re,s[step],ulowx,g/(int)(1/delta_t));
    FILE *ResultU;
    ResultU=fopen(t1,"w");
    if (ResultU==NULL){
      printf("cannot open\n");
      exit(1);
    }
    FILE *ResultV;
    ResultV=fopen(t2,"w");
    if (ResultV==NULL){
      printf("cannot open\n");
      exit(1);
    }
    FILE *Resultp;
    Resultp=fopen(t3,"w");
    if (Resultp==NULL){
      printf("cannot open\n");
      exit(1);
    }
    for (int i=0;i<xmax;i++){
      for(int j=0;j<ymax;j++){
        fprintf(ResultU,"%f ",u[i][j]);
      }
      fprintf(ResultU,"\n");
    }
    for (int i=0;i<xmax;i++){
      for(int j=0;j<ymax;j++){
        fprintf(ResultV,"%f ",v[i][j]);
      }
      fprintf(ResultV,"\n");
    }
    for (int i=0;i<xmax;i++){
      for(int j=0;j<ymax;j++){
        fprintf(Resultp,"%.10f ",p[i][j]);
      }
      fprintf(Resultp,"\n");
    }
    fclose(ResultU);
    fclose(ResultV);
    fclose(Resultp);
   }
  }
  char vv[100];
  char vv2[100];
  char vv3[100];
  char vv4[100];
  char kkk[100];
  char heat[500];
  char heat2[500];
  char heat3[500];
  for (int sss=0;sss<max_step;sss++){
    if (sss%(int)(1/delta_t)==0){
    sprintf(vv,"Navier-Stokes/Re=%.3f,shape=%su(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    sprintf(kkk,"splot '%s' with linespoints\n",vv);
    fprintf(gp,"%s\n",kkk);
    sprintf(vv2,"Navier-Stokes/Re=%.3f,shape=%su(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    sprintf(heat,"splot '%s' with pm3d\n", vv2);
    fprintf(gp2,"%s\n",heat);
    sprintf(vv3,"Navier-Stokes/Re=%.3f,shape=%sv(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    sprintf(heat2,"splot '%s' with pm3d\n", vv3);
    fprintf(gp3,"%s\n",heat2);
    sprintf(vv4,"Navier-Stokes/Re=%.3f,shape=%sp(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    sprintf(heat3,"splot '%s' with pm3d\n", vv4);
    fprintf(gp4,"%s\n",heat3);
  }
  }
  fprintf(gp,"set output\n");
  fflush(gp); //バッファにため込まれているデータを解放する(必須)
  fprintf(gp, "exit\n");
  pclose(gp); 
  fprintf(gp2,"set output\n");
  fflush(gp2); //バッファにため込まれているデータを解放する(必須)
  fprintf(gp2, "exit\n");
  pclose(gp2);
  fprintf(gp3,"set output\n");
  fflush(gp3); //バッファにため込まれているデータを解放する(必須)
  fprintf(gp3, "exit\n");
  pclose(gp3); 
  fprintf(gp4,"set output\n");
  fflush(gp4); //バッファにため込まれているデータを解放する(必須)
  fprintf(gp4, "exit\n");
  pclose(gp4); 
  for (int sss=0;sss<max_step;sss++){
    if (sss%(int)(1/delta_t)==0){
    sprintf(vv,"Navier-Stokes/Re=%.3f,shape=%su(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    //remove(vv);
    sprintf(vv2,"Navier-Stokes/Re=%.3f,shape=%su(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    //remove(vv2);
    sprintf(vv3,"Navier-Stokes/Re=%.3f,shape=%sv(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    //remove(vv3);
    sprintf(vv4,"Navier-Stokes/Re=%.3f,shape=%sp(delta_t=%.5f,t=%d).dat",Re,s[step],delta_t,sss/(int)(1/delta_t));
    //remove(vv4);
    }
  }


  // 計測終了
    // 計測時間を出力
    //ed=omp_get_wtime();
    //times[tt]=(double)(ed-st);
    
    //printf("%d %f\n",tt,times[tt]);
  //}
  ///for(int j=0;j<n;j++){
    //free(b[j]);
  //}
  //free(b);
  //for(int j=0;j<n;j++){
    //free(temp[j]);
  //}
  //free(temp);
  //}
  //FILE *gp3;
  //gp3 = popen("gnuplot -persist","w");
  //fprintf(gp3,"reset\n");
  //fprintf(gp3,"set terminal png\n");
  //fprintf(gp3,"set output 'CNNtime 2D/CNN並列化timelong.png'\n");
  //fprintf(gp3, "plot '-' with lines\n");
  //for(int i=100; i<=100; i++){
    //fprintf(gp3,"%d\t%f\n", xx[i], times[i]);    // データの書き込み
    //printf("%d\t%f\n", xx[i], times[i]);  
    //}  
  //fprintf(gp3,"e\n");
  //pclose(gp3);
  FILE *SDF;
  char ty[100];
  sprintf(ty,"Navier-Stokes/Re=%.3f,shape=%s,lowx=%f,SDF.txt",Re,s[step],ulowx);
  SDF=fopen(ty,"w");
  if (SDF==NULL){
    printf("cannot open\n");
    exit(1);
  }
  
  double sdf[xmax][ymax];
  for(int i=0;i<xmax;i++){
    for(int j=0;j<ymax;j++){
      if (j==0){
        sdf[i][j]=3;
      }
      else if (i==0 || i==xmax-1 || j==ymax-1){
        sdf[i][j]=4;
      }
      else{
        if(wall(s[step],i,j)==0){
          sdf[i][j]=1;
        }
        else{
          sdf[i][j]=5;
        }
      }
    }
  }
  for (int i=0;i<xmax;i++){
    for(int j=0;j<ymax;j++){
      if (i!=0 && i!=xmax-1 && j!=0 && j!=ymax-1){
        if (sdf[i][j]==5){
          if (sdf[i-1][j]!=1 && sdf[i][j-1]!=1 && sdf[i+1][j]!=1 && sdf[i][j+1]!=1){
            sdf[i][j]=0;
          }
        }
      }
    }
  }

  for (int i=0;i<xmax;i++){
    for(int j=0;j<ymax;j++){
      fprintf(SDF,"%f ",sdf[i][j]);
    }
    fprintf(SDF,"\n");
  }
  
  
  fclose(SDF);
  }
  return 0;
}
      
    
  
