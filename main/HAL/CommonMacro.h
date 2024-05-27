#ifndef __COMMON_MACRO_H
#define __COMMON_MACRO_H



/**
  * @brief  �������������������ı�ʱ����һ���¼�
  * @param  now:����صı���(����)
  * @param  func:�¼������ص�����(�����Ǹ�ֵ���������)
  * @retval ��
  */
#define CM_VALUE_MONITOR(now,func)  \
do{                                 \
    static int last=(now);          \
    if(last!=(now))func,last=(now); \
}while(0)

/**
  * @brief  ��һ����������ƵĲ����ӽ�ָ��ֵ
  * @param  src:���ر���
  * @param  dest:���ӽ���ֵ
  * @param  step:����
  * @retval ��
  */
#define CM_VALUE_CLOSE_TO(src,dest,step) \
do{                                      \
    if((src)<(dest))(src)+=(step);       \
    else if((src)>(dest))(src)-=(step);  \
}while(0)

/**
  * @brief  ��һ���������ӻ��߼�ȥһ��ֵ���ڴ��ڵ������ֵ���0��ʼ������0������ֵ��ʼ
  * @param  src:���ر���
  * @param  step:���ӻ��߼��ٵ�ֵ
  * @param  max:���ֵ
  * @retval ��
  */
#define CM_VALUE_STEP(src,step,max) ((src)=(((step)>=0)?(((src)+(step))%(max)):(((src)+(max)+(step))%(max))))

/**
  * @brief  ��һ���������ӻ��߼�ȥһ��ֵ���ڴ������ֵ�����Сֵ��ʼ��С����Сֵ������ֵ��ʼ
  * @param  src:���ر���
  * @param  plus:���ӵ�ֵ
  * @param  min:��Сֵ
  * @param  max:���ֵ
  * @retval ��
  */
#define CM_VALUE_PLUS(src,plus,min,max)           \
do{                                               \
    int __value_temp = (src);                     \
    __value_temp += (plus);                       \
    if(__value_temp<(min))__value_temp=(max);     \
    else if(__value_temp>(max))__value_temp=(min);\
    (src) = __value_temp;                         \
}while(0)

/**
  * @brief  ���ط�Χ�ڵ�ֵ
  * @param  x:ԭʼֵ(��������)
  * @param  min:��Сֵ(��������)
  * @param  max:���ֵ(��������)
  * @retval ��Χ�ڵ�ֵ
  */
#define CM_CONSTRAIN(x,low,high) ((x)<(low)?(low):((x)>(high)?(high):(x)))

/**
  * @brief  ��һ��ֵ������һ����Χ��
  * @param  x:�����Ƶ�ֵ(��������)
  * @param  min:��Сֵ(��������)
  * @param  max:���ֵ(��������)
  * @retval ��
  */
#define CM_VALUE_LIMIT(x,min,max) ((x)=CM_CONSTRAIN((x),(min),(max)))

/**
  * @brief  ��һ��ֵ�ı仯��������ӳ�䵽��һ������
  * @param  x:��ӳ���ֵ(��������)
  * @param  in_min:��ӳ���ֵ����Сֵ
  * @param  in_max:��ӳ���ֵ�����ֵ
  * @param  out_min:��ӳ���ֵ����Сֵ
  * @param  out_max:��ӳ���ֵ�����ֵ
  * @retval ӳ��ֵ���
  */
#define CM_VALUE_MAP(x,in_min,in_max,out_min,out_max) \
    (((x)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))

/**
  * @brief  ������ʽ���ָ��ʱ��ִ��һ������
  * @param  func:��ִ�к���(�����Ǹ�ֵ���������)
  * @param  time:�趨���ʱ��(ms)
  * @retval ��
  */
#define CM_EXECUTE_INTERVAL(func,time)                  \
do{                                                     \
    static unsigned long lasttime=0;                    \
    if(millis()-lasttime>=(time))func,lasttime=millis();\
}while(0)

/**
  * @brief  ��һ�������ظ�����ָ������
  * @param  func:�����ú���(�����Ǹ�ֵ���������)
  * @param  n:�ظ����ô���
  * @retval ��
  */
#define CM_EXECUTE_LOOP(func,n) for(unsigned long i=0;i<(n);i++)func

/**
  * @brief  ִ��һ�������ڲ���ʱ�������ֱ�������ķ���ֵΪָ��ֵ
  * @param  func:�����ú���
  * @param  n:ϣ�������ķ���ֵ
  * @param  timeout:��ʱʱ��
  * @param  flag:�ⲿ�ṩ���������ڼ���Ƿ�ʱ
  * @retval ��
  */
#define CM_EXECUTE_FUNC_WITH_TIMEOUT(func,n,timeout,flag) \
do{                                                       \
    volatile unsigned long start=millis();                \
    (flag)=false;                                         \
    while(millis()-start<(timeout)){                      \
        if(func==(n)){(flag)=true;break;}                 \
    }                                                     \
}while(0)

/**
  * @brief  ����ִֻ��һ�Σ������ڳ�ʼ��
  * @param  func:�����ú���(Ҳ�����Ǹ�ֵ���������)
  * @retval ��
  */
#define CM_EXECUTE_ONCE(func)\
do{\
    static bool isInit = false;\
    if(!isInit){func,isInit=true;}\
}while(0)

/**
  * @brief  ��ȡһ�������Ԫ�ظ���
  * @param  arr:������(��������)
  * @retval ��������Ԫ�ظ���
  */
#define CM_ARRAR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/**
  * @brief  ��һ��ֵǿ�ư�ָ�����ͽ��ͣ������ڽṹ�忽��
  * @param  type:������(��������)
  * @param  data:�����͵�����(��������)
  * @retval �������
  */
#define CM_TYPE_EXPLAIN(type,data) (*((type*)(&(data))))

/**
  * @brief  ��ȡ�ź�������semΪtrueʱִ��һ��func
  * @param  sem:�ź���(bool����)
  * @param  func:�����ú���(Ҳ�����Ǹ�ֵ���������)
  * @retval ��
  */
#define CM_SEMAPHORE_TAKE(sem,func)\
do{\
    if((sem)){func,(sem)=false;}\
}while(0)

#endif
