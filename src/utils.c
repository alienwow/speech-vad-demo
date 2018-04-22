#include "utils.h"

const char * getCharPointer(JNIEnv *env,jcharArray chars)  {
    jchar *buf = (*env)->GetCharArrayElements(env,chars,JNI_FALSE);  
    if(!buf)  
    {  
        return NULL;  
    }  
    return (const char *) buf;  
} 
