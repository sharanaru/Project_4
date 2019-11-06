#ifdef DEBUG
#define logwrite(x) printf("%s ",__func__);printf("x");
#define logstate(x)  if(x==1)printf("State is Temp_Read\n");if(x==2)printf("State is Average/Wait\n");if(x==3)printf("Alert\n");if(x==0)printf("State is Disconnect\n");
#endif
#ifdef NORMAL
#define logwrite(x)
#define logstate(x)
#endif
#define logtemp(x)   printf("Function:%s ",__func__);printf("Temperature at %d\n",x);
#define logavgtemp(x)  printf("Function:%s ",__func__);printf("Average Temperature at %d\n",x);
