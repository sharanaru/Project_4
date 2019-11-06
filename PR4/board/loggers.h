//logger macros- Sharan Arumugam and Abhijeet
#ifdef ddebug
#define logwrite(x) printf("%s ",__func__);printf("x");
#define logstate(x)   printf("MODE is DEBUG ");if(x==1)printf("State is Temp_Read\n");if(x==2)printf("State is Average/Wait\n");if(x==3)printf("Alert\n");if(x==0)printf("State is Disconnect\n");
#define logmachine()  printf("State Machine:%s \n",__func__);
#endif
#ifdef NORMAL
#define logwrite(x)
#define logstate(x)   printf("MODE is NORMAL ") //no state declaration needed so using for mode declaration
#define logmachine()
#endif
#define logtemp(x)   printf("Function:%s ",__func__);printf("Temperature is %d\n",x);
#define logavgtemp(x)  printf("Function:%s ",__func__);printf("Average Temperature is %d\n",x);
#ifdef TEST
#define logwrite(x) printf("%s ",__func__);printf("x");
#define logstate(x)   printf("MODE IS TEST \n")
#define logmachine()
#endif
