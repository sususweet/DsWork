//
// Created by tangyq on 2017/3/11.
//

#ifndef PROJECT1_ERRORHANDLER_H
#define PROJECT1_ERRORHANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#define LOGI(fmt, arg...)   do{printf("[%s:%d[INFO]]: ",__FILE__,__LINE__);printf(fmt,##arg);}while(0)

#define LOGE(fmt, arg...)   do{printf("[%s:%d[ERRO]]:",__FILE__,__LINE__);printf(fmt,arg);printf("\n");}while(0)

#define LOGD(fmt, arg...)   do{printf("[%s:%d[DBUG]]: ",__FILE__,__LINE__);printf(fmt,##arg);}while(0)


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_ERRORHANDLER_H
